#ifndef Variables_h
#define Variables_h

// C++
#include <iostream>
#include <vector>

// ROOT
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"


using namespace std;

class Variables
{
   
public:
   Variables ();
   ~Variables();

   
//===========
// Resolution
//===========
   
   struct energy_scale
   {
      TString var_X_label    = "p_{T}^{e/#gamma, L1}/p_{T}^{e, offline}";
      TString var_X2_label   = "p_{T}^{e, offline} [GeV]";
      TString var_X3_label   = "#eta^{e, offline}";
      TString var_Y_label    = "Events";
      TString var_Y2_label   = "Energy scale";
      TString var_cut_label  = "";
      Int_t var_N_bin        = 50;
      Float_t var_min        = 0;
      Float_t var_max        = 2;
      Bool_t var_log_x       = 0;
      Bool_t var_log_y       = 0;
      Int_t var_CMS_pos      = 0;
      Int_t varLegPos        = 33;
   };
   
   
   struct energy_resolution
   {
      TString var_X_label    = "p_{T}^{e, offline} [GeV]";
      TString var_Y_label    = "Energy resolution";
      TString var_cut_label  = "";
      Int_t var_N_bin        = 100;
      Float_t var_min        = 0;
      Float_t var_max        = 100;
      Bool_t var_log_x       = 0;
      Bool_t var_log_y       = 0;
      Int_t var_CMS_pos      = 0;
      Int_t varLegPos        = 33;
   };
   
   struct pT
   {
      TString var_X_label    = "p_{T}";
      TString var_Y_label    = "Events";
      TString var_cut_label  = "";
      Int_t var_N_bin        = 100;
      Float_t var_min        = 0;
      Float_t var_max        = 100;
      Bool_t var_log_x       = 0;
      Bool_t var_log_y       = 0;
      Int_t var_CMS_pos      = 0;
      Int_t varLegPos        = 33;
   };
   
   
};
#endif
