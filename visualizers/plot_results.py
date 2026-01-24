import numpy as np
import matplotlib.pyplot as plt
import wave
import os
import sys

# Helper to read WAV
def read_wav(filename):
    if not os.path.exists(filename):
        print(f"Error: File {filename} not found.")
        return None, None
        
    with wave.open(filename, 'rb') as wf:
        n_channels = wf.getnchannels()
        sampwidth = wf.getsampwidth()
        framerate = wf.getframerate()
        n_frames = wf.getnframes()
        str_data = wf.readframes(n_frames)
        
        if sampwidth == 2:
            dtype = np.int16
            norm_factor = 32768.0
        else:
            print(f"Unsupported sample width: {sampwidth}")
            return None, None
            
        data = np.frombuffer(str_data, dtype=dtype)
        data = data.astype(np.float32) / norm_factor
        
        return data, framerate

output_dir = "visualizers"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

def plot_adsr():
    filename = "work/tests/adsr.wav"
    data, fs = read_wav(filename)
    if data is None: return

    # Defined timings from adsr.sco (120 BPM, 120 TPB -> 1 sec = 240 ticks)
    # Note 1: Start 0.0s
    # Note 2: Start 0 + 480 + 240 = 720 ticks = 3.0s
    # Note 3: Start 720 + 480 + 240 = 1440 ticks = 6.0s
    # Note 4: Start 1440 + 96 + 480 = 2016 ticks = 8.4s -> Wait, let's recheck sco
    # 0 (N1 start) -> 480 (N1 end) -> +240 (Wait) = 720 (N2 start)
    # 720 (N2 start) -> +480 (N2 end) -> +240 (Wait) = 1440 (N3 start)
    # 1440 (N3 start) -> +96 (N3 end) -> +480 (Wait) = 2016 (N4 start)
    
    # Extract segments (approx 2.5s window for each)
    window_len = int(2.5 * fs)
    
    # 1. Generic ADSR
    start_1 = int(0.0 * fs)
    seg_1 = data[start_1 : start_1 + window_len]
    t_1 = np.arange(len(seg_1)) / fs
    
    plt.figure(figsize=(10, 4))
    plt.plot(t_1, seg_1)
    plt.title('ADSR: Generic (A=0.5, D=0.3, S=0.6, R=0.5)')
    plt.xlabel('Time (s)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.savefig(f"{output_dir}/adsr_generic.png")
    plt.close()

    # 2. Percussive Full
    start_2 = int(3.0 * fs)
    seg_2 = data[start_2 : start_2 + window_len]
    t_2 = np.arange(len(seg_2)) / fs
    
    plt.figure(figsize=(10, 4))
    plt.plot(t_2, seg_2)
    plt.title('ADSR: Percussive Full (Long Decay)')
    plt.xlabel('Time (s)')
    plt.grid(True)
    plt.savefig(f"{output_dir}/adsr_percussive_full.png")
    plt.close()

    # 3. Percussive Interrupted
    start_3 = int(6.0 * fs)
    seg_3 = data[start_3 : start_3 + window_len]
    t_3 = np.arange(len(seg_3)) / fs
    
    plt.figure(figsize=(10, 4))
    plt.plot(t_3, seg_3)
    plt.title('ADSR: Percussive Interrupted (Short Note)')
    plt.xlabel('Time (s)')
    plt.grid(True)
    plt.savefig(f"{output_dir}/adsr_percussive_int.png")
    plt.close()

    # 4. Flat
    start_4 = int(8.4 * fs)
    # Check bounds
    if start_4 + window_len > len(data):
        seg_4 = data[start_4:]
    else:
        seg_4 = data[start_4 : start_4 + window_len]
    t_4 = np.arange(len(seg_4)) / fs
    
    plt.figure(figsize=(10, 4))
    plt.plot(t_4, seg_4)
    plt.title('ADSR: Flat (Violin/Wind)')
    plt.xlabel('Time (s)')
    plt.grid(True)
    plt.savefig(f"{output_dir}/adsr_flat.png")
    plt.close()

def plot_seno():
    filename = "work/tests/seno.wav"
    data, fs = read_wav(filename)
    if data is None: return

    # Zoom in to see the steps
    # Just take a small chunk from the middle of the sustain
    # Note starts at 0, ends at 1s (240 ticks). Sustain is high.
    
    start = int(0.5 * fs)
    length = 200 # samples
    seg = data[start : start + length]
    
    plt.figure(figsize=(10, 4))
    plt.plot(seg, '.-')
    plt.title('Instrument Seno: Signal with N=20 (Truncation Artifacts)')
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.savefig(f"{output_dir}/seno_steps.png")
    plt.close()

def plot_effects():
    filename = "work/tests/effects.wav"
    data, fs = read_wav(filename)
    if data is None: return

    # Timings:
    # Note 1 (Normal): 0 -> 240 (1s) + 120 (0.5s) wait = 1.5s start next
    # Note 2 (Tremolo): 1.5s start -> 240 duration
    # Note 3 (Vibrato): 3.0s start -> 240 duration
    
    # 1. Tremolo
    start_trem = int(1.5 * fs)
    len_trem = int(1.0 * fs)
    seg_trem = data[start_trem : start_trem + len_trem]
    t_trem = np.arange(len(seg_trem)) / fs
    
    plt.figure(figsize=(10, 6))
    plt.subplot(2,1,1)
    plt.plot(t_trem, seg_trem)
    plt.title('Effect: Tremolo (Real)')
    plt.grid(True)
    
    # 2. Vibrato
    start_vib = int(3.0 * fs)
    len_vib = int(1.0 * fs)
    seg_vib = data[start_vib : start_vib + len_vib]
    t_vib = np.arange(len(seg_vib)) / fs
    
    # To see vibrato, we might need to zoom in or look at zero crossings, 
    # but the waveform might just look like a sine. 
    # Let's plot it anyway.
    plt.subplot(2,1,2)
    plt.plot(t_vib, seg_vib)
    plt.title('Effect: Vibrato (Real)')
    plt.grid(True)
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/effects.png")
    plt.close()

def plot_fm():
    # 1. Vibrato
    filename = "work/tests/fm_vibrato.wav"
    data, fs = read_wav(filename)
    if data is not None:
        plt.figure(figsize=(10, 6))
        # Plot Spectrogram to see the vibrato (frequency oscillation)
        plt.specgram(data, NFFT=1024, Fs=fs, noverlap=900)
        plt.title('FM Vibrato (N1=1, N2=0.02, I=2st)')
        plt.ylabel('Frequency')
        plt.xlabel('Time')
        # Limit freq axis to see fundamental
        plt.ylim(0, 1000)
        plt.colorbar(label='Intensity (dB)')
        plt.savefig(f"{output_dir}/fm_vibrato_spec.png")
        plt.close()

    # 2. Instruments (Clarinet / Bell)
    filename = "work/tests/doremi.wav"
    data, fs = read_wav(filename)
    if data is not None:
        # Clarinet is first part, Bell is second part.
        # Clarinet scale: 8 notes * 0.5s (240 ticks at 120bpm is 1s... wait)
        # 120 BPM, 120 TPB -> 1 beat = 0.5s? 
        # Ticks per beat = 120. Beats per minute = 120. -> 2 beats per sec. -> 1 beat = 0.5s.
        # 240 ticks = 2 beats = 1.0s.
        # Scale: 8 notes * 1.0s = 8s.
        # Wait: 480 ticks wait = 2.0s.
        # Bell starts at ~10s.
        
        start_bell = int(10.0 * fs)
        if start_bell < len(data):
            seg_bell = data[start_bell : start_bell + int(3.0*fs)]
            t = np.arange(len(seg_bell)) / fs
            
            plt.figure(figsize=(10, 6))
            plt.subplot(2,1,1)
            plt.plot(t, seg_bell)
            plt.title('FM Bell (N1=1, N2=1.414, I=10->0)')
            plt.grid(True)
            
            # Spectrogram of Bell
            plt.subplot(2,1,2)
            plt.specgram(seg_bell, NFFT=1024, Fs=fs, noverlap=512)
            plt.ylim(0, 4000)
            plt.ylabel('Frequency')
            plt.xlabel('Time')
            
            plt.tight_layout()
            plt.savefig(f"{output_dir}/fm_instruments_bell.png")
            plt.close()

if __name__ == "__main__":
    plot_adsr()
    plot_seno()
    plot_effects()
    plot_fm()
