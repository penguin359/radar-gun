#!/usr/bin/ruby

watch('(src|test/tests)/.*\.(c|h)') { |m| code_changed(m[0]) }

def code_changed(file)
    run "rake unit"
end

def run(cmd)
    result = `cd test && #{cmd} 2>&1 && date`
    cmd = 'growlnotify'
    #options = "-w -n Watchr --image '#{File.expand_path(image)}' --html '#{title}'  -m '#{info}'"
    options = ""
    notify(result, cmd, options) rescue nil
end

def notify(message, cmd, options)
    puts(message)
    message = message.split("\n")#.last(3)
    notify = `which #{cmd}`.chomp

    title = message.find { |e| /mOK/ =~ e } ? "PASSED" : "FAILED"
    if title == "FAILED"
        image = "~/.watchr_images/failed.png"
        info = (message.find_all { |e| / Tests / =~ e }).join("\n")
    else
        image = "~/.watchr_images/passed.png"
        info = (message.find_all { |e| / Tests / =~ e }).join("\n")
    end

    options = "-w -n Watchr --image '#{File.expand_path(image)}' '#{title}' -m '#{info}'"
    system %(#{notify} #{options} &)
end

def main()
	while true
		code_changed('')
		sleep 5
	end
end

#main()
