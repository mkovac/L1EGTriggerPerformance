#ifndef Fitter_h
#define Fitter_h

#include "Settings.h"

// C++
#include <iostream>
#include <vector>
#include<map>

// ROOT
#include "TH1F.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"

// RooFit
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooCrystalBall.h"
#include "RooPlot.h"
#include "RooMsgService.h"
#include "TLegend.h"


using namespace std;
using namespace RooFit;


class Fitter
{
   
public:
   Fitter( TString );
   ~Fitter();
   
   void Fit( TH1F*, TString, TString );
   void Fit( TH1F*, TH1F*, TString, TString );
      
   vector<float> GetFitEnergyScaleEtaBinsMu();
   vector<float> GetFitEnergyScaleEBpTBinsMu();
   vector<float> GetFitEnergyScaleEEpTBinsMu();


private:

   RooRealVar *energy_scale, *mu, *width, *a1, *p1, *a2, *p2;
      
   RooCrystalBall *dcbPdf, *dcbPdf_barrel, *dcbPdf_endcap;
   
   TString _fits_path;
   
   vector<float> _fit_energy_scale_eta_bins_mu, _fit_energy_scale_EB_pt_bins_mu, _fit_energy_scale_EE_pt_bins_mu;
         
};
#endif
