#ifndef Histograms_h
#define Histograms_h

// C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// ROOT
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include "TPaveText.h"
#include "TSystem.h"
#include "TIterator.h"
#include "TROOT.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"


// Include classes
#include "Settings.h"
#include "Fitter.h"
//#include "CMS_lumi.h"
//#include "Cosmetics.h"
#include "Variables.h"


using namespace std;

class Histograms
{
   
public:
   Histograms();
   ~Histograms();
   
   void FillScaleAndPt( float, float, float, int );
    
     
   void SaveHistograms( string );
   void DeleteHistograms();
      
   void GetHistograms( TString );
	
   void PlotHistograms1D( TString, TString, TString );
   void PlotHistograms1DpTBins( TString, TString );
   void PlotHistograms1DEtaBins( TString, TString );

   
   void PlotResolution( TString, TString );
   void PlotScaleVsEta( TString, TString );
   void PlotScaleVsPt( TString, TString );

   void CalculateFWHM( TString );
   
   void FitEnergyScalePtBins( TString, TString);
   void FitEnergyScaleEtaBins( TString, TString);
   
   int SetVariableIndex( TString );
   int SetEmulationIndex( TString );
   
   

   void SavePlots( TCanvas *, TString , TString );

   TLegend *CreateLegend( TString, TString, TGraphErrors*, TGraphErrors* );     
   TPaveText *CreateCutText( string, TString );
      

private:
      
   float _lumi;
   
   vector<TString> _s_emulation_state, _s_eta_bin, _s_pT_bin, _s_fine_eta_bin;
   vector<float> _default_conditions_mu, _emulated_DW_2p5_mu, _default_conditions_mu_EB, _default_conditions_mu_EE, _emulated_DW_2p5_mu_EB, _emulated_DW_2p5_mu_EE;
      
   TString _histo_name, _histo_labels;
   
   float FWHM[Settings::num_of_emulation_states][Settings::num_of_eta_bins][Settings::num_of_pT_bins];


   TH1F *histograms_1D[Settings::num_of_1D_plot_names][Settings::num_of_emulation_states][Settings::num_of_eta_bins];
   TH1F *histograms_1D_pT_bins[Settings::num_of_emulation_states][Settings::num_of_eta_bins][Settings::num_of_pT_bins];
   TH1F *histograms_1D_eta_bins[Settings::num_of_emulation_states][Settings::num_of_fine_eta_bins];
   
   TGraphErrors *resolution[Settings::num_of_emulation_states][Settings::num_of_eta_bins];
   TGraphErrors *scale[Settings::num_of_emulation_states], *scale_vs_pT[Settings::num_of_emulation_states][Settings::num_of_eta_bins];
   
};
#endif
