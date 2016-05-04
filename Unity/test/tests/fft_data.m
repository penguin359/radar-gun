function fft_data
    clc; clear all; close all;

    %fs_hires = 2048;
    fs_hires = 1024;

    % Q31 format
    m = 0;
    n = 31;

    % XXX Note: This generates real data functions. Future versions
    % should produce complex data instead.

    file = fopen('test_data.h', 'w');
    fprintf(file, '#include <fft.h>\n\n');

    % Generate a 1-Volt DC signal
    fs = 64;
    t = [0:fs-1]./fs;
    signal = ones(1, fs);
    name = 'DC';
    disp('1-Volt DC:');
    processSignal(t, signal, fs, name, file);

    % Generate a 1 Hz sine wave
    fs = 64;
    t = [0:fs-1]./fs;
    f = 1;
    signal = sin(2*pi*f*t);
    name = '1Hz';

    disp('1-Hz Sine wave:');
    processSignal(t, signal, fs, name, file);

    fs = 4;
    t = [0:fs-1]./fs;
    f = 1;
    signal = sin(2*pi*f*t);
    name = '1HzShort';
    disp('Short sine wave:');
    processSignal(t, signal, fs, name, file);

    % Generate a signal with multiple frequencies
    fs = 64;
    t = [0:fs-1]./fs;
    f = 1;
    signal = sin(2*pi*f*t) + 2*sin(2*pi*(3*f)*t) + 1.5*sin(2*pi*(6*f)*t);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = 'Multi';

    disp('Multiple Frequencies:');
    processSignal(t, signal, fs, name, file);

    % Generate a signal representing 50 m/s
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 1.868e3;	% 1.868 kHz is about 50 m/s
    signal = sin(2*pi*f*t);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '50ms';
    disp('1.87 kHz or 50 m/s signal:');
    processSignal(t, signal, fs, name, file);

    % Generate a signal representing 20 m/s
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 746;		% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20ms';
    disp('746 Hz or 20 m/s signal:');
    processSignal(t, signal, fs, name, file);

    % Generate a noisy signal representing 20 m/s
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 746;		% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    signal = add_noise(signal, 1.2);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20msNoise';
    disp('746 Hz or 20 m/s signal:');
    processSignal(t, signal, fs, name, file);

    % Generate a very noisy signal representing 20 m/s
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 746;		% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    signal = add_noise(signal, 3.8);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20msBigNoise';
    disp('746 Hz or 20 m/s signal:');
    processSignal(t, signal, fs, name, file);

    % Generate a very very noisy signal representing 20 m/s
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 746;		% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    signal = add_noise(signal, 6.8);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20msGiantNoise';
    disp('746 Hz or 20 m/s signal:');
    processSignal(t, signal, fs, name, file);

    % Generate a representing 20 m/s velocity and 10 m distance
    fs = fs_hires;	% Buffer size for FFT
    fs_per_bin = 4;	% Real sampling frequency is 8192
    t = [0:fs-1]./fs/fs_per_bin;
    f = 853;		% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    %signal = add_noise(signal, 6.8);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20ms10m_up';
    disp('20 m/s 10 m up signal:');
    processSignal(t, signal, fs, name, file);
    f = 640;	% 746 Hz is about 20 m/s
    signal = sin(2*pi*f*t);
    %signal = add_noise(signal, 6.8);
    signal = signal / max(abs(signal)); % scale to +/- 1
    name = '20ms10m_down';
    disp('20 m/s 10 m down signal:');
    processSignal(t, signal, fs, name, file);
end
