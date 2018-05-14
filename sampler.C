#include "TF1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TRandom3.h"

void sampler (int NMAX = 100000000){

  float xmin=0;
  float xmax=3.1415;
  TF1 *func = new TF1("func","sin(3*x)/x",xmin,xmax);
  TH1F *h = new TH1F("h", "histogramma distribuzione",3, 0, 3 );
  for (int i=0; i<NMAX; i++){
    //    h->Fill(func->GetRandom());
  }
  Double_t BR[3];
  TRandom3 *randm= new TRandom3();
  int br;
  BR[1]=1.28E-6; //M2E2
  BR[2]=0.78E-6; //M1E3
  BR[0]=1-BR[1]-BR[2]; //
  Double_t s=0;
  for (int i=0; i<NMAX; i++){
    Double_t u=randm->Uniform();
    for (br=0, s=BR[0]; u>s ;s+=BR[++br] );
    h->Fill(br);
    //    h->Fill(br);
  }
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 500);
  h->Draw();


}
