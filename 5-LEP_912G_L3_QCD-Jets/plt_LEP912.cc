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
	TFile* input_thrust = new TFile("HEPData-Table_47.root", "READ");
	// Read TTree
	TTree* tree = (TTree*)input->Get("tree"); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nChExpe = (TH1F*)input->Get("hist_nChExpe");
	// Beautify
	// hist_nChExpe->SetStats(kFALSE);
	hist_nChExpe->SetLineColor(kRed+1);
	hist_nChExpe->SetMarkerColor(kRed+1);
	hist_nChExpe->SetMarkerStyle(20);
	hist_nChExpe->GetXaxis()->SetTitle("Multiplicity");
	hist_nChExpe->GetYaxis()->SetTitle("Probability");
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
	hist_nChPyth->GetYaxis()->SetTitle("Probability");
	hist_nChPyth->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChPyth->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nChJets = (TH1F*)input->Get("hist_nChJets");
	// Beautify
	// hist_nChJets->SetStats(kFALSE);
	hist_nChJets->SetLineColor(kBlack);
	hist_nChJets->SetMarkerColor(kBlack);
	hist_nChJets->SetMarkerStyle(20);
	hist_nChJets->GetXaxis()->SetTitle("Multiplicity");
	hist_nChJets->GetYaxis()->SetTitle("Probability");
	hist_nChJets->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nChJets->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read Histogram
	TH1F *hist_nParton = (TH1F*)input->Get("hist_nParton");
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
	TH1F *hist_nPQuark = (TH1F*)input->Get("hist_nPQuark");
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
	TH1F *hist_nPGluon = (TH1F*)input->Get("hist_nPGluon");
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
	TH1F *hist_Spheric = (TH1F*)input->Get("hist_Spheric");
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
	TH1F *hist_Lineric = (TH1F*)input->Get("hist_Lineric");
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

	// Read Histogram
	TH1F *hist_ThrustE = (TH1F*)input_thrust->Get("Table 47/Hist1D_y1");
	// Beautify
	// hist_nChExpe->SetStats(kFALSE);
	hist_ThrustE->SetName("Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	hist_ThrustE->SetName("hist_ThrustE");
	hist_ThrustE->SetLineColor(kRed+1);
	hist_ThrustE->SetMarkerColor(kRed+1);
	hist_ThrustE->SetMarkerStyle(48);
	hist_ThrustE->SetMarkerSize(1.5);
	hist_ThrustE->GetXaxis()->SetTitle("Event thrust");
	hist_ThrustE->GetYaxis()->SetTitle("Probability");
	hist_ThrustE->GetXaxis()->SetNdivisions(515, kTRUE);
	hist_ThrustE->GetYaxis()->SetNdivisions(515, kTRUE);

	// Read Histogram
	TH1F *hist_ThrustX = (TH1F*)input_thrust->Get("Table 47/Hist1D_y2");
	// Beautify
	// hist_ThrustX->SetStats(kFALSE);
	hist_ThrustX->SetName("Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	hist_ThrustX->SetName("hist_ThrustX");
	hist_ThrustX->SetLineColor(kGreen+2);
	hist_ThrustX->SetMarkerColor(kGreen+2);
	hist_ThrustX->SetMarkerStyle(49);
	hist_ThrustX->SetMarkerSize(1.5);
	hist_ThrustX->GetXaxis()->SetTitle("Event thrust");
	hist_ThrustX->GetYaxis()->SetTitle("Probability");
	hist_ThrustX->GetXaxis()->SetNdivisions(515, kTRUE);
	hist_ThrustX->GetYaxis()->SetNdivisions(515, kTRUE);

	// Read Histogram
	TH1F *hist_ThrustP = (TH1F*)input->Get("hist_ThrustP");
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
	TH1F *hist_Oblatey = (TH1F*)input->Get("hist_Oblatey");
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
	TH1F *hist_sphAxis = (TH1F*)input->Get("hist_sphAxis");
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
	TH1F *hist_linAxis = (TH1F*)input->Get("hist_linAxis");
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
	TH1F *hist_thrAxis = (TH1F*)input->Get("hist_thrAxis");
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
// Normalising all probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under histogram
	hist_nChExpe->Scale(1.0/hist_nChExpe->Integral());
	hist_nChPyth->Scale(1.0/hist_nChPyth->Integral());

	hist_nChJets->Scale(1.0/hist_nChJets->Integral());

	hist_ThrustE->Scale(1.0/hist_ThrustE->Integral());
	hist_ThrustX->Scale(1.0/hist_ThrustX->Integral());
	hist_ThrustP->Scale(1.0/hist_ThrustP->Integral());

	hist_nParton->Scale(1.0/hist_nParton->Integral());
	hist_nPQuark->Scale(1.0/hist_nPQuark->Integral());
	hist_nPGluon->Scale(1.0/hist_nPGluon->Integral());

	// Print check of integrals
	cout << "Integration : " << hist_nChExpe->Integral() << endl;
	cout << "Integration : " << hist_nChPyth->Integral() << endl;

	cout << "Integration : " << hist_nChJets->Integral() << endl;

	cout << "Integration : " << hist_ThrustE->Integral() << endl;
	cout << "Integration : " << hist_ThrustX->Integral() << endl;
	cout << "Integration : " << hist_ThrustP->Integral() << endl;

	cout << "Integration : " << hist_nParton->Integral() << endl;
	cout << "Integration : " << hist_nPQuark->Integral() << endl;
	cout << "Integration : " << hist_nPGluon->Integral() << endl;

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
	// TF1 *fist_nChPyth = new TF1("fist_nChPyth", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	TF1 *fist_nChPyth = new TF1("fist_nChPyth", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // Beautify
	fist_nChPyth->SetLineWidth(3);
	fist_nChPyth->SetLineColor(kBlue);
	fist_nChPyth->SetLineStyle(2);
	// Rename fit params
	fist_nChPyth->SetParNames("Normalise","Shape","Trials");
	// Input fit params
	// fist_nChPyth->SetParameter(0,1.9);					// c - normalisation
	// fist_nChPyth->SetParameter(1,16);					// k - shape
	// fist_nChPyth->SetParameter(2,0.6);					// n - probability
	fist_nChPyth->SetParameter(0,1.88);				// c - normalisation
	fist_nChPyth->SetParameter(1,12.5);				// k - shape
	fist_nChPyth->SetParameter(2,19);				// n - probability
	// Perform fitting
	hist_nChPyth->Fit("fist_nChPyth", "RME");			// R(range) Q(suppress terminal output) 0(fit display)

	// Fitting function
	// TF1 *fist_nChExpe = new TF1("fist_nChExpe", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	TF1 *fist_nChExpe = new TF1("fist_nChExpe", "([0]*(TMath::Gamma(x+[1])*TMath::Power(([2]/[1]),x))/(TMath::Gamma(x+1)*TMath::Gamma([1])*TMath::Power((1+([2]/[1])),x+[1])))", 2, 56);
	// // Beautify
	fist_nChExpe->SetLineWidth(3);
	fist_nChExpe->SetLineColor(kRed);
	fist_nChExpe->SetLineStyle(2);
	// Rename fit params
	fist_nChExpe->SetParNames("Normalise","Shape","Trials");
	// Input fit params
	// fist_nChPyth->SetParameter(0,1.9);					// c - normalisation
	// fist_nChPyth->SetParameter(1,16);					// k - shape
	// fist_nChPyth->SetParameter(2,0.6);					// n - probability
	fist_nChExpe->SetParameter(0,1.88);				// Normalisation parameter
	fist_nChExpe->SetParameter(1,12.5);				// k - shape parameter
	fist_nChExpe->SetParameter(2,19);				// p - probability parameter
	// Perform fitting
	hist_nChExpe->Fit("fist_nChExpe", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_nChExpe, "Experimental data 284100 events", "p");
	legend->AddEntry(fist_nChExpe, "NBD fit for Experimental data", "l");
	legend->AddEntry(hist_nChPyth, "Pythia 8.312 data 284100 events", "p");
	legend->AddEntry(fist_nChPyth, "NBD fit for Pythia data", "l");

	// Draw histogram
	c_nch->cd();
	hist_nChPyth->Draw("PS");
	hist_nChExpe->Draw("same");
	fist_nChExpe->Draw("same");
	fist_nChPyth->Draw("same");
	legend->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Hadronic Jet Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* c_ncj = new TCanvas("c_ncj", "Hadronic jet multiplicity distributions", 800, 600);
	// Beautify
	// c_ncj->SetLogy();
	c_ncj->SetTickx();
	c_ncj->SetTicky();
	c_ncj->SetGridx();
	c_ncj->SetGridy();

	// Draw histogram
	c_ncj->cd();
	hist_nChJets->Draw("PS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Thrust
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* c_nct = new TCanvas("c_nct", "Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 800, 600);
	// Beautify
	c_nct->SetTitle("Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	c_nct->SetLogy();
	c_nct->SetTickx();
	c_nct->SetTicky();
	c_nct->SetGridx();
	c_nct->SetGridy();

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_ThrustE, "LEP L3 data (udsc)", "p");
	legend->AddEntry(hist_ThrustX, "LEP L3 data (b)", "p");
	legend->AddEntry(hist_ThrustP, "Pythia data (udscb)", "p");

	// Draw histogram
	c_nct->cd();
	hist_ThrustP->Draw("PS");
	hist_ThrustX->Draw("sames");
	hist_ThrustE->Draw("sames");
	legend->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Axes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* c_axx = new TCanvas("c_axx", "Event Axes distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 800, 600);
	// Beautify
	c_axx->SetTitle("Event Axes distributions [ LEP E^{+} E^{-} at 91.2 GeV ]");
	c_axx->SetLogy();
	c_axx->SetTickx();
	c_axx->SetTicky();
	c_axx->SetGridx();
	c_axx->SetGridy();

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_thrAxis, "Thrust axis", "p");
	legend->AddEntry(hist_sphAxis, "Sphericity axis", "p");
	legend->AddEntry(hist_linAxis, "Linear Sphericity axis", "p");

	// Draw histogram
	c_axx->cd();
	hist_thrAxis->Draw("PS");
	hist_sphAxis->Draw("sames");
	hist_linAxis->Draw("sames");
	legend->Draw("same");

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

}