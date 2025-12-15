#include <iostream>
#include <math.h>
#include "instrument_seno.h"
#include "keyvalue.h"

using namespace upc;
using namespace std;

InstrumentSeno::InstrumentSeno(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
  int N;

  if (!kv.to_int("N",N))
    N = 40; //default value
  
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  this->phase = 0;
  this->incPhase = 2 * M_PI /(float) N;
  
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += this->incPhase;
  }
}

void InstrumentSeno::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    this->phase = 0;
    float f0 = 440*pow(2, (note-69.)/12.);
    this->incPhase = 2 * M_PI * f0 / SamplingRate * tbl.size();
    A = vel / 127.;
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}

const std::vector<float> & InstrumentSeno::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  for (unsigned int i=0; i<x.size(); ++i) {
    
    int index = (int) phase;
    x[i] = A * tbl[index];
    phase += incPhase;
    while (phase >= tbl.size())
      phase -= tbl.size();
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
