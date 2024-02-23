// C++
#include <iostream>
#include <fstream>
#include <string>

// ROOT
#include "TApplication.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"

// My own files
#include "include/L1EG.h"
//#include "src/setTDRStyle.cpp"

using namespace std;

//int main( int argc, char *argv[] )
int main()
{
//   setTDRStyle();

   TString eos_path     = "/eos/user/m/mkovac/Production/RUN_3/ECAL/17022024_CMSSW_13_3_0/EGamma1/";
   
   TString scale_plots_path        = "Results/Plots/Scale/";
   TString misc_plots_path         = "Results/Plots/Misc/";
   TString resolution_plots_path   = "Results/Plots/Resolution_vs_pT/";
   TString fits_pT_bins_path       = "Results/Fits/Scale_vs_pT/";
   TString fits_eta_bins_path      = "Results/Fits/Scale_vs_eta/";
   TString scale_vs_eta_plots_path = "Results/Plots/Scale_vs_eta/";
   TString scale_vs_pT_plots_path  = "Results/Plots/Scale_vs_pT/";


   TString path_default  = eos_path + "TnP_L1_emulated/240217_152727/0000/";
   TString path_emulated = eos_path + "TnP_L1_emulated_DW_2p5/240219_135547/0000/";

   TString root_default  = path_default  + "TnP_L1_emulated.root";
   TString root_emulated = path_emulated + "TnP_L1_emulated_DW_2p5.root";
 

   L1EG *l1eg = new L1EG();

//   l1eg->MakeHistograms(root_default);
//   l1eg->MakeHistograms(root_emulated);
//   l1eg->Save();

//   setTDRStyle(); // Needed to reset margins set by 2D histograms

   l1eg->GetHistograms();

//   l1eg->PlotHistograms1D("energy_scale", "default_conditions", scale_plots_path);
//   l1eg->PlotHistograms1D("l1tEmuPt",     "default_conditions", misc_plots_path);
//   l1eg->PlotHistograms1D("eleProbePt",   "default_conditions", misc_plots_path);
//   
//   l1eg->PlotHistograms1D("energy_scale", "emulated_DW_2p5", scale_plots_path);
//   l1eg->PlotHistograms1D("l1tEmuPt",     "emulated_DW_2p5", misc_plots_path);
//   l1eg->PlotHistograms1D("eleProbePt",   "emulated_DW_2p5", misc_plots_path);
//   
//   l1eg->PlotHistograms1DpTBins("default_conditions", scale_plots_path);
//   l1eg->PlotHistograms1DpTBins("emulated_DW_2p5",    scale_plots_path);
//   
//   l1eg->PlotHistograms1DEtaBins("default_conditions", scale_plots_path);
//   l1eg->PlotHistograms1DEtaBins("emulated_DW_2p5",    scale_plots_path);
   
   l1eg->CalculateFWHM("default_conditions");
   l1eg->CalculateFWHM("emulated_DW_2p5");
   
   l1eg->FitEnergyScalePtBins("default_conditions", fits_pT_bins_path);
   l1eg->FitEnergyScalePtBins("emulated_DW_2p5",    fits_pT_bins_path);
   
   l1eg->FitEnergyScaleEtaBins("default_conditions", fits_eta_bins_path);
   l1eg->PlotScaleVsPt("default_conditions", scale_vs_pT_plots_path);
   
   l1eg->FitEnergyScaleEtaBins("emulated_DW_2p5",    fits_eta_bins_path);
   l1eg->PlotScaleVsPt("emulated_DW_2p5",    scale_vs_pT_plots_path);   
   
   l1eg->PlotResolution("default_conditions", resolution_plots_path);
   l1eg->PlotResolution("emulated_DW_2p5",    resolution_plots_path);

   l1eg->PlotScaleVsEta("default_vs_emulated_DW_2p5", scale_vs_eta_plots_path);
   
   
   
//   setTDRStyle();

   delete l1eg;
}