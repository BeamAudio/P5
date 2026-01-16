#include <iostream>
#include <cmath>
#include "instrument_wavetable.h"
#include "wavetable_loader.h"
#include "keyvalue.h"

using namespace upc;
using namespace std;

InstrumentWavetable::InstrumentWavetable(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  KeyValue kv(param);
  string filename;
  
  filename = kv("file");
  if (!filename.empty()) {
      tbl = WavetableLoader::getInstance().load(filename);
  } else {
      cerr << "Error: 'file' parameter missing for InstrumentWavetable. Param: " << param << endl;
      tbl = nullptr;
  }
}

void InstrumentWavetable::command(long cmd, long note, long vel) {
  if (cmd == 9) { // Note On
    bActive = true;
    adsr.start();
    this->phase = 0;
    
    if (tbl && !tbl->empty()) {
        float f0 = 440.0f * pow(2.0f, (note-69.0f)/12.0f);
        // Correct formula: f0 * N / Fs
        this->incPhase = f0 * tbl->size() / (float)SamplingRate;
    } else {
        this->incPhase = 0;
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

const std::vector<float> & InstrumentWavetable::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  if (!tbl || tbl->empty()) {
      x.assign(x.size(), 0);
      return x;
  }

  const vector<float>& table = *tbl;
  unsigned int tableSize = table.size();

  for (unsigned int i=0; i<x.size(); ++i) {
    // Basic truncation
    unsigned int index = (unsigned int) phase;
    if (index >= tableSize) index = 0; // Safety
    
    x[i] = A * table[index];
    
    phase += incPhase;
    while (phase >= tableSize)
      phase -= tableSize;
  }
  
  adsr(x); // Apply envelope

  return x;
}
