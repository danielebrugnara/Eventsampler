#include "Event_generator.h"


Double_t A_M2E2 (double x){
  return 1+5./49*(1./2*(3.*TMath::Power(cos(x), 2) -1))+40./441*(1./8*(35.*TMath::Power(cos(x), 4)-30.*TMath::Power(cos(x), 2)+3)) ;
}

Double_t A_E1M3 (double x){
  return 1-1./8*( 1./2*(3.*TMath::Power(cos(x), 2)-1));
}
Double_t E_M2E2 (double x){
  return TMath::Power(x, 5)*TMath::Power((661.7-x), 5);
}
Double_t E_E1M3 (double x){
  return TMath::Power(x, 3)*TMath::Power((661.7-x), 7)+TMath::Power(x, 7)*TMath::Power((661.7-x), 3);
}

Event_generator::Event_generator()
  :Ang_distr_M2E2("Ang_distr_M2E2", "A_M2E2(x)" , 0, 3.1415 ),
  Ang_distr_E1M3("Ang_distr_E1M3","A_E1M3(x)", 0, 3.1415 ),
  En_distr_M2E2("En_distr_M2E2","E_M2E2(x)", 0, 661.7 ),
  En_distr_E1M3("Ang_distr_E1M3","E_E1M3(x)", 0, 661.7 )
{
//  BR[1]=     1.28E-6; //M2E2
//  BR[2]=     0.78E-6; //M1E3
  BR[1]=0.62 ; //M2E2
  BR[2]=0.38 ; //M1E3
//  BR[1]=0 ; //M2E2
//  BR[2]=1 ; //M1E3
  BR[0]=1-BR[1]-BR[2]; //
  Transition_Energy=661.7;
} //constructor

Event Event_generator::GenerateEvent(){
  //I selects case 1, 2, 3
  Double_t x, y, z;
  randm.Sphere(x, y, z, 1);
  TVector3 position_tmp(x, y, z);
  switch (Branch()){
    case 0: {
              Gamma gamma1(position_tmp, Transition_Energy);
              Event new_event(0, gamma1);
              return new_event;
              break;
            }
    case 1: {
              Double_t energy_tmp=En_distr_M2E2.GetRandom(0, 661.7);
              Double_t angle_tmp=Ang_distr_M2E2.GetRandom(0, 3.1415 );

              Double_t x2, y2, z2; 
              randm.Sphere(x2, y2, z2, 1);
              TVector3 position2_tmp(x2, y2, z2);
              Gamma gamma1(position_tmp,energy_tmp);
              position2_tmp=position_tmp.Cross(position2_tmp);
              position_tmp.Rotate(angle_tmp, position2_tmp);
              Gamma gamma2( position_tmp, Transition_Energy-energy_tmp);
              Event new_event(1, gamma1, gamma2);
              return new_event;
              break;
            }
    case 2: {
              Double_t energy_tmp=En_distr_E1M3.GetRandom(0, 661.7);
              Double_t angle_tmp=Ang_distr_E1M3.GetRandom(0, 3.1415);

              Double_t x2, y2, z2; 
              randm.Sphere(x2, y2, z2, 1);
              TVector3 position2_tmp(x2, y2, z2);
              Gamma gamma1(position_tmp,energy_tmp);
              position2_tmp=position_tmp.Cross(position2_tmp);
              position_tmp.Rotate(angle_tmp, position2_tmp);
              Gamma gamma2( position_tmp, Transition_Energy-energy_tmp);
              Event new_event(2, gamma1, gamma2);
              return new_event;
              break;
            }
  }
  Event new_event;
  std::cerr << "something is wrong  " <<std::endl;
  return new_event;
}



void Event_generator::RunEvents(int HIST, std::string outfile_name, int NMAX){
  std::ofstream out(outfile_name);
  TH1F * h = new TH1F("h", "Relative Angle Distribution", 100, 0, 3.1415);
  TH1F * g = new TH1F("g", "Single #gamma Energy Distribution", 100, 0, 661.7);
  TH1F * h2 = new TH1F("h2", "Relative Angle Distribution", 100, 0, 3.1415);
  TH1F * g2 = new TH1F("g2", "Single #gamma Energy Distribution", 100, 0, 661.7);
  out << "FORMAT 0 0"<<std::endl;
  out << "#maximum info read from file"<<std::endl;
  out << "REACTION 1 1 1 1 0 " <<std::endl;
  out << "#0 energy beam"<<std::endl;
  out << "EMITTED 2 1 1"<<std::endl;
  out << "#2 gammas emitted"<<std::endl;
  for (int i=0; i<NMAX; i++){
    Event ev=GenerateEvent();
    ev.Print(out);
    if (!HIST) continue;
    if (ev.GetNumberOfGammas()>1){
      if (ev.GetEventType()==1){
        h->Fill(ev.GetGamma(0).GetPosition().Angle(ev.GetGamma(1).GetPosition()));
        g->Fill(ev.GetGamma(0).GetEnergy());
       } else {
        h2->Fill(ev.GetGamma(0).GetPosition().Angle(ev.GetGamma(1).GetPosition()));
        g2->Fill(ev.GetGamma(0).GetEnergy());
       }
    }
  }
  out.close();
  TCanvas *canvas =new TCanvas("canvas", "canvas", 1800, 900);
  canvas->Divide(2, 1);
  canvas->cd(1);
  h->SetStats(kFALSE);
  h->GetXaxis()->SetTitle("Angle [rad]");
  h2->SetStats(kFALSE);
  h2->SetLineColor(kRed);
//  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  h2->Draw("same");

  auto legend = new TLegend(0.1, 0.7,0.48, 0.9);
  legend->AddEntry(h, "M2E2");
  legend->AddEntry(h2, "M1E3");
  legend->Draw();

  canvas->cd(2);
  g->SetStats(kFALSE);
  g->GetXaxis()->SetTitle("Energy [keV]");
//  canvas->Update();
  g2->SetStats(kFALSE);
  g2->SetLineColor(kRed);
  canvas->Update();
//  g->GetYaxis()->SetTitle("Counts");
  g->Draw();
//  canvas->Update();
  g2->Draw("same");
  canvas->Update();

  auto legend2 = new TLegend(0.1, 0.7,0.48, 0.9);
  legend2->AddEntry(g, "M2E2");
  legend2->AddEntry(g2, "M1E3");
  legend2->Draw();
}  


int Event_generator::Branch(){
  int br;
  Double_t u=randm.Uniform();
  Double_t s;
  for (br=0, s=BR[0]; u>s ;s+=BR[++br] );
  return br;
}

