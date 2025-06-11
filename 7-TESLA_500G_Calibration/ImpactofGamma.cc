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
void ImpactofGamma() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_NumbISR_912 = (TH1F*)input_912->Get("hist_NumbISR");
	hist_NumbISR_912->SetLineColor(kRed+2); hist_NumbISR_912->SetMarkerColor(kRed+2); hist_NumbISR_912->SetMarkerStyle(kStar); hist_NumbISR_912->SetLineWidth(2); hist_NumbISR_912->SetStats(kFALSE);
	TH1F *hist_NumbISR_160 = (TH1F*)input_160->Get("hist_NumbISR");
	hist_NumbISR_160->SetLineColor(kGreen+2); hist_NumbISR_160->SetMarkerColor(kGreen+2); hist_NumbISR_160->SetMarkerStyle(kStar); hist_NumbISR_160->SetLineWidth(2); hist_NumbISR_160->SetStats(kFALSE);
	TH1F *hist_NumbISR_240 = (TH1F*)input_240->Get("hist_NumbISR");
	hist_NumbISR_240->SetLineColor(kYellow+2); hist_NumbISR_240->SetMarkerColor(kYellow+2); hist_NumbISR_240->SetMarkerStyle(kStar); hist_NumbISR_240->SetLineWidth(2); hist_NumbISR_240->SetStats(kFALSE);
	TH1F *hist_NumbISR_365 = (TH1F*)input_365->Get("hist_NumbISR");
	hist_NumbISR_365->SetLineColor(kBlue+2); hist_NumbISR_365->SetMarkerColor(kBlue+2); hist_NumbISR_365->SetMarkerStyle(kStar); hist_NumbISR_365->SetLineWidth(2); hist_NumbISR_365->SetStats(kFALSE);

	TH1F *hist_EmaxISR_912 = (TH1F*)input_912->Get("hist_EmaxISR");
	hist_EmaxISR_912->SetLineColor(kRed+2); hist_EmaxISR_912->SetMarkerColor(kRed+2); hist_EmaxISR_912->SetMarkerStyle(kStar); hist_EmaxISR_912->SetLineWidth(3); hist_EmaxISR_912->SetStats(kFALSE);
	TH1F *hist_EmaxISR_160 = (TH1F*)input_160->Get("hist_EmaxISR");
	hist_EmaxISR_160->SetLineColor(kGreen+2); hist_EmaxISR_160->SetMarkerColor(kGreen+2); hist_EmaxISR_160->SetMarkerStyle(kStar); hist_EmaxISR_160->SetLineWidth(3); hist_EmaxISR_160->SetStats(kFALSE);
	TH1F *hist_EmaxISR_240 = (TH1F*)input_240->Get("hist_EmaxISR");
	hist_EmaxISR_240->SetLineColor(kYellow+2); hist_EmaxISR_240->SetMarkerColor(kYellow+2); hist_EmaxISR_240->SetMarkerStyle(kStar); hist_EmaxISR_240->SetLineWidth(3); hist_EmaxISR_240->SetStats(kFALSE);
	TH1F *hist_EmaxISR_365 = (TH1F*)input_365->Get("hist_EmaxISR");
	hist_EmaxISR_365->SetLineColor(kBlue+2); hist_EmaxISR_365->SetMarkerColor(kBlue+2); hist_EmaxISR_365->SetMarkerStyle(kStar); hist_EmaxISR_365->SetLineWidth(3); hist_EmaxISR_365->SetStats(kFALSE);
	
	TH1F *hist_EnrgISR_912 = (TH1F*)input_912->Get("hist_EnrgISR");
	hist_EnrgISR_912->SetLineColor(kRed+2); hist_EnrgISR_912->SetMarkerColor(kRed+2); hist_EnrgISR_912->SetMarkerStyle(kStar); hist_EnrgISR_912->SetLineWidth(3); hist_EnrgISR_912->SetStats(kFALSE);
	TH1F *hist_EnrgISR_160 = (TH1F*)input_160->Get("hist_EnrgISR");
	hist_EnrgISR_160->SetLineColor(kGreen+2); hist_EnrgISR_160->SetMarkerColor(kGreen+2); hist_EnrgISR_160->SetMarkerStyle(kStar); hist_EnrgISR_160->SetLineWidth(3); hist_EnrgISR_160->SetStats(kFALSE);
	TH1F *hist_EnrgISR_240 = (TH1F*)input_240->Get("hist_EnrgISR");
	hist_EnrgISR_240->SetLineColor(kYellow+2); hist_EnrgISR_240->SetMarkerColor(kYellow+2); hist_EnrgISR_240->SetMarkerStyle(kStar); hist_EnrgISR_240->SetLineWidth(3); hist_EnrgISR_240->SetStats(kFALSE);
	TH1F *hist_EnrgISR_365 = (TH1F*)input_365->Get("hist_EnrgISR");
	hist_EnrgISR_365->SetLineColor(kBlue+2); hist_EnrgISR_365->SetMarkerColor(kBlue+2); hist_EnrgISR_365->SetMarkerStyle(kStar); hist_EnrgISR_365->SetLineWidth(3); hist_EnrgISR_365->SetStats(kFALSE);

	TH1F *hist_Esprime_912 = (TH1F*)input_912->Get("hist_Esprime_al");
	hist_Esprime_912->SetLineColor(kRed+2); hist_Esprime_912->SetMarkerColor(kRed+2); hist_Esprime_912->SetMarkerStyle(kStar); hist_Esprime_912->SetLineWidth(3); hist_Esprime_912->SetStats(kFALSE);
	TH1F *hist_Esprime_160 = (TH1F*)input_160->Get("hist_Esprime_al");
	hist_Esprime_160->SetLineColor(kGreen+2); hist_Esprime_160->SetMarkerColor(kGreen+2); hist_Esprime_160->SetMarkerStyle(kStar); hist_Esprime_160->SetLineWidth(3); hist_Esprime_160->SetStats(kFALSE);
	TH1F *hist_Esprime_240 = (TH1F*)input_240->Get("hist_Esprime_al");
	hist_Esprime_240->SetLineColor(kYellow+2); hist_Esprime_240->SetMarkerColor(kYellow+2); hist_Esprime_240->SetMarkerStyle(kStar); hist_Esprime_240->SetLineWidth(3); hist_Esprime_240->SetStats(kFALSE);
	TH1F *hist_Esprime_365 = (TH1F*)input_365->Get("hist_Esprime_al");
	hist_Esprime_365->SetLineColor(kBlue+2); hist_Esprime_365->SetMarkerColor(kBlue+2); hist_Esprime_365->SetMarkerStyle(kStar); hist_Esprime_365->SetLineWidth(3); hist_Esprime_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_EmaxISR_912->Scale(1.0/hist_EmaxISR_912->Integral());
	// hist_EmaxISR_160->Scale(1.0/hist_EmaxISR_160->Integral());
	// hist_EmaxISR_240->Scale(1.0/hist_EmaxISR_240->Integral());
	// hist_EmaxISR_365->Scale(1.0/hist_EmaxISR_365->Integral());

	// hist_EnrgISR_912->Scale(1.0/hist_EnrgISR_912->Integral());
	// hist_EnrgISR_160->Scale(1.0/hist_EnrgISR_160->Integral());
	// hist_EnrgISR_240->Scale(1.0/hist_EnrgISR_240->Integral());
	// hist_EnrgISR_365->Scale(1.0/hist_EnrgISR_365->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_Esprime_LEP->GetXaxis()->SetTitle("#sqrt{s} /#sqrt{s'}");
	// hist_Esprime_LEP->GetYaxis()->SetTitle("P(#sqrt{s} /#sqrt{s'})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg->AddEntry(hist_EmaxISR_912, "#sqrt{s} = 91.2 GeV", "p");
	lg->AddEntry(hist_EmaxISR_160, "#sqrt{s} = 160 GeV", "p");
	lg->AddEntry(hist_EmaxISR_240, "#sqrt{s} = 240 GeV", "p");
	lg->AddEntry(hist_EmaxISR_365, "#sqrt{s} = 500 GeV", "p");
	lg->SetTextSize(0.03);
	
	// Create canvas
	TCanvas* cv = new TCanvas("cv", "Impact of ISR on Effective COM", 1200, 1000);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv->Divide(2,2);
	cv->cd(1)->SetLeftMargin(0.15);
	cv->cd(1)->SetLogy();
	cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	cv->cd(2)->SetLeftMargin(0.15);
	cv->cd(2)->SetLogy();
	cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
	cv->cd(3)->SetLeftMargin(0.15);
	cv->cd(3)->SetLogy();
	cv->cd(3)->SetTickx(); cv->cd(3)->SetTicky();
	cv->cd(3)->SetGridx(); cv->cd(3)->SetGridy();
	cv->cd(4)->SetLeftMargin(0.15);
	cv->cd(4)->SetLogy();
	cv->cd(4)->SetTickx(); cv->cd(4)->SetTicky();
	cv->cd(4)->SetGridx(); cv->cd(4)->SetGridy();

	// Draw
	cv->cd(1);
	hist_EnrgISR_912->Draw("P");
	hist_EnrgISR_160->Draw("P SAME");
	hist_EnrgISR_240->Draw("P SAME");
	hist_EnrgISR_365->Draw("P SAME");
	lg->Draw("SAME");

	cv->cd(2);
	hist_EmaxISR_912->Draw("P");
	hist_EmaxISR_160->Draw("P SAME");
	hist_EmaxISR_240->Draw("P SAME");
	hist_EmaxISR_365->Draw("P SAME");
	lg->Draw("SAME");

	cv->cd(3);
	hist_NumbISR_912->Draw("");
	hist_NumbISR_160->Draw("SAME");
	hist_NumbISR_240->Draw("SAME");
	hist_NumbISR_365->Draw("SAME");
	lg->Draw("SAME");

	cv->cd(4);
	hist_Esprime_912->Draw("P");
	hist_Esprime_160->Draw("P SAME");
	hist_Esprime_240->Draw("P SAME");
	hist_Esprime_365->Draw("P SAME");
	lg->Draw("SAME");

	// Set limits
	hist_EmaxISR_912->GetYaxis()->SetRangeUser(1E-1,1E8);
	hist_EnrgISR_912->GetYaxis()->SetRangeUser(1E-1,1E8);
	hist_NumbISR_912->GetYaxis()->SetRangeUser(1E-1,1E6);
	hist_Esprime_912->GetYaxis()->SetRangeUser(1E-1,1E7);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv->Modified();

}