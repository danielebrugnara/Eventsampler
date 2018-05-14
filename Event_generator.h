#if !defined(Event_generator_h)
#define Event_generator_h
#include <fstream>

#include "Event_generator.h"
#include "TRandom3.h"
#include "TF1.h"
#include "Event.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"

class Event_generator {
  public:
    Event_generator(); //constructor
    Event GenerateEvent();
    void RunEvents(int HIST=0, std::string outfile_name="events_run", int NMAX=1000000);  
  private:
    int Branch();
    float BR[3];
    float Transition_Energy;//transition energy
    TF1 Ang_distr_M2E2; //Angular distribution for M2E2 
    TF1 Ang_distr_E1M3; //Angular distribution for E1M3
    TF1 En_distr_M2E2;  //Energy distribution for M2E2
    TF1 En_distr_E1M3;  //Energy distribution for E1M3
    TRandom3 randm;
};



#endif
