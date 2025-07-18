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

// bin widths
vector<double> bins = { 0.005, 0.015, 0.025, 0.035, 0.045, 0.055, 0.065, 0.075, 0.085, 0.095, 0.105, 0.115, 0.125, 0.135, 0.145, 0.155, \
						0.165, 0.175, 0.185, 0.195, 0.205, 0.215, 0.225, 0.235, 0.245, 0.255, 0.265, 0.275, 0.285, 0.295, 0.305, 0.315, \
						0.325, 0.335, 0.345, 0.355, 0.365, 0.375, 0.385, 0.395, 0.405, 0.415, 0.425, 0.435, 0.445 };
// LO params
vector<double> Aval = { 2.58E+01, 1.83E+01, 1.54E+01, 1.35E+01, 1.21E+01, 1.10E+01, 1.00E+01, 9.21E+00, 8.50E+00, 7.87E+00, 7.30E+00, \
						6.79E+00, 6.32E+00, 5.88E+00, 5.48E+00, 5.10E+00, 4.75E+00, 4.41E+00, 4.10E+00, 3.79E+00, 3.50E+00, 3.22E+00, \
						2.95E+00, 2.68E+00, 2.42E+00, 2.16E+00, 1.91E+00, 1.65E+00, 1.38E+00, 1.12E+00, 8.42E-01, 5.57E-01, 2.59E-01, \
						1.71E-02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// NLO params
vector<double> Bval = { -4.96E+02, 2.17E+02, 2.81E+02, 2.92E+02, 2.88E+02, 2.77E+02, 2.64E+02, 2.51E+02, 2.37E+02, 2.24E+02, 2.11E+02, \
						1.99E+02, 1.88E+02, 1.77E+02, 1.67E+02, 1.57E+02, 1.48E+02, 1.39E+02, 1.31E+02, 1.23E+02, 1.15E+02, 1.08E+02, \
						1.01E+02, 9.47E+01, 8.82E+01, 8.21E+01, 7.54E+01, 6.94E+01, 6.30E+01, 5.64E+01, 4.89E+01, 4.14E+01, 3.35E+01, \
						2.11E+01, 8.57E+00, 4.47E+00, 2.43E+00, 1.30E+00, 6.44E-01, 2.82E-01, 5.12E-02, 1.46E-05, 4.66E-05, 0, 0 };
// NNLO params
vector<double> Cval = { -9.00E+03, -3.30E+03, 1.60E+03, 4.00E+03, 4.90E+03, 5.30E+03, 5.50E+03, 5.40E+03, 5.50E+03, 5.20E+03, 5.10E+03, \
						4.80E+03, 4.50E+03, 4.30E+03, 4.10E+03, 3.90E+03, 3.80E+03, 3.50E+03, 3.29E+03, 3.20E+03, 2.98E+03, 2.85E+03, \
						2.63E+03, 2.50E+03, 2.33E+03, 2.35E+03, 2.15E+03, 1.97E+03, 1.80E+03, 1.83E+03, 1.74E+03, 1.57E+03, 1.42E+03, \
						1.03E+03, 2.96E+02, 1.55E+02, 5.30E+01, 3.57E+01, 1.09E+01, 1.80E-01, -1.00E-03, -1.95E-01, -9.00E-03, -1.00E-03, 0 };

// Theory model
double Thrust_Order(double *x, double *par, const vector<double>& A, const vector<double>& B, const vector<double>& C, int order) {
    
	double tau = x[0];
    double alphaS = par[0];
    double asbar = alphaS / (2 * TMath::Pi());

    for (size_t i = 0; i < bins.size(); ++i) {
        if (fabs(tau - bins[i]) < 0.005) {
            double val = 0;
            if (order == 1) val += asbar * A[i];
            if (order == 2) val += asbar * A[i] + asbar * asbar * B[i];
            if (order == 3) val += asbar * A[i] + asbar * asbar * B[i] + asbar * asbar * asbar * C[i];
            return val;
        }
    }
    return 0;
}

// Wrapper LO
double Thrust_LOOO(double *x, double *par) {
    return par[1] * Thrust_Order(x, par, Aval, Bval, Cval, 1);
}

// Wrapper NLO
double Thrust_NLOO(double *x, double *par) {
    return par[1] * Thrust_Order(x, par, Aval, Bval, Cval, 2);
}

// Wrapper NNLO
double Thrust_NNLO(double *x, double *par) {
    return par[1] * Thrust_Order(x, par, Aval, Bval, Cval, 3);
}

// Code
void ImpactofAlpha()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912_wiHadron = new TFile("cut_FCC912_wiHadron.root", "READ");
	TFile *input_912_woHadron = new TFile("cut_FCC912_woHadron.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth_Zq");
	hist_wiHadron->SetLineColor(kBlack); hist_wiHadron->SetMarkerColor(kBlack); hist_wiHadron->SetMarkerStyle(kStar); hist_wiHadron->SetLineWidth(1); 
	TH1F *hist_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_Zq");
	hist_woHadron->SetLineColor(kBlack); hist_woHadron->SetMarkerColor(kBlack); hist_woHadron->SetMarkerStyle(kStar); hist_woHadron->SetLineWidth(1); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading theory curves
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define
	TH1F *hist_LOOO = new TH1F("hist_LOOO", "Inverse Thrust", 45, 0.0, 0.45);
	hist_LOOO->SetLineColor(kGreen+2); hist_LOOO->SetMarkerColor(kGreen+2); hist_LOOO->SetMarkerStyle(kCircle); hist_LOOO->SetLineWidth(1);
	TH1F *hist_NLOO = new TH1F("hist_NLOO", "Inverse Thrust", 45, 0.0, 0.45);
	hist_NLOO->SetLineColor(kBlue+2); hist_NLOO->SetMarkerColor(kBlue+2); hist_NLOO->SetMarkerStyle(kCircle); hist_NLOO->SetLineWidth(1);
	TH1F *hist_NNLO = new TH1F("hist_NNLO", "Inverse Thrust", 45, 0.0, 0.45);
	hist_NNLO->SetLineColor(kRed+2); hist_NNLO->SetMarkerColor(kRed+2); hist_NNLO->SetMarkerStyle(kCircle); hist_NNLO->SetLineWidth(1);
	
	// Import
	ifstream infile_01("THEORY_912_THRUST.txt");
	
	// Buffers
	double T, A, B, C, LOOO, NLOO, NNLO;
	double alps=0.1183/(2*TMath::Pi());
	
	// Read
	while ( !infile_01.eof() ) {
		
		// Order
		infile_01 >> T >> A >> B >> C;
		
		// Check
		if (infile_01.fail()) break;
		
		// Compute 
		LOOO = alps * A;
		NLOO = alps * A + alps*alps * B;
		NNLO = alps * A + alps*alps * B + alps*alps*alps * C;

		// Populate
		int bin = hist_LOOO->FindBin(T);
		hist_LOOO->SetBinContent(bin, LOOO); hist_LOOO->SetBinError(bin, 0.0);
		hist_NLOO->SetBinContent(bin, NLOO); hist_NLOO->SetBinError(bin, 0.0);
		hist_NNLO->SetBinContent(bin, NNLO); hist_NNLO->SetBinError(bin, 0.0);

	}
	// Close
	infile_01.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading experimental curves
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Thr, Prb, Err_Thr, Err_Prb;

	// // Read Histogram
	TH1F *hist_ThrExpAL = new TH1F("hist_ThrExpAL", "Inverse Thrust", 45, 0.0, 0.45);
	// Beautify
	hist_ThrExpAL->SetLineColor(kYellow+2); hist_ThrExpAL->SetMarkerColor(kYellow+2); hist_ThrExpAL->SetMarkerStyle(kOpenTriangleUp);
	hist_ThrExpAL->SetTitle("Inverse Thrust");
	hist_ThrExpAL->SetName("hist_ThrExpAL");
	hist_ThrExpAL->GetXaxis()->SetTitle("1-T");
	hist_ThrExpAL->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_03("EXP_LEP_912_ALEPH_THR.txt");
	// Read through TXT
	while ( !infile_03.eof() ) {
		// Set reading order
		infile_03 >> Thr >> Prb >> Err_Thr >> Err_Prb;
		// Populate histogram
		hist_ThrExpAL->SetBinContent(hist_ThrExpAL->FindBin(Thr), Prb);
		// Populate error bar
		hist_ThrExpAL->SetBinError(hist_ThrExpAL->FindBin(Thr), Err_Prb);
	}
	// Close file
	infile_03.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute hadronisation correction factor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_HadrFact = (TH1F*)hist_woHadron->Clone("hist_HadrFact");
	hist_HadrFact->SetTitle("Hadronisation Correction;1 - T;Correction Factor");
	hist_HadrFact->Divide(hist_wiHadron);
	hist_HadrFact->SetLineColor(kBlue+2); hist_HadrFact->SetMarkerColor(kBlue+2); hist_HadrFact->SetMarkerStyle(kStar);
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extract alphaS from fit to thrust distribution
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_woHadron->Scale(1.0/hist_woHadron->Integral("width"));
	
	for (int i = 1; i <= hist_ThrExpAL->GetNbinsX(); ++i) {
		double val = hist_ThrExpAL->GetBinContent(i);
		double err = hist_ThrExpAL->GetBinError(i);  // keep original error
		double corr = hist_HadrFact->GetBinContent(i);

		hist_ThrExpAL->SetBinContent(i, val * corr);
		hist_ThrExpAL->SetBinError(i, err);  // or set to 0 if you want no error
	}

	TF1 *fitLOOO = new TF1("fitLOOO", Thrust_LOOO, 0.1, 0.3, 2);
	TF1 *fitNLOO = new TF1("fitNLOO", Thrust_NLOO, 0.1, 0.3, 2);
	TF1 *fitNNLO = new TF1("fitNNLO", Thrust_NNLO, 0.1, 0.3, 2);

	fitLOOO->SetParName(0, "alpha_{s}"); fitLOOO->SetParName(1, "Norm");
	fitNLOO->SetParName(0, "alpha_{s}"); fitNLOO->SetParName(1, "Norm");
	fitNNLO->SetParName(0, "alpha_{s}"); fitNNLO->SetParName(1, "Norm");

	fitLOOO->SetParameter(0, 0.112); 
	// fitLOOO->SetParameter(1, 60E3);
	fitLOOO->SetParLimits(0, 0.02, 0.20);
	// fitLOOO->SetParLimits(1, 0, 60E3);

	// fitNLOO->SetParameter(0, 0.1183); 
	// fitNLOO->SetParameter(1, 3.95971);
	// fitNLOO->SetParLimits(0, 0.02, 0.20);
	// fitNLOO->SetParLimits(1, 50E3, 60E3);

	// fitNNLO->SetParameter(0, 0.1183); 
	// fitNNLO->SetParameter(1, 3.95971);
	// fitNNLO->SetParLimits(0, 0.02, 0.20);
	// fitNNLO->SetParLimits(1, 50E3, 60E3);

	hist_ThrExpAL->Fit(fitLOOO, "RN");
	// hist_ThrExpAL->Fit(fitNLOO, "RN");
	// hist_woHadron->Fit(fitNNLO, "RN");

	TCanvas* c_fit = new TCanvas("c_fit", "Fits of Thrust Distribution", 800, 600);
	c_fit->cd(); c_fit->SetLogy();
	c_fit->SetLeftMargin(0.15);
	c_fit->SetTickx(); c_fit->SetTicky();
	c_fit->SetGridx(); c_fit->SetGridy();

	TLegend* leg = new TLegend(0.64, 0.65, 0.87, 0.87);
	leg->AddEntry(hist_woHadron, "PYTHIA 8.312", "P");
	leg->AddEntry(hist_ThrExpAL, "ALEPH (corrected)", "P");
	leg->AddEntry(fitLOOO, "Theory-LO fitting", "L");
	// leg->AddEntry(fitNLOO, "Fit Theory-NLO", "L");
	// leg->AddEntry(fitNNLO, "Fit Theory-NNLO", "L");
	leg->SetTextSize(0.03);	

	fitLOOO->SetLineColor(kGreen+2);
	fitNLOO->SetLineColor(kBlue+2);
	fitNNLO->SetLineColor(kRed+2);

	hist_woHadron->Draw("PL");
	hist_ThrExpAL->Draw("PL SAME");
	fitLOOO->Draw("SAME");
	// fitNLOO->Draw("SAME");
	// fitNNLO->Draw("SAME");
	leg->Draw();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_wiHadron->SetStats(kFALSE);
	hist_woHadron->SetStats(kFALSE);
	hist_ThrExpAL->SetStats(kFALSE);
	hist_HadrFact->SetStats(kFALSE);
	hist_LOOO->SetStats(kFALSE);
	hist_NLOO->SetStats(kFALSE);
	hist_NNLO->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising with area under hist
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// cout << hist_LOOO->Integral() << endl;
	// cout << hist_NLOO->Integral() << endl;
	// cout << hist_NNLO->Integral() << endl;

	// hist_wiHadron->Scale(1.0/hist_wiHadron->Integral());
	// hist_woHadron->Scale(1.0/hist_woHadron->Integral());
	// hist_ThrExpAL->Scale(1.0/hist_ThrExpAL->Integral());
	// hist_LOOO->Scale(1.0/hist_LOOO->Integral());
	// hist_NLOO->Scale(1.0/hist_NLOO->Integral());
	// hist_NNLO->Scale(1.0/hist_NNLO->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Add legend
	// TLegend *lg1 = new TLegend(0.64, 0.65, 0.87, 0.87);
	// lg1->AddEntry(hist_wiHadron, "with hadronisation", "p");
	// lg1->AddEntry(hist_woHadron, "woth hadronisation", "p");
	// lg1->SetTextSize(0.03);

	// // Add legend
	// TLegend *lg2 = new TLegend(0.64, 0.65, 0.87, 0.87);
	// // lg2->AddEntry(hist_LOOO, "Theory-LO", "p");
	// // lg2->AddEntry(hist_NLOO, "Theory-NLO", "p");
	// lg2->AddEntry(hist_NNLO, "Theory-NNLO", "p");
	// lg2->AddEntry(hist_ThrExpAL, "Exp-ALEPH", "p");
	// lg2->AddEntry(hist_woHadron, "PYTHIA 8.312", "p");
	// lg2->SetTextSize(0.03);

	// // Create canvas
	// TCanvas* cv = new TCanvas("cv", "FCC-ee Studies", 1000, 800);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// cv->Divide(2,2);
	// cv->cd(1)->SetLeftMargin(0.15);
	// cv->cd(1)->SetLogy();
	// cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	// cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	// cv->cd(2)->SetLeftMargin(0.15);
	// cv->cd(2)->SetLogy();
	// cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	// cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
	// cv->cd(3)->SetLeftMargin(0.15);
	// cv->cd(3)->SetTickx(); cv->cd(3)->SetTicky();
	// cv->cd(3)->SetGridx(); cv->cd(3)->SetGridy();
	
	// // Draw
	// cv->cd(1);
	// hist_woHadron->Draw("P");
	// hist_wiHadron->Draw("P SAME");
	// lg1->Draw("SAME");	
	// cv->cd(2);
	// hist_woHadron->Draw("P");
	// // hist_LOOO->Draw("P SAME");
	// // hist_NLOO->Draw("P SAME");
	// hist_NNLO->Draw("P SAME");
	// hist_ThrExpAL->Draw("P SAME");
	// lg2->Draw("SAME");
	// cv->cd(3);
	// hist_HadrFact->Draw("P");

	// // Set limits
	// // hist_wiHadron->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_woHadron->GetYaxis()->SetRangeUser(1E-6,1E0);
	// hist_HadrFact->GetYaxis()->SetRangeUser(0,2);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv->Modified();

	// // Output alpha_s result
	// std::cout << "\nExtracted alpha_s (LO)   = " << fitLOOO->GetParameter(0) 
	// 		<< " ± " << fitLOOO->GetParError(0) << std::endl;
	// std::cout << "Extracted alpha_s (NLO)  = " << fitNLOO->GetParameter(0) 
	// 		<< " ± " << fitNLOO->GetParError(0) << std::endl;
	// std::cout << "Extracted alpha_s (NNLO) = " << fitNNLO->GetParameter(0) 
	// 		<< " ± " << fitNNLO->GetParError(0) << std::endl;

}