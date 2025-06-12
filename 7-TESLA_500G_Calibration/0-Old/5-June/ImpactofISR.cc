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
void ImpactofISR()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TFile* input_LEP912 = new TFile("cut_TES50t_wiR.root", "READ");
	TFile* input_TES50t = new TFile("cut_LEP912_wiR.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Esprime_LEP = (TH1F*)input_LEP912->Get("hist_Esprime_norm"); 
	hist_Esprime_LEP->SetLineColor(kRed+2); hist_Esprime_LEP->SetMarkerColor(kRed+2); hist_Esprime_LEP->SetMarkerStyle(kStar); hist_Esprime_LEP->SetLineWidth(3); hist_Esprime_LEP->SetStats(kFALSE);

	TH1F *hist_Esprime_FCC = (TH1F*)input_TES50t->Get("hist_Esprime_norm"); 
	hist_Esprime_FCC->SetLineColor(kBlue); hist_Esprime_FCC->SetMarkerColor(kBlue); hist_Esprime_FCC->SetMarkerStyle(kStar); hist_Esprime_FCC->SetLineWidth(3); hist_Esprime_FCC->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_Esprime_LEP->Scale(1.0/hist_Esprime_LEP->Integral());
	hist_Esprime_FCC->Scale(1.0/hist_Esprime_FCC->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_Esprime_LEP->GetXaxis()->SetTitle("#sqrt{s} /#sqrt{s'}");
	hist_Esprime_LEP->GetYaxis()->SetTitle("P(#sqrt{s} /#sqrt{s'})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg_thr = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg_thr->AddEntry(hist_Esprime_LEP, "#sqrt{s} = 91.2 GeV", "p");
	lg_thr->AddEntry(hist_Esprime_FCC, "#sqrt{s} = 500 GeV", "p");
	lg_thr->SetTextSize(0.03);
	
	// Create canvas
	TCanvas* c_thr = new TCanvas("c_thr", "Impact of ISR on Effective COM", 1200, 480);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	c_thr->Divide(2,1);
	c_thr->cd(1)->SetLeftMargin(0.15);
	c_thr->cd(1)->SetLogy();
	c_thr->cd(1)->SetTickx(); c_thr->cd(1)->SetTicky();
	c_thr->cd(1)->SetGridx(); c_thr->cd(1)->SetGridy();
	c_thr->cd(2)->SetLeftMargin(0.15);
	c_thr->cd(2)->SetLogy();
	c_thr->cd(2)->SetTickx(); c_thr->cd(2)->SetTicky();
	c_thr->cd(2)->SetGridx(); c_thr->cd(2)->SetGridy();

	// Draw
	c_thr->cd(1);
	hist_Esprime_LEP->Draw("P");
	hist_Esprime_FCC->Draw("P SAME");

	c_thr->cd(2);
	hist_Esprime_LEP->Draw("P");
	hist_Esprime_FCC->Draw("P SAME");
	lg_thr->Draw("SAME");

	// Set limits
	hist_Esprime_LEP->GetYaxis()->SetRangeUser(1E-6,1E1);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	c_thr->Modified();

}