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
#include "TH2F.h"
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
#include "TLorentzVector.h"
#include "TEllipse.h"
#include "TText.h"
#include "TPolyLine3D.h"
#include <TVectorF.h>
// Header
using namespace std;

// Code
void ImpactofExp()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("cut_FCC160.root", "READ");
	TFile *input_180 = new TFile("cut_FCC180.root", "READ");
	TFile *input_240 = new TFile("cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("cut_FCC365.root", "READ");
	TFile *input_500 = new TFile("cut_FCC500.root", "READ");

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
	hist_Thr1999->SetTitle("Inverse Thrust wo Top wo ISR");
	hist_Thr1999->SetName("hist_Thr1999");
	hist_Thr1999->GetXaxis()->SetTitle("1-T");
	hist_Thr1999->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_01("3-LEP-data/EXP_TES_500_THR_wot.txt");
	// Read through TXT
	while ( !infile_01.eof() ) {
		// Set reading order
		infile_01 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr1999->SetBinContent(hist_Thr1999->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr1999->SetBinError(hist_Thr1999->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_01.close();

	// // Read Histogram
	TH1F *hist_Thr199T = new TH1F("hist_Thr199T", "Inverse Thrust (wi top)", 500, 0, 0.4);
	// Beautify
	hist_Thr199T->SetTitle("Inverse Thrust wi Top wo ISR");
	hist_Thr199T->SetName("hist_Thr199T");
	hist_Thr199T->GetXaxis()->SetTitle("1-T");
	hist_Thr199T->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_02("3-LEP-data/EXP_TES_500_THR_wit.txt");
	// Read through TXT
	while ( !infile_02.eof() ) {
		// Set reading order
		infile_02 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr199T->SetBinContent(hist_Thr199T->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr199T->SetBinError(hist_Thr199T->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_02.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of ISR Cuts on Thrust/Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_Thr1999->SetLineColor(kBlack); hist_Thr1999->SetMarkerColor(kBlack); hist_Thr1999->SetMarkerStyle(kOpenTriangleUp); hist_Thr1999->SetLineWidth(2); 
	hist_Thr199T->SetLineColor(kBlack); hist_Thr199T->SetMarkerColor(kBlack); hist_Thr199T->SetMarkerStyle(kOpenTriangleUp); hist_Thr199T->SetLineWidth(2); 

	TH1F *hist_ThrPy99 = (TH1F*)input_500->Get("hist_ThrPy99_Zq");
	hist_ThrPy99->SetLineColor(kYellow+2); hist_ThrPy99->SetMarkerColor(kYellow+2); hist_ThrPy99->SetMarkerStyle(kOpenTriangleUp); hist_ThrPy99->SetLineWidth(2); 
	TH1F *hist_ThrPy9T = (TH1F*)input_500->Get("hist_ThrPy99_Zt");
	hist_ThrPy9T->SetLineColor(kYellow+2); hist_ThrPy9T->SetMarkerColor(kYellow+2); hist_ThrPy9T->SetMarkerStyle(kOpenTriangleUp); hist_ThrPy9T->SetLineWidth(2); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_Thr1999->Scale(1.0/hist_Thr1999->Integral());
	hist_Thr199T->Scale(1.0/hist_Thr199T->Integral());
	hist_ThrPy99->Scale(1.0/hist_ThrPy99->Integral());
	hist_ThrPy9T->Scale(1.0/hist_ThrPy9T->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_Thr1999->SetStats(kFALSE);
	hist_Thr199T->SetStats(kFALSE);
	hist_ThrPy99->SetStats(kFALSE);
	hist_ThrPy9T->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg->AddEntry(hist_Thr1999, "1999 TESLA study", "p");
	lg->AddEntry(hist_ThrPy99, "PYTHIA 8.3 study", "p");
	lg->SetTextSize(0.03);

	// Create canvas
	TCanvas* cv = new TCanvas("cv", "FCC-ee ISR Studies", 1200, 600);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv->Divide(2,1);
	cv->cd(1)->SetLeftMargin(0.15);
	cv->cd(1)->SetLogy();
	cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	cv->cd(2)->SetLeftMargin(0.15);
	cv->cd(2)->SetLogy();
	cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
 
	// Draw
	cv->cd(1);
	hist_Thr1999->Draw("P");
	hist_ThrPy99->Draw("P SAME");
	lg->Draw("SAME");	
	cv->cd(2);
	hist_Thr199T->Draw("P");
	hist_ThrPy9T->Draw("P SAME");
	lg->Draw("SAME");

	// Set limits
	hist_Thr1999->GetYaxis()->SetRangeUser(1E-4,1E0);
	hist_Thr199T->GetYaxis()->SetRangeUser(1E-4,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv->Modified();

}