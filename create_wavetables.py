import numpy as np
import os

def write_wtb(filename, samples):
    with open(filename, 'w') as f:
        # Join samples with spaces
        f.write(" ".join(f"{s:.6f}" for s in samples))

def create_tables():
    if not os.path.exists("work"):
        os.makedirs("work")
        
    # High resolution sine (N=1024)
    N_high = 1024
    t_high = np.linspace(0, 2*np.pi, N_high, endpoint=False)
    sine_high = np.sin(t_high)
    write_wtb("work/sine.wtb", sine_high)
    print("Created work/sine.wtb")
    
    # Low resolution sine (N=20) for "Seno" exercise
    N_low = 20
    t_low = np.linspace(0, 2*np.pi, N_low, endpoint=False)
    sine_low = np.sin(t_low)
    write_wtb("work/sine_small.wtb", sine_low)
    print("Created work/sine_small.wtb")

if __name__ == "__main__":
    create_tables()
