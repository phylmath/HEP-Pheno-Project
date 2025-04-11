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
// Importing file, Reading TTree
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile* input_TES50t = new TFile("cut_TES500_wiT.root", "READ");
	TFile* input_TES500 = new TFile("cut_TES500_woT.root", "READ");
	TFile* input_LEP912 = new TFile("cut_LEP912.root", "READ");
	
	// Read TTree
	TTree* trees_TES50t = (TTree*)input_TES50t->Get("tree_cut");
	TTree* trees_TES500 = (TTree*)input_TES500->Get("tree_cut");
	TTree* trees_LEP912 = (TTree*)input_LEP912->Get("tree_cut");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nHadron_TES50t = (TH1F*)input_TES50t->Get("hist_nHadron");
	// Beautify
	hist_nHadron_TES50t->SetStats(kFALSE);
	hist_nHadron_TES50t->SetLineColor(kBlue+2);
	hist_nHadron_TES50t->SetMarkerColor(kBlue+2);
	hist_nHadron_TES50t->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *KNOO_nHadron_TES50t = (TH1F*)input_TES50t->Get("KNOO_nHadron");
	// Beautify
	KNOO_nHadron_TES50t->SetStats(kFALSE);
	KNOO_nHadron_TES50t->SetLineColor(kBlue+2);
	KNOO_nHadron_TES50t->SetMarkerColor(kBlue+2);
	KNOO_nHadron_TES50t->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *hist_ThrPyth_TES50t = (TH1F*)input_TES50t->Get("hist_ThrPyth");
	// Beautify
	hist_ThrPyth_TES50t->SetStats(kFALSE);
	hist_ThrPyth_TES50t->SetLineColor(kBlack);
	hist_ThrPyth_TES50t->SetMarkerColor(kBlack);
	hist_ThrPyth_TES50t->SetMarkerStyle(kOpenTriangleUp);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nHadron_TES500 = (TH1F*)input_TES500->Get("hist_nHadron");
	// Beautify
	hist_nHadron_TES500->SetStats(kFALSE);
	hist_nHadron_TES500->SetLineColor(kBlack);
	hist_nHadron_TES500->SetMarkerColor(kBlack);
	hist_nHadron_TES500->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *KNOO_nHadron_TES500 = (TH1F*)input_TES500->Get("KNOO_nHadron");
	// Beautify
	KNOO_nHadron_TES500->SetStats(kFALSE);
	KNOO_nHadron_TES500->SetLineColor(kBlack);
	KNOO_nHadron_TES500->SetMarkerColor(kBlack);
	KNOO_nHadron_TES500->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *hist_ThrPyth_TES500 = (TH1F*)input_TES500->Get("hist_ThrPyth");
	// Beautify
	hist_ThrPyth_TES500->SetStats(kFALSE);
	hist_ThrPyth_TES500->SetLineColor(kBlack);
	hist_ThrPyth_TES500->SetMarkerColor(kBlack);
	hist_ThrPyth_TES500->SetMarkerStyle(kOpenTriangleUp);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nHadron_LEP912 = (TH1F*)input_LEP912->Get("hist_nHadron");
	// Beautify
	hist_nHadron_LEP912->SetStats(kFALSE);
	hist_nHadron_LEP912->SetLineColor(kGreen+2);
	hist_nHadron_LEP912->SetMarkerColor(kGreen+2);
	hist_nHadron_LEP912->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *KNOO_nHadron_LEP912 = (TH1F*)input_LEP912->Get("KNOO_nHadron");
	// Beautify
	KNOO_nHadron_LEP912->SetStats(kFALSE);
	KNOO_nHadron_LEP912->SetLineColor(kGreen+2);
	KNOO_nHadron_LEP912->SetMarkerColor(kGreen+2);
	KNOO_nHadron_LEP912->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *hist_ThrPyth_LEP912 = (TH1F*)input_LEP912->Get("hist_ThrPyth");
	// Beautify
	hist_ThrPyth_LEP912->SetStats(kFALSE);
	hist_ThrPyth_LEP912->SetLineColor(kGreen+2);
	hist_ThrPyth_LEP912->SetMarkerColor(kGreen+2);
	hist_ThrPyth_LEP912->SetMarkerStyle(kOpenTriangleUp);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Importing raw TEXT data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_Thr1999 = new TH1F("hist_Thr1999", "Differential Thrust (without top)", 500, 0, 0.4);
	// Beautify
	hist_Thr1999->SetStats(kFALSE);
	hist_Thr1999->SetName("Differential Thrust e^{+}e^{-}");
	hist_Thr1999->SetName("hist_Thr1999");
	hist_Thr1999->SetLineColor(kRed+2);
	hist_Thr1999->SetMarkerColor(kRed+2);
	hist_Thr1999->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr1999->GetXaxis()->SetTitle("1-T");
	hist_Thr1999->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr1999->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr1999->GetYaxis()->SetNdivisions(510, kTRUE);
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
	TH1F *hist_Thr199T = new TH1F("hist_Thr199T", "Differential Thrust (with top)", 500, 0, 0.4);
	// Beautify
	hist_Thr199T->SetStats(kFALSE);
	hist_Thr199T->SetName("Differential Thrust e^{+}e^{-}");
	hist_Thr199T->SetName("hist_Thr199T");
	hist_Thr199T->SetLineColor(kRed+2);
	hist_Thr199T->SetMarkerColor(kRed+2);
	hist_Thr199T->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr199T->GetXaxis()->SetTitle("1-T");
	hist_Thr199T->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr199T->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr199T->GetYaxis()->SetNdivisions(510, kTRUE);
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
	hist_nHadron_LEP912->Scale(1.0/hist_nHadron_LEP912->Integral());
	hist_nHadron_TES500->Scale(1.0/hist_nHadron_TES500->Integral());
	hist_nHadron_TES50t->Scale(1.0/hist_nHadron_TES50t->Integral());

	KNOO_nHadron_LEP912->Scale(1.0/KNOO_nHadron_LEP912->Integral());
	KNOO_nHadron_TES500->Scale(1.0/KNOO_nHadron_TES500->Integral());
	KNOO_nHadron_TES50t->Scale(1.0/KNOO_nHadron_TES50t->Integral());

	hist_ThrPyth_LEP912->Scale(1.0/hist_ThrPyth_LEP912->Integral());
	hist_ThrPyth_TES500->Scale(1.0/hist_ThrPyth_TES500->Integral());
	hist_ThrPyth_TES50t->Scale(1.0/hist_ThrPyth_TES50t->Integral());
	
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

	// Add legend
	TLegend *leg_nch = new TLegend(0.4, 0.2, 0.85, 0.4);
	leg_nch->AddEntry(hist_nHadron_TES50t, "500 GeV (wi top)", "p");
	leg_nch->AddEntry(hist_nHadron_TES500, "500 GeV (wo top)", "p");
	leg_nch->AddEntry(hist_nHadron_LEP912, "91.2 GeV (LEP)", "p");
	leg_nch->SetTextSize(0.03);

	// Create canvas
	TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);

	// Beautify
	c_nch->Divide(2,1);
	c_nch->cd(1)->SetLeftMargin(0.15);
	c_nch->cd(1)->SetLogy();
	c_nch->cd(1)->SetTickx(); c_nch->cd(1)->SetTicky();
	c_nch->cd(1)->SetGridx(); c_nch->cd(1)->SetGridy();
	c_nch->cd(2)->SetLeftMargin(0.15);
	c_nch->cd(2)->SetLogy();
	c_nch->cd(2)->SetTickx(); c_nch->cd(2)->SetTicky();
	c_nch->cd(2)->SetGridx(); c_nch->cd(2)->SetGridy();
	
	// Draw
	c_nch->cd(1);
	hist_nHadron_TES50t->Draw("P");
	hist_nHadron_TES500->Draw("PSAME");
	hist_nHadron_LEP912->Draw("PSAME");
	leg_nch->Draw("SAME");
	c_nch->cd(2);
	KNOO_nHadron_TES50t->Draw("P");
	KNOO_nHadron_TES500->Draw("PSAME");
	KNOO_nHadron_LEP912->Draw("PSAME");
	leg_nch->Draw("SAME");

	hist_nHadron_TES50t->GetYaxis()->SetRangeUser(1E-5,1E0);
	KNOO_nHadron_TES50t->GetYaxis()->SetRangeUser(1E-5,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	c_nch->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg_thr1 = new TLegend(0.4, 0.2, 0.85, 0.4);
	lg_thr1->AddEntry(hist_ThrPyth_TES500, "Pythia 8.3 500 GeV", "p");
	// lg_thr1->AddEntry(hist_ThrPyth_LEP912, "Pythia 8.3 91.2 GeV", "p");
	lg_thr1->AddEntry(hist_Thr1999, "1999 TESLA study", "p");
	lg_thr1->SetTextSize(0.04);

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
	hist_ThrPyth_TES500->Draw("PSAME");
	hist_ThrPyth_LEP912->Draw("PSAME");
	lg_thr1->Draw("SAME");
	c_thr->cd(2);
	hist_Thr199T->Draw("P");
	hist_ThrPyth_TES50t->Draw("PSAME");
	hist_ThrPyth_LEP912->Draw("PSAME");
	lg_thr1->Draw("SAME");



	// Modify stat-box
	gStyle->SetOptStat();
	c_thr->Modified();

}