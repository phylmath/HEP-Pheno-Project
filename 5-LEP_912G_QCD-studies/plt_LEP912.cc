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
// Extras
// void Beautify(TH1F inhist);


// Code
void plt_LEP912()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating file, Reading TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile* input_LEP_Z0 = new TFile("out_LEP912_Z0.root", "READ");
	TFile* input_LEP_2W = new TFile("out_LEP912_2W.root", "READ");
	// TFile* input_thrust = new TFile("HEPData-Table_47.root", "READ");
	// Read TTree
	TTree* tree = (TTree*)input_LEP_Z0->Get("tree");

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nChPyZ0 = (TH1F*)input_LEP_Z0->Get("hist_nChPyth");
	// Beautify
	hist_nChPyZ0->SetStats(kFALSE);
	hist_nChPyZ0->SetName("Fit results");
	hist_nChPyZ0->SetLineColor(kBlack);
	hist_nChPyZ0->SetMarkerColor(kBlack);
	hist_nChPyZ0->SetMarkerStyle(kOpenSquare);
	hist_nChPyZ0->GetXaxis()->SetTitle("N_{CH}");
	hist_nChPyZ0->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChPyZ0->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChPyZ0->GetYaxis()->SetNdivisions(510, kTRUE);

	// Make Histogram
	TH1F *hist_nChExLZ = new TH1F("hist_nChExLZ", " ", 28, 1, 57);
	// Beautify
	hist_nChExLZ->SetStats(kFALSE);
	hist_nChExLZ->SetName(" L3 91.2 GeV ]");
	hist_nChExLZ->SetName("hist_nChExLZ");
	hist_nChExLZ->SetLineColor(kBlack);
	hist_nChExLZ->SetMarkerColor(kBlack);
	hist_nChExLZ->SetMarkerStyle(kOpenCircle);
	hist_nChExLZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nChExLZ->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChExLZ->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChExLZ->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_00("EXP_LEP_912_L3_NCH.txt");
	// Read through TXT
	while ( !infile_00.eof() ) {
		// Set reading order
		infile_00 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_nChExLZ->SetBinContent(hist_nChExLZ->FindBin(Nch), Prb);
		// Populate error bar
		hist_nChExLZ->SetBinError(hist_nChExLZ->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_00.close();

	// Make Histogram
	TH1F *hist_nChExOZ = new TH1F("hist_nChExOZ", " ", 27, 1, 55);
	// Beautify
	hist_nChExOZ->SetStats(kFALSE);
	hist_nChExOZ->SetName(" OPAL 91.2 GeV ]");
	hist_nChExOZ->SetName("hist_nChExOZ");
	hist_nChExOZ->SetLineColor(kBlack);
	hist_nChExOZ->SetMarkerColor(kBlack);
	hist_nChExOZ->SetMarkerStyle(kOpenTriangleUp);
	hist_nChExOZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nChExOZ->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChExOZ->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChExOZ->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_01("EXP_LEP_912_OPAL_NCH.txt");
	// Read through TXT
	while ( !infile_01.eof() ) {
		// Set reading order
		infile_01 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_nChExOZ->SetBinContent(hist_nChExOZ->FindBin(Nch), Prb);
		// Populate error bar
		hist_nChExOZ->SetBinError(hist_nChExOZ->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_01.close();

	// Read Histogram
	TH1F *hist_nChPy2W = (TH1F*)input_LEP_2W->Get("hist_nChPyth");
	// Beautify
	hist_nChPy2W->SetStats(kFALSE);
	hist_nChPy2W->SetName("Fit results");
	hist_nChPy2W->SetLineColor(kRed+1);
	hist_nChPy2W->SetMarkerColor(kRed+1);
	hist_nChPy2W->SetMarkerStyle(kOpenSquare);
	hist_nChPy2W->GetXaxis()->SetTitle("N_{CH}");
	hist_nChPy2W->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChPy2W->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChPy2W->GetYaxis()->SetNdivisions(510, kTRUE);

	// Make Histogram
	TH1F *hist_nChExLW = new TH1F("hist_nChExLW", " ", 22, 9, 53);
	// Beautify
	hist_nChExLW->SetStats(kFALSE);
	hist_nChExLW->SetName(" L3 161 GeV ]");
	hist_nChExLW->SetName("hist_nChExLW");
	hist_nChExLW->SetLineColor(kRed+1);
	hist_nChExLW->SetMarkerColor(kRed+1);
	hist_nChExLW->SetMarkerStyle(kOpenCircle);
	hist_nChExLW->GetXaxis()->SetTitle("N_{CH}");
	hist_nChExLW->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChExLW->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChExLW->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_03("EXP_LEP_161_L3_NCH.txt");
	// Read through TXT
	while ( !infile_03.eof() ) {
		// Set reading order
		infile_03 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_nChExLW->SetBinContent(hist_nChExLW->FindBin(Nch), Prb);
		// Populate error bar
		hist_nChExLW->SetBinError(hist_nChExLW->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_03.close();

	// Make Histogram
	TH1F *hist_nChExOW = new TH1F("hist_nChExOW", " ", 25, 7, 57);
	// Beautify
	hist_nChExOW->SetStats(kFALSE);
	hist_nChExOW->SetName(" OPAL 161 GeV ]");
	hist_nChExOW->SetName("hist_nChExOW");
	hist_nChExOW->SetLineColor(kRed+1);
	hist_nChExOW->SetMarkerColor(kRed+1);
	hist_nChExOW->SetMarkerStyle(kOpenTriangleUp);
	hist_nChExOW->GetXaxis()->SetTitle("N_{CH}");
	hist_nChExOW->GetYaxis()->SetTitle("P(N_{CH})");
	hist_nChExOW->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChExOW->GetYaxis()->SetNdivisions(510, kTRUE);
	// Import data
	ifstream infile_02("EXP_LEP_161_OPAL_NCH.txt");
	// Read through TXT
	while ( !infile_02.eof() ) {
		// Set reading order
		infile_02 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_nChExOW->SetBinContent(hist_nChExOW->FindBin(Nch), Prb);
		// Populate error bar
		hist_nChExOW->SetBinError(hist_nChExOW->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_02.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nJetsCh = (TH1F*)input_LEP_Z0->Get("hist_nJetsCh");
	// Beautify
	// hist_nJetsCh->SetStats(kFALSE);
	hist_nJetsCh->SetLineColor(kBlue+1);
	hist_nJetsCh->SetMarkerColor(kBlue+1);
	hist_nJetsCh->SetMarkerStyle(20);
	hist_nJetsCh->GetXaxis()->SetTitle("Multiplicity");
	hist_nJetsCh->GetYaxis()->SetTitle("Probability");
	hist_nJetsCh->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nJetsCh->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nParton = (TH1F*)input_LEP_Z0->Get("hist_nParton");
	// Beautify
	hist_nParton->SetStats(kFALSE);
	hist_nParton->SetLineColor(kRed+1);
	hist_nParton->SetMarkerColor(kRed+1);
	hist_nParton->SetMarkerStyle(20);
	hist_nParton->GetXaxis()->SetTitle("Multiplicity");
	hist_nParton->GetYaxis()->SetTitle("Probability");
	hist_nParton->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nParton->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nPQuark = (TH1F*)input_LEP_Z0->Get("hist_nPQuark");
	// Beautify
	hist_nPQuark->SetStats(kFALSE);
	hist_nPQuark->SetLineColor(kBlue+1);
	hist_nPQuark->SetMarkerColor(kBlue+1);
	hist_nPQuark->SetMarkerStyle(20);
	hist_nPQuark->GetXaxis()->SetTitle("Multiplicity");
	hist_nPQuark->GetYaxis()->SetTitle("Probability");
	hist_nPQuark->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nPQuark->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nPGluon = (TH1F*)input_LEP_Z0->Get("hist_nPGluon");
	// Beautify
	hist_nPGluon->SetStats(kFALSE);
	hist_nPGluon->SetLineColor(kGreen+1);
	hist_nPGluon->SetMarkerColor(kGreen+1);
	hist_nPGluon->SetMarkerStyle(20);
	hist_nPGluon->GetXaxis()->SetTitle("Multiplicity");
	hist_nPGluon->GetYaxis()->SetTitle("Probability");
	hist_nPGluon->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nPGluon->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_Spheric = (TH1F*)input_LEP_Z0->Get("hist_Spheric");
	// Beautify
	hist_Spheric->SetStats(kFALSE);
	hist_Spheric->SetLineColor(kBlack);
	hist_Spheric->SetMarkerColor(kBlack);
	hist_Spheric->SetMarkerStyle(20);
	hist_Spheric->GetXaxis()->SetTitle("Sphericity");
	hist_Spheric->GetYaxis()->SetTitle("Probability");
	hist_Spheric->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Spheric->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_Lineric = (TH1F*)input_LEP_Z0->Get("hist_Lineric");
	// Beautify
	hist_Lineric->SetStats(kFALSE);
	hist_Lineric->SetLineColor(kBlack);
	hist_Lineric->SetMarkerColor(kBlack);
	hist_Lineric->SetMarkerStyle(20);
	hist_Lineric->GetXaxis()->SetTitle("Linearity");
	hist_Lineric->GetYaxis()->SetTitle("Probability");
	hist_Lineric->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Lineric->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	// TH1F *hist_ThrustE = (TH1F*)input_thrust->Get("Table 47/Hist1D_y1");
	TH1F *hist_ThrustE = new TH1F("hist_ThrustE", "Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 17, 0.575, 1.);
	// Beautify
	// hist_ThrustE->SetStats(kFALSE);
	hist_ThrustE->SetName("Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	hist_ThrustE->SetName("hist_ThrustE");
	hist_ThrustE->SetLineColor(kRed+1);
	hist_ThrustE->SetMarkerColor(kRed+1);
	hist_ThrustE->SetMarkerStyle(48);
	hist_ThrustE->SetMarkerSize(1.5);
	hist_ThrustE->GetXaxis()->SetTitle("Thrust");
	hist_ThrustE->GetYaxis()->SetTitle("Probability");
	hist_ThrustE->GetXaxis()->SetNdivisions(515, kTRUE);
	hist_ThrustE->GetYaxis()->SetNdivisions(515, kTRUE);
	// Import data
	ifstream infile_10("EXP_LEP_912_L3_THR_udsc.txt");
	// Read through TXT
	while ( !infile_10.eof() ) {
		// Set reading order
		infile_10 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_ThrustE->SetBinContent(hist_ThrustE->FindBin(Nch), Prb);
		// Populate error bar
		hist_ThrustE->SetBinError(hist_ThrustE->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_10.close();

	// // Read Histogram
	// TH1F *hist_ThrustX = (TH1F*)input_thrust->Get("Table 47/Hist1D_y2");
	TH1F *hist_ThrustX = new TH1F("hist_ThrustX", "Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 17, 0.575, 1.);
	// Beautify
	// hist_ThrustX->SetStats(kFALSE);
	hist_ThrustX->SetName("Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	hist_ThrustX->SetName("hist_ThrustX");
	hist_ThrustX->SetLineColor(kGreen+2);
	hist_ThrustX->SetMarkerColor(kGreen+2);
	hist_ThrustX->SetMarkerStyle(49);
	hist_ThrustX->SetMarkerSize(1.5);
	hist_ThrustX->GetXaxis()->SetTitle("Thrust");
	hist_ThrustX->GetYaxis()->SetTitle("Probability");
	hist_ThrustX->GetXaxis()->SetNdivisions(515, kTRUE);
	hist_ThrustX->GetYaxis()->SetNdivisions(515, kTRUE);
	// Import data
	ifstream infile_11("EXP_LEP_912_L3_THR_b.txt");
	// Read through TXT
	while ( !infile_11.eof() ) {
		// Set reading order
		infile_11 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_ThrustX->SetBinContent(hist_ThrustX->FindBin(Nch), Prb);
		// Populate error bar
		hist_ThrustX->SetBinError(hist_ThrustX->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_11.close();

	// Read Histogram
	TH1F *hist_ThrustP = (TH1F*)input_LEP_Z0->Get("hist_ThrustP");
	// Beautify
	// hist_ThrustP->SetStats(kFALSE);
	hist_ThrustP->SetLineColor(kBlue+1);
	hist_ThrustP->SetMarkerColor(kBlue+1);
	hist_ThrustP->SetMarkerStyle(29);
	hist_ThrustP->SetMarkerSize(1.5);
	hist_ThrustP->GetXaxis()->SetTitle("Thrust");
	hist_ThrustP->GetYaxis()->SetTitle("Probability");
	hist_ThrustP->GetXaxis()->SetNdivisions(515, kTRUE);
	hist_ThrustP->GetYaxis()->SetNdivisions(515, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_Oblatey = (TH1F*)input_LEP_Z0->Get("hist_Oblatey");
	// Beautify
	hist_Oblatey->SetStats(kFALSE);
	hist_Oblatey->SetLineColor(kBlack);
	hist_Oblatey->SetMarkerColor(kBlack);
	hist_Oblatey->SetMarkerStyle(20);
	hist_Oblatey->GetXaxis()->SetTitle("Oblateness");
	hist_Oblatey->GetYaxis()->SetTitle("Probability");
	hist_Oblatey->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Oblatey->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_sphAxis = (TH1F*)input_LEP_Z0->Get("hist_sphAxis");
	// Beautify
	hist_sphAxis->SetStats(kFALSE);
	hist_sphAxis->SetLineColor(kRed+1);
	hist_sphAxis->SetMarkerColor(kRed+1);
	hist_sphAxis->SetMarkerStyle(20);
	hist_sphAxis->GetXaxis()->SetTitle("Sphericity axis");
	hist_sphAxis->GetYaxis()->SetTitle("Probability");
	hist_sphAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_sphAxis->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_linAxis = (TH1F*)input_LEP_Z0->Get("hist_linAxis");
	// Beautify
	hist_linAxis->SetStats(kFALSE);
	hist_linAxis->SetLineColor(kGreen+2);
	hist_linAxis->SetMarkerColor(kGreen+2);
	hist_linAxis->SetMarkerStyle(20);
	hist_linAxis->GetXaxis()->SetTitle("Linearity axis");
	hist_linAxis->GetYaxis()->SetTitle("Probability");
	hist_linAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_linAxis->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_thrAxis = (TH1F*)input_LEP_Z0->Get("hist_thrAxis");
	// Beautify
	hist_thrAxis->SetStats(kFALSE);
	hist_thrAxis->SetLineColor(kBlue+1);
	hist_thrAxis->SetMarkerColor(kBlue+1);
	hist_thrAxis->SetMarkerStyle(20);
	hist_thrAxis->GetXaxis()->SetTitle("Thrust axis");
	hist_thrAxis->GetYaxis()->SetTitle("Probability");
	hist_thrAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_thrAxis->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_nChExLZ->Scale(1.0/hist_nChExLZ->Integral());
	hist_nChExLW->Scale(1.0/hist_nChExLW->Integral());
	hist_nChExOZ->Scale(1.0/hist_nChExOZ->Integral());
	hist_nChExOW->Scale(1.0/hist_nChExOW->Integral());
	hist_nChPyZ0->Scale(1.0/hist_nChPyZ0->Integral());
	hist_nChPy2W->Scale(1.0/hist_nChPy2W->Integral());

	hist_nJetsCh->Scale(1.0/hist_nJetsCh->Integral());

	hist_ThrustE->Scale(1.0/hist_ThrustE->Integral());
	hist_ThrustX->Scale(1.0/hist_ThrustX->Integral());
	hist_ThrustP->Scale(1.0/hist_ThrustP->Integral());

	hist_nParton->Scale(1.0/hist_nParton->Integral());
	hist_nPQuark->Scale(1.0/hist_nPQuark->Integral());
	hist_nPGluon->Scale(1.0/hist_nPGluon->Integral());

	// Print check of integrals
	cout << "Integration : " << hist_nChExLZ->Integral() << endl;
	cout << "Integration : " << hist_nChExLW->Integral() << endl;
	cout << "Integration : " << hist_nChExOZ->Integral() << endl;
	cout << "Integration : " << hist_nChExOW->Integral() << endl;
	cout << "Integration : " << hist_nChPyZ0->Integral() << endl;
	cout << "Integration : " << hist_nChPy2W->Integral() << endl;

	cout << "Integration : " << hist_nJetsCh->Integral() << endl;

	cout << "Integration : " << hist_ThrustE->Integral() << endl;
	cout << "Integration : " << hist_ThrustX->Integral() << endl;
	cout << "Integration : " << hist_ThrustP->Integral() << endl;

	cout << "Integration : " << hist_nParton->Integral() << endl;
	cout << "Integration : " << hist_nPQuark->Integral() << endl;
	cout << "Integration : " << hist_nPGluon->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Axes params
	double histNch = hist_nChPyZ0->GetMean();
	double histMax = hist_nChPyZ0->GetXaxis()->GetXmax()/histNch;
	double histMin = hist_nChPyZ0->GetXaxis()->GetXmin()/histNch;
	double histBin = hist_nChPyZ0->GetBinWidth(10)/histNch;
	int numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChPyZ0 = new TH1D("KNOO_nChPyZ0", "KNO Scaled Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", numBin, 0, histMax);
	// Beautify
	KNOO_nChPyZ0->SetStats(kFALSE);
	KNOO_nChPyZ0->SetLineColor(kBlack);
	KNOO_nChPyZ0->SetMarkerColor(kBlack);
	KNOO_nChPyZ0->SetMarkerStyle(kOpenSquare);
	KNOO_nChPyZ0->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChPyZ0->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChPyZ0->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChPyZ0->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChPyZ0->GetNbinsX(); ++bin) {
	double nCh = hist_nChPyZ0->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChPyZ0->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChPyZ0->GetBinContent(bin) * histNch;
	double scaledError = hist_nChPyZ0->GetBinError(bin) * histNch;
	KNOO_nChPyZ0->Fill(scaledNch, scaledContent);
	KNOO_nChPyZ0->SetBinError(KNOO_nChPyZ0->FindBin(scaledNch), scaledError);
	}

	// Axes params
	histNch = hist_nChExLZ->GetMean();
	histMax = hist_nChExLZ->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nChExLZ->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nChExLZ->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChExLZ = new TH1D("KNOO_nChExLZ", " ", numBin, 0, histMax);
	// Beautify
	KNOO_nChExLZ->SetStats(kFALSE);
	KNOO_nChExLZ->SetLineColor(kBlack);
	KNOO_nChExLZ->SetMarkerColor(kBlack);
	KNOO_nChExLZ->SetMarkerStyle(kOpenCircle);
	KNOO_nChExLZ->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChExLZ->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChExLZ->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChExLZ->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChExLZ->GetNbinsX(); ++bin) {
	double nCh = hist_nChExLZ->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChExLZ->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChExLZ->GetBinContent(bin) * histNch;
	double scaledError = hist_nChExLZ->GetBinError(bin) * histNch;
	KNOO_nChExLZ->Fill(scaledNch, scaledContent);
	KNOO_nChExLZ->SetBinError(KNOO_nChExLZ->FindBin(scaledNch), scaledError);
	}

	// Axes params
	histNch = hist_nChExOZ->GetMean();
	histMax = hist_nChExOZ->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nChExOZ->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nChExOZ->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChExOZ = new TH1D("KNOO_nChExOZ", " ", numBin, 0, histMax);
	// Beautify
	KNOO_nChExOZ->SetStats(kFALSE);
	KNOO_nChExOZ->SetLineColor(kBlack);
	KNOO_nChExOZ->SetMarkerColor(kBlack);
	KNOO_nChExOZ->SetMarkerStyle(kOpenTriangleUp);
	KNOO_nChExOZ->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChExOZ->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChExOZ->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChExOZ->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChExOZ->GetNbinsX(); ++bin) {
	double nCh = hist_nChExOZ->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChExOZ->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChExOZ->GetBinContent(bin) * histNch;
	double scaledError = hist_nChExOZ->GetBinError(bin) * histNch;
	KNOO_nChExOZ->Fill(scaledNch, scaledContent);
	KNOO_nChExOZ->SetBinError(KNOO_nChExOZ->FindBin(scaledNch), scaledError);
	}

	// Axes params
	histNch = hist_nChPy2W->GetMean();
	histMax = hist_nChPy2W->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nChPy2W->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nChPy2W->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChPy2W = new TH1D("KNOO_nChPy2W", " ", numBin, 0, histMax);
	// Beautify
	KNOO_nChPy2W->SetStats(kFALSE);
	KNOO_nChPy2W->SetLineColor(kRed+1);
	KNOO_nChPy2W->SetMarkerColor(kRed+1);
	KNOO_nChPy2W->SetMarkerStyle(kOpenSquare);
	KNOO_nChPy2W->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChPy2W->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChPy2W->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChPy2W->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChPy2W->GetNbinsX(); ++bin) {
	double nCh = hist_nChPy2W->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChPy2W->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChPy2W->GetBinContent(bin) * histNch;
	double scaledError = hist_nChPy2W->GetBinError(bin) * histNch;
	KNOO_nChPy2W->Fill(scaledNch, scaledContent);
	KNOO_nChPy2W->SetBinError(KNOO_nChPy2W->FindBin(scaledNch), scaledError);
	}

	// Axes params
	histNch = hist_nChExLW->GetMean();
	histMax = hist_nChExLW->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nChExLW->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nChExLW->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChExLW = new TH1D("KNOO_nChExLW", " ", numBin, 0, histMax);
	// Beautify
	KNOO_nChExLW->SetStats(kFALSE);
	KNOO_nChExLW->SetLineColor(kRed+1);
	KNOO_nChExLW->SetMarkerColor(kRed+1);
	KNOO_nChExLW->SetMarkerStyle(kOpenCircle);
	KNOO_nChExLW->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChExLW->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChExLW->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChExLW->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChExLW->GetNbinsX(); ++bin) {
	double nCh = hist_nChExLW->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChExLW->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChExLW->GetBinContent(bin) * histNch;
	double scaledError = hist_nChExLW->GetBinError(bin) * histNch;
	KNOO_nChExLW->Fill(scaledNch, scaledContent);
	KNOO_nChExLW->SetBinError(KNOO_nChExLW->FindBin(scaledNch), scaledError);
	}

	// Axes params
	histNch = hist_nChExOW->GetMean();
	histMax = hist_nChExOW->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nChExOW->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nChExOW->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nChExOW = new TH1D("KNOO_nChExOW", " ", numBin, 0, histMax);
	// Beautify
	KNOO_nChExOW->SetStats(kFALSE);
	KNOO_nChExOW->SetLineColor(kRed+1);
	KNOO_nChExOW->SetMarkerColor(kRed+1);
	KNOO_nChExOW->SetMarkerStyle(kOpenTriangleUp);
	KNOO_nChExOW->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nChExOW->GetYaxis()->SetTitle("P(N_{CH}) x N_{CH}");
	KNOO_nChExOW->GetXaxis()->SetNdivisions(510, kTRUE);
	KNOO_nChExOW->GetYaxis()->SetNdivisions(510, kTRUE);
	// Fill histogram
	for (int bin = 1; bin <= hist_nChExOW->GetNbinsX(); ++bin) {
	double nCh = hist_nChExOW->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nChExOW->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nChExOW->GetBinContent(bin) * histNch;
	double scaledError = hist_nChExOW->GetBinError(bin) * histNch;
	KNOO_nChExOW->Fill(scaledNch, scaledContent);
	KNOO_nChExOW->SetBinError(KNOO_nChExOW->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Charged Hadronic Multiplicity (Experimental vs Pythia)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_nChPyZ0, "Pythia 8.3 at Z0", "p");
	legend->AddEntry(hist_nChExLZ, "LEP L3 at Z0", "p");
	legend->AddEntry(hist_nChExOZ, "LEP OPAL at Z0", "p");
	legend->AddEntry(hist_nChPy2W, "Pythia 8.3 at 2W", "p");
	legend->AddEntry(hist_nChExLW, "LEP L3 at 2W", "p");
	legend->AddEntry(hist_nChExOW, "LEP OPAL at 2W", "p");
	// legend->AddEntry(fist_nChExpe, "NBD fit for Experimental data", "l");
	// legend->AddEntry(fist_nChPyth, "NBD fit for Pythia data", "l");

	// Create canvas
	TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);
	// Beautify
	// c_nch->SetLogy();
	// c_nch->SetTickx();
	// c_nch->SetTicky();
	// c_nch->SetGridx();
	// c_nch->SetGridy();
	// Draw
	c_nch->Divide(2,1);
	c_nch->cd(1);
	c_nch->cd(1)->SetLogy();
	c_nch->cd(1)->SetTickx();
	c_nch->cd(1)->SetTicky();
	c_nch->cd(1)->SetGridx();
	c_nch->cd(1)->SetGridy();
	hist_nChPyZ0->Draw("PS");
	hist_nChExLZ->Draw("same");
	hist_nChExOZ->Draw("same");
	hist_nChPy2W->Draw("same");
	hist_nChExLW->Draw("same");
	hist_nChExOW->Draw("same");
	legend->Draw("same");
	c_nch->cd(2);
	c_nch->cd(2)->SetLogy();
	c_nch->cd(2)->SetTickx();
	c_nch->cd(2)->SetTicky();
	c_nch->cd(2)->SetGridx();
	c_nch->cd(2)->SetGridy();
	KNOO_nChPyZ0->Draw("PS");
	KNOO_nChExLZ->Draw("same");
	KNOO_nChExOZ->Draw("same");
	KNOO_nChPy2W->Draw("same");
	KNOO_nChExLW->Draw("same");
	KNOO_nChExOW->Draw("same");
	legend->Draw("same");

	// // Fit Pythia data
	// TF1 *fist_nChPyth = new TF1("fist_nChPyth", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // Beautify
	// fist_nChPyth->SetLineWidth(3);
	// fist_nChPyth->SetLineColor(kBlue);
	// fist_nChPyth->SetLineStyle(2);
	// // Rename fit params
	// fist_nChPyth->SetParNames("C","K","<N>");
	// // Input fit params
	// fist_nChPyth->SetParameter(0,1.88);				// c - normalisation
	// fist_nChPyth->SetParameter(1,12.5);				// k - shape
	// fist_nChPyth->SetParameter(2,19);				// n - expected mean
	// // Perform fit
	// hist_nChPyZ0->Fit("fist_nChPyth", "RME");		// R(range) Q(suppress terminal output) 0(fit display)
	// // Draw
	// fist_nChPyth->Draw("same");

	// // Fit Experimental data
	// TF1 *fist_nChExpe = new TF1("fist_nChExpe", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // Beautify
	// fist_nChExpe->SetLineWidth(3);
	// fist_nChExpe->SetLineColor(kRed);
	// fist_nChExpe->SetLineStyle(2);
	// // Rename fit params
	// fist_nChExpe->SetParNames("C","K","<N>");
	// // Input fit params
	// fist_nChExpe->SetParameter(0,1.88);				// c - normalisation
	// fist_nChExpe->SetParameter(1,12.5);				// k - shape
	// fist_nChExpe->SetParameter(2,19);				// n - expected mean
	// // Perform fit
	// hist_nChExLZ->Fit("fist_nChExpe", "RME");		// R(range) Q(suppress terminal output) 0(fit display)
	// // Draw fit
	// fist_nChExpe->Draw("same");

	// Modify stat-box
	gStyle->SetOptStat();
	gStyle->SetErrorX(0.00001);
	// TPaveStats *ps = (TPaveStats *)c_nch->GetPrimitive("stats");
	// ps->SetName("mystats");
	// // Delete existing lines
	// TList *listOfLines = ps->GetListOfLines();
	// listOfLines->Remove(ps->GetLineWith("Entries"));
	// listOfLines->Remove(ps->GetLineWith("Mean"));
	// listOfLines->Remove(ps->GetLineWith("Std"));
	// // Add fit params
	// stringstream buffer;
	// ps->AddText("NBD Fit (Pythia data)");
	// buffer << "#chi^{2}/CDF = " << fist_nChPyth->GetChisquare() << " / " << fist_nChPyth->GetNDF();
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "  C = " << fist_nChPyth->GetParameter(0) << " #pm " << fist_nChPyth->GetParError(0);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "  K = " << fist_nChPyth->GetParameter(1) << " #pm " << fist_nChPyth->GetParError(1);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "<N> = " << fist_nChPyth->GetParameter(2) << " #pm " << fist_nChPyth->GetParError(2);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// ps->AddText("NBD Fit (LEP-L3 data)");
	// buffer << "#chi^{2}/CDF = " << fist_nChExpe->GetChisquare() << " / " << fist_nChExpe->GetNDF();
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "  C = " << fist_nChExpe->GetParameter(0) << " #pm " << fist_nChExpe->GetParError(0);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "  K = " << fist_nChExpe->GetParameter(1) << " #pm " << fist_nChExpe->GetParError(1);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// buffer << "<N> = " << fist_nChExpe->GetParameter(2) << " #pm " << fist_nChExpe->GetParError(2);
	// ps->AddText(buffer.str().c_str());
	// buffer.str(std::string());
	// // Update stat-box
	// hist_nChPyZ0->SetStats(0);
	// hist_nChExLZ->SetStats(0);
	c_nch->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Hadronic Jet Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_ncj = new TCanvas("c_ncj", "Hadronic jet multiplicity distributions", 800, 600);
	// // Beautify
	// // c_ncj->SetLogy();
	// c_ncj->SetTickx();
	// c_ncj->SetTicky();
	// c_ncj->SetGridx();
	// c_ncj->SetGridy();

	// // Draw histogram
	// c_ncj->cd();
	// hist_nJetsCh->Draw("PS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_nct = new TCanvas("c_nct", "Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 800, 600);
	// // Beautify
	// c_nct->SetTitle("Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	// c_nct->SetLogy();
	// c_nct->SetTickx();
	// c_nct->SetTicky();
	// c_nct->SetGridx();
	// c_nct->SetGridy();

	// // Add legend
	// TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	// legend->AddEntry(hist_ThrustE, "LEP L3 data (udsc)", "p");
	// legend->AddEntry(hist_ThrustX, "LEP L3 data (b)", "p");
	// legend->AddEntry(hist_ThrustP, "Pythia data (udscb)", "p");

	// // Draw histogram
	// c_nct->cd();
	// hist_ThrustP->Draw("PS");
	// hist_ThrustE->Draw("sames");
	// hist_ThrustX->Draw("sames");
	// legend->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Event Axes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_axx = new TCanvas("c_axx", "Event Axes distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 800, 600);
	// // Beautify
	// c_axx->SetTitle("Event Axes distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	// c_axx->SetLogy();
	// c_axx->SetTickx();
	// c_axx->SetTicky();
	// c_axx->SetGridx();
	// c_axx->SetGridy();

	// // Add legend
	// TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	// legend->AddEntry(hist_thrAxis, "Thrust axis", "p");
	// legend->AddEntry(hist_sphAxis, "Sphericity axis", "p");
	// legend->AddEntry(hist_linAxis, "Linear Sphericity axis", "p");

	// // Draw histogram
	// c_axx->cd();
	// hist_thrAxis->Draw("PS");
	// hist_sphAxis->Draw("sames");
	// hist_linAxis->Draw("sames");
	// legend->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Intermediate Parton Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_imp = new TCanvas("c_imp", "Intermediate Parton Multiplicity distributions", 800, 600);
	// // Beautify
	// c_imp->SetLogy();
	// c_imp->SetTickx();
	// c_imp->SetTicky();
	// c_imp->SetGridx();
	// c_imp->SetGridy();

	// // Add legend
	// TLegend* lege_imp = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lege_imp->AddEntry(hist_nParton, "Intermediate parton multiplicity", "p");
	// lege_imp->AddEntry(hist_nPQuark, "Intermediate quarks multiplicity", "p");
	// lege_imp->AddEntry(hist_nPGluon, "Intermediate gluons multiplicity", "p");

	// // Draw histogram
	// hist_nParton->Draw("c_imp");
	// hist_nPQuark->Draw("same");
	// hist_nPGluon->Draw("same");
	// lege_imp->Draw("same");

}

// void Beautify(TH1F inhist)
// {

// }