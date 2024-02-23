#ifndef Settings_h
#define Settings_h

// C++
#include <iostream>

#include "TString.h"


using namespace std;

class Settings
{

public:

   Settings();
   ~Settings();

   static int SetVariableIndex( TString );
   static int SetEmulationIndex( TString );
   static int SetPtIndex( TString );


   enum _1D_plot_name
   {
      energy_scale      = 0,
      energy_resolution = 1,
      l1tEmuPt          = 2,
      eleProbePt        = 3,
      MAX_NUM_OF_1D_PLOT_NAMES
   };

   enum _2D_plot_name
   {
      MZ1vsMZ2           = 0,
      MZ1vsMZ2_M4L118130 = 1,
      MAX_NUM_OF_2D_PLOT_NAMES
   };


   enum _emulation_state
   {
      default_conditions  = 0,
      emulated_DW_2p5     = 1,
      MAX_NUM_OF_EMULATION_STATES
   };

   enum _eta_bins
   {
      ECAL_barrel  = 0,
      ECAL_endcap  = 1,
      MAX_NUM_OF_ETA_BINS
   };

   enum _fine_eta_bins
   {
      eta_0p0_0p1  = 0,
      eta_0p1_0p2  = 1,
      eta_0p2_0p3  = 2,
      eta_0p3_0p4  = 3,
      eta_0p4_0p5  = 4,
      eta_0p5_0p6  = 5,
      eta_0p6_0p7  = 6,
      eta_0p7_0p8  = 7,
      eta_0p8_0p9  = 8,
      eta_0p9_1p0  = 9,
      eta_1p0_1p1  = 10,
      eta_1p1_1p2  = 11,
      eta_1p2_1p3  = 12,
      eta_1p3_1p5  = 13,
      eta_1p5_1p6  = 14,
      eta_1p6_1p7  = 15,
      eta_1p7_1p8  = 16,
      eta_1p8_1p9  = 17,
      eta_1p9_2p0  = 18,
      eta_2p0_2p1  = 19,
      eta_2p1_2p2  = 20,
      eta_2p2_2p3  = 21,
      eta_2p3_2p4  = 22,
      eta_2p4_2p5  = 23,
      MAX_NUM_OF_FINE_ETA_BINS
   };
   
   enum _pT_bins
   {
      pT_5_10   = 0,
      pT_10_15  = 1,
      pT_15_20  = 2,
      pT_20_25  = 3,
      pT_25_30  = 4,
      pT_30_35  = 5,
      pT_35_40  = 6,
      pT_40_50  = 7,
      pT_50_60  = 8,
      pT_60_70  = 9,
      pT_70_80  = 10,
      pT_80_90  = 11,
      pT_90_100 = 12,
      MAX_NUM_OF_PT_BINS
   };


   static const int num_of_emulation_states = MAX_NUM_OF_EMULATION_STATES;
   static const int num_of_1D_plot_names    = MAX_NUM_OF_1D_PLOT_NAMES;
   static const int num_of_2D_plot_names    = MAX_NUM_OF_2D_PLOT_NAMES;
   static const int num_of_eta_bins         = MAX_NUM_OF_ETA_BINS;
   static const int num_of_fine_eta_bins    = MAX_NUM_OF_FINE_ETA_BINS;
   static const int num_of_pT_bins          = MAX_NUM_OF_PT_BINS;

   
   private:

};

#endif