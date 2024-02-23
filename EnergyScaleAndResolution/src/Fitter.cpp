// Include classes
#include "Fitter.h"

#include "TSystem.h"


using namespace std;

// Constructor
//=================================
Fitter::Fitter( TString fits_path )
{
   
   gStyle->SetOptTitle(0);
   
   _fits_path = fits_path;
   
   energy_scale = new RooRealVar("energy_scale", "", 0, 2);
   width = new RooRealVar("width", "width", 0.1, 0, 2);
   mu = new RooRealVar("mu", "mu",          1,   0, 2);
   a1 = new RooRealVar("a1", "a1",          1,   0, 100);
   p1 = new RooRealVar("p1", "p1",          1,   0, 100);
   a2 = new RooRealVar("a2", "a2",          1,   0, 100);
   p2 = new RooRealVar("p2", "p2",          1,   0, 100);
   
   _fit_energy_scale_EB_pt_bins_mu.clear();
   _fit_energy_scale_EE_pt_bins_mu.clear();
   
   dcbPdf = new RooCrystalBall("dcbPdf", "DoubleSidedCB", *energy_scale, *mu, *width, *a1, *p1, *a2, *p2);
   dcbPdf_barrel = new RooCrystalBall("dcbPdf", "DoubleSidedCB", *energy_scale, *mu, *width, *a1, *p1, *a2, *p2);
   dcbPdf_endcap = new RooCrystalBall("dcbPdf", "DoubleSidedCB", *energy_scale, *mu, *width, *a1, *p1, *a2, *p2);


}
//=================================


//==================================
Fitter::~Fitter() {}
//==================================



//============================================================================================
void Fitter::Fit(TH1F *histogram_1, TH1F *histogram_2, TString emulation_name, TString pT_bin)
{   
   width->setVal(0.1);
   mu->setVal(1);
   
   RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
   
   TCanvas *FitCanvas = new TCanvas("Fit test", "Fit test", 800, 600);
   TLegend *legend = new TLegend(0.65,0.73,0.86,0.87);

   RooDataHist *hist_barrel = new RooDataHist("hist_barrel", "hist_barrel", *energy_scale, Import(*histogram_1));
   RooDataHist *hist_endcap = new RooDataHist("hist_endcap", "hist_endcap", *energy_scale, Import(*histogram_2));

   auto frame = energy_scale->frame();
   frame->GetYaxis()->SetTitleOffset(1.3);
   frame->GetXaxis()->SetTitleOffset(1.3); 

   auto result_barrel = dcbPdf_barrel->fitTo(*hist_barrel, SumW2Error(false), Save(true), PrintLevel(-1), PrintEvalErrors(-1), Verbose(kFALSE));
//   result_barrel->Print();
   _fit_energy_scale_EB_pt_bins_mu.push_back(mu->getVal());   
   
   frame->GetXaxis()->SetTitle("p_{T}^{e/#gamma, L1}/p_{T}^{e, offline}");
   hist_barrel->plotOn(frame, MarkerColor(kRed-4), DrawOption("X0 P"));
   dcbPdf_barrel->plotOn(frame, LineColor(kRed-4));
   

   auto result_endcap = dcbPdf_endcap->fitTo(*hist_endcap, SumW2Error(false), Save(true), PrintLevel(-1), PrintEvalErrors(-1), Verbose(kFALSE));
//   result_endcap->Print();
   _fit_energy_scale_EE_pt_bins_mu.push_back(mu->getVal());

   hist_endcap->plotOn(frame, MarkerColor(kAzure+2), DrawOption("X0 P"));
   dcbPdf_endcap->plotOn(frame, LineColor(kAzure+2));
   
   
   frame->Draw();
   FitCanvas->Draw();
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + pT_bin + ".pdf");  
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + pT_bin + ".eps");  
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + pT_bin + ".png");  
   gSystem->Exec("convert -density 150 -quality 100 " + _fits_path + emulation_name + "_" + pT_bin + ".eps " + _fits_path + emulation_name + "_" + pT_bin + ".png");
   
   
    
}
//============================================================================================



//=============================================================================
void Fitter::Fit(TH1F *histogram, TString emulation_name, TString fine_eta_bin)
{   
   width->setVal(0.2);
   mu->setVal(1);
   
   RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
   
   TCanvas *FitCanvas = new TCanvas("Fit test", "Fit test", 800, 600);

   RooDataHist *hist = new RooDataHist("Histogram", "Histogram", *energy_scale, Import(*histogram));

   auto frame = energy_scale->frame();
   frame->GetYaxis()->SetTitleOffset(1.3);
   frame->GetXaxis()->SetTitleOffset(1.3); 

   auto result = dcbPdf->fitTo(*hist, SumW2Error(false), Save(true), PrintLevel(-1), PrintEvalErrors(-1), Verbose(kFALSE));
//   result->Print();

//   cout << fine_eta_bin << " mu = " << mu->getVal() << endl;
   _fit_energy_scale_eta_bins_mu.push_back(mu->getVal());
   
   frame->GetXaxis()->SetTitle("p_{T}^{e/#gamma, L1}/p_{T}^{e, offline}");
   hist->plotOn(frame, DrawOption("X0 P"));
   dcbPdf->plotOn(frame);
   
   frame->Draw();
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + fine_eta_bin + ".pdf");
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + fine_eta_bin + ".eps");
   FitCanvas->SaveAs(_fits_path + emulation_name + "_" + fine_eta_bin + ".png");
   gSystem->Exec("convert -density 150 -quality 100 " + _fits_path + emulation_name + "_" + fine_eta_bin + ".eps " + _fits_path + emulation_name + "_" + fine_eta_bin + ".png");
   
}
//=============================================================================



//================================================================================================
//TLegend* Fitter::CreateLegend( RooDataHist *graph_1, RooDataHist *graph_2 )
//{
//   TLegend *legend = new TLegend(.65, .75, .85, .85);
//
//   legend->SetFillColor(0);
//   legend->SetBorderSize(0);
//   legend->SetFillStyle(0);
//
//   legend->AddEntry( graph_1, "Barrel |#eta^{e, offline}| < 1.440", "p" );
//   legend->AddEntry( graph_2, "Endcap 1.479 < |#eta^{e, offline}| < 2.500", "p" );
//
//   return legend;
//}
//================================================================================================



//================================================
vector<float> Fitter::GetFitEnergyScaleEtaBinsMu()
{   
   return _fit_energy_scale_eta_bins_mu;
}
//================================================



//================================================
vector<float> Fitter::GetFitEnergyScaleEBpTBinsMu()
{   
   return _fit_energy_scale_EB_pt_bins_mu;
}
//================================================



//================================================
vector<float> Fitter::GetFitEnergyScaleEEpTBinsMu()
{   
   return _fit_energy_scale_EE_pt_bins_mu;
}
//================================================


