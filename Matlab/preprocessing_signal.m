close all
clear
clc

% Load data
load subjek1a.txt
load subjek1b.txt
load subjek2a.txt
load subjek2b.txt
load subjek3a.txt
load subjek3b.txt
load subjek4a.txt
load subjek4b.txt

chanel1 = subjek3a(:,1); %flexor
chanel2 = subjek3a(:,2); %extensor
%%
% Properti sinyal
fs = 500;
ts = 1/fs;
time = (0:length(chanel1)-1)/fs;

% plot raw data
figure
subplot(2,1,1), plot(time, chanel1), xlabel("time (s)"), ylabel("amplitudo");
title("sinyal mentah flexor"); grid minor
subplot(2,1,2), plot(time, chanel2), xlabel("time (s)"), ylabel("amplitudo");
title("sinyal mentah Extensor"); grid minor
%%
% Analisis spektral metode Welch
window = hamming(1839);
noverlap = 460;
nfft = 1000;

[pxx_chanel1, fw_chanel1] = pwelch(chanel1, window, noverlap, nfft,fs);
[pxx_chanel2, fw_chanel2] = pwelch(chanel2, window, noverlap, nfft,fs);

% Plot 
figure
subplot(2,1,1), plot(fw_chanel1, 10*log10(pxx_chanel1)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("Power sepectral density (metode Welch) sinyal flexor mentah"); grid minor;
subplot(2,1,2), plot(fw_chanel2, 10*log10(pxx_chanel2)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("Power sepectral density (metode Welch) sinyal Extensor mentah"); grid minor;
%%
%Filter Bandpass
bandpass_filter = bandpass;
chanel1_bandpass = filter(bandpass_filter, chanel1);
chanel2_bandpass = filter(bandpass_filter, chanel2);

% Analisis Spektral
[pxx_chanel1_bandpass, fw_chanel1_bandpass] = pwelch(chanel1_bandpass, window, noverlap, nfft,fs);
[pxx_chanel2_bandpass, fw_chanel2_bandpass] = pwelch(chanel2_bandpass, window, noverlap, nfft,fs);

% Plot
figure
subplot(2,2,1), plot(time, chanel1_bandpass), xlabel("waktu (s)"), ylabel("Amplitudo");
title("Flexor filter bandpass "); grid minor;
subplot(2,2,2), plot(time, chanel2_bandpass), xlabel("waktu (s)"), ylabel("Amplitudo");
title("Extensor filter bandpass "); grid minor;
subplot(2,2,3), plot(fw_chanel1_bandpass, 10*log10(pxx_chanel1_bandpass)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("power sepctral density (metode Welch)"); grid minor;
subplot(2,2,4), plot(fw_chanel2_bandpass, 10*log10(pxx_chanel2_bandpass)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("power sepctral density (metode Welch)"); grid minor;
% Filter Notch 50
Notch_filter50 = Notch_50;
chanel1_notch50 = filter(Notch_filter50, chanel1_bandpass);
chanel2_notch50 = filter(Notch_filter50, chanel2_bandpass);

% Filter notch 100
Notch_filter100 = Notch_100;
chanel1_notch100 = filter(Notch_filter100, chanel1_notch50);
chanel2_notch100 = filter(Notch_filter100, chanel2_notch50);

% Filter notch 150
Notch_filter150 = Notch_150;
chanel1_notch150 = filter(Notch_filter150, chanel1_notch100);
chanel2_notch150 = filter(Notch_filter150, chanel2_notch100);

% Filter notch 200
Notch_filter200 = Notch_200;
chanel1_notch200 = filter(Notch_filter200, chanel1_notch150);
chanel2_notch200 = filter(Notch_filter200, chanel2_notch150);

% Analisis Spektral
[pxx_chanel1_notch200, fw_chanel1_notch200] = pwelch(chanel1_notch200, window, noverlap, nfft,fs);
[pxx_chanel2_notch200, fw_chanel2_notch200] = pwelch(chanel2_notch200, window, noverlap, nfft,fs);

% Plot
figure
subplot(2,2,1), plot(time, chanel1_notch200), xlabel("waktu (s)"), ylabel("Amplitudo");
title("Flexor filtered"); grid minor;
subplot(2,2,2), plot(time, chanel2_notch200), xlabel("waktu (s)"), ylabel("Amplitudo");
title("Extensor filtered"); grid minor;
subplot(2,2,3), plot(fw_chanel1_notch200, 10*log10(pxx_chanel1_notch200)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("power sepctral density (metode Welch)"); grid minor;
subplot(2,2,4), plot(fw_chanel2_notch200, 10*log10(pxx_chanel2_notch200)), xlabel("frekuensi (Hz)"), ylabel("PSD (dB/Hz)");
title("power sepctral density (metode Welch)"); grid minor;
% reactifier
ch1_abs = abs(chanel1_notch200);
ch2_abs = abs(chanel2_notch200);
% Moving Average
N = 2; %jumlah sampling
% Parameter
window_ms = 100;              % Window dalam milidetik
window_samples = round(fs * window_ms / 1000);  % Konversi ke sampel

% Moving Average Filter
signal_moving_avg_ch1 = movmean(ch1_abs, window_samples);
signal_moving_avg_ch2 = movmean(ch2_abs, window_samples);

% Plot
t = (0:length(ch1_abs)-1)/fs;

figure;
subplot(2,1,1), plot(t, ch1_abs, 'k'); hold on;
subplot(2,1,1), plot(t, signal_moving_avg_ch1, 'r', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Amplitude');
legend('Rectified Signal', 'Moving Average Envelope');
title('Envelope Detection dengan Moving Average');
grid on;
subplot(2,1,2), plot(t, ch2_abs, 'k'); hold on;
subplot(2,1,2), plot(t, signal_moving_avg_ch2, 'r', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Amplitude');
legend('Rectified Signal', 'Moving Average Envelope');
title('Envelope Detection dengan Moving Average');
grid on;