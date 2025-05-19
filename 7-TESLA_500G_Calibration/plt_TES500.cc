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
void plt_TES500()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOTs
	TFile* input_TES50t_noR = new TFile("cut_TES50t_noR.root", "READ");
	TFile* input_TES500_noR = new TFile("cut_TES500_noR.root", "READ");
	TFile* input_TES50t_wiR = new TFile("cut_TES50t_wiR.root", "READ");
	TFile* input_TES500_wiR = new TFile("cut_TES500_wiR.root", "READ");
	TFile* input_LEP912_noR = new TFile("cut_LEP912_noR.root", "READ");
	TFile* input_LEP912_wiR = new TFile("cut_LEP912_wiR.root", "READ");
	
	// Read TTrees
	TTree* trees_TES50t_noR = (TTree*)input_TES50t_noR->Get("tree_cut");
	TTree* trees_TES500_noR = (TTree*)input_TES500_noR->Get("tree_cut");
	TTree* trees_TES50t_wiR = (TTree*)input_TES50t_wiR->Get("tree_cut");
	TTree* trees_TES500_wiR = (TTree*)input_TES500_wiR->Get("tree_cut");
	TTree* trees_LEP912_noR = (TTree*)input_LEP912_noR->Get("tree_cut");
	TTree* trees_LEP912_wiR = (TTree*)input_LEP912_wiR->Get("tree_cut");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_nHadron_TES500_noR = (TH1F*)input_TES500_noR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_TES500_noR = (TH1F*)input_TES500_noR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_TES500_noR = (TH1F*)input_TES500_noR->Get("hist_ThrPyth");

	TH1F *hist_nHadron_TES50t_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_TES50t_noR = (TH1F*)input_TES50t_noR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_TES50t_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth");

	TH1F *hist_nHadron_TES50t_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_TES50t_wiR = (TH1F*)input_TES50t_wiR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_TES50t_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth");

	TH1F *hist_nHadron_TES500_wiR = (TH1F*)input_TES500_wiR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_TES500_wiR = (TH1F*)input_TES500_wiR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_TES500_wiR = (TH1F*)input_TES500_wiR->Get("hist_ThrPyth");

	TH1F *hist_nHadron_LEP912_noR = (TH1F*)input_LEP912_noR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_LEP912_noR = (TH1F*)input_LEP912_noR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_LEP912_noR = (TH1F*)input_LEP912_noR->Get("hist_ThrPyth");

	TH1F *hist_nHadron_LEP912_wiR = (TH1F*)input_LEP912_wiR->Get("hist_nHadron");
	TH1F *KNOO_nHadron_LEP912_wiR = (TH1F*)input_LEP912_wiR->Get("KNOO_nHadron");
	TH1F *hist_ThrPyth_LEP912_wiR = (TH1F*)input_LEP912_wiR->Get("hist_ThrPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Beautify histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_nHadron_TES500_noR->SetLineColor(kRed+2); hist_nHadron_TES500_noR->SetMarkerColor(kRed+2); hist_nHadron_TES500_noR->SetMarkerStyle(kOpenCircle);
	hist_nHadron_TES500_wiR->SetLineColor(kRed+2); hist_nHadron_TES500_wiR->SetMarkerColor(kRed+2); hist_nHadron_TES500_wiR->SetMarkerStyle(kStar);
	hist_nHadron_TES50t_noR->SetLineColor(kBlue+2); hist_nHadron_TES50t_noR->SetMarkerColor(kBlue+2); hist_nHadron_TES50t_noR->SetMarkerStyle(kOpenCircle);
	hist_nHadron_TES50t_wiR->SetLineColor(kBlue+2); hist_nHadron_TES50t_wiR->SetMarkerColor(kBlue+2); hist_nHadron_TES50t_wiR->SetMarkerStyle(kStar);
	hist_nHadron_LEP912_noR->SetLineColor(kGreen+2); hist_nHadron_LEP912_noR->SetMarkerColor(kGreen+2); hist_nHadron_LEP912_noR->SetMarkerStyle(kOpenCircle);
	hist_nHadron_LEP912_wiR->SetLineColor(kGreen+2); hist_nHadron_LEP912_wiR->SetMarkerColor(kGreen+2); hist_nHadron_LEP912_wiR->SetMarkerStyle(kStar);

	KNOO_nHadron_TES500_noR->SetLineColor(kRed+2); KNOO_nHadron_TES500_noR->SetMarkerColor(kRed+2); KNOO_nHadron_TES500_noR->SetMarkerStyle(kOpenCircle);
	KNOO_nHadron_TES500_wiR->SetLineColor(kRed+2); KNOO_nHadron_TES500_wiR->SetMarkerColor(kRed+2); KNOO_nHadron_TES500_wiR->SetMarkerStyle(kStar);
	KNOO_nHadron_TES50t_noR->SetLineColor(kBlue+2); KNOO_nHadron_TES50t_noR->SetMarkerColor(kBlue+2); KNOO_nHadron_TES50t_noR->SetMarkerStyle(kOpenCircle);
	KNOO_nHadron_TES50t_wiR->SetLineColor(kBlue+2); KNOO_nHadron_TES50t_wiR->SetMarkerColor(kBlue+2); KNOO_nHadron_TES50t_wiR->SetMarkerStyle(kStar);
	KNOO_nHadron_LEP912_noR->SetLineColor(kGreen+2); KNOO_nHadron_LEP912_noR->SetMarkerColor(kGreen+2); KNOO_nHadron_LEP912_noR->SetMarkerStyle(kOpenCircle);
	KNOO_nHadron_LEP912_wiR->SetLineColor(kGreen+2); KNOO_nHadron_LEP912_wiR->SetMarkerColor(kGreen+2); KNOO_nHadron_LEP912_wiR->SetMarkerStyle(kStar);

	hist_ThrPyth_TES500_noR->SetLineColor(kBlue+2); hist_ThrPyth_TES500_noR->SetMarkerColor(kBlue+2); hist_ThrPyth_TES500_noR->SetMarkerStyle(kOpenCircle);
	hist_ThrPyth_TES500_wiR->SetLineColor(kBlue+2); hist_ThrPyth_TES500_wiR->SetMarkerColor(kBlue+2); hist_ThrPyth_TES500_wiR->SetMarkerStyle(kStar);
	hist_ThrPyth_TES50t_noR->SetLineColor(kBlue+2); hist_ThrPyth_TES50t_noR->SetMarkerColor(kBlue+2); hist_ThrPyth_TES50t_noR->SetMarkerStyle(kOpenCircle);
	hist_ThrPyth_TES50t_wiR->SetLineColor(kBlue+2); hist_ThrPyth_TES50t_wiR->SetMarkerColor(kBlue+2); hist_ThrPyth_TES50t_wiR->SetMarkerStyle(kStar);
	hist_ThrPyth_LEP912_noR->SetLineColor(kGreen+2); hist_ThrPyth_LEP912_noR->SetMarkerColor(kGreen+2); hist_ThrPyth_LEP912_noR->SetMarkerStyle(kOpenCircle);
	hist_ThrPyth_LEP912_wiR->SetLineColor(kGreen+2); hist_ThrPyth_LEP912_wiR->SetMarkerColor(kGreen+2); hist_ThrPyth_LEP912_wiR->SetMarkerStyle(kStar);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable statboxes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_nHadron_TES500_noR->SetStats(kFALSE); KNOO_nHadron_TES500_noR->SetStats(kFALSE); hist_ThrPyth_TES500_noR->SetStats(kFALSE);
	hist_nHadron_TES50t_noR->SetStats(kFALSE); KNOO_nHadron_TES50t_noR->SetStats(kFALSE); hist_ThrPyth_TES50t_noR->SetStats(kFALSE);
	hist_nHadron_TES50t_wiR->SetStats(kFALSE); KNOO_nHadron_TES50t_wiR->SetStats(kFALSE); hist_ThrPyth_TES50t_wiR->SetStats(kFALSE);
	hist_nHadron_TES500_wiR->SetStats(kFALSE); KNOO_nHadron_TES500_wiR->SetStats(kFALSE); hist_ThrPyth_TES500_wiR->SetStats(kFALSE);
	hist_nHadron_LEP912_noR->SetStats(kFALSE); KNOO_nHadron_LEP912_noR->SetStats(kFALSE); hist_ThrPyth_LEP912_noR->SetStats(kFALSE);
	hist_nHadron_LEP912_wiR->SetStats(kFALSE); KNOO_nHadron_LEP912_wiR->SetStats(kFALSE); hist_ThrPyth_LEP912_wiR->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Importing raw TEXT data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_Thr1999 = new TH1F("hist_Thr1999", "Inverse Thrust (wo top)", 500, 0, 0.4);
	// Beautify
	hist_Thr1999->SetStats(kFALSE);
	hist_Thr1999->SetTitle("Inverse Thrust wo Top wo ISR");
	hist_Thr1999->SetName("hist_Thr1999");
	hist_Thr1999->SetLineColor(kBlack);
	hist_Thr1999->SetMarkerColor(kBlack);
	hist_Thr1999->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr1999->GetXaxis()->SetTitle("1-T");
	hist_Thr1999->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_10("EXP_TES_500_THR_wot.txt");
	// Read through TXT
	while ( !infile_10.eof() ) {
		// Set reading order
		infile_10 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr1999->SetBinContent(hist_Thr1999->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr1999->SetBinError(hist_Thr1999->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_10.close();	

	// // Read Histogram
	TH1F *hist_Thr199T = new TH1F("hist_Thr199T", "Inverse Thrust (wi top)", 500, 0, 0.4);
	// Beautify
	hist_Thr199T->SetStats(kFALSE);
	hist_Thr199T->SetTitle("Inverse Thrust wi Top wo ISR");
	hist_Thr199T->SetName("hist_Thr199T");
	hist_Thr199T->SetLineColor(kBlack);
	hist_Thr199T->SetMarkerColor(kBlack);
	hist_Thr199T->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr199T->GetXaxis()->SetTitle("1-T");
	hist_Thr199T->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_11("EXP_TES_500_THR_wit.txt");
	// Read through TXT
	while ( !infile_11.eof() ) {
		// Set reading order
		infile_11 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr199T->SetBinContent(hist_Thr199T->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr199T->SetBinError(hist_Thr199T->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_11.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_nHadron_LEP912_noR->Scale(1.0/hist_nHadron_LEP912_noR->Integral());
	hist_nHadron_LEP912_wiR->Scale(1.0/hist_nHadron_LEP912_wiR->Integral());
	hist_nHadron_TES500_noR->Scale(1.0/hist_nHadron_TES500_noR->Integral());
	hist_nHadron_TES50t_noR->Scale(1.0/hist_nHadron_TES50t_noR->Integral());
	hist_nHadron_TES500_wiR->Scale(1.0/hist_nHadron_TES500_wiR->Integral());
	hist_nHadron_TES50t_wiR->Scale(1.0/hist_nHadron_TES50t_wiR->Integral());

	// Divide by area under hist
	// KNOO_nHadron_LEP912_noR->Scale(1.0/KNOO_nHadron_LEP912_noR->Integral());
	// KNOO_nHadron_LEP912_wiR->Scale(1.0/KNOO_nHadron_LEP912_wiR->Integral());
	// KNOO_nHadron_TES500_noR->Scale(1.0/KNOO_nHadron_TES500_noR->Integral());
	// KNOO_nHadron_TES50t_noR->Scale(1.0/KNOO_nHadron_TES50t_noR->Integral());
	// KNOO_nHadron_TES500_wiR->Scale(1.0/KNOO_nHadron_TES500_wiR->Integral());
	// KNOO_nHadron_TES50t_wiR->Scale(1.0/KNOO_nHadron_TES50t_wiR->Integral());

	// Divide by area under hist
	hist_ThrPyth_LEP912_noR->Scale(1.0/hist_ThrPyth_LEP912_noR->Integral());
	hist_ThrPyth_LEP912_wiR->Scale(1.0/hist_ThrPyth_LEP912_wiR->Integral());
	hist_ThrPyth_TES500_noR->Scale(1.0/hist_ThrPyth_TES500_noR->Integral());
	hist_ThrPyth_TES50t_noR->Scale(1.0/hist_ThrPyth_TES50t_noR->Integral());
	hist_ThrPyth_TES500_wiR->Scale(1.0/hist_ThrPyth_TES500_wiR->Integral());
	hist_ThrPyth_TES50t_wiR->Scale(1.0/hist_ThrPyth_TES50t_wiR->Integral());
	
	// Divide by area under hist
	hist_Thr1999->Scale(1.0/hist_Thr1999->Integral());
	hist_Thr199T->Scale(1.0/hist_Thr199T->Integral());

	// Print check of integrals
	// cout << "Integration : " << hist_nHadron->Integral() << endl;
	// cout << "Integration : " << KNOO_nHadron->Integral() << endl;
	// cout << "Integration : " << hist_ThrPyth->Integral() << endl;
	// cout << "Integration : " << hist_Thr1999->Integral() << endl;
	// cout << "Integration : " << hist_Thr199T->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Charged Hadronic Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Add legend
	// TLegend *leg_nch = new TLegend(0.4, 0.2, 0.85, 0.4);
	// leg_nch->AddEntry(hist_nHadron_TES50t_wiR, "500 GeV (wi top wi ISR)", "p");
	// leg_nch->AddEntry(hist_nHadron_TES50t_noR, "500 GeV (wi top wo ISR)", "p");
	// leg_nch->AddEntry(hist_nHadron_TES500_wiR, "500 GeV (wo top wi ISR)", "p");
	// leg_nch->AddEntry(hist_nHadron_TES500_noR, "500 GeV (wo top wo ISR)", "p");
	// leg_nch->AddEntry(hist_nHadron_LEP912_wiR, "91.2 GeV (wi ISR)", "p");
	// leg_nch->AddEntry(hist_nHadron_LEP912_noR, "91.2 GeV (wo ISR)", "p");
	// leg_nch->SetTextSize(0.03);

	// // Create canvas
	// TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);

	// // Beautify
	// c_nch->Divide(2,1);
	// c_nch->cd(1)->SetLeftMargin(0.15);
	// c_nch->cd(1)->SetLogy();
	// c_nch->cd(1)->SetTickx(); c_nch->cd(1)->SetTicky();
	// c_nch->cd(1)->SetGridx(); c_nch->cd(1)->SetGridy();
	// c_nch->cd(2)->SetLeftMargin(0.15);
	// c_nch->cd(2)->SetLogy();
	// c_nch->cd(2)->SetTickx(); c_nch->cd(2)->SetTicky();
	// c_nch->cd(2)->SetGridx(); c_nch->cd(2)->SetGridy();
	
	// // Draw
	// c_nch->cd(1);
	// hist_nHadron_TES50t_wiR->Draw("P");
	// hist_nHadron_TES500_wiR->Draw("PSAME");
	// hist_nHadron_TES50t_noR->Draw("PSAME");
	// hist_nHadron_TES500_noR->Draw("PSAME");
	// hist_nHadron_LEP912_noR->Draw("PSAME");
	// hist_nHadron_LEP912_wiR->Draw("PSAME");
	// leg_nch->Draw("SAME");
	// c_nch->cd(2);
	// KNOO_nHadron_TES50t_wiR->Draw("P");
	// KNOO_nHadron_TES500_wiR->Draw("PSAME");
	// KNOO_nHadron_TES50t_noR->Draw("PSAME");
	// KNOO_nHadron_TES500_noR->Draw("PSAME");
	// KNOO_nHadron_LEP912_noR->Draw("PSAME");
	// KNOO_nHadron_LEP912_wiR->Draw("PSAME");
	// leg_nch->Draw("SAME");

	// hist_nHadron_TES50t_wiR->GetYaxis()->SetRangeUser(1E-5,1E0);
	// KNOO_nHadron_TES50t_wiR->GetYaxis()->SetRangeUser(1E-5,1E0);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// c_nch->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust (impact of ISR/top)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	// Add legend
// 	TLegend *lg_thr = new TLegend(0.4, 0.2, 0.85, 0.4);
// 	lg_thr->AddEntry(hist_ThrPyth_TES50t_noR, "500 GeV (wo ISR)", "p");
// 	lg_thr->AddEntry(hist_ThrPyth_TES500_wiR, "500 GeV (wi ISR)", "p");
// 	lg_thr->AddEntry(hist_ThrPyth_LEP912_noR, "91.2 GeV (wo ISR)", "p");
// 	lg_thr->AddEntry(hist_ThrPyth_LEP912_wiR, "91.2 GeV (wi ISR)", "p");
// 	lg_thr->AddEntry(hist_Thr1999, "1999 TESLA study", "p");
// 	lg_thr->SetTextSize(0.04);

// 	// Create canvas
// 	TCanvas* c_thr = new TCanvas("c_thr", "Inverse Thrust distributions", 800, 600);

// 	// Beautify
// 	gStyle->SetErrorX(0.000000001);
// 	c_thr->Divide(2,1);
// 	c_thr->cd(1)->SetLeftMargin(0.15);
// 	c_thr->cd(1)->SetLogy();
// 	c_thr->cd(1)->SetTickx(); c_thr->cd(1)->SetTicky();
// 	c_thr->cd(1)->SetGridx(); c_thr->cd(1)->SetGridy();
// 	c_thr->cd(2)->SetLeftMargin(0.15);
// 	c_thr->cd(2)->SetLogy();
// 	c_thr->cd(2)->SetTickx(); c_thr->cd(2)->SetTicky();
// 	c_thr->cd(2)->SetGridx(); c_thr->cd(2)->SetGridy();
	
// 	hist_Thr1999->GetYaxis()->SetRangeUser(1E-4,1E0);
// 	hist_Thr199T->GetYaxis()->SetRangeUser(1E-4,1E0);

// 	// Draw
// 	c_thr->cd(1);
// 	hist_Thr1999->Draw("P");
// 	hist_ThrPyth_TES500_wiR->Draw("PSAME");
// 	hist_ThrPyth_TES500_noR->Draw("PSAME");
// 	hist_ThrPyth_LEP912_wiR->Draw("PSAME");
// 	hist_ThrPyth_LEP912_noR->Draw("PSAME");
// 	lg_thr->Draw("SAME");
// 	c_thr->cd(2);
// 	hist_Thr199T->Draw("P");
// 	hist_ThrPyth_TES50t_wiR->Draw("PSAME");
// 	hist_ThrPyth_TES50t_noR->Draw("PSAME");
// 	hist_ThrPyth_LEP912_wiR->Draw("PSAME");
// 	hist_ThrPyth_LEP912_noR->Draw("PSAME");
// 	lg_thr->Draw("SAME");

// // Modify stat-box
// 	gStyle->SetOptStat();
// 	c_thr->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of ISR/Top on Thrust/Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	TH1F *hist_ThrPyth_TES50t_wiR_000 = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_000");
// 	TH1F *hist_ThrPyth_TES50t_wiR_300 = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_300");
// 	TH1F *hist_ThrPyth_TES50t_wiR_425 = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_425");
// 	TH1F *hist_ThrPyth_TES50t_wiR_500 = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_500");

// 	TH1F *hist_nHadron_TES50t_wiR_000 = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_000");
// 	TH1F *hist_nHadron_TES50t_wiR_300 = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_300");
// 	TH1F *hist_nHadron_TES50t_wiR_425 = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_425");
// 	TH1F *hist_nHadron_TES50t_wiR_500 = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_500");

// 	hist_ThrPyth_TES50t_wiR_000->SetLineColor(kYellow+2); hist_ThrPyth_TES50t_wiR_000->SetMarkerColor(kYellow+2); hist_ThrPyth_TES50t_wiR_000->SetMarkerStyle(53); hist_ThrPyth_TES50t_wiR_000->SetMarkerSize(1.5);
// 	hist_ThrPyth_TES50t_wiR_300->SetLineColor(kBlue+2); hist_ThrPyth_TES50t_wiR_300->SetMarkerColor(kBlue+2); hist_ThrPyth_TES50t_wiR_300->SetMarkerStyle(53); hist_ThrPyth_TES50t_wiR_300->SetMarkerSize(1.5);
// 	hist_ThrPyth_TES50t_wiR_425->SetLineColor(kGreen+2); hist_ThrPyth_TES50t_wiR_425->SetMarkerColor(kGreen+2); hist_ThrPyth_TES50t_wiR_425->SetMarkerStyle(53); hist_ThrPyth_TES50t_wiR_425->SetMarkerSize(1.5);
// 	hist_ThrPyth_TES50t_wiR_500->SetLineColor(kRed+2); hist_ThrPyth_TES50t_wiR_500->SetMarkerColor(kRed+2); hist_ThrPyth_TES50t_wiR_500->SetMarkerStyle(53); hist_ThrPyth_TES50t_wiR_500->SetMarkerSize(1.5);

// 	hist_nHadron_TES50t_wiR_000->SetLineColor(kYellow+2); hist_nHadron_TES50t_wiR_000->SetMarkerColor(kYellow+2); hist_nHadron_TES50t_wiR_000->SetMarkerStyle(53); hist_nHadron_TES50t_wiR_000->SetMarkerSize(1.5);
// 	hist_nHadron_TES50t_wiR_300->SetLineColor(kBlue+2); hist_nHadron_TES50t_wiR_300->SetMarkerColor(kBlue+2); hist_nHadron_TES50t_wiR_300->SetMarkerStyle(53); hist_nHadron_TES50t_wiR_300->SetMarkerSize(1.5);
// 	hist_nHadron_TES50t_wiR_425->SetLineColor(kGreen+2); hist_nHadron_TES50t_wiR_425->SetMarkerColor(kGreen+2); hist_nHadron_TES50t_wiR_425->SetMarkerStyle(53); hist_nHadron_TES50t_wiR_425->SetMarkerSize(1.5);
// 	hist_nHadron_TES50t_wiR_500->SetLineColor(kRed+2); hist_nHadron_TES50t_wiR_500->SetMarkerColor(kRed+2); hist_nHadron_TES50t_wiR_500->SetMarkerStyle(53); hist_nHadron_TES50t_wiR_500->SetMarkerSize(1.5);

// 	hist_ThrPyth_TES50t_wiR_000->SetStats(kFALSE); hist_ThrPyth_TES50t_wiR_300->SetStats(kFALSE); hist_ThrPyth_TES50t_wiR_425->SetStats(kFALSE); hist_ThrPyth_TES50t_wiR_500->SetStats(kFALSE);
// 	hist_nHadron_TES50t_wiR_000->SetStats(kFALSE); hist_nHadron_TES50t_wiR_300->SetStats(kFALSE); hist_nHadron_TES50t_wiR_425->SetStats(kFALSE); hist_nHadron_TES50t_wiR_500->SetStats(kFALSE);

// 	hist_ThrPyth_TES50t_wiR_000->Scale(1.0/hist_ThrPyth_TES50t_wiR_000->Integral()); hist_ThrPyth_TES50t_wiR_300->Scale(1.0/hist_ThrPyth_TES50t_wiR_300->Integral());
// 	hist_ThrPyth_TES50t_wiR_425->Scale(1.0/hist_ThrPyth_TES50t_wiR_425->Integral()); hist_ThrPyth_TES50t_wiR_500->Scale(1.0/hist_ThrPyth_TES50t_wiR_500->Integral());
// 	hist_nHadron_TES50t_wiR_000->Scale(1.0/hist_nHadron_TES50t_wiR_000->Integral()); hist_nHadron_TES50t_wiR_300->Scale(1.0/hist_nHadron_TES50t_wiR_300->Integral());
// 	hist_nHadron_TES50t_wiR_425->Scale(1.0/hist_nHadron_TES50t_wiR_425->Integral()); hist_nHadron_TES50t_wiR_500->Scale(1.0/hist_nHadron_TES50t_wiR_500->Integral());

// 	// Add legend
// 	TLegend *lg_thr2 = new TLegend(0.4, 0.2, 0.85, 0.4);
// 	lg_thr2->AddEntry(hist_ThrPyth_TES50t_wiR_000, "#sqrt{s'} cut at 0 GeV", "p");
// 	lg_thr2->AddEntry(hist_ThrPyth_TES50t_wiR_300, "#sqrt{s'} cut at 300 GeV", "p");
// 	lg_thr2->AddEntry(hist_ThrPyth_TES50t_wiR_425, "#sqrt{s'} cut at 425 GeV", "p");
// 	lg_thr2->AddEntry(hist_ThrPyth_TES50t_wiR_500, "#sqrt{s'} cut at 500 GeV", "p");
// 	lg_thr2->SetTextSize(0.03);

// 	// Create canvas
// 	TCanvas* c_thr2 = new TCanvas("c_thr2", "Impact of #sqrt{s'} cuts on Event Shapes", 800, 600);

// 	// Beautify
// 	gStyle->SetErrorX(0.000000001);
// 	c_thr2->Divide(2,1);
// 	c_thr2->cd(1)->SetLeftMargin(0.15);
// 	c_thr2->cd(1)->SetLogy();
// 	c_thr2->cd(1)->SetTickx(); c_thr2->cd(1)->SetTicky();
// 	c_thr2->cd(1)->SetGridx(); c_thr2->cd(1)->SetGridy();
// 	c_thr2->cd(2)->SetLeftMargin(0.15);
// 	c_thr2->cd(2)->SetLogy();
// 	c_thr2->cd(2)->SetTickx(); c_thr2->cd(2)->SetTicky();
// 	c_thr2->cd(2)->SetGridx(); c_thr2->cd(2)->SetGridy();

// 	hist_ThrPyth_TES50t_wiR_000->GetYaxis()->SetRangeUser(1E-4,1E0);
// 	hist_nHadron_TES50t_wiR_000->GetYaxis()->SetRangeUser(1E-5,1E0);

// 	// Draw
// 	c_thr2->cd(1);
// 	hist_ThrPyth_TES50t_wiR_000->Draw("P");
// 	hist_ThrPyth_TES50t_wiR_300->Draw("PSAME");
// 	hist_ThrPyth_TES50t_wiR_425->Draw("PSAME");
// 	hist_ThrPyth_TES50t_wiR_500->Draw("PSAME");
// 	lg_thr2->Draw("SAME");
// 	c_thr2->cd(2);
// 	hist_nHadron_TES50t_wiR_000->Draw("P");
// 	hist_nHadron_TES50t_wiR_300->Draw("PSAME");
// 	hist_nHadron_TES50t_wiR_425->Draw("PSAME");
// 	hist_nHadron_TES50t_wiR_500->Draw("PSAME");
// 	lg_thr2->Draw("SAME");

// // Modify stat-box
// 	gStyle->SetOptStat();
// 	c_thr2->Modified();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of Processes on Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// TH1F *hist_Esprime_Zq = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_Zq");
	// TH1F *hist_Esprime_ZZ = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_ZZ");
	// TH1F *hist_Esprime_WW = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_WW");
	// TH1F *hist_Esprime_tt = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_tt");
	// TH1F *hist_Esprime_ZZWWtt = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_ZZWWtt");

	// TH1F *hist_ThrPyth_Zq = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_Zq");
	// TH1F *hist_ThrPyth_ZZ = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_ZZ");
	// TH1F *hist_ThrPyth_WW = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_WW");
	// TH1F *hist_ThrPyth_tt = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_tt");
	// TH1F *hist_ThrPyth_ZZWWtt = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_ZZWWtt");

	// hist_Esprime_Zq->SetLineColor(kYellow+2); hist_Esprime_Zq->SetMarkerColor(kYellow+2); hist_Esprime_Zq->SetMarkerStyle(kStar); hist_Esprime_Zq->SetLineWidth(2);
	// hist_Esprime_ZZ->SetLineColor(kBlue+2); hist_Esprime_ZZ->SetMarkerColor(kBlue+2); hist_Esprime_ZZ->SetMarkerStyle(kStar); hist_Esprime_ZZ->SetLineWidth(2);
	// hist_Esprime_WW->SetLineColor(kGreen+2); hist_Esprime_WW->SetMarkerColor(kGreen+2); hist_Esprime_WW->SetMarkerStyle(kStar); hist_Esprime_WW->SetLineWidth(2);
	// hist_Esprime_tt->SetLineColor(kRed+2); hist_Esprime_tt->SetMarkerColor(kRed+2); hist_Esprime_tt->SetMarkerStyle(kStar); hist_Esprime_tt->SetLineWidth(2);
	// hist_Esprime_ZZWWtt->SetLineColor(kMagenta+2); hist_Esprime_ZZWWtt->SetMarkerColor(kMagenta+2); hist_Esprime_ZZWWtt->SetMarkerStyle(kStar); hist_Esprime_ZZWWtt->SetLineWidth(2);

	// hist_ThrPyth_TES50t_wiR->SetLineColor(kBlack); hist_ThrPyth_TES50t_wiR->SetMarkerColor(kBlack); hist_ThrPyth_TES50t_wiR->SetMarkerStyle(kStar); hist_ThrPyth_TES50t_wiR->SetLineWidth(3);
	// hist_ThrPyth_Zq->SetLineColor(kYellow+2); hist_ThrPyth_Zq->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq->SetMarkerStyle(kStar); hist_ThrPyth_Zq->SetLineWidth(3);
	// hist_ThrPyth_ZZ->SetLineColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerStyle(kStar); hist_ThrPyth_ZZ->SetLineWidth(3);
	// hist_ThrPyth_WW->SetLineColor(kGreen+2); hist_ThrPyth_WW->SetMarkerColor(kGreen+2); hist_ThrPyth_WW->SetMarkerStyle(kStar); hist_ThrPyth_WW->SetLineWidth(3);
	// hist_ThrPyth_tt->SetLineColor(kRed+2); hist_ThrPyth_tt->SetMarkerColor(kRed+2); hist_ThrPyth_tt->SetMarkerStyle(kStar); hist_ThrPyth_tt->SetLineWidth(3);
	// hist_ThrPyth_ZZWWtt->SetLineColor(kMagenta+2); hist_ThrPyth_ZZWWtt->SetMarkerColor(kMagenta+2); hist_ThrPyth_ZZWWtt->SetMarkerStyle(kStar); hist_ThrPyth_ZZWWtt->SetLineWidth(3);

	// hist_Esprime_Zq->SetStats(kFALSE); hist_Esprime_ZZ->SetStats(kFALSE); hist_Esprime_WW->SetStats(kFALSE); hist_Esprime_tt->SetStats(kFALSE);
	// hist_ThrPyth_Zq->SetStats(kFALSE); hist_ThrPyth_ZZ->SetStats(kFALSE); hist_ThrPyth_WW->SetStats(kFALSE); hist_ThrPyth_tt->SetStats(kFALSE);
	// hist_Esprime_ZZWWtt->SetStats(kFALSE); hist_ThrPyth_ZZWWtt->SetStats(kFALSE);

	// hist_ThrPyth_Zq->Scale(1.0/hist_ThrPyth_Zq->Integral()); hist_ThrPyth_ZZ->Scale(1.0/hist_ThrPyth_ZZ->Integral());
	// hist_ThrPyth_WW->Scale(1.0/hist_ThrPyth_WW->Integral()); hist_ThrPyth_tt->Scale(1.0/hist_ThrPyth_tt->Integral());
	// hist_ThrPyth_ZZWWtt->Scale(1.0/hist_ThrPyth_ZZWWtt->Integral());

	// // Add legend
	// TLegend *lg_thr3 = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lg_thr3->AddEntry(hist_Esprime_Zq, "ee#rightarrow#gamma/Z_{0}#rightarrowq#bar{q}", "pl");
	// lg_thr3->AddEntry(hist_Esprime_WW, "ee#rightarrowW^{+}W^{-}#rightarrowq#bar{q}", "pl");
	// lg_thr3->AddEntry(hist_Esprime_ZZ, "ee#rightarrowZ_{0}Z_{0}#rightarrowq#bar{q}", "pl");
	// lg_thr3->AddEntry(hist_Esprime_tt, "ee#rightarrow#gamma/Z_{0}#rightarrowt#bar{t}", "pl");
	// lg_thr3->AddEntry(hist_Esprime_ZZWWtt, "ee#rightarrowZZ,WW,t#bar{t}", "pl");
	// lg_thr3->AddEntry(hist_ThrPyth_TES50t_wiR, "ee#rightarrow#gamma/Z/ZZ/WW/t#bar{t}#rightarrowq#bar{q}", "p");
	// lg_thr3->AddEntry(hist_Thr199T, "1999 TESLA study", "p");
	// lg_thr3->SetTextSize(0.03);
	
	// // Create canvas
	// TCanvas* c_thr3 = new TCanvas("c_thr3", "Process-separated Event Shapes", 800, 600);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// c_thr3->Divide(2,1);
	// c_thr3->cd(1)->SetLeftMargin(0.15);
	// c_thr3->cd(1)->SetLogy();
	// c_thr3->cd(1)->SetTickx(); c_thr3->cd(1)->SetTicky();
	// c_thr3->cd(1)->SetGridx(); c_thr3->cd(1)->SetGridy();
	// c_thr3->cd(2)->SetLeftMargin(0.15);
	// c_thr3->cd(2)->SetLogy();
	// c_thr3->cd(2)->SetTickx(); c_thr3->cd(2)->SetTicky();
	// c_thr3->cd(2)->SetGridx(); c_thr3->cd(2)->SetGridy();
	
	// // Draw
	// c_thr3->cd(1);
	// hist_Esprime_Zq->Draw("L");
	// hist_Esprime_ZZ->Draw("LSAME");
	// hist_Esprime_WW->Draw("LSAME");
	// hist_Esprime_tt->Draw("LSAME");
	// hist_Esprime_ZZWWtt->Draw("LSAME");
	// lg_thr3->Draw("SAME");
	// c_thr3->cd(2);
	// hist_ThrPyth_Zq->Draw("P");
	// hist_ThrPyth_ZZ->Draw("PSAME");
	// hist_ThrPyth_WW->Draw("PSAME");
	// hist_ThrPyth_tt->Draw("PSAME");
	// hist_ThrPyth_ZZWWtt->Draw("PSAME");
	// hist_ThrPyth_TES50t_wiR->Draw("PSAME");
	// hist_Thr199T->Draw("PSAME");
	// lg_thr3->Draw("SAME");

	// // Set limits
	// hist_Esprime_Zq->GetYaxis()->SetRangeUser(1E0,1E7);
	// hist_ThrPyth_TES50t_wiR->GetYaxis()->SetRangeUser(1E-7,1E1);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// c_thr3->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of Processes on Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Esprime_Zq_noR = (TH1F*)input_TES50t_noR->Get("hist_Esprime_Zq");
	TH1F *hist_Esprime_ZZ_noR = (TH1F*)input_TES50t_noR->Get("hist_Esprime_ZZ");
	TH1F *hist_Esprime_WW_noR = (TH1F*)input_TES50t_noR->Get("hist_Esprime_WW");
	TH1F *hist_Esprime_tt_noR = (TH1F*)input_TES50t_noR->Get("hist_Esprime_tt");
	TH1F *hist_Esprime_Zq_wiR = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_Zq");
	TH1F *hist_Esprime_ZZ_wiR = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_ZZ");
	TH1F *hist_Esprime_WW_wiR = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_WW");
	TH1F *hist_Esprime_tt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_Esprime_tt");

	TH1F *hist_ThrPy99_al_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPy99_000"); hist_ThrPy99_al_noR->Scale(1.0/hist_ThrPy99_al_noR->Integral());
	TH1F *hist_ThrPy99_Zq_noR = (TH1F*)input_TES500_noR->Get("hist_ThrPy99_Zq"); hist_ThrPy99_Zq_noR->Scale(1.0/hist_ThrPy99_Zq_noR->Integral());
	TH1F *hist_ThrPy99_ZZ_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPy99_ZZ"); hist_ThrPy99_ZZ_noR->Scale(1.0/hist_ThrPy99_ZZ_noR->Integral());
	TH1F *hist_ThrPy99_WW_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPy99_WW"); hist_ThrPy99_WW_noR->Scale(1.0/hist_ThrPy99_WW_noR->Integral());
	TH1F *hist_ThrPy99_tt_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPy99_tt"); hist_ThrPy99_tt_noR->Scale(1.0/hist_ThrPy99_tt_noR->Integral());
	TH1F *hist_ThrPy99_Zt_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPy99_Zt"); hist_ThrPy99_Zt_noR->Scale(1.0/hist_ThrPy99_Zt_noR->Integral());
	TH1F *hist_ThrPy99_al_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_000"); hist_ThrPy99_al_wiR->Scale(1.0/hist_ThrPy99_al_wiR->Integral());
	TH1F *hist_ThrPy99_Zq_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_Zq"); hist_ThrPy99_Zq_wiR->Scale(1.0/hist_ThrPy99_Zq_wiR->Integral());
	TH1F *hist_ThrPy99_ZZ_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_ZZ"); hist_ThrPy99_ZZ_wiR->Scale(1.0/hist_ThrPy99_ZZ_wiR->Integral());
	TH1F *hist_ThrPy99_WW_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_WW"); hist_ThrPy99_WW_wiR->Scale(1.0/hist_ThrPy99_WW_wiR->Integral());
	TH1F *hist_ThrPy99_tt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_tt"); hist_ThrPy99_tt_wiR->Scale(1.0/hist_ThrPy99_tt_wiR->Integral());
	TH1F *hist_ThrPy99_Zt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPy99_Zt"); hist_ThrPy99_Zt_wiR->Scale(1.0/hist_ThrPy99_Zt_wiR->Integral());

	TH1F *hist_ThrPyth_al_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_000");
	TH1F *hist_ThrPyth_Zq_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_ZZ_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_ZZ");
	TH1F *hist_ThrPyth_WW_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_WW");
	TH1F *hist_ThrPyth_tt_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_tt");
	TH1F *hist_ThrPyth_Zt_noR = (TH1F*)input_TES50t_noR->Get("hist_ThrPyth_Zt");
	TH1F *hist_ThrPyth_al_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_000");
	TH1F *hist_ThrPyth_Zq_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_ZZ_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_ZZ");
	TH1F *hist_ThrPyth_WW_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_WW");
	TH1F *hist_ThrPyth_tt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_tt");
	TH1F *hist_ThrPyth_Zt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_ThrPyth_Zt");

	TH1F *hist_nHadron_al_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron_000");
	TH1F *hist_nHadron_Zq_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron_Zq");
	TH1F *hist_nHadron_ZZ_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron_ZZ");
	TH1F *hist_nHadron_WW_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron_WW");
	TH1F *hist_nHadron_tt_noR = (TH1F*)input_TES50t_noR->Get("hist_nHadron_tt");
	TH1F *hist_nHadron_al_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_000");
	TH1F *hist_nHadron_Zq_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_Zq");
	TH1F *hist_nHadron_ZZ_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_ZZ");
	TH1F *hist_nHadron_WW_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_WW");
	TH1F *hist_nHadron_tt_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nHadron_tt");

	hist_Esprime_Zq_noR->SetLineColor(kYellow+2); hist_Esprime_Zq_noR->SetMarkerColor(kYellow+2); hist_Esprime_Zq_noR->SetMarkerStyle(kStar); hist_Esprime_Zq_noR->SetLineWidth(2); hist_Esprime_Zq_noR->SetStats(kFALSE);
	hist_Esprime_ZZ_noR->SetLineColor(kBlue+2); hist_Esprime_ZZ_noR->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_noR->SetMarkerStyle(kStar); hist_Esprime_ZZ_noR->SetLineWidth(2); hist_Esprime_ZZ_noR->SetStats(kFALSE);
	hist_Esprime_WW_noR->SetLineColor(kGreen+2); hist_Esprime_WW_noR->SetMarkerColor(kGreen+2); hist_Esprime_WW_noR->SetMarkerStyle(kStar); hist_Esprime_WW_noR->SetLineWidth(2); hist_Esprime_WW_noR->SetStats(kFALSE);
	hist_Esprime_tt_noR->SetLineColor(kRed+2); hist_Esprime_tt_noR->SetMarkerColor(kRed+2); hist_Esprime_tt_noR->SetMarkerStyle(kStar); hist_Esprime_tt_noR->SetLineWidth(2); hist_Esprime_tt_noR->SetStats(kFALSE);

	hist_Esprime_Zq_wiR->SetLineColor(kYellow+2); hist_Esprime_Zq_wiR->SetMarkerColor(kYellow+2); hist_Esprime_Zq_wiR->SetMarkerStyle(kStar); hist_Esprime_Zq_wiR->SetLineWidth(2); hist_Esprime_Zq_wiR->SetStats(kFALSE);
	hist_Esprime_ZZ_wiR->SetLineColor(kBlue+2); hist_Esprime_ZZ_wiR->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_wiR->SetMarkerStyle(kStar); hist_Esprime_ZZ_wiR->SetLineWidth(2); hist_Esprime_ZZ_wiR->SetStats(kFALSE);
	hist_Esprime_WW_wiR->SetLineColor(kGreen+2); hist_Esprime_WW_wiR->SetMarkerColor(kGreen+2); hist_Esprime_WW_wiR->SetMarkerStyle(kStar); hist_Esprime_WW_wiR->SetLineWidth(2); hist_Esprime_WW_wiR->SetStats(kFALSE);
	hist_Esprime_tt_wiR->SetLineColor(kRed+2); hist_Esprime_tt_wiR->SetMarkerColor(kRed+2); hist_Esprime_tt_wiR->SetMarkerStyle(kStar); hist_Esprime_tt_wiR->SetLineWidth(2); hist_Esprime_tt_wiR->SetStats(kFALSE);

	hist_ThrPy99_al_noR->SetLineColor(kBlack); hist_ThrPy99_al_noR->SetMarkerColor(kBlack); hist_ThrPy99_al_noR->SetMarkerStyle(kStar); hist_ThrPy99_al_noR->SetLineWidth(3); hist_ThrPy99_al_noR->SetStats(kFALSE);
	hist_ThrPy99_Zq_noR->SetLineColor(kYellow+2); hist_ThrPy99_Zq_noR->SetMarkerColor(kYellow+2); hist_ThrPy99_Zq_noR->SetMarkerStyle(kStar); hist_ThrPy99_Zq_noR->SetLineWidth(3); hist_ThrPy99_Zq_noR->SetStats(kFALSE);
	hist_ThrPy99_ZZ_noR->SetLineColor(kBlue+2); hist_ThrPy99_ZZ_noR->SetMarkerColor(kBlue+2); hist_ThrPy99_ZZ_noR->SetMarkerStyle(kStar); hist_ThrPy99_ZZ_noR->SetLineWidth(3); hist_ThrPy99_ZZ_noR->SetStats(kFALSE);
	hist_ThrPy99_WW_noR->SetLineColor(kGreen+2); hist_ThrPy99_WW_noR->SetMarkerColor(kGreen+2); hist_ThrPy99_WW_noR->SetMarkerStyle(kStar); hist_ThrPy99_WW_noR->SetLineWidth(3); hist_ThrPy99_WW_noR->SetStats(kFALSE);
	hist_ThrPy99_tt_noR->SetLineColor(kRed+2); hist_ThrPy99_tt_noR->SetMarkerColor(kRed+2); hist_ThrPy99_tt_noR->SetMarkerStyle(kStar); hist_ThrPy99_tt_noR->SetLineWidth(3); hist_ThrPy99_tt_noR->SetStats(kFALSE);   
	hist_ThrPy99_Zt_noR->SetLineColor(kMagenta+2); hist_ThrPy99_Zt_noR->SetMarkerColor(kMagenta+2); hist_ThrPy99_Zt_noR->SetMarkerStyle(kStar); hist_ThrPy99_Zt_noR->SetLineWidth(3); hist_ThrPy99_Zt_noR->SetStats(kFALSE);   

	hist_ThrPy99_al_wiR->SetLineColor(kBlack); hist_ThrPy99_al_wiR->SetMarkerColor(kBlack); hist_ThrPy99_al_wiR->SetMarkerStyle(kStar); hist_ThrPy99_al_wiR->SetLineWidth(3); hist_ThrPy99_al_wiR->SetStats(kFALSE);
	hist_ThrPy99_Zq_wiR->SetLineColor(kYellow+2); hist_ThrPy99_Zq_wiR->SetMarkerColor(kYellow+2); hist_ThrPy99_Zq_wiR->SetMarkerStyle(kStar); hist_ThrPy99_Zq_wiR->SetLineWidth(3); hist_ThrPy99_Zq_wiR->SetStats(kFALSE);
	hist_ThrPy99_ZZ_wiR->SetLineColor(kBlue+2); hist_ThrPy99_ZZ_wiR->SetMarkerColor(kBlue+2); hist_ThrPy99_ZZ_wiR->SetMarkerStyle(kStar); hist_ThrPy99_ZZ_wiR->SetLineWidth(3); hist_ThrPy99_ZZ_wiR->SetStats(kFALSE);
	hist_ThrPy99_WW_wiR->SetLineColor(kGreen+2); hist_ThrPy99_WW_wiR->SetMarkerColor(kGreen+2); hist_ThrPy99_WW_wiR->SetMarkerStyle(kStar); hist_ThrPy99_WW_wiR->SetLineWidth(3); hist_ThrPy99_WW_wiR->SetStats(kFALSE);
	hist_ThrPy99_tt_wiR->SetLineColor(kRed+2); hist_ThrPy99_tt_wiR->SetMarkerColor(kRed+2); hist_ThrPy99_tt_wiR->SetMarkerStyle(kStar); hist_ThrPy99_tt_wiR->SetLineWidth(3); hist_ThrPy99_tt_wiR->SetStats(kFALSE);  
	hist_ThrPy99_Zt_wiR->SetLineColor(kMagenta+2); hist_ThrPy99_Zt_wiR->SetMarkerColor(kMagenta+2); hist_ThrPy99_Zt_wiR->SetMarkerStyle(kStar); hist_ThrPy99_Zt_wiR->SetLineWidth(3); hist_ThrPy99_Zt_wiR->SetStats(kFALSE);  

	hist_ThrPyth_al_noR->SetLineColor(kBlack); hist_ThrPyth_al_noR->SetMarkerColor(kBlack); hist_ThrPyth_al_noR->SetMarkerStyle(kStar); hist_ThrPyth_al_noR->SetLineWidth(3); hist_ThrPyth_al_noR->SetStats(kFALSE);
	hist_ThrPyth_Zq_noR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_noR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_noR->SetMarkerStyle(kStar); hist_ThrPyth_Zq_noR->SetLineWidth(3); hist_ThrPyth_Zq_noR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_noR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_noR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_noR->SetMarkerStyle(kStar); hist_ThrPyth_ZZ_noR->SetLineWidth(3); hist_ThrPyth_ZZ_noR->SetStats(kFALSE);
	hist_ThrPyth_WW_noR->SetLineColor(kGreen+2); hist_ThrPyth_WW_noR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_noR->SetMarkerStyle(kStar); hist_ThrPyth_WW_noR->SetLineWidth(3); hist_ThrPyth_WW_noR->SetStats(kFALSE);
	hist_ThrPyth_tt_noR->SetLineColor(kRed+2); hist_ThrPyth_tt_noR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_noR->SetMarkerStyle(kStar); hist_ThrPyth_tt_noR->SetLineWidth(3); hist_ThrPyth_tt_noR->SetStats(kFALSE);   
	hist_ThrPyth_Zt_noR->SetLineColor(kMagenta+2); hist_ThrPyth_Zt_noR->SetMarkerColor(kMagenta+2); hist_ThrPyth_Zt_noR->SetMarkerStyle(kStar); hist_ThrPyth_Zt_noR->SetLineWidth(3); hist_ThrPyth_Zt_noR->SetStats(kFALSE);   

	hist_ThrPyth_al_wiR->SetLineColor(kBlack); hist_ThrPyth_al_wiR->SetMarkerColor(kBlack); hist_ThrPyth_al_wiR->SetMarkerStyle(kStar); hist_ThrPyth_al_wiR->SetLineWidth(3); hist_ThrPyth_al_wiR->SetStats(kFALSE);
	hist_ThrPyth_Zq_wiR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_wiR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_wiR->SetMarkerStyle(kStar); hist_ThrPyth_Zq_wiR->SetLineWidth(3); hist_ThrPyth_Zq_wiR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_wiR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_wiR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_wiR->SetMarkerStyle(kStar); hist_ThrPyth_ZZ_wiR->SetLineWidth(3); hist_ThrPyth_ZZ_wiR->SetStats(kFALSE);
	hist_ThrPyth_WW_wiR->SetLineColor(kGreen+2); hist_ThrPyth_WW_wiR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_wiR->SetMarkerStyle(kStar); hist_ThrPyth_WW_wiR->SetLineWidth(3); hist_ThrPyth_WW_wiR->SetStats(kFALSE);
	hist_ThrPyth_tt_wiR->SetLineColor(kRed+2); hist_ThrPyth_tt_wiR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_wiR->SetMarkerStyle(kStar); hist_ThrPyth_tt_wiR->SetLineWidth(3); hist_ThrPyth_tt_wiR->SetStats(kFALSE);  
	hist_ThrPyth_Zt_wiR->SetLineColor(kMagenta+2); hist_ThrPyth_Zt_wiR->SetMarkerColor(kMagenta+2); hist_ThrPyth_Zt_wiR->SetMarkerStyle(kStar); hist_ThrPyth_Zt_wiR->SetLineWidth(3); hist_ThrPyth_Zt_wiR->SetStats(kFALSE);  

	hist_nHadron_al_noR->SetLineColor(kBlack); hist_nHadron_al_noR->SetMarkerColor(kBlack); hist_nHadron_al_noR->SetMarkerStyle(kStar); hist_nHadron_al_noR->SetLineWidth(3); hist_nHadron_al_noR->SetStats(kFALSE);
	hist_nHadron_Zq_noR->SetLineColor(kYellow+2); hist_nHadron_Zq_noR->SetMarkerColor(kYellow+2); hist_nHadron_Zq_noR->SetMarkerStyle(kStar); hist_nHadron_Zq_noR->SetLineWidth(3); hist_nHadron_Zq_noR->SetStats(kFALSE);
	hist_nHadron_ZZ_noR->SetLineColor(kBlue+2); hist_nHadron_ZZ_noR->SetMarkerColor(kBlue+2); hist_nHadron_ZZ_noR->SetMarkerStyle(kStar); hist_nHadron_ZZ_noR->SetLineWidth(3); hist_nHadron_ZZ_noR->SetStats(kFALSE);
	hist_nHadron_WW_noR->SetLineColor(kGreen+2); hist_nHadron_WW_noR->SetMarkerColor(kGreen+2); hist_nHadron_WW_noR->SetMarkerStyle(kStar); hist_nHadron_WW_noR->SetLineWidth(3); hist_nHadron_WW_noR->SetStats(kFALSE);
	hist_nHadron_tt_noR->SetLineColor(kRed+2); hist_nHadron_tt_noR->SetMarkerColor(kRed+2); hist_nHadron_tt_noR->SetMarkerStyle(kStar); hist_nHadron_tt_noR->SetLineWidth(3); hist_nHadron_tt_noR->SetStats(kFALSE);   

	hist_nHadron_al_wiR->SetLineColor(kBlack); hist_nHadron_al_wiR->SetMarkerColor(kBlack); hist_nHadron_al_wiR->SetMarkerStyle(kStar); hist_nHadron_al_wiR->SetLineWidth(3); hist_nHadron_al_wiR->SetStats(kFALSE);
	hist_nHadron_Zq_wiR->SetLineColor(kYellow+2); hist_nHadron_Zq_wiR->SetMarkerColor(kYellow+2); hist_nHadron_Zq_wiR->SetMarkerStyle(kStar); hist_nHadron_Zq_wiR->SetLineWidth(3); hist_nHadron_Zq_wiR->SetStats(kFALSE);
	hist_nHadron_ZZ_wiR->SetLineColor(kBlue+2); hist_nHadron_ZZ_wiR->SetMarkerColor(kBlue+2); hist_nHadron_ZZ_wiR->SetMarkerStyle(kStar); hist_nHadron_ZZ_wiR->SetLineWidth(3); hist_nHadron_ZZ_wiR->SetStats(kFALSE);
	hist_nHadron_WW_wiR->SetLineColor(kGreen+2); hist_nHadron_WW_wiR->SetMarkerColor(kGreen+2); hist_nHadron_WW_wiR->SetMarkerStyle(kStar); hist_nHadron_WW_wiR->SetLineWidth(3); hist_nHadron_WW_wiR->SetStats(kFALSE);
	hist_nHadron_tt_wiR->SetLineColor(kRed+2); hist_nHadron_tt_wiR->SetMarkerColor(kRed+2); hist_nHadron_tt_wiR->SetMarkerStyle(kStar); hist_nHadron_tt_wiR->SetLineWidth(3); hist_nHadron_tt_wiR->SetStats(kFALSE);  

	hist_ThrPyth_al_noR->SetTitle("Inverse Thrust wo ISR");hist_ThrPyth_al_noR->GetYaxis()->SetTitle("# Events");
	hist_ThrPyth_al_wiR->SetTitle("Inverse Thrust wi ISR");hist_ThrPyth_al_wiR->GetYaxis()->SetTitle("# Events");
	hist_nHadron_al_noR->SetTitle("Charged Multiplicity wo ISR");hist_nHadron_al_noR->GetYaxis()->SetTitle("# Events");
	hist_nHadron_al_wiR->SetTitle("Charged Multiplicity wi ISR");hist_nHadron_al_wiR->GetYaxis()->SetTitle("# Events");

	// Add legend
	TLegend *lg_thr4 = new TLegend(0.4, 0.2, 0.6, 0.4);
	lg_thr4->AddEntry(hist_nHadron_al_noR, "ee#rightarrowq#bar{q}", "p");
	lg_thr4->AddEntry(hist_nHadron_Zq_noR, "ee#rightarrow#gamma*/Z#rightarrowq#bar{q}", "pl");
	lg_thr4->AddEntry(hist_nHadron_ZZ_noR, "ee#rightarrowWW#rightarrowq#bar{q}", "pl");
	lg_thr4->AddEntry(hist_nHadron_WW_noR, "ee#rightarrowZZ#rightarrowq#bar{q}", "pl");
	lg_thr4->AddEntry(hist_nHadron_tt_noR, "ee#rightarrowt#bar{t}#rightarrowq#bar{q}", "pl");
	lg_thr4->AddEntry(hist_Thr199T, "1999 TESLA study", "pl");
	lg_thr4->SetTextSize(0.03);

	// Add legend
	TLegend *lg_thr5 = new TLegend(0.4, 0.2, 0.6, 0.4);
	lg_thr5->AddEntry(hist_ThrPy99_Zq_noR, "ee#rightarrow#gamma*/Z#rightarrowq#bar{q}", "pl");
	lg_thr5->AddEntry(hist_Thr199T, "1999 TESLA study", "pl");
	lg_thr5->SetTextSize(0.03);

	// Add legend
	TLegend *lg_thr6 = new TLegend(0.4, 0.2, 0.6, 0.4);
	lg_thr6->AddEntry(hist_ThrPy99_Zt_noR, "ee#rightarrow#gamma*/Z/t#bar{t}#rightarrowq#bar{q}", "pl");
	lg_thr6->AddEntry(hist_Thr199T, "1999 TESLA study", "pl");
	lg_thr6->SetTextSize(0.03);

	// Create canvas
	TCanvas* c_thr4 = new TCanvas("c_thr4", "Process-separated Event Shapes", 1000, 1400);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	c_thr4->Divide(2,3);
	c_thr4->cd(1)->SetLeftMargin(0.15);
	c_thr4->cd(1)->SetLogy();
	c_thr4->cd(1)->SetTickx(); c_thr4->cd(1)->SetTicky();
	c_thr4->cd(1)->SetGridx(); c_thr4->cd(1)->SetGridy();
	c_thr4->cd(2)->SetLeftMargin(0.15);
	c_thr4->cd(2)->SetLogy();
	c_thr4->cd(2)->SetTickx(); c_thr4->cd(2)->SetTicky();
	c_thr4->cd(2)->SetGridx(); c_thr4->cd(2)->SetGridy();
	c_thr4->cd(3)->SetLeftMargin(0.15);
	c_thr4->cd(3)->SetLogy();
	c_thr4->cd(3)->SetTickx(); c_thr4->cd(3)->SetTicky();
	c_thr4->cd(3)->SetGridx(); c_thr4->cd(3)->SetGridy();
	c_thr4->cd(4)->SetLeftMargin(0.15);
	c_thr4->cd(4)->SetLogy();
	c_thr4->cd(4)->SetTickx(); c_thr4->cd(4)->SetTicky();
	c_thr4->cd(4)->SetGridx(); c_thr4->cd(4)->SetGridy();
	c_thr4->cd(5)->SetLeftMargin(0.15);
	c_thr4->cd(5)->SetLogy();
	c_thr4->cd(5)->SetTickx(); c_thr4->cd(5)->SetTicky();
	c_thr4->cd(5)->SetGridx(); c_thr4->cd(5)->SetGridy();
	c_thr4->cd(6)->SetLeftMargin(0.15);
	c_thr4->cd(6)->SetLogy();
	c_thr4->cd(6)->SetTickx(); c_thr4->cd(6)->SetTicky();
	c_thr4->cd(6)->SetGridx(); c_thr4->cd(6)->SetGridy();

	// Draw
	c_thr4->cd(1);
	hist_nHadron_al_noR->Draw("P");
	hist_nHadron_Zq_noR->Draw("PSAME");
	hist_nHadron_ZZ_noR->Draw("PSAME");
	hist_nHadron_WW_noR->Draw("PSAME");
	hist_nHadron_tt_noR->Draw("PSAME");
	lg_thr4->Draw("SAME");
	c_thr4->cd(2);
	hist_nHadron_al_wiR->Draw("P");
	hist_nHadron_Zq_wiR->Draw("PSAME");
	hist_nHadron_ZZ_wiR->Draw("PSAME");
	hist_nHadron_WW_wiR->Draw("PSAME");
	hist_nHadron_tt_wiR->Draw("PSAME");
	lg_thr4->Draw("SAME");
	c_thr4->cd(3);
	hist_ThrPyth_al_noR->Draw("P");
	hist_ThrPyth_Zq_noR->Draw("PSAME");
	hist_ThrPyth_ZZ_noR->Draw("PSAME");
	hist_ThrPyth_WW_noR->Draw("PSAME");
	hist_ThrPyth_tt_noR->Draw("PSAME");
	lg_thr4->Draw("SAME");
	c_thr4->cd(4);
	hist_ThrPyth_al_wiR->Draw("P");
	hist_ThrPyth_Zq_wiR->Draw("PSAME");
	hist_ThrPyth_ZZ_wiR->Draw("PSAME");
	hist_ThrPyth_WW_wiR->Draw("PSAME");
	hist_ThrPyth_tt_wiR->Draw("PSAME");
	lg_thr4->Draw("SAME");	
	c_thr4->cd(5);
	hist_Thr1999->Draw("P");
	hist_ThrPy99_Zq_noR->Draw("PSAME");
	// hist_ThrPyth_Zq_noR->Draw("PSAME");
	lg_thr5->Draw("SAME");	
	c_thr4->cd(6);
	hist_Thr199T->Draw("P");
	hist_ThrPy99_Zt_noR->Draw("PSAME");
	// hist_ThrPyth_Zt_noR->Draw("PSAME");
	lg_thr6->Draw("SAME");
	
	hist_ThrPyth_Zq_noR->Scale(1.0/hist_ThrPyth_Zq_noR->Integral());
	hist_ThrPyth_Zt_noR->Scale(1.0/hist_ThrPyth_Zt_noR->Integral());
	hist_ThrPyth_Zq_wiR->Scale(1.0/hist_ThrPyth_Zq_wiR->Integral());

	// Set limits
	hist_ThrPyth_al_noR->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_ThrPyth_al_wiR->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_nHadron_al_noR->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_nHadron_al_wiR->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_Thr1999->GetYaxis()->SetRangeUser(1E-7,1E0);
	hist_Thr199T->GetYaxis()->SetRangeUser(1E-7,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	c_thr4->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Jets
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// TH1F *hist_nJetTot_al_noR = (TH1F*)input_TES50t_noR->Get("hist_nJetTot");
	// TH1F *hist_nJetTot_al_wiR = (TH1F*)input_TES50t_wiR->Get("hist_nJetTot");

	// hist_nJetTot_al_noR->SetLineColor(kYellow+2); hist_nJetTot_al_noR->SetMarkerColor(kYellow+2); hist_nJetTot_al_noR->SetMarkerStyle(kStar); hist_nJetTot_al_noR->SetLineWidth(2); hist_nJetTot_al_noR->SetStats(kFALSE);
	// hist_nJetTot_al_wiR->SetLineColor(kBlue+2); hist_nJetTot_al_wiR->SetMarkerColor(kBlue+2); hist_nJetTot_al_wiR->SetMarkerStyle(kStar); hist_nJetTot_al_wiR->SetLineWidth(2); hist_nJetTot_al_wiR->SetStats(kFALSE); 

	// hist_nJetTot_al_noR->SetTitle("Total Jet multiplicity");hist_nJetTot_al_noR->GetYaxis()->SetTitle("# Events");
	// hist_nJetTot_al_wiR->SetTitle("Total Jet multiplicity");hist_nJetTot_al_wiR->GetYaxis()->SetTitle("# Events");

	// // Add legend
	// TLegend *lg_thr7 = new TLegend(0.4, 0.2, 0.6, 0.4);
	// lg_thr7->AddEntry(hist_nJetTot_al_noR, "ee#rightarrowq#bar{q}", "p");
	// lg_thr7->AddEntry(hist_nJetTot_al_wiR, "ee(#gamma)#rightarrowq#bar{q}", "pl");
	// lg_thr7->SetTextSize(0.03);

	// // Create canvas
	// TCanvas* c_thr5 = new TCanvas("c_thr5", "Process-separated Event Shapes", 600, 500);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// c_thr5->SetLeftMargin(0.15);
	// c_thr5->SetLogy();
	// c_thr5->SetTickx(); c_thr5->SetTicky();
	// c_thr5->SetGridx(); c_thr5->SetGridy();

	// // Draw
	// c_thr5->cd(1);
	// hist_nJetTot_al_noR->Draw("P");
	// hist_nJetTot_al_wiR->Draw("PSAME");
	// lg_thr7->Draw("SAME");

	// // Set limits
	// // hist_nJetTot_al_noR->GetYaxis()->SetRangeUser(1E0,1E5);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// c_thr5->Modified();

}