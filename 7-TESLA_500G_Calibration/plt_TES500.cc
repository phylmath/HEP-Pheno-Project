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
	TFile* input_TES500 = new TFile("out_TES500.root", "READ");
	// Read TTree
	TTree* tree = (TTree*)input_TES500->Get("tree");

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

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

	// Read Histogram
	TH1F *hist_ThrustP = (TH1F*)input_TES500->Get("hist_ThrustP");
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
	// Draw legend
	legend->Draw("same");

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
	// c_nch->cd(1)->SetLogy();
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
	// c_nch->cd(2)->SetLogy();
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

}