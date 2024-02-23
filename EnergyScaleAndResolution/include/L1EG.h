#ifndef Plotter_h
#define Plotter_h

// C++
#include <iostream>
#include <fstream>
#include <iomanip> // For setprecision
#include <vector>
#include <map>
#include <cstdlib>

// ROOT
#include "TApplication.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TColor.h"

// Include classes
#include "Tree.h"
#include "Settings.h"
#include "Histograms.h"


using namespace std;

class L1EG: public Tree
{

public:
	
	L1EG();
	~L1EG();
   
   void MakeHistograms( TString );
   void Save();
   void Delete();
   void GetHistograms();
   void PlotHistograms1D( TString, TString, TString );
   void PlotHistograms1DpTBins( TString, TString );
   void PlotHistograms1DEtaBins( TString, TString );
   
   void CalculateFWHM( TString );
   void PlotResolution( TString, TString );
   void PlotScaleVsEta( TString, TString );
   void PlotScaleVsPt( TString, TString );
      
   void FitEnergyScalePtBins( TString, TString);
   void FitEnergyScaleEtaBins( TString, TString);

   int FindCurrentEmulationState( TString );

//   void plot_1D_single( TString, TString, TString, int, int );
//   void plot_2D_single( TString, TString, TString, int );

   
private:

   TFile *input_file;
   TTree *input_tree;

   Histograms *histograms;
   
   int _current_emulation_state;
 
};
#endif
