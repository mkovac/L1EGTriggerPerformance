// Include classes
#include "L1EG.h"

// Constructor
//=================
L1EG::L1EG():Tree()
{
   histograms = new Histograms();
   _current_emulation_state = -999;
   
}
//=================


// Destructor
//===========
L1EG::~L1EG()
{
}
//===========



//==================================================
void L1EG::MakeHistograms( TString input_file_name )
{
   
   // Find current emulation state
   _current_emulation_state = FindCurrentEmulationState( input_file_name );
   
   cout << "_current_emulation_state = " << _current_emulation_state << endl;


   input_file = new TFile(input_file_name);

   input_tree = (TTree*)input_file->Get("Ntuplizer/TagAndProbe");
   Init(input_tree);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
   cout << "[nentries] " << nentries << endl << endl;



   for( Long64_t jentry = 0; jentry<nentries; jentry++ )
   {
      Long64_t ientry = LoadTree(jentry);
      if( ientry < 0 ) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      
      if( l1tEmuPt == -1 ) continue;
      
//      cout << "[EventNumber] " << EventNumber << endl;
//      cout << "[pT at 0] " << allEl_Pt->at(0) << endl;
//      cout << "[pT at 1] " << allEl_Pt->at(1) << endl;


      // Fill histograms
      histograms->FillScaleAndPt( l1tEmuPt, eleProbePt, eleProbeEta, _current_emulation_state );

      
   } // end for loop

   cout << "[INFO] Histograms for " << input_file_name << " filled." << endl;
}
//==================================================



//===============
void L1EG::Save()
{
   system("mkdir -p ROOT_files");
   histograms->SaveHistograms("ROOT_files/Histograms.root");

   cout << "[INFO] All histograms are saved in a root file." << endl;
}
//===============



//========================
void L1EG::GetHistograms()
{
   histograms->GetHistograms("ROOT_files/Histograms.root");

   cout << "[INFO] Got all histograms." << endl;
}
//========================



//=================
void L1EG::Delete()
{
//   histograms->DeleteHistos();
//
//   cout << "[INFO] Memory clean-up done." << endl;
}
//=================



//==========================================================================================
void L1EG::PlotHistograms1D( TString variable_name, TString emulation_name, TString folder )
{
   histograms->PlotHistograms1D( variable_name, emulation_name, folder );

}
//==========================================================================================



//=========================================================================
void L1EG::PlotHistograms1DpTBins( TString emulation_name, TString folder )
{
   histograms->PlotHistograms1DpTBins( emulation_name, folder );

}
//=========================================================================



//==========================================================================
void L1EG::PlotHistograms1DEtaBins( TString emulation_name, TString folder )
{
   histograms->PlotHistograms1DEtaBins( emulation_name, folder );

}
//==========================================================================



//================================================
void L1EG::CalculateFWHM( TString emulation_name )
{
   histograms->CalculateFWHM( emulation_name );

}
//================================================



//=====================================================================
void L1EG::PlotResolution( TString emulation_name, TString plots_path )
{
   histograms->PlotResolution( emulation_name, plots_path );

}
//=====================================================================



//=====================================================================
void L1EG::PlotScaleVsEta( TString emulation_name, TString plots_path )
{
   histograms->PlotScaleVsEta( emulation_name, plots_path );

}
//=====================================================================



//=====================================================================
void L1EG::PlotScaleVsPt( TString emulation_name, TString plots_path )
{
   histograms->PlotScaleVsPt( emulation_name, plots_path );

}
//=====================================================================



//========================================================================
void L1EG::FitEnergyScalePtBins( TString emulation_name, TString fits_path )
{
   histograms->FitEnergyScalePtBins( emulation_name, fits_path );

}
//========================================================================



//=========================================================================
void L1EG::FitEnergyScaleEtaBins( TString emulation_name, TString fits_path )
{
   histograms->FitEnergyScaleEtaBins( emulation_name, fits_path );

}
//=========================================================================



//===========================================================
int L1EG::FindCurrentEmulationState( TString input_file_name)
{

   int current_emulation_state = -999;

   // Assign dataset to correct emulation state
   if( input_file_name.Contains("TnP_L1_emulated") )        current_emulation_state = Settings::default_conditions;
   if( input_file_name.Contains("TnP_L1_emulated_DW_2p5") ) current_emulation_state = Settings::emulated_DW_2p5;
   // End assign dataset to correct emulation state

   return current_emulation_state;
   
}
//===========================================================
