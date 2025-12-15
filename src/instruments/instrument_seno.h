#ifndef INSTRUMENT_PIANO
#define INSTRUMENT_PIANO

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class InstrumentPiano: public upc::Instrument {
    EnvelopeADSR adsr;
    float phase, incPhase;
	float A;
    std::vector<float> tbl;
  public:
    InstrumentPiano(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif