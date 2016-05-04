function processSignal(t, signal, fs, name, file)
    signal_int = convertToQ15(signal);

    figure;
    plot(t, signal_int);

    print_to_file(file, sprintf('static const int32c din%s[] = {', name));
    print_data(file, signal_int);

    N = fs;
    freq = [0:fs-1];
    z = fft(signal, fs)./fs;
    freq2 = freq(1:floor(N/2));
    z2 = z(1:floor(N/2));

    figure;
    plot(freq2, abs(z2));
    %plot(real(z2), imag(z2));

    print_to_file(file, sprintf('static const int32c fft%s[] = {', name));
    print_data(file, convertToQ15(z));

    print_to_file(file, ...
	sprintf('static const int log2N%s = %d;\n', name, log(fs)/log(2)));
end
