function print_to_file(file, text)
    disp(text);
    fprintf(file, '%s\n', text);
end
