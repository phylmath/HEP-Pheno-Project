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

	// Read Histograms
	TH1F *hist_nChExpe = (TH1F*)input->Get("hist_nChExpe");
	TH1F *hist_nChPyth = (TH1F*)input->Get("hist_nChPyth");
	TH1F *hist_nChJets = (TH1F*)input->Get("hist_nChJets");
	TH1F *hist_nParton = (TH1F*)input->Get("hist_nParton");
	TH1F *hist_nPQuark = (TH1F*)input->Get("hist_nPQuark");
	TH1F *hist_nPGluon = (TH1F*)input->Get("hist_nPGluon");
	TH1F *hist_Spheric = (TH1F*)input->Get("hist_Spheric");
	TH1F *hist_Lineric = (TH1F*)input->Get("hist_Lineric");
	TH1F *hist_Thrusty = (TH1F*)input->Get("hist_Thrusty");
	TH1F *hist_Oblatey = (TH1F*)input->Get("hist_Oblatey");
	TH1F *hist_sphAxis = (TH1F*)input->Get("hist_sphAxis");
	TH1F *hist_linAxis = (TH1F*)input->Get("hist_linAxis");
	TH1F *hist_thrAxis = (TH1F*)input->Get("hist_thrAxis");

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

	// Create canvas
	TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);
	// Beautify
	// c_nch->SetLogy();
	c_nch->SetTickx();
	c_nch->SetTicky();
	c_nch->SetGridx();
	c_nch->SetGridy();

	// Fitting function
	TF1 *fist_nChPyth = new TF1("fist_nChPyth", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	// TF1 *fist_nChPyth = new TF1("fist_nChPyth", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // Beautify
	fist_nChPyth->SetLineWidth(3);
	fist_nChPyth->SetLineColor(kBlue);
	fist_nChPyth->SetLineStyle(2);
	// Rename fit params
	fist_nChPyth->SetParNames("Normalise","Shape","Trials");
	// Input fit params
	fist_nChPyth->SetParameter(0,1.6);				// c - normalisation
	fist_nChPyth->SetParameter(1,16.1);					// k - shape
	fist_nChPyth->SetParameter(2,0.522);				// n - probability
	// Perform fitting
	hist_nChPyth->Fit("fist_nChPyth", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

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
	// fist_nChExpe->SetParameter(0,1.2);			// Normalisation parameter
	// fist_nChExpe->SetParameter(1,14);			// k - shape parameter
	// fist_nChExpe->SetParameter(2,14);			// p - probability parameter
	// // Perform fitting
	// hist_nChExpe->Fit("fist_nChExpe", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_nChExpe, "Experimental data 284100 events", "p");
	// legend->AddEntry(fist_nChExpe, "NBD fit for Experimental data", "l");
	legend->AddEntry(hist_nChPyth, "Pythia 8.312 data 284100 events", "p");
	legend->AddEntry(fist_nChPyth, "NBD fit for Pythia data", "l");

	// Draw histogram
	c_nch->cd();
	hist_nChPyth->Draw("PS");
	hist_nChExpe->Draw("same");
	// fist_nChExpe->Draw("same");
	fist_nChPyth->Draw("same");
	legend->Draw("same");

	// Confirm normalisation
	cout << "Integration (Exp) : " << hist_nChExpe->Integral() << endl;
	cout << "Integration (Pen) : " << hist_nChPyth->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Hadronic Jet Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_ncj = new TCanvas("c_ncj", "Hadronic jet multiplicity distributions", 800, 600);
	// // Beautify
	// c_ncj->SetLogy();
	// c_ncj->SetTickx();
	// c_ncj->SetTicky();
	// c_ncj->SetGridx();
	// c_ncj->SetGridy();

	// // Draw histogram
	// hist_jet->Draw("c_ncj");

	// // Confirm normalisation
	// cout << "Integration (Pen) : " << hist_nChExpe->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	// TCanvas* c_imp = new TCanvas("c_imp", "Intermediate Parton Multiplicity distributions", 800, 600);
	// // Beautify
	// c_imp->SetLogy();
	// c_imp->SetTickx();
	// c_imp->SetTicky();
	// c_imp->SetGridx();
	// c_imp->SetGridy();

	// // Add legend
	// TLegend* lege_imp = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lege_imp->AddEntry(hist_ncp, "Intermediate parton multiplicity", "p");
	// lege_imp->AddEntry(hist_ncq, "Intermediate quarks multiplicity", "p");
	// lege_imp->AddEntry(hist_ncg, "Intermediate gluons multiplicity", "p");

	// // Draw histogram
	// hist_ncp->Draw("c_imp");
	// hist_ncq->Draw("sames");
	// hist_ncg->Draw("sames");
	// lege_imp->Draw("same");

	// // Confirm normalisation
	// cout << "Integration (nCp) : " << hist_ncp->Integral() << endl;
	// cout << "Integration (nCq) : " << hist_ncq->Integral() << endl;
	// cout << "Integration (nCg) : " << hist_ncg->Integral() << endl;

}