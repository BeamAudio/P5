#include <iostream>
#include <math.h>
#include "instrument_fm.h"
#include "wavetable_loader.h"
#include "keyvalue.h"

using namespace upc;
using namespace std;

InstrumentFM::InstrumentFM(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  KeyValue kv(param);

  if (!kv.to_float("N1", N1)) N1 = 1.0f;
  if (!kv.to_float("N2", N2)) N2 = 1.0f;
  
  if (kv.to_float("I_semitones", I_semitones)) {
      use_semitones = true;
      I = 0; // Calculated dynamically or at note on
  } else {
      use_semitones = false;
      if (!kv.to_float("I", I)) I = 1.0f;
  }

  // Load Wavetable
  string filename = kv("file");
  if (filename.empty()) {
      // Default to the standard sine if no file specified (fallback)
      filename = "work/sine.wtb"; 
  }
  
  // Try to load. If it fails (file not found), tbl will be null.
  // We assume the user has generated work/sine.wtb as per instructions.
  tbl = WavetableLoader::getInstance().load(filename);
  
  if (!tbl) {
      cerr << "Warning: InstrumentFM could not load wavetable: " << filename << endl;
  }
}

void InstrumentFM::command(long cmd, long note, long vel) {
  if (cmd == 9) { // Note On
    bActive = true;
    adsr.start();
    
    float f0 = 440.0f * pow(2.0f, (note-69.0f)/12.0f);
    
    // Calculate frequencies
    float fc = f0 * N1;
    float fm = f0 * N2;
    
    // Calculate increments
    // If using a table, inc is still in radians because our lookup math will convert radians -> index
    inc_c = 2 * M_PI * fc / SamplingRate;
    inc_m = 2 * M_PI * fm / SamplingRate;
    
    phi_c = 0;
    phi_m = 0;
    
    if (use_semitones) {
        if (N2 != 0)
            I = (N1 / N2) * (pow(2.0f, I_semitones/12.0f) - 1.0f);
        else
            I = 0;
    }
    
    A = vel / 127.0f;
  }
  else if (cmd == 8) { // Note Off
    adsr.stop();
  }
  else if (cmd == 0) { // Force Off
    adsr.end();
  }
}

const std::vector<float> & InstrumentFM::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  // Safety check
  if (!tbl || tbl->empty()) {
      x.assign(x.size(), 0);
      return x;
  }

  unsigned int tbl_size = tbl->size();
  const vector<float>& table = *tbl;

  // 1. Fill x with 1.0 (dummy for ADSR)
  x.assign(x.size(), 1.0f);
  
  // 2. Get ADSR envelope
  adsr(x);
  
  // 3. FM Synthesis using Wavetable Lookup
  for (unsigned int i=0; i<x.size(); ++i) {
      float env = x[i];
      float current_I = I * env;
      
      // 1. Modulator Lookup
      // Calculate modulator index from phase
      // Index = (phi / 2PI) * Size
      float mod_index_f = (phi_m / (2 * M_PI)) * tbl_size;
      unsigned int mod_idx = (unsigned int)mod_index_f;
      if (mod_idx >= tbl_size) mod_idx = 0; // Wrap safety
      
      float modulator_val = table[mod_idx];
      
      // 2. Carrier Lookup
      // Phase = phi_c + I * modulator_output
      float carrier_phase = phi_c + current_I * modulator_val;
      
      // Wrap carrier phase to 0..2PI range for lookup logic
      // Note: simple fmod is slow, but phase can be negative or large positive
      while (carrier_phase < 0) carrier_phase += 2*M_PI;
      while (carrier_phase >= 2*M_PI) carrier_phase -= 2*M_PI;
      
      float car_index_f = (carrier_phase / (2 * M_PI)) * tbl_size;
      unsigned int car_idx = (unsigned int)car_index_f;
      if (car_idx >= tbl_size) car_idx = 0;
      
      float carrier_val = table[car_idx];
      
      x[i] = A * env * carrier_val;
      
      phi_c += inc_c;
      phi_m += inc_m;
      
      while (phi_c >= 2*M_PI) phi_c -= 2*M_PI;
      while (phi_m >= 2*M_PI) phi_m -= 2*M_PI;
  }

  return x;
}