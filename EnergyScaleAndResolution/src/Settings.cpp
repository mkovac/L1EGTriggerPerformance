// Include classes
#include "Settings.h"

// Constructor
//=====================
Settings::Settings() {}
//=====================


//======================
Settings::~Settings() {}
//======================


//=====================================================
int Settings::SetVariableIndex( TString variable_name )
{

   if ( variable_name == "energy_scale" )    return Settings::energy_scale;
   else if ( variable_name == "l1tEmuPt" )   return Settings::l1tEmuPt;
   else if ( variable_name == "eleProbePt" ) return Settings::eleProbePt;
   else
   {
      cout << "[ERROR] Wrong variable name choosen!" << endl;
      //abort;
      return Settings::energy_scale;
   }
}
//=====================================================



//=======================================================
int Settings::SetEmulationIndex( TString emulation_name )
{

   if ( emulation_name == "default_conditions" )   return Settings::default_conditions;
   else if ( emulation_name == "emulated_DW_2p5" ) return Settings::emulated_DW_2p5;
   else
   {
      cout << "[ERROR] Wrong variable name choosen!" << endl;
      //abort;
      return Settings::default_conditions;
   }
}
//=======================================================



//========================================
int Settings::SetPtIndex( TString pT_bin )
{

   if ( pT_bin == "pT_5_10" )   return Settings::pT_5_10;
   else if ( pT_bin == "pT_10_15" ) return Settings::pT_10_15;
   else if ( pT_bin == "pT_15_20" ) return Settings::pT_15_20;
   else if ( pT_bin == "pT_20_25" ) return Settings::pT_20_25;
   else if ( pT_bin == "pT_25_30" ) return Settings::pT_25_30;
   else if ( pT_bin == "pT_30_35" ) return Settings::pT_30_35;
   else if ( pT_bin == "pT_35_40" ) return Settings::pT_35_40;
   else if ( pT_bin == "pT_40_50" ) return Settings::pT_40_50;
   else if ( pT_bin == "pT_50_60" ) return Settings::pT_50_60;
   else if ( pT_bin == "pT_60_70" ) return Settings::pT_60_70;
   else if ( pT_bin == "pT_70_80" ) return Settings::pT_70_80;
   else if ( pT_bin == "pT_80_90" ) return Settings::pT_80_90;
   else if ( pT_bin == "pT_90_100" ) return Settings::pT_90_100;
   else
   {
      cout << "[ERROR] Wrong variable name choosen!" << endl;
      //abort;
      return Settings::pT_5_10;
   }
}
//========================================
