function print_data(file, signal_int)
    formatstr = '\t%11d, %11d';
    data = '';
    k = 0;
    for i = signal_int
        if k < 1
            data = [data, sprintf([formatstr ', ' ], real(i), imag(i))];
            k = k + 1;
        else
            data = [data, sprintf([formatstr ',\n'], real(i), imag(i))];
            k = 0;
        end
    end
    data = [data, sprintf('};\n')];
    print_to_file(file, data);
end
