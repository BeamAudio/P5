import numpy as np
import os

def create_wtb(filename, n_samples):
    t = np.linspace(0, 2*np.pi, n_samples, endpoint=False)
    s = np.sin(t)
    # Ensure directory exists
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    with open(filename, 'w') as f:
        f.write(' '.join(map(str, s)))
    print(f"Created {filename} with {n_samples} samples.")

if __name__ == "__main__":
    # Base sine wave for high-quality synthesis
    create_wtb("work/sine.wtb", 1024)
    # Low-resolution sine for showing steps in the Seno exercise
    create_wtb("work/sine_small.wtb", 20)
