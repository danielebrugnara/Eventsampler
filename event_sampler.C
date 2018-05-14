#include "Event_generator.h"

void event_sampler(int HIST=0, int SAMPLES=1000000){
  gROOT->ProcessLine(".L Event.C+");
  gROOT->ProcessLine(".L Event_generator.C+");
  Event_generator event;
  event.RunEvents(HIST, "events_run" , SAMPLES);

}
