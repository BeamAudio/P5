#ifndef INSTRUMENT_WAVETABLE_H
#define INSTRUMENT_WAVETABLE_H

#include "instrument.h"
#include "envelope_adsr.h"
#include <string>
#include <vector>

namespace upc {
  class InstrumentWavetable : public Instrument {
  public:
    InstrumentWavetable(const std::string &param);
    void command(long cmd, long note, long velocity=100);
    const std::vector<float> & synthesize();
    
  private:
    EnvelopeADSR adsr;
    const std::vector<float>* tbl; // Pointer to the shared wavetable
    float phase;
    float incPhase;
    float A;
  };
}
#endif
