#ifndef INSTRUMENT_FM_H
#define INSTRUMENT_FM_H

#include "instrument.h"
#include "envelope_adsr.h"
#include <vector>
#include <string>

namespace upc {
  class InstrumentFM: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int n_active;
    
    // Parameters
    float N1; // Carrier ratio
    float N2; // Modulator ratio
    float I;  // Modulation Index (Peak)
    bool use_semitones; // If true, I is calculated from I_semitones
    float I_semitones;

    // State
    float phi_c; // Carrier phase
    float phi_m; // Modulator phase
    float inc_c; // Carrier increment
    float inc_m; // Modulator increment
    float A;     // Current Amplitude
    
    // Wavetable support
    const std::vector<float> *tbl;

  public:
    InstrumentFM(const std::string &param);
    void command(long cmd, long note, long vel);
    const std::vector<float> & synthesize();
    bool is_active() const { return bActive; }
  };
}

#endif
