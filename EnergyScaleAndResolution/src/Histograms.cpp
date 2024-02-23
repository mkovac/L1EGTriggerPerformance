#include "Histograms.h"

#include <TROOT.h>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// Constructor
//====================================================
Histograms::Histograms()
{
   

   _s_emulation_state.push_back("default_conditions");
   _s_emulation_state.push_back("emulated_DW_2p5");
   
   _s_eta_bin.push_back("ECAL_barrel");
   _s_eta_bin.push_back("ECAL_endcap");
   
   _s_pT_bin.push_back("pT_5_10");
   _s_pT_bin.push_back("pT_10_15");
   _s_pT_bin.push_back("pT_15_20");
   _s_pT_bin.push_back("pT_20_25");
   _s_pT_bin.push_back("pT_25_30");
   _s_pT_bin.push_back("pT_30_35");
   _s_pT_bin.push_back("pT_35_40");
   _s_pT_bin.push_back("pT_40_50");
   _s_pT_bin.push_back("pT_50_60");
   _s_pT_bin.push_back("pT_60_70");   
   _s_pT_bin.push_back("pT_70_80");   
   _s_pT_bin.push_back("pT_80_90");   
   _s_pT_bin.push_back("pT_90_100");
   
   _s_fine_eta_bin.push_back("eta_0p0_0p1");
   _s_fine_eta_bin.push_back("eta_0p1_0p2");
   _s_fine_eta_bin.push_back("eta_0p2_0p3");
   _s_fine_eta_bin.push_back("eta_0p3_0p4");
   _s_fine_eta_bin.push_back("eta_0p4_0p5");
   _s_fine_eta_bin.push_back("eta_0p5_0p6");
   _s_fine_eta_bin.push_back("eta_0p6_0p7");
   _s_fine_eta_bin.push_back("eta_0p7_0p8");
   _s_fine_eta_bin.push_back("eta_0p8_0p9");
   _s_fine_eta_bin.push_back("eta_0p9_1p0");
   _s_fine_eta_bin.push_back("eta_1p0_1p1");
   _s_fine_eta_bin.push_back("eta_1p1_1p2");
   _s_fine_eta_bin.push_back("eta_1p2_1p3");
   _s_fine_eta_bin.push_back("eta_1p3_1p5");
   _s_fine_eta_bin.push_back("eta_1p5_1p6");
   _s_fine_eta_bin.push_back("eta_1p6_1p7");
   _s_fine_eta_bin.push_back("eta_1p7_1p8");
   _s_fine_eta_bin.push_back("eta_1p8_1p9");
   _s_fine_eta_bin.push_back("eta_1p9_2p0");
   _s_fine_eta_bin.push_back("eta_2p0_2p1");
   _s_fine_eta_bin.push_back("eta_2p1_2p2");
   _s_fine_eta_bin.push_back("eta_2p2_2p3");
   _s_fine_eta_bin.push_back("eta_2p3_2p4");
   _s_fine_eta_bin.push_back("eta_2p4_2p5");


   for ( int i_emul = 0; i_emul < Settings::num_of_emulation_states; i_emul++ )
   {
      for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
      {
         _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         _histo_labels = ";" + Variables::energy_scale().var_X_label + ";" + Variables::energy_scale().var_Y_label;
         histograms_1D[Settings::energy_scale][i_emul][i_eta] = new TH1F(_histo_name, _histo_labels, Variables::energy_scale().var_N_bin,
                                                                         Variables::energy_scale().var_min, Variables::energy_scale().var_max);
                                                                               
         _histo_name = "l1tEmuPt_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         _histo_labels = ";" + Variables::pT().var_X_label + ";" + Variables::pT().var_Y_label;
         histograms_1D[Settings::l1tEmuPt][i_emul][i_eta] = new TH1F(_histo_name, _histo_labels, Variables::pT().var_N_bin,
                                                                     Variables::pT().var_min, Variables::pT().var_max);

         _histo_name = "eleProbePt_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         _histo_labels = ";" + Variables::pT().var_X_label + ";" + Variables::pT().var_Y_label;
         histograms_1D[Settings::eleProbePt][i_emul][i_eta] = new TH1F(_histo_name, _histo_labels, Variables::pT().var_N_bin,
                                                                       Variables::pT().var_min, Variables::pT().var_max);
                                                                                            
         for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
         {
            _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta) + "_" + _s_pT_bin.at(i_pT);
            _histo_labels = ";" + Variables::energy_scale().var_X_label + ";" + Variables::energy_scale().var_Y_label;
            histograms_1D_pT_bins[i_emul][i_eta][i_pT] = new TH1F(_histo_name, _histo_labels, Variables::energy_scale().var_N_bin,
                                                                  Variables::energy_scale().var_min, Variables::energy_scale().var_max);
         }// end i_pT
      }// end i_eta
   
      for ( int i_fine_eta = 0; i_fine_eta < Settings::num_of_fine_eta_bins; i_fine_eta++ )
      {
         _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_fine_eta_bin.at(i_fine_eta);
         _histo_labels = ";" + Variables::energy_scale().var_X_label + ";" + Variables::energy_scale().var_Y_label;
         histograms_1D_eta_bins[i_emul][i_fine_eta] = new TH1F(_histo_name, _histo_labels, Variables::energy_scale().var_N_bin,
                                                               Variables::energy_scale().var_min, Variables::energy_scale().var_max);
      }// end i_fine_eta
   }// end i_emul
   
}
//==================================




//=======================
Histograms::~Histograms()
{
}
//=======================



//====
// M4l
//====================================================================================
void Histograms::FillScaleAndPt( float l1tEmuPt, float eleProbePt, float eleProbeEta, int emul_state )
{

   double ratio = l1tEmuPt/double(eleProbePt);
      
   if ( abs(eleProbeEta) < 1.440 )
   {
      if ( eleProbePt > 32 )
      {
         histograms_1D[Settings::energy_scale][emul_state][Settings::ECAL_barrel]->Fill(ratio);
         histograms_1D[Settings::l1tEmuPt][emul_state][Settings::ECAL_barrel]->Fill(l1tEmuPt);
         histograms_1D[Settings::eleProbePt][emul_state][Settings::ECAL_barrel]->Fill(eleProbePt);
      }
      
      if      ( eleProbePt >= 5 && eleProbePt < 10 )   histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_5_10]->Fill(ratio);
      else if ( eleProbePt >= 10 && eleProbePt < 15 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_10_15]->Fill(ratio);
      else if ( eleProbePt >= 15 && eleProbePt < 20 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_15_20]->Fill(ratio);
      else if ( eleProbePt >= 20 && eleProbePt < 25 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_20_25]->Fill(ratio);
      else if ( eleProbePt >= 25 && eleProbePt < 30 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_25_30]->Fill(ratio);
      else if ( eleProbePt >= 30 && eleProbePt < 35 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_30_35]->Fill(ratio);
      else if ( eleProbePt >= 35 && eleProbePt < 40 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_35_40]->Fill(ratio);
      else if ( eleProbePt >= 40 && eleProbePt < 50 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_40_50]->Fill(ratio);
      else if ( eleProbePt >= 50 && eleProbePt < 60 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_50_60]->Fill(ratio);
      else if ( eleProbePt >= 60 && eleProbePt < 70 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_60_70]->Fill(ratio);
      else if ( eleProbePt >= 70 && eleProbePt < 80 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_70_80]->Fill(ratio);
      else if ( eleProbePt >= 80 && eleProbePt < 90 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_80_90]->Fill(ratio);
      else if ( eleProbePt >= 90 && eleProbePt < 100 ) histograms_1D_pT_bins[emul_state][Settings::ECAL_barrel][Settings::pT_90_100]->Fill(ratio);
   }
   else if ( 1.479 < abs(eleProbeEta) && abs(eleProbeEta) < 2.5 )
   {
      if ( eleProbePt > 32 )
      {
         histograms_1D[Settings::energy_scale][emul_state][Settings::ECAL_endcap]->Fill(ratio);
         histograms_1D[Settings::l1tEmuPt][emul_state][Settings::ECAL_endcap]->Fill(l1tEmuPt);
         histograms_1D[Settings::eleProbePt][emul_state][Settings::ECAL_endcap]->Fill(eleProbePt);
      }
      
      if      ( eleProbePt >= 5 && eleProbePt < 10 )   histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_5_10]->Fill(ratio);
      else if ( eleProbePt >= 10 && eleProbePt < 15 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_10_15]->Fill(ratio);
      else if ( eleProbePt >= 15 && eleProbePt < 20 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_15_20]->Fill(ratio);
      else if ( eleProbePt >= 20 && eleProbePt < 25 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_20_25]->Fill(ratio);
      else if ( eleProbePt >= 25 && eleProbePt < 30 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_25_30]->Fill(ratio);
      else if ( eleProbePt >= 30 && eleProbePt < 35 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_30_35]->Fill(ratio);
      else if ( eleProbePt >= 35 && eleProbePt < 40 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_35_40]->Fill(ratio);
      else if ( eleProbePt >= 40 && eleProbePt < 50 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_40_50]->Fill(ratio);
      else if ( eleProbePt >= 50 && eleProbePt < 60 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_50_60]->Fill(ratio);
      else if ( eleProbePt >= 60 && eleProbePt < 70 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_60_70]->Fill(ratio);
      else if ( eleProbePt >= 70 && eleProbePt < 80 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_70_80]->Fill(ratio);
      else if ( eleProbePt >= 80 && eleProbePt < 90 )  histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_80_90]->Fill(ratio);
      else if ( eleProbePt >= 90 && eleProbePt < 100 ) histograms_1D_pT_bins[emul_state][Settings::ECAL_endcap][Settings::pT_90_100]->Fill(ratio);
   }
   
   if      (eleProbeEta >= 0.0 && eleProbeEta < 0.1) histograms_1D_eta_bins[emul_state][Settings::eta_0p0_0p1]->Fill(ratio);
   else if (eleProbeEta >= 0.1 && eleProbeEta < 0.2) histograms_1D_eta_bins[emul_state][Settings::eta_0p1_0p2]->Fill(ratio);
   else if (eleProbeEta >= 0.2 && eleProbeEta < 0.3) histograms_1D_eta_bins[emul_state][Settings::eta_0p2_0p3]->Fill(ratio);
   else if (eleProbeEta >= 0.3 && eleProbeEta < 0.4) histograms_1D_eta_bins[emul_state][Settings::eta_0p3_0p4]->Fill(ratio);
   else if (eleProbeEta >= 0.4 && eleProbeEta < 0.5) histograms_1D_eta_bins[emul_state][Settings::eta_0p4_0p5]->Fill(ratio);
   else if (eleProbeEta >= 0.5 && eleProbeEta < 0.6) histograms_1D_eta_bins[emul_state][Settings::eta_0p5_0p6]->Fill(ratio);
   else if (eleProbeEta >= 0.6 && eleProbeEta < 0.7) histograms_1D_eta_bins[emul_state][Settings::eta_0p6_0p7]->Fill(ratio);
   else if (eleProbeEta >= 0.7 && eleProbeEta < 0.8) histograms_1D_eta_bins[emul_state][Settings::eta_0p7_0p8]->Fill(ratio);
   else if (eleProbeEta >= 0.8 && eleProbeEta < 0.9) histograms_1D_eta_bins[emul_state][Settings::eta_0p8_0p9]->Fill(ratio);
   else if (eleProbeEta >= 0.9 && eleProbeEta < 1.0) histograms_1D_eta_bins[emul_state][Settings::eta_0p9_1p0]->Fill(ratio);
   else if (eleProbeEta >= 1.0 && eleProbeEta < 1.1) histograms_1D_eta_bins[emul_state][Settings::eta_1p0_1p1]->Fill(ratio);
   else if (eleProbeEta >= 1.1 && eleProbeEta < 1.2) histograms_1D_eta_bins[emul_state][Settings::eta_1p1_1p2]->Fill(ratio);
   else if (eleProbeEta >= 1.2 && eleProbeEta < 1.3) histograms_1D_eta_bins[emul_state][Settings::eta_1p2_1p3]->Fill(ratio);
   else if (eleProbeEta >= 1.3 && eleProbeEta < 1.5) histograms_1D_eta_bins[emul_state][Settings::eta_1p3_1p5]->Fill(ratio);
   else if (eleProbeEta >= 1.5 && eleProbeEta < 1.6) histograms_1D_eta_bins[emul_state][Settings::eta_1p5_1p6]->Fill(ratio);
   else if (eleProbeEta >= 1.6 && eleProbeEta < 1.7) histograms_1D_eta_bins[emul_state][Settings::eta_1p6_1p7]->Fill(ratio);
   else if (eleProbeEta >= 1.7 && eleProbeEta < 1.8) histograms_1D_eta_bins[emul_state][Settings::eta_1p7_1p8]->Fill(ratio);
   else if (eleProbeEta >= 1.8 && eleProbeEta < 1.9) histograms_1D_eta_bins[emul_state][Settings::eta_1p8_1p9]->Fill(ratio);
   else if (eleProbeEta >= 1.9 && eleProbeEta < 2.0) histograms_1D_eta_bins[emul_state][Settings::eta_1p9_2p0]->Fill(ratio);
   else if (eleProbeEta >= 2.0 && eleProbeEta < 2.1) histograms_1D_eta_bins[emul_state][Settings::eta_2p0_2p1]->Fill(ratio);
   else if (eleProbeEta >= 2.1 && eleProbeEta < 2.2) histograms_1D_eta_bins[emul_state][Settings::eta_2p1_2p2]->Fill(ratio);
   else if (eleProbeEta >= 2.2 && eleProbeEta < 2.3) histograms_1D_eta_bins[emul_state][Settings::eta_2p2_2p3]->Fill(ratio);
   else if (eleProbeEta >= 2.3 && eleProbeEta < 2.4) histograms_1D_eta_bins[emul_state][Settings::eta_2p3_2p4]->Fill(ratio);
   else if (eleProbeEta >= 2.4 && eleProbeEta < 2.5) histograms_1D_eta_bins[emul_state][Settings::eta_2p4_2p5]->Fill(ratio);
    
   
//   cout << "[Resolution]" << ratio << endl;
//   cout << "[l1tEmuPt]" << l1tEmuPt << endl;
//   cout << "[eleProbePt]" << eleProbePt << endl;

}
//====================================================================================



//=============================================
void Histograms::SaveHistograms( string file_name )
{
   TFile *fOutHistos = new TFile(file_name.c_str(), "recreate");
   fOutHistos->cd();

   for (int i_emul = 0; i_emul < Settings::num_of_emulation_states; i_emul++)
   {
      for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
      {
         histograms_1D[Settings::energy_scale][i_emul][i_eta]->Scale(1./histograms_1D[Settings::energy_scale][i_emul][i_eta]->Integral());
         histograms_1D[Settings::l1tEmuPt][i_emul][i_eta]    ->Scale(1./histograms_1D[Settings::l1tEmuPt][i_emul][i_eta]    ->Integral());
         histograms_1D[Settings::eleProbePt][i_emul][i_eta]  ->Scale(1./histograms_1D[Settings::eleProbePt][i_emul][i_eta]  ->Integral());
         
         histograms_1D[Settings::energy_scale][i_emul][i_eta]->Write();
         histograms_1D[Settings::l1tEmuPt][i_emul][i_eta]    ->Write();
         histograms_1D[Settings::eleProbePt][i_emul][i_eta]  ->Write();
         
         for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
         {
            histograms_1D_pT_bins[i_emul][i_eta][i_pT]->Scale(1./histograms_1D_pT_bins[i_emul][i_eta][i_pT]->Integral());
            histograms_1D_pT_bins[i_emul][i_eta][i_pT]->Write();
         }
      }
      
      for ( int i_fine_eta = 0; i_fine_eta < Settings::num_of_fine_eta_bins; i_fine_eta++ )
      {
         histograms_1D_eta_bins[i_emul][i_fine_eta]->Scale(1./histograms_1D_eta_bins[i_emul][i_fine_eta]->Integral());;
         histograms_1D_eta_bins[i_emul][i_fine_eta]->Write();
      }
   }

   fOutHistos->Close();
   delete fOutHistos;
}
//=============================================



//=============================
void Histograms::DeleteHistograms()
{

//   for ( int i_emul = 0; i_emul < Settings::num_of_emulation_states; i_emul++ )
//   {
//      for ( int i_1Dhistos = 0; i_1Dhistos < Settings::num_of_1D_plot_names; i_1Dhistos++ )
//      {
//         delete histograms_1D[i_1Dhistos][i_emul];
//      }
//   }

}
//=============================



//=============================================
void Histograms::GetHistograms( TString file_name )
{
   TFile* histo_file = TFile::Open(file_name);

   for (int i_emul = 0; i_emul < Settings::num_of_emulation_states; i_emul++)
   {
      for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
      {
         _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         histograms_1D[Settings::energy_scale][i_emul][i_eta] = (TH1F*)histo_file->Get(_histo_name);
      
         _histo_name = "l1tEmuPt_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         histograms_1D[Settings::l1tEmuPt][i_emul][i_eta] = (TH1F*)histo_file->Get(_histo_name);
      
         _histo_name = "eleProbePt_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta);
         histograms_1D[Settings::eleProbePt][i_emul][i_eta] = (TH1F*)histo_file->Get(_histo_name);
         
         for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
         {
            _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_eta_bin.at(i_eta) + "_" + _s_pT_bin.at(i_pT);
            histograms_1D_pT_bins[i_emul][i_eta][i_pT] = (TH1F*)histo_file->Get(_histo_name);
         }
      }
      
      for ( int i_fine_eta = 0; i_fine_eta < Settings::num_of_fine_eta_bins; i_fine_eta++ )
      {
         _histo_name = "Energy_scale_" + _s_emulation_state.at(i_emul) + "_" + _s_fine_eta_bin.at(i_fine_eta);
         histograms_1D_eta_bins[i_emul][i_fine_eta] = (TH1F*)histo_file->Get(_histo_name);
      }
   }
}
//=============================================



//==================================
//void Histograms::ScaleHistograms1D()
//{
//
//   for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
//   {
//      for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
//      {
//         for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
//         { 
//            histograms_1D[i_variable][i_emulation][i_eta]->Scale(1. / histograms_1D[i_variable][i_emulation][i_eta]->Integral());
//         }
//      }
//   }
//
//}
//==================================




//====================================================================================================
void Histograms::PlotHistograms1D( TString variable_name, TString emulation_name, TString plots_path )
{

   int i_variable  = Settings::SetVariableIndex(variable_name);
   int i_emulation = Settings::SetEmulationIndex(emulation_name);


   TCanvas *canvas = new TCanvas(variable_name, variable_name, 600, 600);

   for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
   { 
      if (variable_name == "energy_scale")
      {         
         histograms_1D[i_variable][i_emulation][i_eta]->SetMarkerSize(2);
//         histograms_1D[i_variable][i_emulation][i_eta]->Scale(1. / histograms_1D[i_variable][i_emulation][i_eta]->Integral());
         histograms_1D[i_variable][i_emulation][i_eta]->Draw("p E1 X0 SAME");
      }
      else
      {
//         histograms_1D[i_variable][i_emulation][i_eta]->Scale(1. / histograms_1D[i_variable][i_emulation][i_eta]->Integral());
         histograms_1D[i_variable][i_emulation][i_eta]->Draw("HIST SAME");
      }
   }

   TString out_file_name = plots_path  + variable_name + "_" + emulation_name;
   SavePlots(canvas, out_file_name, plots_path);
   delete canvas;
}
//====================================================================================================



//===================================================================================
void Histograms::PlotHistograms1DpTBins( TString emulation_name, TString plots_path )
{

   int i_emulation = Settings::SetEmulationIndex(emulation_name);


   for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
   {
      
      TCanvas *canvas = new TCanvas("Scale", "Scale", 600, 600);
      
      for ( int i_eta = 0; i_eta < Settings::num_of_eta_bins; i_eta++ )
      {
         histograms_1D_pT_bins[i_emulation][i_eta][i_pT]->SetMarkerSize(2);
//         histograms_1D_pT_bins[i_emulation][i_eta][i_pT]->Scale(1. / histograms_1D_pT_bins[i_emulation][i_eta][i_pT]->Integral());
         histograms_1D_pT_bins[i_emulation][i_eta][i_pT]->Draw("p E1 X0 SAME");
      }// end for i_eta
      
      TString out_file_name = plots_path + emulation_name + "_" + _s_pT_bin.at(i_pT);
      SavePlots(canvas, out_file_name, plots_path);
      delete canvas;
 
   }// end for i_pT

}
//===================================================================================



//====================================================================================
void Histograms::PlotHistograms1DEtaBins( TString emulation_name, TString plots_path )
{
   
   int i_emulation = Settings::SetEmulationIndex(emulation_name);

   for ( int i_fine_eta = 0; i_fine_eta < Settings::num_of_fine_eta_bins; i_fine_eta++ )
   {
      TCanvas *canvas = new TCanvas("Scale", "Scale", 600, 600);
      
      histograms_1D_eta_bins[i_emulation][i_fine_eta]->SetMarkerSize(2);
//      histograms_1D_eta_bins[i_emulation][i_fine_eta]->Scale(1. / histograms_1D_eta_bins[i_emulation][i_fine_eta]->Integral());
      histograms_1D_eta_bins[i_emulation][i_fine_eta]->Draw("p E1 X0 SAME");
      
      TString out_file_name = plots_path + emulation_name + "_" + _s_fine_eta_bin.at(i_fine_eta);
      SavePlots(canvas, out_file_name, plots_path);
      delete canvas;
   }

}
//====================================================================================



//==========================================================================
void Histograms::PlotResolution( TString emulation_name, TString plots_path )
{

   int i_emulation = Settings::SetEmulationIndex(emulation_name);

   auto canvas = new TCanvas("Energy resolution","Energy resolution", 650, 500);
   auto multigraph = new TMultiGraph();
   
   const int n = 13;
   
   float x[n] = {7.5, 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 45, 55, 65, 75, 85, 95};
   
   float ex[n] = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 5, 5, 5, 5, 5, 5};
   
   float ey[n] = {0};
   
   resolution[i_emulation][Settings::ECAL_barrel] = new TGraphErrors( n, x, &FWHM[i_emulation][Settings::ECAL_barrel][0], ex, ey );
   resolution[i_emulation][Settings::ECAL_endcap] = new TGraphErrors( n, x, &FWHM[i_emulation][Settings::ECAL_endcap][0], ex, ey );
   
//   resolution[i_emulation][Settings::ECAL_barrel]->SetTitle("TGraphAsymmErrors Example");
//   resolution[i_emulation][Settings::ECAL_endcap]->SetTitle("TGraphAsymmErrors Example");
   
   resolution[i_emulation][Settings::ECAL_barrel]->SetMarkerColor(kRed-4);
   resolution[i_emulation][Settings::ECAL_barrel]->SetLineColor(kRed-4);
   resolution[i_emulation][Settings::ECAL_barrel]->SetMarkerStyle(20);
   
   resolution[i_emulation][Settings::ECAL_endcap]->SetMarkerColor(kAzure+2);
   resolution[i_emulation][Settings::ECAL_endcap]->SetLineColor(kAzure+2);
   resolution[i_emulation][Settings::ECAL_endcap]->SetMarkerStyle(21);
   
   multigraph->Add(resolution[i_emulation][Settings::ECAL_barrel]);
   multigraph->Add(resolution[i_emulation][Settings::ECAL_endcap]);
   
   multigraph->GetXaxis()->SetTitle(Variables::energy_resolution().var_X_label);
   multigraph->GetYaxis()->SetTitle(Variables::energy_resolution().var_Y_label);
  
   multigraph->Draw("AP");
   
   
   TLegend *legend;
   legend = CreateLegend("right", "eta", resolution[i_emulation][Settings::ECAL_barrel], resolution[i_emulation][Settings::ECAL_endcap]);
   legend->Draw();
 
//resolution_canvas->BuildLegend();

//   TPaveText *text;
//
//   if ( variable_name == "energy_scale" )
//   {
//      text = CreateCutText("right top", "p_{T}^{offline} > 0");
////      text->Draw();
//   }
  

//   CMS_lumi *lumi = new CMS_lumi;
//   lumi->set_lumi(c, _lumi);
   
   TString out_file_name = plots_path + "Resolution_vs_pT_" + emulation_name;
   SavePlots(canvas, out_file_name, plots_path);
   delete canvas;
}
//==========================================================================



//===========================================================================
void Histograms::PlotScaleVsEta( TString emulation_name, TString plots_path )
{
   auto canvas = new TCanvas("Energy scale","Energy scale", 650, 500);
   auto multigraph = new TMultiGraph();
   
   const int n = 24;
   
   vector<float> x{0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95, 1.05, 1.15, 1.25, 1.4, 1.55, 1.65, 1.75, 1.85, 1.95, 2.05, 2.15, 2.25, 2.35, 2.45};
   vector<float> ex{0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
   vector<float> ey{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   
   scale[Settings::default_conditions] = new TGraphErrors(n, &x[0], &_default_conditions_mu[0], &ex[0], &ey[0]);
   scale[Settings::emulated_DW_2p5]    = new TGraphErrors(n, &x[0], &_emulated_DW_2p5_mu[0],    &ex[0], &ey[0]);

   
   scale[Settings::default_conditions]->SetMarkerColor(kRed-4);
   scale[Settings::default_conditions]->SetLineColor(kRed-4);
   scale[Settings::default_conditions]->SetMarkerStyle(20);
   
   scale[Settings::emulated_DW_2p5]->SetMarkerColor(kAzure+2);
   scale[Settings::emulated_DW_2p5]->SetLineColor(kAzure+2);
   scale[Settings::emulated_DW_2p5]->SetMarkerStyle(21);
   
   multigraph->Add(scale[Settings::emulated_DW_2p5]);
   multigraph->Add(scale[Settings::default_conditions]);
   
   multigraph->GetXaxis()->SetTitle(Variables::energy_scale().var_X3_label);
   multigraph->GetYaxis()->SetTitle(Variables::energy_scale().var_Y2_label);
  
   multigraph->SetMinimum(0.9);
   multigraph->SetMaximum(1.2);
   multigraph->Draw("AP");
   
   
   TLegend *legend;
   legend = CreateLegend("right", "emulation", scale[Settings::default_conditions], scale[Settings::emulated_DW_2p5]);
   legend->Draw();
 
   
   TString out_file_name = plots_path + "Scale_" + emulation_name;
   SavePlots(canvas, out_file_name, plots_path);
   delete canvas;


}
//===========================================================================



//===========================================================================
void Histograms::PlotScaleVsPt( TString emulation_name, TString plots_path )
{
   
   int i_emulation = Settings::SetEmulationIndex(emulation_name);
   
   auto canvas = new TCanvas("Energy scale","Energy scale", 650, 500);
   auto multigraph = new TMultiGraph();
   
   const int n = 13;
   
   vector<float> x{7.5, 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 45, 55, 65, 75, 85, 95};
   vector<float> ex{2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 5, 5, 5, 5, 5, 5};
   vector<float> ey{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   
   if( emulation_name == "default_conditions" )
   {
      scale_vs_pT[i_emulation][Settings::ECAL_barrel] = new TGraphErrors(n, &x[0], &_default_conditions_mu_EB[0], &ex[0], &ey[0]);
      scale_vs_pT[i_emulation][Settings::ECAL_endcap] = new TGraphErrors(n, &x[0], &_default_conditions_mu_EE[0], &ex[0], &ey[0]);
   }
   if( emulation_name == "emulated_DW_2p5" )
   {
      scale_vs_pT[i_emulation][Settings::ECAL_barrel] = new TGraphErrors(n, &x[0], &_emulated_DW_2p5_mu_EB[0], &ex[0], &ey[0]);
      scale_vs_pT[i_emulation][Settings::ECAL_endcap] = new TGraphErrors(n, &x[0], &_emulated_DW_2p5_mu_EE[0], &ex[0], &ey[0]);  
   }

   
   scale_vs_pT[i_emulation][Settings::ECAL_barrel]->SetMarkerColor(kRed-4);
   scale_vs_pT[i_emulation][Settings::ECAL_barrel]->SetLineColor(kRed-4);
   scale_vs_pT[i_emulation][Settings::ECAL_barrel]->SetMarkerStyle(20);
   
   scale_vs_pT[i_emulation][Settings::ECAL_endcap]->SetMarkerColor(kAzure+2);
   scale_vs_pT[i_emulation][Settings::ECAL_endcap]->SetLineColor(kAzure+2);
   scale_vs_pT[i_emulation][Settings::ECAL_endcap]->SetMarkerStyle(21);
   
   multigraph->Add(scale_vs_pT[i_emulation][Settings::ECAL_barrel]);
   multigraph->Add(scale_vs_pT[i_emulation][Settings::ECAL_endcap]);
   
   multigraph->GetXaxis()->SetTitle(Variables::energy_scale().var_X2_label);
   multigraph->GetYaxis()->SetTitle(Variables::energy_scale().var_Y2_label);
  
   multigraph->SetMinimum(0.9);
   multigraph->SetMaximum(1.2);
   multigraph->Draw("AP");
   
   
   TLegend *legend;
   legend = CreateLegend("right", "eta", scale_vs_pT[i_emulation][Settings::ECAL_barrel], scale_vs_pT[i_emulation][Settings::ECAL_endcap]);
   legend->Draw();
 
   
   TString out_file_name = plots_path + "Scale_" + emulation_name;
   SavePlots(canvas, out_file_name, plots_path);
   delete canvas;


}
//===========================================================================



//=============================================================================
void Histograms::FitEnergyScalePtBins( TString emulation_name, TString fits_path)
{
   
   int i_emulation = Settings::SetEmulationIndex(emulation_name);
   
   Fitter *Fit = new Fitter(fits_path);
   
   for( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
   {
      Fit->Fit(histograms_1D_pT_bins[i_emulation][Settings::ECAL_barrel][i_pT],
               histograms_1D_pT_bins[i_emulation][Settings::ECAL_endcap][i_pT],
               emulation_name, _s_pT_bin.at(i_pT));
   }  
   
   Fit->Fit(histograms_1D[Settings::energy_scale][i_emulation][Settings::ECAL_barrel],
            histograms_1D[Settings::energy_scale][i_emulation][Settings::ECAL_endcap],
            emulation_name, "all");
   
   if( emulation_name == "default_conditions" )
   {
      _default_conditions_mu_EB = Fit->GetFitEnergyScaleEBpTBinsMu();
      _default_conditions_mu_EE = Fit->GetFitEnergyScaleEEpTBinsMu();
      
     cout << " mu = " << _default_conditions_mu_EB.at(0) << endl;
     cout << " mu = " << _default_conditions_mu_EB.at(1) << endl;
     cout << " mu = " << _default_conditions_mu_EB.at(2) << endl;
     cout << " mu = " << _default_conditions_mu_EB.at(3) << endl;
     
     cout << " mu = " << _default_conditions_mu_EE.at(0) << endl;
     cout << " mu = " << _default_conditions_mu_EE.at(1) << endl;
     cout << " mu = " << _default_conditions_mu_EE.at(2) << endl;
     cout << " mu = " << _default_conditions_mu_EE.at(3) << endl; 
   }
   if( emulation_name == "emulated_DW_2p5" )
   {
      _emulated_DW_2p5_mu_EB = Fit->GetFitEnergyScaleEBpTBinsMu();
      _emulated_DW_2p5_mu_EE = Fit->GetFitEnergyScaleEEpTBinsMu();
      
      
     cout << " mu = " << _emulated_DW_2p5_mu_EB.at(0) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EB.at(1) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EB.at(2) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EB.at(3) << endl;
     
     cout << " mu = " << _emulated_DW_2p5_mu_EE.at(0) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EE.at(1) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EE.at(2) << endl;
     cout << " mu = " << _emulated_DW_2p5_mu_EE.at(3) << endl; 
   }
   
   delete Fit;
   
}
//=============================================================================



//==============================================================================
void Histograms::FitEnergyScaleEtaBins( TString emulation_name, TString fits_path)
{
   
   int i_emulation = Settings::SetEmulationIndex(emulation_name);
   
   Fitter *Fit = new Fitter(fits_path);
   
   for (int i_fine_eta = 0; i_fine_eta < Settings::num_of_fine_eta_bins; i_fine_eta++)
   {
      Fit->Fit(histograms_1D_eta_bins[i_emulation][i_fine_eta], emulation_name, _s_fine_eta_bin.at(i_fine_eta));
   }
   
   if ( emulation_name == "default_conditions" ) _default_conditions_mu = Fit->GetFitEnergyScaleEtaBinsMu();
   if ( emulation_name == "emulated_DW_2p5" )    _emulated_DW_2p5_mu    = Fit->GetFitEnergyScaleEtaBinsMu();
            
   delete Fit;
      
//   for (float i : _default_conditions_mu)
//      cout << i << endl;
}
//==============================================================================



//======================================================
void Histograms::CalculateFWHM( TString emulation_name )
{
   
   int i_emulation = Settings::SetEmulationIndex(emulation_name);
      

   for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
   {
      TH1F *histogram_1 = (TH1F*)histograms_1D_pT_bins[i_emulation][Settings::ECAL_barrel][i_pT]->Clone();
      TH1F *histogram_2 = (TH1F*)histograms_1D_pT_bins[i_emulation][Settings::ECAL_endcap][i_pT]->Clone();
   
      int EB_bin_1 = histogram_1->FindFirstBinAbove(histogram_1->GetMaximum()/2);
      int EB_bin_2 = histogram_1->FindLastBinAbove(histogram_1->GetMaximum()/2);
   
      int EE_bin_1 = histogram_2->FindFirstBinAbove(histogram_2->GetMaximum()/2);
      int EE_bin_2 = histogram_2->FindLastBinAbove(histogram_2->GetMaximum()/2);
   
      double fwhm_EB = histogram_1->GetBinCenter(EB_bin_2) - histogram_1->GetBinCenter(EB_bin_1);
      double fwhm_EE = histogram_2->GetBinCenter(EE_bin_2) - histogram_2->GetBinCenter(EE_bin_1);
      
      FWHM[i_emulation][Settings::ECAL_barrel][i_pT] = fwhm_EB;
      FWHM[i_emulation][Settings::ECAL_endcap][i_pT] = fwhm_EE;

//      cout << "EB_bin_1 = " << EB_bin_1 << endl << "EB_bin_2 = " << EB_bin_2 << endl << "EE_bin_1 = " << EE_bin_1 << endl << "EE_bin_2 = " << EE_bin_2 << endl << endl;
   }
   
//   for ( int i_pT = 0; i_pT < Settings::num_of_pT_bins; i_pT++ )
//   {
//      cout << "FWHM barrel pT bin " << i_pT << " = " << FWHM[i_emulation][Settings::ECAL_barrel][i_pT] << endl;
//      cout << "FWHM endcap pT bin " << i_pT << " = " << FWHM[i_emulation][Settings::ECAL_endcap][i_pT] << endl;
//
//   }

}
//======================================================



//=======================================================================================
void Histograms::SavePlots( TCanvas *canvas, TString out_file_name,  TString plots_path )
{
//   system("mkdir -p " + plots_path);
   canvas->SaveAs(out_file_name + ".pdf");
//   canvas->SaveAs(out_file_name + ".root");
   canvas->SaveAs(out_file_name + ".eps");
   canvas->SaveAs(out_file_name + ".png");
   gSystem->Exec("convert -density 150 -quality 100 " + out_file_name + ".eps " + out_file_name + ".png");
}
//=======================================================================================



//================================================================================================
TLegend* Histograms::CreateLegend( TString position, TString type, TGraphErrors *graph_1, TGraphErrors *graph_2 )
{
   TLegend *legend = new TLegend(.65, .75, .85, .85);

   legend->SetFillColor(0);
   legend->SetBorderSize(0);
   legend->SetFillStyle(0);

   if( type == "eta" )
   {
      legend->AddEntry( graph_1, "Barrel |#eta^{e, offline}| < 1.440", "p" );
      legend->AddEntry( graph_2, "Endcap 1.479 < |#eta^{e, offline}| < 2.500", "p" );
   }
   else if( type == "emulation" )
   {
      legend->AddEntry( graph_1, "Default conditions",  "p" );
      legend->AddEntry( graph_2, "Emulated conditions", "p" );
   }
   else
   {
      cout << "Invalid legend type." << endl;     
   }

   return legend;
}
//================================================================================================



//========================================================================
TPaveText* Histograms::CreateCutText( string position, TString cut_label )
{
   TPaveText *pav;
   pav = new TPaveText(.21, .81, .51, .91 ,"brNDC"); // Default initalisiation to avoid scram compilation error

   if ( position == "left top" )    pav = new TPaveText(.21, .81, .51, .91 ,"brNDC");
   if ( position == "right top" )   pav = new TPaveText(.61, .81, .91, .91 ,"brNDC");
   if ( position == "middle top" )  pav = new TPaveText(.41, .81, .71, .91 ,"brNDC");
   if ( position == "left under 2D legend" ) pav = new TPaveText(.18, .72, .31, .78 ,"brNDC");

   pav->SetFillStyle(0);
   pav->SetBorderSize(0);
   pav->SetTextAlign(11);
   pav->SetTextSize(0.032);
   pav->SetTextFont(42);
   pav->AddText(cut_label);

   return pav;
}
//========================================================================
