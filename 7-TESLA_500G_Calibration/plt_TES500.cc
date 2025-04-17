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
	hist_Thr1999->SetName("Thrust");
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
	hist_Thr199T->SetName("Thrust");
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
	KNOO_nHadron_LEP912_noR->Scale(1.0/KNOO_nHadron_LEP912_noR->Integral());
	KNOO_nHadron_LEP912_wiR->Scale(1.0/KNOO_nHadron_LEP912_wiR->Integral());
	KNOO_nHadron_TES500_noR->Scale(1.0/KNOO_nHadron_TES500_noR->Integral());
	KNOO_nHadron_TES50t_noR->Scale(1.0/KNOO_nHadron_TES50t_noR->Integral());
	KNOO_nHadron_TES500_wiR->Scale(1.0/KNOO_nHadron_TES500_wiR->Integral());
	KNOO_nHadron_TES50t_wiR->Scale(1.0/KNOO_nHadron_TES50t_wiR->Integral());

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

	// Add legend
	TLegend *lg_thr = new TLegend(0.4, 0.2, 0.85, 0.4);
	lg_thr->AddEntry(hist_ThrPyth_TES50t_noR, "500 GeV (wo ISR)", "p");
	lg_thr->AddEntry(hist_ThrPyth_TES500_wiR, "500 GeV (wi ISR)", "p");
	lg_thr->AddEntry(hist_ThrPyth_LEP912_noR, "91.2 GeV (wo ISR)", "p");
	lg_thr->AddEntry(hist_ThrPyth_LEP912_wiR, "91.2 GeV (wi ISR)", "p");
	lg_thr->AddEntry(hist_Thr1999, "1999 TESLA study", "p");
	lg_thr->SetTextSize(0.04);

	// Create canvas
	TCanvas* c_thr = new TCanvas("c_thr", "Inverse Thrust distributions", 800, 600);

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
	
	hist_Thr1999->GetYaxis()->SetRangeUser(1E-4,1E0);
	hist_Thr199T->GetYaxis()->SetRangeUser(1E-4,1E0);

	// Draw
	c_thr->cd(1);
	hist_Thr1999->Draw("P");
	hist_ThrPyth_TES500_wiR->Draw("PSAME");
	hist_ThrPyth_TES500_noR->Draw("PSAME");
	hist_ThrPyth_LEP912_wiR->Draw("PSAME");
	hist_ThrPyth_LEP912_noR->Draw("PSAME");
	lg_thr->Draw("SAME");
	c_thr->cd(2);
	hist_Thr199T->Draw("P");
	hist_ThrPyth_TES50t_wiR->Draw("PSAME");
	hist_ThrPyth_TES50t_noR->Draw("PSAME");
	hist_ThrPyth_LEP912_wiR->Draw("PSAME");
	hist_ThrPyth_LEP912_noR->Draw("PSAME");
	lg_thr->Draw("SAME");

// Modify stat-box
	gStyle->SetOptStat();
	c_thr->Modified();

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

}