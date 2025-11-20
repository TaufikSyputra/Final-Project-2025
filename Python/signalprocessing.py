import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import welch, butter, filtfilt, iirnotch

# Load data dari file .txt dengan delimiter spasi
data = np.loadtxt('subjek4a.txt', delimiter=' ')

# Raw data
ch1 = data[:, 0]  # flexor digitorum
ch2 = data[:, 1]  # extensor digitorum

# Properti sinyal
fs = 500  # sampling frequency (Hz)
ts = 1 / fs  # sampling period (s)
time = np.arange(len(ch1)) / fs  # waktu

# Plot raw data
plt.figure(figsize=(10, 6))

plt.subplot(2, 1, 1)
plt.plot(time, ch1)
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Channel 1 - Flexor Digitorum (raw)")
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(time, ch2)
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Channel 2 - Extensor Digitorum (raw)")
plt.grid(True)
plt.tight_layout()

# Analisis spektral (Welch) dengan overlap
f1, Pxx1 = welch(ch1, fs=500, nperseg= 2500, noverlap= 526)
f2, Pxx2 = welch(ch2, fs=500, nperseg= 2500, noverlap= 526)

# Konversi ke dB/Hz
Pxx1_db = 10 * np.log10(Pxx1)
Pxx2_db = 10 * np.log10(Pxx2)

# Plot PSD
plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(f1, Pxx1_db)
plt.title("PSD Channel 1 (Flexor Digitorum) - Welch (dB/Hz)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("PSD (dB/Hz)")
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(f2, Pxx2_db)
plt.title("PSD Channel 2 (Extensor Digitorum) - Welch (dB/Hz)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("PSD (dB/Hz)")
plt.grid(True)
plt.tight_layout()

# =============Preprocessing================
# Filtering signal
def bandpass_filter(signal, fs, lowcut=30, highcut=148, order=4):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return filtfilt(b, a, signal)

def notch_filter(signal, fs, notch_freq=50, Q=50):
    nyq = 0.5 * fs
    w0 = notch_freq / nyq
    b, a = iirnotch(w0, Q)
    return filtfilt(b, a, signal)

# Apply filters

# Bandpass + Notch untuk masing-masing channel
ch1_filtered = notch_filter(bandpass_filter(ch1, fs), fs)
ch2_filtered = notch_filter(bandpass_filter(ch2, fs), fs)

# ======== PLOT SINYAL YANG TELAH DIFILTER =========
plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(time, ch1_filtered)
plt.title("Channel 1 - Flexor Digitorum (Filtered)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(time, ch2_filtered)
plt.title("Channel 2 - Extensor Digitorum (Filtered)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.tight_layout()
# plt.show()

# Analisis spektral (Welch) dengan overlap untuk sinyal yang telah difilter
f1_fil, Pxx1_fil = welch(ch1_filtered, fs=500, nperseg= 2500, noverlap= 526)
f2_fil, Pxx2_fil = welch(ch2_filtered, fs=500, nperseg= 2500, noverlap= 526)

# Konversi ke dB/Hz
Pxx1_fil_db = 10 * np.log10(Pxx1_fil)
Pxx2_fil_db = 10 * np.log10(Pxx2_fil)

# Plot PSD
plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(f1_fil, Pxx1_fil_db)
plt.title("PSD Channel 1 (Flexor Digitorum) - Welch (dB/Hz)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("PSD (dB/Hz)")
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(f2_fil, Pxx2_fil_db)
plt.title("PSD Channel 2 (Extensor Digitorum) - Welch (dB/Hz)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("PSD (dB/Hz)")
plt.grid(True)
plt.tight_layout()
#plt.show()

#============Normalisasi sinyal==============
# bersihkan sinyal dari nilai ekstrem
mask = (ch1_filtered <= 200) & (ch1_filtered >= -200) & \
       (ch2_filtered <= 200) & (ch2_filtered >= -200)

ch1_cleaned = ch1_filtered[mask]
ch2_cleaned = ch2_filtered[mask]
time_cleaned = time[mask]

# Normalisasi sinyal
ch1_normalized = ch1_cleaned * 200/ np.max(np.abs(ch1_cleaned))
ch2_normalized = ch2_cleaned * 200/ np.max(np.abs(ch2_cleaned))
# Plot sinyal yang telah dinormalisasi
plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(time_cleaned, ch1_normalized)
plt.title("Channel 1 - Flexor Digitorum (Filtered and Normalized)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(time_cleaned, ch2_normalized)
plt.title("Channel 2 - Extensor Digitorum (Filtered and Normalized)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.tight_layout()
plt.show()