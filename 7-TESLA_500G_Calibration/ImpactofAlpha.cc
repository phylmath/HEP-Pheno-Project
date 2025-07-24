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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// bin widths
vector<double> bins = { 0.005, 0.015, 0.025, 0.035, 0.045, 0.055, 0.065, 0.075, 0.085, 0.095, 0.105, 0.115, 0.125, 0.135, 0.145, 0.155, \
						0.165, 0.175, 0.185, 0.195, 0.205, 0.215, 0.225, 0.235, 0.245, 0.255, 0.265, 0.275, 0.285, 0.295, 0.305, 0.315, \
						0.325, 0.335, 0.345, 0.355, 0.365, 0.375, 0.385, 0.395, 0.405, 0.415, 0.425, 0.435, 0.445 };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Theoretical model for Thrust
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LO parameters A_T
vector<double> A_THR = {
  2.58e+01, 1.83e+01, 1.54e+01, 1.35e+01, 1.21e+01, 1.10e+01, 1.00e+01, 9.21e+00, 8.50e+00, 7.87e+00,
  7.30e+00, 6.79e+00, 6.32e+00, 5.88e+00, 5.48e+00, 5.10e+00, 4.75e+00, 4.41e+00, 4.10e+00, 3.79e+00,
  3.50e+00, 3.22e+00, 2.95e+00, 2.68e+00, 2.42e+00, 2.16e+00, 1.91e+00, 1.65e+00, 1.38e+00, 1.12e+00,
  8.42e-01, 5.57e-01, 2.59e-01, 1.71e-02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// NLO parameters B_T
vector<double> B_THR = {
 -4.96e+02, 2.17e+02, 2.81e+02, 2.92e+02, 2.88e+02, 2.77e+02, 2.64e+02, 2.51e+02, 2.37e+02, 2.24e+02,
  2.11e+02, 1.99e+02, 1.88e+02, 1.77e+02, 1.67e+02, 1.57e+02, 1.48e+02, 1.39e+02, 1.31e+02, 1.23e+02,
  1.15e+02, 1.08e+02, 1.01e+02, 9.47e+01, 8.82e+01, 8.21e+01, 7.54e+01, 6.94e+01, 6.30e+01, 5.64e+01,
  4.89e+01, 4.14e+01, 3.35e+01, 2.11e+01, 8.57e+00, 4.47e+00, 2.43e+00, 1.30e+00, 6.44e-01, 2.82e-01,
  5.12e-02, 1.46e-05, 4.66e-05, 0
};

// NNLO parameters C_T
vector<double> C_THR = {
 -9.00e+03, -3.30e+03, 1.60e+03, 4.00e+03, 4.90e+03, 5.30e+03, 5.50e+03, 5.40e+03, 5.50e+03, 5.20e+03,
  5.10e+03, 4.80e+03, 4.50e+03, 4.30e+03, 4.10e+03, 3.90e+03, 3.80e+03, 3.50e+03, 3.29e+03, 3.20e+03,
  2.98e+03, 2.85e+03, 2.63e+03, 2.50e+03, 2.33e+03, 2.35e+03, 2.15e+03, 1.97e+03, 1.80e+03, 1.83e+03,
  1.74e+03, 1.57e+03, 1.42e+03, 1.03e+03, 2.96e+02, 1.55e+02, 5.30e+01, 3.57e+01, 1.09e+01, 1.80e-01,
 -1.00e-03, -1.95e-01, -9.00e-03, -1.00e-03
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Theory model
double THR_Order(double *x, double *par, const vector<double>& A, const vector<double>& B, const vector<double>& C, int order) {
    
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Wrapper LO
double THR_LOOO(double *x, double *par) {
    return par[1] * THR_Order(x, par, A_THR, B_THR, C_THR, 1);
}

// Wrapper NLO
double THR_NLOO(double *x, double *par) {
    return par[1] * THR_Order(x, par, A_THR, B_THR, C_THR, 2);
}

// Wrapper NNLO
double THR_NNLO(double *x, double *par) {
    return par[1] * THR_Order(x, par, A_THR, B_THR, C_THR, 3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Theoretical model for CPR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LO params A_C
vector<double> A_CPR = {
	3.5327e+01, 2.7963e+01, 2.5124e+01, 2.2369e+01, 2.1887e+01, 2.0774e+01, 1.9831e+01, 1.9042e+01, 1.8340e+01, 1.7710e+01,
	1.7152e+01, 1.6637e+01, 1.6145e+01, 1.5713e+01, 1.5312e+01, 1.4933e+01, 1.4572e+01, 1.4228e+01, 1.3915e+01, 1.3609e+01,
	1.3321e+01, 1.3039e+01, 1.2779e+01, 1.2524e+01, 1.2281e+01, 1.2046e+01, 1.1823e+01, 1.1608e+01, 1.1392e+01, 1.1197e+01,
	1.1002e+01, 1.0810e+01, 1.0627e+01, 1.0451e+01, 1.0273e+01, 1.0101e+01, 9.9461e+00, 9.7874e+00, 9.6281e+00, 9.4488e+00,
	9.3321e+00, 9.1940e+00, 9.0491e+00, 8.9004e+00, 8.7791e+00, 8.6545e+00, 8.5181e+00, 8.3521e+00, 8.1526e+00, 8.1526e+00
};
// NLO params B_C
vector<double> B_CPR = {
 -2.1510e+03, -4.7510e+02, -1.4510e+02, -1.3010e+02, -1.0910e+02, 1.7110e+02, 2.1500e+02, 2.4400e+02, 2.6700e+02, 2.8300e+02,
  2.9610e+02, 3.0610e+02, 3.0600e+02, 3.1810e+02, 3.2000e+02, 3.2300e+02, 3.2400e+02, 3.2600e+02, 3.2420e+02, 3.2270e+02,
  3.2190e+02, 3.2140e+02, 3.2080e+02, 3.1840e+02, 3.1760e+02, 3.1600e+02, 3.1390e+02, 3.0790e+02, 3.0780e+02, 3.0290e+02,
  2.9900e+02, 2.9080e+02, 2.9640e+02, 2.9410e+02, 2.8970e+02, 2.8960e+02, 2.8430e+02, 2.8100e+02, 2.7520e+02, 2.7300e+02,
  2.7110e+02, 2.6850e+02, 2.6360e+02, 2.6160e+02, 2.5800e+02, 2.5550e+02, 2.5180e+02, 2.4910e+02, 2.4650e+02, 2.4650e+02
};
// NNLO params C_C
vector<double> C_CPR = {
  3.0640e+04, -3.0400e+04, -2.1500e+04, -1.4800e+04, -1.1200e+04, -7.6000e+03, -5.7000e+03, -2.7500e+03, -1.0600e+03, -7.5000e+02,
  1.4000e+03, 1.6500e+03, 3.0000e+03, 3.1000e+03, 3.9000e+03, 4.1000e+03, 4.3000e+03, 4.8000e+03, 5.4000e+03, 5.9000e+03,
  5.8000e+03, 5.5000e+03, 5.9000e+03, 6.2000e+03, 6.7000e+03, 6.4000e+03, 6.6000e+03, 6.6000e+03, 6.9000e+03, 6.8000e+03,
  5.8000e+03, 5.8000e+03, 5.6000e+03, 5.8000e+03, 5.6000e+03, 5.4000e+03, 5.0000e+03, 4.8000e+03, 4.6000e+03, 4.3000e+03,
  4.2000e+03, 4.1000e+03, 4.0000e+03, 3.9000e+03, 3.9000e+03, 3.8000e+03, 3.6000e+03, 3.5000e+03, 3.4000e+03, 3.4000e+03
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Theory model
double CPR_Order(double *x, double *par, const vector<double>& A, const vector<double>& B, const vector<double>& C, int order) {
    
	double tau = x[0]; double alphaS = par[0]; double asbar = alphaS / (2 * TMath::Pi());

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Wrapper LO
double CPR_LOOO(double *x, double *par) {
    return par[1] * CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 1);
}

// Wrapper NLO
double CPR_NLOO(double *x, double *par) {
    return par[1] * CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 2);
}

// Wrapper NNLO
double CPR_NNLO(double *x, double *par) {
    return par[1] * CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Code
void ImpactofAlpha()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912_wiHadron = new TFile("cut_FCC912_wiHadron.root", "READ");
	TFile *input_912_woHadron = new TFile("cut_FCC912_woHadron.root", "READ");
	TFile *input_912 = new TFile("cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth_Zq");
	hist_wiHadron->SetLineColor(kBlack); hist_wiHadron->SetMarkerColor(kBlack); hist_wiHadron->SetMarkerStyle(26); hist_wiHadron->SetLineWidth(2); hist_wiHadron->SetMarkerSize(2);
	TH1F *hist_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_Zq");
	hist_woHadron->SetLineColor(kBlack); hist_woHadron->SetMarkerColor(kBlack); hist_woHadron->SetMarkerStyle(26); hist_woHadron->SetLineWidth(2); hist_woHadron->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute hadronisation correction factor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrCorr_912 = (TH1F*)hist_woHadron->Clone("hist_ThrCorr_912");
	hist_ThrCorr_912->SetTitle("Hadronisation Correction;1 - T;Correction Factor");
	hist_ThrCorr_912->Divide(hist_wiHadron);
	hist_ThrCorr_912->SetLineColor(kBlue+2); hist_ThrCorr_912->SetMarkerColor(kBlue+2); hist_ThrCorr_912->SetMarkerStyle(kStar);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_ThrPyth_912 = (TH1F*)input_912->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_912->SetLineColor(kBlack); hist_ThrPyth_912->SetMarkerColor(kBlack); hist_ThrPyth_912->SetMarkerStyle(26); hist_ThrPyth_912->SetLineWidth(2); hist_ThrPyth_912->SetMarkerSize(2);
	TH1F *hist_ThrPyth_160 = (TH1F*)input_160->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_160->SetLineColor(kBlack); hist_ThrPyth_160->SetMarkerColor(kBlack); hist_ThrPyth_160->SetMarkerStyle(26); hist_ThrPyth_160->SetLineWidth(2); hist_ThrPyth_160->SetMarkerSize(2);
	TH1F *hist_ThrPyth_240 = (TH1F*)input_240->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_240->SetLineColor(kBlack); hist_ThrPyth_240->SetMarkerColor(kBlack); hist_ThrPyth_240->SetMarkerStyle(26); hist_ThrPyth_240->SetLineWidth(2); hist_ThrPyth_240->SetMarkerSize(2);
	TH1F *hist_ThrPyth_365 = (TH1F*)input_365->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_365->SetLineColor(kBlack); hist_ThrPyth_365->SetMarkerColor(kBlack); hist_ThrPyth_365->SetMarkerStyle(26); hist_ThrPyth_365->SetLineWidth(2); hist_ThrPyth_365->SetMarkerSize(2);

	TH1F *hist_CprPyth_912 = (TH1F*)input_912->Get("hist_CprPyth");
	hist_CprPyth_912->SetLineColor(kBlack); hist_CprPyth_912->SetMarkerColor(kBlack); hist_CprPyth_912->SetMarkerStyle(26); hist_CprPyth_912->SetLineWidth(2); hist_CprPyth_912->SetMarkerSize(2);
	TH1F *hist_CprPyth_160 = (TH1F*)input_160->Get("hist_CprPyth");
	hist_CprPyth_160->SetLineColor(kBlack); hist_CprPyth_160->SetMarkerColor(kBlack); hist_CprPyth_160->SetMarkerStyle(26); hist_CprPyth_160->SetLineWidth(2); hist_CprPyth_160->SetMarkerSize(2);
	TH1F *hist_CprPyth_240 = (TH1F*)input_240->Get("hist_CprPyth");
	hist_CprPyth_240->SetLineColor(kBlack); hist_CprPyth_240->SetMarkerColor(kBlack); hist_CprPyth_240->SetMarkerStyle(26); hist_CprPyth_240->SetLineWidth(2); hist_CprPyth_240->SetMarkerSize(2);
	TH1F *hist_CprPyth_365 = (TH1F*)input_365->Get("hist_CprPyth");
	hist_CprPyth_365->SetLineColor(kBlack); hist_CprPyth_365->SetMarkerColor(kBlack); hist_CprPyth_365->SetMarkerStyle(26); hist_CprPyth_365->SetLineWidth(2); hist_CprPyth_365->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_woHadron->Scale(1.0/hist_woHadron->Integral("width"));

	hist_ThrPyth_912->Scale(1.0/hist_ThrPyth_912->Integral("width"));
	hist_CprPyth_912->Scale(1.0/hist_CprPyth_912->Integral("width"));

	hist_ThrPyth_160->Scale(1.0/hist_ThrPyth_160->Integral("width"));
	hist_CprPyth_160->Scale(1.0/hist_CprPyth_160->Integral("width"));

	hist_ThrPyth_240->Scale(1.0/hist_ThrPyth_240->Integral("width"));
	hist_CprPyth_240->Scale(1.0/hist_CprPyth_240->Integral("width"));

	hist_ThrPyth_365->Scale(1.0/hist_ThrPyth_365->Integral("width"));
	hist_CprPyth_365->Scale(1.0/hist_CprPyth_365->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_woHadron->SetStats(kFALSE);
	hist_wiHadron->SetStats(kFALSE);

	hist_ThrPyth_912->SetStats(kFALSE);
	hist_ThrPyth_160->SetStats(kFALSE);
	hist_ThrPyth_240->SetStats(kFALSE);
	hist_ThrPyth_365->SetStats(kFALSE);

	hist_CprPyth_912->SetStats(kFALSE);
	hist_CprPyth_160->SetStats(kFALSE);
	hist_CprPyth_240->SetStats(kFALSE);
	hist_CprPyth_365->SetStats(kFALSE);
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit PYTHIA to Theory
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "****************************************" << endl;
	cout << "Fitting (1-T) at 91.2 GeV at LO" << endl;

	TF1 *hist_fitThLO_912 = new TF1("hist_fitThLO_912", THR_LOOO, 0.1, 0.3, 2);
	hist_fitThLO_912->SetParName(0, "alpha_{s}"); hist_fitThLO_912->SetParName(1, "Norm"); 
	hist_fitThLO_912->SetLineColor(kGreen+1); hist_fitThLO_912->SetMarkerColor(kGreen+1); hist_fitThLO_912->SetMarkerStyle(53); hist_fitThLO_912->SetLineWidth(2); hist_fitThLO_912->SetMarkerSize(1);

	hist_fitThLO_912->SetParameter(0, 0.112); 
	// hist_fitThLO_912->SetParameter(1, 60E3);
	hist_fitThLO_912->SetParLimits(0, 0.02, 0.20);
	// hist_fitThLO_912->SetParLimits(1, 0, 60E3);

	hist_ThrPyth_912->Fit(hist_fitThLO_912, "RN");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "****************************************" << endl;
	cout << "Fitting (1-T) at 91.2 GeV at NLO" << endl;

	TF1 *hist_fitThNL_912 = new TF1("hist_fitThNL_912", THR_NLOO, 0.1, 0.3, 2);
	hist_fitThNL_912->SetParName(0, "alpha_{s}"); hist_fitThNL_912->SetParName(1, "Norm"); 
	hist_fitThNL_912->SetLineColor(kRed+1); hist_fitThNL_912->SetMarkerColor(kRed+1); hist_fitThNL_912->SetMarkerStyle(53); hist_fitThNL_912->SetLineWidth(2); hist_fitThNL_912->SetMarkerSize(1);

	hist_fitThNL_912->SetParameter(0, 0.112); 
	// hist_fitThNL_912->SetParameter(1, 60E3);
	hist_fitThNL_912->SetParLimits(0, 0.02, 0.20);
	// hist_fitThNL_912->SetParLimits(1, 0, 60E3);

	hist_ThrPyth_912->Fit(hist_fitThNL_912, "RN");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "****************************************" << endl;
	cout << "Fitting (1-T) at 91.2 GeV at NNLO" << endl;

	TF1 *hist_fitThNN_912 = new TF1("hist_fitThNN_912", THR_NNLO, 0.1, 0.3, 2);
	hist_fitThNN_912->SetParName(0, "alpha_{s}"); hist_fitThNN_912->SetParName(1, "Norm"); 
	hist_fitThNN_912->SetLineColor(kBlue+1); hist_fitThNN_912->SetMarkerColor(kBlue+1); hist_fitThNN_912->SetMarkerStyle(53); hist_fitThNN_912->SetLineWidth(2); hist_fitThNN_912->SetMarkerSize(1);

	hist_fitThNN_912->SetParameter(0, 0.112); 
	// hist_fitThNN_912->SetParameter(1, 60E3);
	hist_fitThNN_912->SetParLimits(0, 0.02, 0.20);
	// hist_fitThNN_912->SetParLimits(1, 0, 60E3);

	hist_ThrPyth_912->Fit(hist_fitThNN_912, "RN");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "****************************************" << endl;
	cout << "Fitting (Cpar) at 91.2 GeV at LO" << endl;

	TF1 *hist_fitCpLO_912 = new TF1("hist_fitCpLO_912", CPR_LOOO, 0.1, 0.3, 2);
	hist_fitCpLO_912->SetParName(0, "alpha_{s}"); hist_fitCpLO_912->SetParName(1, "Norm"); 
	hist_fitCpLO_912->SetLineColor(kGreen+1); hist_fitCpLO_912->SetMarkerColor(kGreen+1); hist_fitCpLO_912->SetMarkerStyle(53); hist_fitCpLO_912->SetLineWidth(2); hist_fitCpLO_912->SetMarkerSize(1);

	hist_fitCpLO_912->SetParameter(0, 0.112); 
	// hist_fitCpLO_912->SetParameter(1, 60E3);
	hist_fitCpLO_912->SetParLimits(0, 0.02, 0.20);
	// hist_fitCpLO_912->SetParLimits(1, 0, 60E3);

	hist_ThrPyth_912->Fit(hist_fitCpLO_912, "RN");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_912->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_912->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_912->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_160->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_160->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_160->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_160->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_240->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_240->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_240->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_240->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_365->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_365->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_365->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_365->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_912->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_912->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_912->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_912->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_160->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_160->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_160->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_160->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_240->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_240->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_240->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_240->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_365->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_365->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_365->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_365->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_912->SetTitle("");
	hist_ThrPyth_160->SetTitle("");
	hist_ThrPyth_240->SetTitle("");
	hist_ThrPyth_365->SetTitle("");

	hist_CprPyth_912->SetTitle("");
	hist_CprPyth_160->SetTitle("");
	hist_CprPyth_240->SetTitle("");
	hist_CprPyth_365->SetTitle("");

	// Create canvas
	TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1400, 1000);

	TLegend* lg = new TLegend(0.65, 0.88, 0.92, 0.95);
	lg->AddEntry(hist_ThrPyth_912, "PYTHIA 8.312", "L");
	lg->AddEntry(hist_fitThLO_912, "#it{O}(#alpha_{s}^{1}) theory fit", "L");
	lg->AddEntry(hist_fitThNL_912, "#it{O}(#alpha_{s}^{2}) theory fit", "L");
	lg->SetTextSize(0.03);	

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv1->SetMargin(0, 0, 0, 0); 
	cv1->Divide(2,1);
	for (int i = 1; i <= 2; i++) {
		cv1->cd(i);
		gPad->SetTopMargin(0.015);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		// gPad->SetGridx(); gPad->SetGridy();
		gPad->SetLogy();
	}

	// Draw
	cv1->cd(1);

	hist_ThrPyth_912->Draw("HIST");
	hist_fitThLO_912->Draw("L SAME");
	hist_fitThNL_912->Draw("L SAME");
	hist_fitThNN_912->Draw("L SAME");

	hist_ThrPyth_160->Scale(1E3);
	hist_ThrPyth_160->Draw("HIST SAME");
	
	hist_ThrPyth_240->Scale(1E6);
	hist_ThrPyth_240->Draw("HIST SAME");

	hist_ThrPyth_365->Scale(1E9);
	hist_ThrPyth_365->Draw("HIST SAME");

	lg->Draw("SAME");	

	cv1->cd(2);

	hist_CprPyth_912->Draw("HIST");
	hist_fitCpLO_912->Draw("L SAME");

	hist_CprPyth_160->Scale(1E3);
	hist_CprPyth_160->Draw("HIST SAME");
	
	hist_CprPyth_240->Scale(1E6);
	hist_CprPyth_240->Draw("HIST SAME");

	hist_CprPyth_365->Scale(1E9);
	hist_CprPyth_365->Draw("HIST SAME");

	lg->Draw("SAME");

	// Set limits
	hist_ThrPyth_912->GetYaxis()->SetRangeUser(1E-4,1E12);
	hist_ThrPyth_912->GetXaxis()->SetRangeUser(0,0.38);
	hist_CprPyth_912->GetYaxis()->SetRangeUser(1E-4,1E12);
	hist_CprPyth_912->GetXaxis()->SetRangeUser(0,0.38);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

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
	// lg2->AddEntry(hist_ThrExAL_912, "Exp-ALEPH", "p");
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
	// hist_ThrExAL_912->Draw("P SAME");
	// lg2->Draw("SAME");
	// cv->cd(3);
	// hist_ThrCorr_912->Draw("P");

	// // Set limits
	// // hist_wiHadron->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_woHadron->GetYaxis()->SetRangeUser(1E-6,1E0);
	// hist_ThrCorr_912->GetYaxis()->SetRangeUser(0,2);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv->Modified();

	// // Output alpha_s result
	// std::cout << "\nExtracted alpha_s (LO)   = " << hist_fitThLO_912->GetParameter(0) 
	// 		<< " ± " << hist_fitThLO_912->GetParError(0) << std::endl;
	// std::cout << "Extracted alpha_s (NLO)  = " << fitNLOO->GetParameter(0) 
	// 		<< " ± " << fitNLOO->GetParError(0) << std::endl;
	// std::cout << "Extracted alpha_s (NNLO) = " << fitNNLO->GetParameter(0) 
	// 		<< " ± " << fitNNLO->GetParError(0) << std::endl;

}