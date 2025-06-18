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
void ImpactofRun() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("cut_FCC160.root", "READ");
	TFile *input_180 = new TFile("cut_FCC180.root", "READ");
	TFile *input_240 = new TFile("cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of ISR Cuts on Thrust/Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_100 = (TH1F*)input_912->Get("hist_ThrPyth_000");
	TH1F *hist_ThrPyth_160_100 = (TH1F*)input_160->Get("hist_ThrPyth_100");
	TH1F *hist_ThrPyth_180_100 = (TH1F*)input_180->Get("hist_ThrPyth_100");
	TH1F *hist_ThrPyth_240_100 = (TH1F*)input_240->Get("hist_ThrPyth_100");
	TH1F *hist_ThrPyth_365_100 = (TH1F*)input_365->Get("hist_ThrPyth_100");
	TH1F *hist_nHadron_912_100 = (TH1F*)input_912->Get("hist_nHadron_000");
	TH1F *hist_nHadron_160_100 = (TH1F*)input_160->Get("hist_nHadron_100");
	TH1F *hist_nHadron_180_100 = (TH1F*)input_180->Get("hist_nHadron_100");
	TH1F *hist_nHadron_240_100 = (TH1F*)input_240->Get("hist_nHadron_100");
	TH1F *hist_nHadron_365_100 = (TH1F*)input_365->Get("hist_nHadron_100");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_100->Scale(1.0/hist_ThrPyth_912_100->Integral());
	hist_ThrPyth_160_100->Scale(1.0/hist_ThrPyth_160_100->Integral());
	hist_ThrPyth_180_100->Scale(1.0/hist_ThrPyth_180_100->Integral());
	hist_ThrPyth_240_100->Scale(1.0/hist_ThrPyth_240_100->Integral());
	hist_ThrPyth_365_100->Scale(1.0/hist_ThrPyth_365_100->Integral());
	hist_nHadron_912_100->Scale(1.0/hist_nHadron_912_100->Integral());
	hist_nHadron_160_100->Scale(1.0/hist_nHadron_160_100->Integral());
	hist_nHadron_180_100->Scale(1.0/hist_nHadron_180_100->Integral());
	hist_nHadron_240_100->Scale(1.0/hist_nHadron_240_100->Integral());
	hist_nHadron_365_100->Scale(1.0/hist_nHadron_365_100->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_ThrPyth_365_000->GetXaxis()->SetTitle("#sqrt{s} /#sqrt{s'}");
	// hist_ThrPyth_365_000->GetYaxis()->SetTitle("P(#sqrt{s} /#sqrt{s'})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Running of <1-T>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double Sprime[] = {91.2, 160.0, 180.0, 240.0, 365.0};
	double Thrust[] = {hist_ThrPyth_912_100->GetMean(), hist_ThrPyth_160_100->GetMean(), hist_ThrPyth_180_100->GetMean(), hist_ThrPyth_240_100->GetMean(), hist_ThrPyth_365_100->GetMean()};
	double Hadron[] = {hist_nHadron_912_100->GetMean(), hist_nHadron_160_100->GetMean(), hist_nHadron_180_100->GetMean(), hist_nHadron_240_100->GetMean(), hist_nHadron_365_100->GetMean()};

	TGraph* grap_RunThrust = new TGraph(sizeof(Sprime)/sizeof(Sprime[0]), Sprime, Thrust);
	grap_RunThrust->SetTitle("Running of Inverse Thrust");
	grap_RunThrust->GetXaxis()->SetTitle("#sqrt{s}");
	grap_RunThrust->GetYaxis()->SetTitle("<1-T>");
	grap_RunThrust->SetLineColor(kBlack); 
	grap_RunThrust->SetMarkerColor(kBlack); 
	grap_RunThrust->SetMarkerStyle(kStar); 
	grap_RunThrust->SetLineWidth(2); 

	TGraph* grap_RunHadron = new TGraph(sizeof(Sprime)/sizeof(Sprime[0]), Sprime, Hadron);
	grap_RunHadron->SetTitle("Running of Charged Multiplicity");
	grap_RunHadron->GetXaxis()->SetTitle("#sqrt{s}");
	grap_RunHadron->GetYaxis()->SetTitle("<N_{CH}>");
	grap_RunHadron->SetLineColor(kBlack);
	grap_RunHadron->SetMarkerColor(kBlack);
	grap_RunHadron->SetMarkerStyle(kStar);
	grap_RunHadron->SetLineWidth(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv = new TCanvas("cv", "FCC-ee ISR Studies", 1200, 600);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv->Divide(2,1);
	cv->cd(1)->SetLeftMargin(0.15);
	cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	cv->cd(2)->SetLeftMargin(0.15);
	cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
 
	// Draw
	cv->cd(1);
	grap_RunThrust->Draw("ALP");
	cv->cd(2);
	grap_RunHadron->Draw("ALP");

	// Set limits
	// grap_RunThrust->GetYaxis()->SetRangeUser(1E-5,1E0);
	// grap_RunHadron->GetYaxis()->SetRangeUser(1E-7,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv->Modified();
}