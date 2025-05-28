/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TList.h"
// Header
using namespace std;

// Code
void ImpactofHiggs()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TFile* input_TES50t_noH = new TFile("cut_TES50t_noR_noH.root", "READ");
	TFile* input_TES50t = new TFile("cut_TES50t_noR.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_al_noH = (TH1F*)input_TES50t->Get("hist_ThrPyth_noH"); 
	hist_ThrPyth_al_noH->SetLineColor(kBlack); hist_ThrPyth_al_noH->SetMarkerColor(kBlack); hist_ThrPyth_al_noH->SetMarkerStyle(kStar); hist_ThrPyth_al_noH->SetLineWidth(3); hist_ThrPyth_al_noH->SetStats(kFALSE);

	TH1F *hist_ThrPyth_al = (TH1F*)input_TES50t->Get("hist_ThrPyth_000");
	hist_ThrPyth_al->SetLineColor(kBlack); hist_ThrPyth_al->SetMarkerColor(kBlack); hist_ThrPyth_al->SetMarkerStyle(kStar); hist_ThrPyth_al->SetLineWidth(3); hist_ThrPyth_al->SetStats(kFALSE);
	TH1F *hist_ThrPyth_Zq = (TH1F*)input_TES50t->Get("hist_ThrPyth_Zq"); 
	hist_ThrPyth_Zq->SetLineColor(kYellow+2); hist_ThrPyth_Zq->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq->SetMarkerStyle(kStar); hist_ThrPyth_Zq->SetLineWidth(3); hist_ThrPyth_Zq->SetStats(kFALSE);
	TH1F *hist_ThrPyth_ZZ = (TH1F*)input_TES50t->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ->SetLineColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerStyle(kStar); hist_ThrPyth_ZZ->SetLineWidth(3); hist_ThrPyth_ZZ->SetStats(kFALSE);
	TH1F *hist_ThrPyth_WW = (TH1F*)input_TES50t->Get("hist_ThrPyth_WW"); 
	hist_ThrPyth_WW->SetLineColor(kGreen+2); hist_ThrPyth_WW->SetMarkerColor(kGreen+2); hist_ThrPyth_WW->SetMarkerStyle(kStar); hist_ThrPyth_WW->SetLineWidth(3); hist_ThrPyth_WW->SetStats(kFALSE);
	TH1F *hist_ThrPyth_tt = (TH1F*)input_TES50t->Get("hist_ThrPyth_tt"); 
	hist_ThrPyth_tt->SetLineColor(kRed+2); hist_ThrPyth_tt->SetMarkerColor(kRed+2); hist_ThrPyth_tt->SetMarkerStyle(kStar); hist_ThrPyth_tt->SetLineWidth(3); hist_ThrPyth_tt->SetStats(kFALSE);   
	TH1F *hist_ThrPyth_Zt = (TH1F*)input_TES50t->Get("hist_ThrPyth_Zt"); 
	hist_ThrPyth_Zt->SetLineColor(kMagenta+2); hist_ThrPyth_Zt->SetMarkerColor(kMagenta+2); hist_ThrPyth_Zt->SetMarkerStyle(kStar); hist_ThrPyth_Zt->SetLineWidth(3); hist_ThrPyth_Zt->SetStats(kFALSE);  
	TH1F *hist_ThrPyth_HZ = (TH1F*)input_TES50t->Get("hist_ThrPyth_HZ"); 
	hist_ThrPyth_HZ->SetLineColor(kBlue+2); hist_ThrPyth_HZ->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ->SetMarkerStyle(kCircle); hist_ThrPyth_HZ->SetLineWidth(2); hist_ThrPyth_HZ->SetStats(kFALSE);
	TH1F *hist_ThrPyth_hZ = (TH1F*)input_TES50t->Get("hist_ThrPyth_hZ"); 
	hist_ThrPyth_hZ->SetLineColor(kGreen+2); hist_ThrPyth_hZ->SetMarkerColor(kGreen+2); hist_ThrPyth_hZ->SetMarkerStyle(kCircle); hist_ThrPyth_hZ->SetLineWidth(2); hist_ThrPyth_hZ->SetStats(kFALSE);
	TH1F *hist_ThrPyth_hW = (TH1F*)input_TES50t->Get("hist_ThrPyth_hW"); 
	hist_ThrPyth_hW->SetLineColor(kRed+2); hist_ThrPyth_hW->SetMarkerColor(kRed+2); hist_ThrPyth_hW->SetMarkerStyle(kCircle); hist_ThrPyth_hW->SetLineWidth(2); hist_ThrPyth_hW->SetStats(kFALSE);	

	TH1F *hist_nHadron_al = (TH1F*)input_TES50t->Get("hist_nHadron_000");
	hist_nHadron_al->SetLineColor(kBlack); hist_nHadron_al->SetMarkerColor(kBlack); hist_nHadron_al->SetMarkerStyle(kStar); hist_nHadron_al->SetLineWidth(3); hist_nHadron_al->SetStats(kFALSE);
	TH1F *hist_nHadron_Zq = (TH1F*)input_TES50t->Get("hist_nHadron_Zq"); 
	hist_nHadron_Zq->SetLineColor(kYellow+2); hist_nHadron_Zq->SetMarkerColor(kYellow+2); hist_nHadron_Zq->SetMarkerStyle(kStar); hist_nHadron_Zq->SetLineWidth(3); hist_nHadron_Zq->SetStats(kFALSE);
	TH1F *hist_nHadron_ZZ = (TH1F*)input_TES50t->Get("hist_nHadron_ZZ"); 
	hist_nHadron_ZZ->SetLineColor(kBlue+2); hist_nHadron_ZZ->SetMarkerColor(kBlue+2); hist_nHadron_ZZ->SetMarkerStyle(kStar); hist_nHadron_ZZ->SetLineWidth(3); hist_nHadron_ZZ->SetStats(kFALSE);
	TH1F *hist_nHadron_WW = (TH1F*)input_TES50t->Get("hist_nHadron_WW"); 
	hist_nHadron_WW->SetLineColor(kGreen+2); hist_nHadron_WW->SetMarkerColor(kGreen+2); hist_nHadron_WW->SetMarkerStyle(kStar); hist_nHadron_WW->SetLineWidth(3); hist_nHadron_WW->SetStats(kFALSE);
	TH1F *hist_nHadron_tt = (TH1F*)input_TES50t->Get("hist_nHadron_tt"); 
	hist_nHadron_tt->SetLineColor(kRed+2); hist_nHadron_tt->SetMarkerColor(kRed+2); hist_nHadron_tt->SetMarkerStyle(kStar); hist_nHadron_tt->SetLineWidth(3); hist_nHadron_tt->SetStats(kFALSE);
	TH1F *hist_nHadron_HZ = (TH1F*)input_TES50t->Get("hist_nHadron_HZ"); 
	hist_nHadron_HZ->SetLineColor(kBlue+2); hist_nHadron_HZ->SetMarkerColor(kBlue+2); hist_nHadron_HZ->SetMarkerStyle(kCircle); hist_nHadron_HZ->SetLineWidth(2); hist_nHadron_HZ->SetStats(kFALSE);
	TH1F *hist_nHadron_hZ = (TH1F*)input_TES50t->Get("hist_nHadron_hZ"); 
	hist_nHadron_hZ->SetLineColor(kGreen+2); hist_nHadron_hZ->SetMarkerColor(kGreen+2); hist_nHadron_hZ->SetMarkerStyle(kCircle); hist_nHadron_hZ->SetLineWidth(2); hist_nHadron_hZ->SetStats(kFALSE);
	TH1F *hist_nHadron_hW = (TH1F*)input_TES50t->Get("hist_nHadron_hW"); 
	hist_nHadron_hW->SetLineColor(kRed+2); hist_nHadron_hW->SetMarkerColor(kRed+2); hist_nHadron_hW->SetMarkerStyle(kCircle); hist_nHadron_hW->SetLineWidth(2); hist_nHadron_hW->SetStats(kFALSE);

	TH1F *hist_nHadron_al_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_000");
	hist_nHadron_al_noH->SetLineColor(kBlack); hist_nHadron_al_noH->SetMarkerColor(kBlack); hist_nHadron_al_noH->SetMarkerStyle(kStar); hist_nHadron_al_noH->SetLineWidth(3); hist_nHadron_al_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_Zq_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_Zq"); 
	hist_nHadron_Zq_noH->SetLineColor(kYellow+2); hist_nHadron_Zq_noH->SetMarkerColor(kYellow+2); hist_nHadron_Zq_noH->SetMarkerStyle(kStar); hist_nHadron_Zq_noH->SetLineWidth(3); hist_nHadron_Zq_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_ZZ_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_ZZ"); 
	hist_nHadron_ZZ_noH->SetLineColor(kBlue+2); hist_nHadron_ZZ_noH->SetMarkerColor(kBlue+2); hist_nHadron_ZZ_noH->SetMarkerStyle(kStar); hist_nHadron_ZZ_noH->SetLineWidth(3); hist_nHadron_ZZ_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_WW_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_WW"); 
	hist_nHadron_WW_noH->SetLineColor(kGreen+2); hist_nHadron_WW_noH->SetMarkerColor(kGreen+2); hist_nHadron_WW_noH->SetMarkerStyle(kStar); hist_nHadron_WW_noH->SetLineWidth(3); hist_nHadron_WW_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_tt_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_tt"); 
	hist_nHadron_tt_noH->SetLineColor(kRed+2); hist_nHadron_tt_noH->SetMarkerColor(kRed+2); hist_nHadron_tt_noH->SetMarkerStyle(kStar); hist_nHadron_tt_noH->SetLineWidth(3); hist_nHadron_tt_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_HZ_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_HZ"); 
	hist_nHadron_HZ_noH->SetLineColor(kBlue+2); hist_nHadron_HZ_noH->SetMarkerColor(kBlue+2); hist_nHadron_HZ_noH->SetMarkerStyle(kCircle); hist_nHadron_HZ_noH->SetLineWidth(2); hist_nHadron_HZ_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_hZ_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_hZ"); 
	hist_nHadron_hZ_noH->SetLineColor(kGreen+2); hist_nHadron_hZ_noH->SetMarkerColor(kGreen+2); hist_nHadron_hZ_noH->SetMarkerStyle(kCircle); hist_nHadron_hZ_noH->SetLineWidth(2); hist_nHadron_hZ_noH->SetStats(kFALSE);
	TH1F *hist_nHadron_hW_noH = (TH1F*)input_TES50t_noH->Get("hist_nHadron_hW"); 
	hist_nHadron_hW_noH->SetLineColor(kRed+2); hist_nHadron_hW_noH->SetMarkerColor(kRed+2); hist_nHadron_hW_noH->SetMarkerStyle(kCircle); hist_nHadron_hW_noH->SetLineWidth(2); hist_nHadron_hW_noH->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_ThrPyth_al->Scale(1.0/hist_ThrPyth_al->Integral());
	// hist_ThrPyth_Zq->Scale(1.0/hist_ThrPyth_Zq->Integral());
	// hist_ThrPyth_ZZ->Scale(1.0/hist_ThrPyth_ZZ->Integral());
	// hist_ThrPyth_WW->Scale(1.0/hist_ThrPyth_WW->Integral());
	// hist_ThrPyth_tt->Scale(1.0/hist_ThrPyth_tt->Integral());
	// hist_ThrPyth_Zt->Scale(1.0/hist_ThrPyth_Zt->Integral());
	// hist_ThrPyth_HZ->Scale(1.0/hist_ThrPyth_HZ->Integral());
	// hist_ThrPyth_hZ->Scale(1.0/hist_ThrPyth_hZ->Integral());
	// hist_ThrPyth_hW->Scale(1.0/hist_ThrPyth_hW->Integral());
	// hist_ThrPyth_al_noH->Scale(1.0/hist_ThrPyth_al_noH->Integral());
	// hist_nHadron_al->Scale(1.0/hist_nHadron_al->Integral());
	// hist_nHadron_Zq->Scale(1.0/hist_nHadron_Zq->Integral());
	// hist_nHadron_ZZ->Scale(1.0/hist_nHadron_ZZ->Integral());
	// hist_nHadron_WW->Scale(1.0/hist_nHadron_WW->Integral());
	// hist_nHadron_tt->Scale(1.0/hist_nHadron_tt->Integral());
	// hist_nHadron_HZ->Scale(1.0/hist_nHadron_HZ->Integral());
	// hist_nHadron_hZ->Scale(1.0/hist_nHadron_hZ->Integral());
	// hist_nHadron_hW->Scale(1.0/hist_nHadron_hW->Integral());
	// hist_nHadron_al_noH->Scale(1.0/hist_nHadron_al_noH->Integral());
	// hist_nHadron_Zq_noH->Scale(1.0/hist_nHadron_Zq_noH->Integral());
	// hist_nHadron_ZZ_noH->Scale(1.0/hist_nHadron_ZZ_noH->Integral());
	// hist_nHadron_WW_noH->Scale(1.0/hist_nHadron_WW_noH->Integral());
	// hist_nHadron_tt_noH->Scale(1.0/hist_nHadron_tt_noH->Integral());
	// hist_nHadron_HZ_noH->Scale(1.0/hist_nHadron_HZ_noH->Integral());
	// hist_nHadron_hZ_noH->Scale(1.0/hist_nHadron_hZ_noH->Integral());
	// hist_nHadron_hW_noH->Scale(1.0/hist_nHadron_hW_noH->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al->SetTitle("Inverse Thrust"); hist_ThrPyth_al->GetYaxis()->SetTitle("P(1-T)");

	hist_nHadron_al->SetTitle("Charged Multiplicity with Higgs"); hist_nHadron_al->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nHadron_al_noH->SetTitle("Charged Multiplicity without Higgs"); hist_nHadron_al->GetYaxis()->SetTitle("P(N_{CH})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg_thr = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg_thr->AddEntry(hist_nHadron_al, "ee#rightarrowq#bar{q}", "p");
	lg_thr->AddEntry(hist_nHadron_Zq, "ee#rightarrow#gamma*/Z#rightarrowq#bar{q}", "pl");
	lg_thr->AddEntry(hist_nHadron_ZZ, "ee#rightarrowWW#rightarrowq#bar{q}", "pl");
	lg_thr->AddEntry(hist_nHadron_WW, "ee#rightarrowZZ#rightarrowq#bar{q}", "pl");
	lg_thr->AddEntry(hist_nHadron_tt, "ee#rightarrowt#bar{t}#rightarrowq#bar{q}", "pl");
	lg_thr->AddEntry(hist_nHadron_HZ, "ee#rightarrowZH#rightarrowq#bar{q}", "pl");
	lg_thr->AddEntry(hist_nHadron_hZ, "ee#rightarroweeH", "pl");
	lg_thr->AddEntry(hist_nHadron_hW, "ee#rightarrow#nu_{e}#bar{#nu_{e}}H", "pl");
	lg_thr->SetTextSize(0.03);

	// Add legend
	TLegend *lg_thr2 = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg_thr2->AddEntry(hist_nHadron_al, "with Higgs", "p");
	lg_thr2->AddEntry(hist_nHadron_al_noH, "woth Higgs", "p");
	lg_thr2->SetTextSize(0.03);
	
	// Create canvas
	TCanvas* c_thr = new TCanvas("c_thr", "Process-separated Event Shapes", 1000, 1400);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	c_thr->Divide(2,3);
	c_thr->cd(1)->SetLeftMargin(0.15);
	c_thr->cd(1)->SetLogy();
	c_thr->cd(1)->SetTickx(); c_thr->cd(1)->SetTicky();
	c_thr->cd(1)->SetGridx(); c_thr->cd(1)->SetGridy();
	c_thr->cd(2)->SetLeftMargin(0.15);
	c_thr->cd(2)->SetLogy();
	c_thr->cd(2)->SetTickx(); c_thr->cd(2)->SetTicky();
	c_thr->cd(2)->SetGridx(); c_thr->cd(2)->SetGridy();
	c_thr->cd(3)->SetLeftMargin(0.15);
	c_thr->cd(3)->SetLogy();
	c_thr->cd(3)->SetTickx(); c_thr->cd(3)->SetTicky();
	c_thr->cd(3)->SetGridx(); c_thr->cd(3)->SetGridy();
	c_thr->cd(4)->SetLeftMargin(0.15);
	c_thr->cd(4)->SetLogy();
	c_thr->cd(4)->SetTickx(); c_thr->cd(4)->SetTicky();
	c_thr->cd(4)->SetGridx(); c_thr->cd(4)->SetGridy();

	// Draw
	c_thr->cd(1);
	hist_nHadron_al_noH->Draw("P");
	hist_nHadron_Zq_noH->Draw("P SAME");
	hist_nHadron_ZZ_noH->Draw("P SAME");
	hist_nHadron_WW_noH->Draw("P SAME");
	hist_nHadron_tt_noH->Draw("P SAME");
	hist_nHadron_HZ_noH->Draw("P SAME");
	hist_nHadron_hZ_noH->Draw("P SAME");
	hist_nHadron_hW_noH->Draw("P SAME");

	c_thr->cd(2);
	hist_nHadron_al->Draw("P");
	hist_nHadron_Zq->Draw("P SAME");
	hist_nHadron_ZZ->Draw("P SAME");
	hist_nHadron_WW->Draw("P SAME");
	hist_nHadron_tt->Draw("P SAME");
	hist_nHadron_HZ->Draw("P SAME");
	hist_nHadron_hZ->Draw("P SAME");
	hist_nHadron_hW->Draw("P SAME");
	lg_thr->Draw("SAME");

	// hist_nHadron_al_noH->Scale(1.0/hist_nHadron_al_noH->Integral());
	// hist_nHadron_al->Scale(1.0/hist_nHadron_al->Integral());
	// hist_nHadron_al->GetYaxis()->SetRangeUser(1E-6,1E0);

	c_thr->cd(3);
	hist_nHadron_al->Draw("P");
	hist_nHadron_al_noH->Draw("P SAME");
	lg_thr2->Draw("SAME");

	c_thr->cd(4);
	hist_ThrPyth_al->Draw("P");
	hist_ThrPyth_al_noH->Draw("P SAME");

	c_thr->cd(5);
	c_thr->cd(6);

	// Set limits
	// hist_ThrPyth_al->GetYaxis()->SetRangeUser(1E-6,1E0);
	// hist_nHadron_al->GetYaxis()->SetRangeUser(1E-6,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	c_thr->Modified();

}