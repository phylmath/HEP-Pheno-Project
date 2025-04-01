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
// Creating file, Reading TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile* inputfile_LEP_Z0 = new TFile("out_LEP_912.root", "READ");
	TFile* inputfile_TESLEP = new TFile("out_TES_LEP.root", "READ");
	TFile* inputfile_TES500 = new TFile("out_TES_500.root", "READ");
	TFile* inputfile_TES50t = new TFile("out_TES_50t.root", "READ");
	
	// Read TTree
	TTree* trees_LEP_Z0 = (TTree*)inputfile_LEP_Z0->Get("tree");
	TTree* trees_TESLEP = (TTree*)inputfile_TESLEP->Get("tree");
	TTree* trees_TES500 = (TTree*)inputfile_TES500->Get("tree");
	TTree* trees_TES50t = (TTree*)inputfile_TES50t->Get("tree");

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nCh_LEP_Z0 = (TH1F*)inputfile_LEP_Z0->Get("hist_nChPyth");
	// Beautify
	hist_nCh_LEP_Z0->SetStats(kFALSE);
	hist_nCh_LEP_Z0->SetTitle("Charged Hadron Multiplicity e^{+}e^{-}");
	hist_nCh_LEP_Z0->SetName("hist_nCh_LEP_Z0");
	hist_nCh_LEP_Z0->SetLineColor(kBlack);
	hist_nCh_LEP_Z0->SetMarkerColor(kBlack);
	hist_nCh_LEP_Z0->SetMarkerStyle(kOpenCircle);
	hist_nCh_LEP_Z0->GetXaxis()->SetTitle("N_{CH}");
	hist_nCh_LEP_Z0->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nCh_LEP_Z0->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nCh_LEP_Z0->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nCh_TESLEP = (TH1F*)inputfile_TESLEP->Get("hist_nChPyth");
	// Beautify
	hist_nCh_TESLEP->SetStats(kFALSE);
	hist_nCh_TESLEP->SetTitle("Charged Hadron Multiplicity e^{+}e^{-}");
	hist_nCh_TESLEP->SetName("hist_nCh_TESLEP");
	hist_nCh_TESLEP->SetLineColor(kBlack);
	hist_nCh_TESLEP->SetMarkerColor(kBlack);
	hist_nCh_TESLEP->SetMarkerStyle(kOpenTriangleUp);
	hist_nCh_TESLEP->GetXaxis()->SetTitle("N_{CH}");
	hist_nCh_TESLEP->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nCh_TESLEP->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nCh_TESLEP->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nCh_TES500 = (TH1F*)inputfile_TES500->Get("hist_nChPyth");
	// Beautify
	hist_nCh_TES500->SetStats(kFALSE);
	hist_nCh_TES500->SetTitle("Charged Hadron Multiplicity e^{+}e^{-}");
	hist_nCh_TES500->SetName("hist_nCh_TES500");
	hist_nCh_TES500->SetLineColor(kRed+1);
	hist_nCh_TES500->SetMarkerColor(kRed+1);
	hist_nCh_TES500->SetMarkerStyle(kOpenTriangleUp);
	hist_nCh_TES500->GetXaxis()->SetTitle("N_{CH}");
	hist_nCh_TES500->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nCh_TES500->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nCh_TES500->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nCh_TES50t = (TH1F*)inputfile_TES50t->Get("hist_nChPyth");
	// Beautify
	hist_nCh_TES50t->SetStats(kFALSE);
	hist_nCh_TES50t->SetTitle("Charged Hadron Multiplicity e^{+}e^{-}");
	hist_nCh_TES50t->SetName("hist_nCh_TES50t");
	hist_nCh_TES50t->SetLineColor(kGreen+1);
	hist_nCh_TES50t->SetMarkerColor(kGreen+1);
	hist_nCh_TES50t->SetMarkerStyle(kOpenTriangleUp);
	hist_nCh_TES50t->GetXaxis()->SetTitle("N_{CH}");
	hist_nCh_TES50t->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nCh_TES50t->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nCh_TES50t->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_Thr_LEP_Z0 = (TH1F*)inputfile_LEP_Z0->Get("hist_ThrustP");
	// Beautify
	hist_Thr_LEP_Z0->SetStats(kFALSE);
	hist_Thr_LEP_Z0->SetTitle("Differential Thrust e^{+}e^{-}");
	hist_Thr_LEP_Z0->SetName("hist_Thr_LEP_Z0");
	hist_Thr_LEP_Z0->SetLineColor(kGreen+2);
	hist_Thr_LEP_Z0->SetMarkerColor(kGreen+2);
	hist_Thr_LEP_Z0->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_LEP_Z0->GetXaxis()->SetTitle("1-T");
	hist_Thr_LEP_Z0->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_LEP_Z0->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_LEP_Z0->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Thr_TESLEP = (TH1F*)inputfile_TESLEP->Get("hist_ThrustP");
	// Beautify
	hist_Thr_TESLEP->SetStats(kFALSE);
	hist_Thr_TESLEP->SetTitle("Differential Thrust e^{+}e^{-}");
	hist_Thr_TESLEP->SetName("hist_Thr_TESLEP");
	hist_Thr_TESLEP->SetLineColor(kBlack);
	hist_Thr_TESLEP->SetMarkerColor(kBlack);
	hist_Thr_TESLEP->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_TESLEP->GetXaxis()->SetTitle("1-T");
	hist_Thr_TESLEP->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_TESLEP->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_TESLEP->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Thr_TES500 = (TH1F*)inputfile_TES500->Get("hist_ThrustP");
	// Beautify
	hist_Thr_TES500->SetStats(kFALSE);
	hist_Thr_TES500->SetTitle("Differential Thrust (without top)");
	hist_Thr_TES500->SetName("hist_Thr_TES500");
	hist_Thr_TES500->SetLineColor(kRed+2);
	hist_Thr_TES500->SetMarkerColor(kRed+2);
	hist_Thr_TES500->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_TES500->GetXaxis()->SetTitle("1-T");
	hist_Thr_TES500->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_TES500->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_TES500->GetYaxis()->SetNdivisions(510, kTRUE);

	// // Read Histogram
	TH1F *hist_Thr_Exp500 = new TH1F("hist_Thr_Exp500", "Differential Thrust (without top)", 500, 0, 0.4);
	// Beautify
	hist_Thr_Exp500->SetStats(kFALSE);
	hist_Thr_Exp500->SetName("Differential Thrust e^{+}e^{-}");
	hist_Thr_Exp500->SetName("hist_Thr_Exp500");
	hist_Thr_Exp500->SetLineColor(kBlack);
	hist_Thr_Exp500->SetMarkerColor(kBlack);
	hist_Thr_Exp500->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_Exp500->GetXaxis()->SetTitle("1-T");
	hist_Thr_Exp500->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_Exp500->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_Exp500->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_10("EXP_TES_500_THR_wot.txt");
	// Read through TXT
	while ( !infile_10.eof() ) {
		// Set reading order
		infile_10 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr_Exp500->SetBinContent(hist_Thr_Exp500->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr_Exp500->SetBinError(hist_Thr_Exp500->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_10.close();	

	// Read Histogram
	TH1F *hist_Thr_TES50t = (TH1F*)inputfile_TES50t->Get("hist_ThrustP");
	// Beautify
	hist_Thr_TES50t->SetStats(kFALSE);
	hist_Thr_TES50t->SetTitle("Differential Thrust (with top)");
	hist_Thr_TES50t->SetName("hist_Thr_TES50t");
	hist_Thr_TES50t->SetLineColor(kRed+2);
	hist_Thr_TES50t->SetMarkerColor(kRed+2);
	hist_Thr_TES50t->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_TES50t->GetXaxis()->SetTitle("1-T");
	hist_Thr_TES50t->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_TES50t->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_TES50t->GetYaxis()->SetNdivisions(510, kTRUE);

	// // Read Histogram
	TH1F *hist_Thr_Exp50t = new TH1F("hist_Thr_Exp50t", "Differential Thrust (with top)", 500, 0, 0.4);
	// Beautify
	hist_Thr_Exp50t->SetStats(kFALSE);
	hist_Thr_Exp50t->SetName("Differential Thrust e^{+}e^{-}");
	hist_Thr_Exp50t->SetName("hist_Thr_Exp50t");
	hist_Thr_Exp50t->SetLineColor(kBlack);
	hist_Thr_Exp50t->SetMarkerColor(kBlack);
	hist_Thr_Exp50t->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr_Exp50t->GetXaxis()->SetTitle("1-T");
	hist_Thr_Exp50t->GetYaxis()->SetTitle("P(1-T)");
	hist_Thr_Exp50t->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thr_Exp50t->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_11("EXP_TES_500_THR_wit.txt");
	// Read through TXT
	while ( !infile_11.eof() ) {
		// Set reading order
		infile_11 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr_Exp50t->SetBinContent(hist_Thr_Exp50t->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr_Exp50t->SetBinError(hist_Thr_Exp50t->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_11.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_nCh_LEP_Z0->Scale(1.0/hist_nCh_LEP_Z0->Integral());
	hist_nCh_TESLEP->Scale(1.0/hist_nCh_TESLEP->Integral());
	hist_nCh_TES500->Scale(1.0/hist_nCh_TES500->Integral());
	hist_nCh_TES50t->Scale(1.0/hist_nCh_TES50t->Integral());
	hist_Thr_LEP_Z0->Scale(1.0/hist_Thr_LEP_Z0->Integral());
	hist_Thr_TESLEP->Scale(1.0/hist_Thr_TESLEP->Integral());
	hist_Thr_TES500->Scale(1.0/hist_Thr_TES500->Integral());
	hist_Thr_TES50t->Scale(1.0/hist_Thr_TES50t->Integral());
	hist_Thr_Exp500->Scale(1.0/hist_Thr_Exp500->Integral());
	hist_Thr_Exp50t->Scale(1.0/hist_Thr_Exp50t->Integral());

	// Print check of integrals
	cout << "Integration : " << hist_nCh_LEP_Z0->Integral() << endl;
	cout << "Integration : " << hist_nCh_TESLEP->Integral() << endl;
	cout << "Integration : " << hist_nCh_TES500->Integral() << endl;
	cout << "Integration : " << hist_nCh_TES50t->Integral() << endl;
	cout << "Integration : " << hist_Thr_LEP_Z0->Integral() << endl;
	cout << "Integration : " << hist_Thr_TESLEP->Integral() << endl;
	cout << "Integration : " << hist_Thr_TES500->Integral() << endl;
	cout << "Integration : " << hist_Thr_TES50t->Integral() << endl;
	cout << "Integration : " << hist_Thr_Exp500->Integral() << endl;
	cout << "Integration : " << hist_Thr_Exp50t->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// KNO params
	double histNch=0.0, histMax=0.0, histMin=0.0, histBin=0.0; int numBin=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nCh_LEP_Z0->GetMean();
	histMax = hist_nCh_LEP_Z0->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nCh_LEP_Z0->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nCh_LEP_Z0->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nCh_LEP_Z0 = new TH1D("KNOO_nCh_LEP_Z0", "KNO Charged Hadron Multiplicity e^{+}e^{-}", numBin, 0, histMax);
	// Beautify
	KNOO_nCh_LEP_Z0->SetStats(kFALSE);
	KNOO_nCh_LEP_Z0->SetLineColor(kBlack);
	KNOO_nCh_LEP_Z0->SetMarkerColor(kBlack);
	KNOO_nCh_LEP_Z0->SetMarkerStyle(kOpenCircle);
	KNOO_nCh_LEP_Z0->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nCh_LEP_Z0->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nCh_LEP_Z0->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nCh_LEP_Z0->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nCh_LEP_Z0->GetNbinsX(); ++bin) {
	double nCh = hist_nCh_LEP_Z0->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nCh_LEP_Z0->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nCh_LEP_Z0->GetBinContent(bin) * histNch;
	double scaledError = hist_nCh_LEP_Z0->GetBinError(bin) * histNch;
	KNOO_nCh_LEP_Z0->Fill(scaledNch, scaledContent);
	KNOO_nCh_LEP_Z0->SetBinError(KNOO_nCh_LEP_Z0->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nCh_TESLEP->GetMean();
	histMax = hist_nCh_TESLEP->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nCh_TESLEP->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nCh_TESLEP->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nCh_TESLEP = new TH1D("KNOO_nCh_TESLEP", "KNO Charged Hadron Multiplicity e^{+}e^{-}", numBin, 0, histMax);
	// Beautify
	KNOO_nCh_TESLEP->SetStats(kFALSE);
	KNOO_nCh_TESLEP->SetLineColor(kBlack);
	KNOO_nCh_TESLEP->SetMarkerColor(kBlack);
	KNOO_nCh_TESLEP->SetMarkerStyle(kOpenTriangleUp);
	KNOO_nCh_TESLEP->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nCh_TESLEP->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nCh_TESLEP->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nCh_TESLEP->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nCh_TESLEP->GetNbinsX(); ++bin) {
	double nCh = hist_nCh_TESLEP->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nCh_TESLEP->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nCh_TESLEP->GetBinContent(bin) * histNch;
	double scaledError = hist_nCh_TESLEP->GetBinError(bin) * histNch;
	KNOO_nCh_TESLEP->Fill(scaledNch, scaledContent);
	KNOO_nCh_TESLEP->SetBinError(KNOO_nCh_TESLEP->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nCh_TES500->GetMean();
	histMax = hist_nCh_TES500->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nCh_TES500->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nCh_TES500->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nCh_TES500 = new TH1D("KNOO_nCh_TES500", "KNO Charged Hadron Multiplicity e^{+}e^{-}", numBin, 0, histMax);
	// Beautify
	KNOO_nCh_TES500->SetStats(kFALSE);
	KNOO_nCh_TES500->SetLineColor(kRed+1);
	KNOO_nCh_TES500->SetMarkerColor(kRed+1);
	KNOO_nCh_TES500->SetMarkerStyle(kOpenTriangleUp);
	KNOO_nCh_TES500->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nCh_TES500->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nCh_TES500->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nCh_TES500->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nCh_TES500->GetNbinsX(); ++bin) {
	double nCh = hist_nCh_TES500->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nCh_TES500->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nCh_TES500->GetBinContent(bin) * histNch;
	double scaledError = hist_nCh_TES500->GetBinError(bin) * histNch;
	KNOO_nCh_TES500->Fill(scaledNch, scaledContent);
	KNOO_nCh_TES500->SetBinError(KNOO_nCh_TES500->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nCh_TES50t->GetMean();
	histMax = hist_nCh_TES50t->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nCh_TES50t->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nCh_TES50t->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nCh_TES50t = new TH1D("KNOO_nCh_TES50t", "KNO Charged Hadron Multiplicity e^{+}e^{-}", numBin, 0, histMax);
	// Beautify
	KNOO_nCh_TES50t->SetStats(kFALSE);
	KNOO_nCh_TES50t->SetLineColor(kGreen+1);
	KNOO_nCh_TES50t->SetMarkerColor(kGreen+1);
	KNOO_nCh_TES50t->SetMarkerStyle(kOpenTriangleUp);
	KNOO_nCh_TES50t->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nCh_TES50t->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nCh_TES50t->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nCh_TES50t->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nCh_TES50t->GetNbinsX(); ++bin) {
	double nCh = hist_nCh_TES50t->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nCh_TES50t->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nCh_TES50t->GetBinContent(bin) * histNch;
	double scaledError = hist_nCh_TES50t->GetBinError(bin) * histNch;
	KNOO_nCh_TES50t->Fill(scaledNch, scaledContent);
	KNOO_nCh_TES50t->SetBinError(KNOO_nCh_TES50t->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Charged Hadronic Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *leg_nch = new TLegend(0.4, 0.2, 0.85, 0.4);
	leg_nch->AddEntry(hist_nCh_LEP_Z0, "91.2 GeV (LEP)", "p");
	leg_nch->AddEntry(hist_nCh_TESLEP, "500. GeV (LEP)", "p");
	leg_nch->AddEntry(hist_nCh_TES500, "500. GeV (TESLA)", "p");
	leg_nch->AddEntry(hist_nCh_TES50t, "500. GeV (TESLA+top)", "p");
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
	hist_nCh_TES500->Draw("PS");
	hist_nCh_TES50t->Draw("same");
	hist_nCh_TESLEP->Draw("same");
	hist_nCh_LEP_Z0->Draw("same");
	leg_nch->Draw("same");
	c_nch->cd(2);
	KNOO_nCh_TES500->Draw("PS");
	KNOO_nCh_TES50t->Draw("same");
	KNOO_nCh_TESLEP->Draw("same");
	KNOO_nCh_LEP_Z0->Draw("same");
	leg_nch->Draw("same");

	// Modify stat-box
	gStyle->SetOptStat();
	c_nch->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Add legend
	// TLegend *lg_thr1 = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lg_thr1->AddEntry(hist_Thr_LEP_Z0, "Pythia 8.3 LEPZ0", "p");
	// lg_thr1->AddEntry(hist_Thr_TES500, "Pythia 8.3 TESLA", "p");
	// lg_thr1->AddEntry(hist_Thr_Exp500, "1999 Study TESLA", "p");
	// lg_thr1->SetTextSize(0.04);

	// // Add legend
	// TLegend *lg_thr2 = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lg_thr2->AddEntry(hist_Thr_TES50t, "Pythia 8.3 TESLA", "p");
	// lg_thr2->AddEntry(hist_Thr_Exp50t, "1999 Study TESLA", "p");
	// lg_thr2->SetTextSize(0.04);

	// // Create canvas
	// TCanvas* c_thr = new TCanvas("c_thr", "Charged hadron multiplicity distributions", 800, 600);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// c_thr->Divide(2,1);
	// c_thr->cd(1)->SetLeftMargin(0.15);
	// c_thr->cd(1)->SetLogy();
	// c_thr->cd(1)->SetTickx(); c_thr->cd(1)->SetTicky();
	// c_thr->cd(1)->SetGridx(); c_thr->cd(1)->SetGridy();
	// c_thr->cd(2)->SetLeftMargin(0.15);
	// c_thr->cd(2)->SetLogy();
	// c_thr->cd(2)->SetTickx(); c_thr->cd(2)->SetTicky();
	// c_thr->cd(2)->SetGridx(); c_thr->cd(2)->SetGridy();
	
	// // Draw
	// c_thr->cd(1);
	// hist_Thr_Exp500->Draw("p");
	// hist_Thr_TES500->Draw("psame");
	// hist_Thr_LEP_Z0->Draw("psame");
	// lg_thr1->Draw("same");
	// c_thr->cd(2);
	// hist_Thr_Exp50t->Draw("p");
	// hist_Thr_TES50t->Draw("psame");
	// lg_thr2->Draw("same");

	// hist_Thr_TES500->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_Thr_Exp500->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_Thr_TES50t->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_Thr_Exp50t->GetYaxis()->SetRangeUser(1E-4,1E0);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// c_thr->Modified();

}