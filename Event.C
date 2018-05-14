#include "Event.h"

Gamma::Gamma(){
}


Gamma::Gamma(const TVector3 & Pos, float En ){
  SetPosition(Pos);
  SetEnergy(En);
}

void Gamma::SetEnergy(float En){
  Energy=En;
}
void Gamma::SetPosition(const TVector3 &  Pos){
  Position=Pos;
}   

float Gamma::GetEnergy(){
  return Energy;
}
TVector3 Gamma::GetPosition(){
  return Position;
}   


Event::Event(){
 br=-1;
}



Event::Event(int br,const Gamma &  gamma1){
  this->br=br; 
  AddGamma(gamma1);
}

Event::Event(int br, const  Gamma & gamma1, const  Gamma &  gamma2){
  this->br=br;
  AddGamma(gamma1);
  AddGamma(gamma2);
}

int  Event::GetNumberOfGammas(){
  return gammas.size();
}     

int Event::GetEventType(){
  return br;
};

void Event::AddGamma(Gamma gamma){
  gammas.push_back(gamma);
}
Gamma Event::GetGamma (int nr){
  return gammas[nr]; 
}

void Event::Print(std::ostream &  out) {
  out << "$"<<std::endl; //event start
  out << "-101 55 137 0 0 0 0 0 0 0 " << std::endl; //emitter line
  for (unsigned int i=0; i<gammas.size(); i++){
    out<<"1  "<<gammas[i].GetEnergy() << " ";
    out<< gammas[i].GetPosition().X()<< " "; 
    out<< gammas[i].GetPosition().Y()<< " ";
    out<< gammas[i].GetPosition().Z()<< " 0 0 0 "<<std::endl;
  }
  out<< std::endl;
  // 0 en x y z 
  //1 en1 x
  //  en2 x2 y2
}
