function signal_out = add_noise(signal, amplitude)
    signal_out = signal + randn(size(signal))*amplitude;
end
