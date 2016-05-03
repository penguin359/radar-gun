clc; clear all; close all;
format short eng;

c = 2.9979e8;   % Speed of light in a vacuum (m/s)
f0 = 5.6e9;     % Fundamental frequency of CW Radar (Hz)
lambda0 = c/f0; % Fundamental wavelength (m)
R_min = 1;      % Minimum range of radar (m)
R_max = 100;    % Maximum range of radar (m)
phase_min = 2*pi*(2*R_min)/lambda0 % Minimum phase shift (radians)
phase_max = 2*pi*(2*R_max)/lambda0 % Maximum phase shift (radians)

% Fastest pitches at around 100 mph or 44.7 m/s
% Knuckleball down to 25 mph or 11.2 m/s
vr_min = 20;    % Minimum detectable speed (m/s)
vr_max = 100;   % Maximum detectable speed (m/s)
fd_min = 2*vr_min/c*f0 % Minimum doppler shift
fd_max = 2*vr_max/c*f0 % Maximum doppler shift

v = 30;         % Velocity magnitude of moving target (m/s)
theta = 30;     % Velocity angle relative to radar (degrees)
vr = v*cosd(30);% Velocity magnitude towards radar (m/s)

%%

N = 2000;       % Number of samples in buffer
%fd_max = 5e3;
fd_max = 4096;
fs = 2*fd_max;
Ts = 1/fs;
fd_min = fs/N

%%

vr = 50;                % Velocity (m/s)
fd = 2*vr/c*f0          % Doppler shift
vr = 20;                % Velocity (m/s)
fd = 2*vr/c*f0          % Doppler shift

%%

fd = 1868;
vr = fd/2*c/f0
fd = 100;
vr = fd/2*c/f0

%%

Tm = 1/4;               % FMCW Modulation time (s)
fm = 1/Tm;
delta_f = 200e6;        % Change in frequency across modulation
R = 10;                 % Disance from home plate (m)
fr = R*4*fm*delta_f/c   % Frequency due to distance of stationary object

%%

vr = 20;                % Velocity (m/s)
fd = 2*vr/c*f0          % Doppler shift
fup = abs(fr+fd)
fdown = abs(fr-fd)

%%

fr = 1/2*(fdown+fup)
fd = 1/2*(fdown-fup)

%%

R_max = 130; % Maximum distance to fence from home plate (m)
R_plate = 18.3; % Distance to pitcher mound from home plate (m)

fm = 0.5e3
delta_f = 200e6
%fdown = 4e6
fdown = .5e6
fup = fdown

fr = 1/2*(fdown+fup)
fd = 1/2*(fdown-fup)
R = c*fr/(4*fm*delta_f)

%%

R_desired_max = 2.5*R_plate
fr_max = R_desired_max/c*(4*fm*delta_f)
R_desired_min = .2*R_plate
fr_min = R_desired_min/c*(4*fm*delta_f)

adc_sample_time = 4e-6;
fadc = 1/adc_sample_time
%n_samples = 4096
n_samples = 512
fs_min = fadc/n_samples
    
