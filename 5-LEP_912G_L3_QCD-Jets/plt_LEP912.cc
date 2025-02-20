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
// Header
using namespace std;

// Code
void plt_LEP912()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating file, Reading TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile* input = new TFile("out_LEP912.root", "READ");

	// Read TTree
	TTree* tree = (TTree*)input->Get("tree"); 

	// Read Histogram
	TH1F *hist_nChExpe = (TH1F*)input->Get("hist_nChExpe");
	// Beautify
	// hist_nChExpe->SetStats(kFALSE);
	hist_nChExpe->SetLineColor(kRed+1);
	hist_nChExpe->SetMarkerColor(kRed+1);
	hist_nChExpe->SetMarkerStyle(20);
	hist_nChExpe->GetXaxis()->SetTitle("Multiplicity");
	hist_nChExpe->GetYaxis()->SetTitle("Probability Pn");
	hist_nChExpe->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChExpe->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nChPyth = (TH1F*)input->Get("hist_nChPyth");
	// Beautify
	// hist_nChPyth->SetStats(kFALSE);
	hist_nChPyth->SetLineColor(kBlue+1);
	hist_nChPyth->SetMarkerColor(kBlue+1);
	hist_nChPyth->SetMarkerStyle(20);
	hist_nChPyth->GetXaxis()->SetTitle("Multiplicity");
	hist_nChPyth->GetYaxis()->SetTitle("Probability Pn");
	hist_nChPyth->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChPyth->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nChJets = (TH1F*)input->Get("hist_nChJets");
	// Beautify
	// hist_nChJets->SetStats(kFALSE);
	hist_nChJets->SetLineColor(kBlack);
	hist_nChJets->SetMarkerColor(kBlack);
	hist_nChJets->SetMarkerStyle(20);
	hist_nChJets->SetLineWidth(4);
	hist_nChJets->GetXaxis()->SetTitle("Multiplicity");
	hist_nChJets->GetYaxis()->SetTitle("Probability Pn");
	hist_nChJets->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChJets->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nParton = (TH1F*)input->Get("hist_nParton");
	// Beautify
	hist_nParton->SetStats(kFALSE);
	hist_nParton->SetLineColor(kRed+1);
	hist_nParton->SetMarkerColor(kRed+1);
	hist_nParton->SetMarkerStyle(20);
	hist_nParton->SetLineWidth(4);
	hist_nParton->GetXaxis()->SetTitle("Multiplicity");
	hist_nParton->GetYaxis()->SetTitle("Probability Pn");
	hist_nParton->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nParton->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nPQuark = (TH1F*)input->Get("hist_nPQuark");
	// Beautify
	hist_nPQuark->SetStats(kFALSE);
	hist_nPQuark->SetLineColor(kBlue+1);
	hist_nPQuark->SetMarkerColor(kBlue+1);
	hist_nPQuark->SetMarkerStyle(20);
	hist_nPQuark->SetLineWidth(4);
	hist_nPQuark->GetXaxis()->SetTitle("Multiplicity");
	hist_nPQuark->GetYaxis()->SetTitle("Probability Pn");
	hist_nPQuark->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nPQuark->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_nPGluon = (TH1F*)input->Get("hist_nPGluon");
	// Beautify
	hist_nPGluon->SetStats(kFALSE);
	hist_nPGluon->SetLineColor(kGreen+1);
	hist_nPGluon->SetMarkerColor(kGreen+1);
	hist_nPGluon->SetMarkerStyle(20);
	hist_nPGluon->SetLineWidth(4);
	hist_nPGluon->GetXaxis()->SetTitle("Multiplicity");
	hist_nPGluon->GetYaxis()->SetTitle("Probability Pn");
	hist_nPGluon->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nPGluon->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Spheric = (TH1F*)input->Get("hist_Spheric");
	// Beautify
	hist_Spheric->SetStats(kFALSE);
	hist_Spheric->SetLineColor(kBlack);
	hist_Spheric->SetMarkerColor(kBlack);
	hist_Spheric->SetMarkerStyle(20);
	hist_Spheric->SetLineWidth(4);
	hist_Spheric->GetXaxis()->SetTitle("Sphericity");
	hist_Spheric->GetYaxis()->SetTitle("Probability Pn");
	hist_Spheric->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Spheric->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Lineric = (TH1F*)input->Get("hist_Lineric");
	// Beautify
	hist_Lineric->SetStats(kFALSE);
	hist_Lineric->SetLineColor(kBlack);
	hist_Lineric->SetMarkerColor(kBlack);
	hist_Lineric->SetMarkerStyle(20);
	hist_Lineric->SetLineWidth(4);
	hist_Lineric->GetXaxis()->SetTitle("Linearity");
	hist_Lineric->GetYaxis()->SetTitle("Probability Pn");
	hist_Lineric->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Lineric->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Thrusty = (TH1F*)input->Get("hist_Thrusty");
	// Beautify
	// hist_Thrusty->SetStats(kFALSE);
	hist_Thrusty->SetLineColor(kBlack);
	hist_Thrusty->SetMarkerColor(kBlack);
	hist_Thrusty->SetMarkerStyle(20);
	hist_Thrusty->SetLineWidth(4);
	hist_Thrusty->GetXaxis()->SetTitle("Thrust");
	hist_Thrusty->GetYaxis()->SetTitle("Probability Pn");
	hist_Thrusty->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Thrusty->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_Oblatey = (TH1F*)input->Get("hist_Oblatey");
	// Beautify
	hist_Oblatey->SetStats(kFALSE);
	hist_Oblatey->SetLineColor(kBlack);
	hist_Oblatey->SetMarkerColor(kBlack);
	hist_Oblatey->SetMarkerStyle(20);
	hist_Oblatey->SetLineWidth(4);
	hist_Oblatey->GetXaxis()->SetTitle("Oblateness");
	hist_Oblatey->GetYaxis()->SetTitle("Probability Pn");
	hist_Oblatey->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_Oblatey->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_sphAxis = (TH1F*)input->Get("hist_sphAxis");
	// Beautify
	hist_sphAxis->SetStats(kFALSE);
	hist_sphAxis->SetLineColor(kBlack);
	hist_sphAxis->SetMarkerColor(kBlack);
	hist_sphAxis->SetMarkerStyle(20);
	hist_sphAxis->SetLineWidth(4);
	hist_sphAxis->GetXaxis()->SetTitle("Sphericity axis");
	hist_sphAxis->GetYaxis()->SetTitle("Probability Pn");
	hist_sphAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_sphAxis->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_linAxis = (TH1F*)input->Get("hist_linAxis");
	// Beautify
	hist_linAxis->SetStats(kFALSE);
	hist_linAxis->SetLineColor(kBlack);
	hist_linAxis->SetMarkerColor(kBlack);
	hist_linAxis->SetMarkerStyle(20);
	hist_linAxis->SetLineWidth(4);
	hist_linAxis->GetXaxis()->SetTitle("Linearity axis");
	hist_linAxis->GetYaxis()->SetTitle("Probability Pn");
	hist_linAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_linAxis->GetYaxis()->SetNdivisions(510, kTRUE);

	// Read Histogram
	TH1F *hist_thrAxis = (TH1F*)input->Get("hist_thrAxis");
	// Beautify
	hist_thrAxis->SetStats(kFALSE);
	hist_thrAxis->SetLineColor(kBlack);
	hist_thrAxis->SetMarkerColor(kBlack);
	hist_thrAxis->SetMarkerStyle(20);
	hist_thrAxis->SetLineWidth(4);
	hist_thrAxis->GetXaxis()->SetTitle("Thrust axis");
	hist_thrAxis->GetYaxis()->SetTitle("Probability Pn");
	hist_thrAxis->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_thrAxis->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising all probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// hist_nChExpe->Scale(1.0/hist_nChExpe->Integral());
	// hist_nChPyth->Scale(1.0/hist_nChPyth->Integral());
	// hist_nChJets->Scale(1.0/hist_nChJets->Integral());
	// hist_nParton->Scale(1.0/hist_nParton->Integral());
	// hist_nPQuark->Scale(1.0/hist_nPQuark->Integral());
	// hist_nPGluon->Scale(1.0/hist_nPGluon->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Charged Hadronic Multiplicity (Experimental vs Pythia)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);
	// // Beautify
	// // c_nch->SetLogy();
	// c_nch->SetTickx();
	// c_nch->SetTicky();
	// c_nch->SetGridx();
	// c_nch->SetGridy();

	// // Fitting function
	// // TF1 *fist_nChPyth = new TF1("fist_nChPyth", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	// TF1 *fist_nChPyth = new TF1("fist_nChPyth", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // // Beautify
	// fist_nChPyth->SetLineWidth(3);
	// fist_nChPyth->SetLineColor(kBlue);
	// fist_nChPyth->SetLineStyle(2);
	// // Rename fit params
	// fist_nChPyth->SetParNames("Normalise","Shape","Trials");
	// // Input fit params
	// // fist_nChPyth->SetParameter(0,1.9);					// c - normalisation
	// // fist_nChPyth->SetParameter(1,16);					// k - shape
	// // fist_nChPyth->SetParameter(2,0.6);					// n - probability
	// fist_nChPyth->SetParameter(0,1.88);				// c - normalisation
	// fist_nChPyth->SetParameter(1,12.5);				// k - shape
	// fist_nChPyth->SetParameter(2,19);				// n - probability
	// // Perform fitting
	// hist_nChPyth->Fit("fist_nChPyth", "RME");			// R(range) Q(suppress terminal output) 0(fit display)

	// // Fitting function
	// // TF1 *fist_nChExpe = new TF1("fist_nChExpe", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	// TF1 *fist_nChExpe = new TF1("fist_nChExpe", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // // Beautify
	// fist_nChExpe->SetLineWidth(3);
	// fist_nChExpe->SetLineColor(kRed);
	// fist_nChExpe->SetLineStyle(2);
	// // Rename fit params
	// fist_nChExpe->SetParNames("Normalise","Shape","Trials");
	// // Input fit params
	// // fist_nChPyth->SetParameter(0,1.9);					// c - normalisation
	// // fist_nChPyth->SetParameter(1,16);					// k - shape
	// // fist_nChPyth->SetParameter(2,0.6);					// n - probability
	// fist_nChExpe->SetParameter(0,1.88);				// Normalisation parameter
	// fist_nChExpe->SetParameter(1,12.5);				// k - shape parameter
	// fist_nChExpe->SetParameter(2,19);				// p - probability parameter
	// // Perform fitting
	// hist_nChExpe->Fit("fist_nChExpe", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

	// // Add legend
	// TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	// legend->AddEntry(hist_nChExpe, "Experimental data 284100 events", "p");
	// legend->AddEntry(fist_nChExpe, "NBD fit for Experimental data", "l");
	// legend->AddEntry(hist_nChPyth, "Pythia 8.312 data 284100 events", "p");
	// legend->AddEntry(fist_nChPyth, "NBD fit for Pythia data", "l");

	// // Draw histogram
	// c_nch->cd();
	// hist_nChPyth->Draw("PS");
	// hist_nChExpe->Draw("same");
	// fist_nChExpe->Draw("same");
	// fist_nChPyth->Draw("same");
	// legend->Draw("same");

	// // Confirm normalisation
	// cout << "Integration (Exp) : " << hist_nChExpe->Integral() << endl;
	// cout << "Integration (Pen) : " << hist_nChPyth->Integral() << endl;

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
	// hist_nChJets->Draw("PS");

	// // Confirm normalisation
	// cout << "Integration : " << hist_nChJets->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_nct = new TCanvas("c_nct", "Hadronic jet multiplicity distributions", 800, 600);
	// // Beautify
	// c_nct->SetLogy();
	// c_nct->SetTickx();
	// c_nct->SetTicky();
	// c_nct->SetGridx();
	// c_nct->SetGridy();

	// // Draw histogram
	// c_nct->cd();
	// hist_Thrusty->Draw("PS");

	// // Confirm normalisation
	// cout << "Integration : " << hist_Thrusty->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Intermediate Parton Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* c_imp = new TCanvas("c_imp", "Intermediate Parton Multiplicity distributions", 800, 600);
	// Beautify
	c_imp->SetLogy();
	c_imp->SetTickx();
	c_imp->SetTicky();
	c_imp->SetGridx();
	c_imp->SetGridy();

	// Add legend
	TLegend* lege_imp = new TLegend(0.4, 0.2, 0.85, 0.4);
	lege_imp->AddEntry(hist_nParton, "Intermediate parton multiplicity", "p");
	lege_imp->AddEntry(hist_nPQuark, "Intermediate quarks multiplicity", "p");
	lege_imp->AddEntry(hist_nPGluon, "Intermediate gluons multiplicity", "p");

	// Draw histogram
	hist_nParton->Draw("c_imp");
	hist_nPQuark->Draw("same");
	hist_nPGluon->Draw("same");
	lege_imp->Draw("same");

	// Confirm normalisation
	cout << "Integration (nCp) : " << hist_nParton->Integral() << endl;
	cout << "Integration (nCq) : " << hist_nPQuark->Integral() << endl;
	cout << "Integration (nCg) : " << hist_nPGluon->Integral() << endl;

}