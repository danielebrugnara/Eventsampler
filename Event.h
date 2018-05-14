#if !defined(Event_h)
#define Event_h
#include <ostream>

#include "TVector3.h"

class Gamma {
  public:
    Gamma();
    Gamma(const TVector3 & Pos, float En );
    void SetEnergy(float En);
    void   SetPosition(const TVector3 & Pos);   
    float GetEnergy();
    TVector3   GetPosition();   
  private:
    float Energy;
    TVector3 Position;    
};



class Event {

  public:
    Event();
    Event(int br,const Gamma &  gamma1);
    Event(int br,const Gamma &  gamma1, const Gamma & gamma2);
    int  GetNumberOfGammas();
    int GetEventType();
    void AddGamma(Gamma gamma);
    Gamma GetGamma (int nr);
    void Print(std::ostream &  out); 
  private: 
    std::vector<Gamma> gammas;
    int br;
};


#endif
