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
	TFile* inputfile_TES500 = new TFile("cut_TES500.root", "READ");
	
	// Read TTree
	TTree* trees_LEP_Z0 = (TTree*)inputfile_TES500->Get("tree_cut");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nHadron = (TH1F*)inputfile_TES500->Get("hist_nHadron");
	// Beautify
	hist_nHadron->SetStats(kFALSE);
	hist_nHadron->SetLineColor(kBlack);
	hist_nHadron->SetMarkerColor(kBlack);
	hist_nHadron->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *KNOO_nHadron = (TH1F*)inputfile_TES500->Get("KNOO_nHadron");
	// Beautify
	KNOO_nHadron->SetStats(kFALSE);
	KNOO_nHadron->SetLineColor(kBlack);
	KNOO_nHadron->SetMarkerColor(kBlack);
	KNOO_nHadron->SetMarkerStyle(kOpenCircle);

	// Read Histogram
	TH1F *hist_ThrPyth = (TH1F*)inputfile_TES500->Get("hist_ThrPyth");
	// Beautify
	hist_ThrPyth->SetStats(kFALSE);
	hist_ThrPyth->SetLineColor(kBlack);
	hist_ThrPyth->SetMarkerColor(kBlack);
	hist_ThrPyth->SetMarkerStyle(kOpenTriangleUp);

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
	hist_nHadron->Scale(1.0/hist_nHadron->Integral());
	KNOO_nHadron->Scale(1.0/KNOO_nHadron->Integral());
	hist_ThrPyth->Scale(1.0/hist_ThrPyth->Integral());
	hist_Thr1999->Scale(1.0/hist_Thr1999->Integral());
	hist_Thr199T->Scale(1.0/hist_Thr199T->Integral());

	// Print check of integrals
	cout << "Integration : " << hist_nHadron->Integral() << endl;
	cout << "Integration : " << KNOO_nHadron->Integral() << endl;
	cout << "Integration : " << hist_ThrPyth->Integral() << endl;
	cout << "Integration : " << hist_Thr1999->Integral() << endl;
	cout << "Integration : " << hist_Thr199T->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Charged Hadronic Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *leg_nch = new TLegend(0.4, 0.2, 0.85, 0.4);
	leg_nch->AddEntry(hist_nHadron, "500 GeV (TESLA)", "p");
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
	hist_nHadron->Draw("PS");
	leg_nch->Draw("same");
	c_nch->cd(2);
	KNOO_nHadron->Draw("PS");
	leg_nch->Draw("same");

	// Modify stat-box
	gStyle->SetOptStat();
	c_nch->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg_thr1 = new TLegend(0.4, 0.2, 0.85, 0.4);
	lg_thr1->AddEntry(hist_Thr1999, "Pythia 8.3 LEPZ0", "p");
	lg_thr1->AddEntry(hist_Thr1999, "1999 Study TESLA", "p");
	lg_thr1->SetTextSize(0.04);

	// Add legend
	TLegend *lg_thr2 = new TLegend(0.4, 0.2, 0.85, 0.4);
	lg_thr2->AddEntry(hist_Thr199T, "Pythia 8.3 TESLA", "p");
	lg_thr2->AddEntry(hist_Thr199T, "1999 Study TESLA", "p");
	lg_thr2->SetTextSize(0.04);

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
	
	// Draw
	c_thr->cd(1);
	hist_Thr1999->Draw("p");
	lg_thr1->Draw("same");
	c_thr->cd(2);
	hist_Thr199T->Draw("p");
	lg_thr2->Draw("same");

	hist_Thr1999->GetYaxis()->SetRangeUser(1E-4,1E0);
	hist_Thr199T->GetYaxis()->SetRangeUser(1E-4,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	c_thr->Modified();

}