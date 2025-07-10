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

// Theoretical model
Double_t theory_thrust(Double_t *x, Double_t *par) {
    Double_t t = x[0];
    Double_t a = par[0];  // alpha_s
    return exp(-5 * t) * (1 + 2 * a * log(1 / (t + 1e-4)));
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

	TH1F *hist_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth");
	hist_wiHadron->SetLineColor(kBlack); hist_wiHadron->SetMarkerColor(kBlack); hist_wiHadron->SetMarkerStyle(kStar); hist_wiHadron->SetLineWidth(1); 
	TH1F *hist_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth");
	hist_woHadron->SetLineColor(kRed+2); hist_woHadron->SetMarkerColor(kRed+2); hist_woHadron->SetMarkerStyle(kStar); hist_woHadron->SetLineWidth(1); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_wiHadron->Scale(1.0/hist_wiHadron->Integral());
	hist_woHadron->Scale(1.0/hist_woHadron->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute hadronisation correction factor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_HadrFact = (TH1F*)hist_woHadron->Clone("hist_HadrFact");
	hist_HadrFact->SetTitle("Hadronisation Correction;1 - T;Correction Factor");
	hist_HadrFact->Divide(hist_wiHadron);
	hist_HadrFact->SetLineColor(kBlue+2); hist_HadrFact->SetMarkerColor(kBlue+2); hist_HadrFact->SetMarkerStyle(21);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extract alphaS from fit to thrust distribution
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TF1 *fitTheory = new TF1("fitTheory", theory_thrust, 0.1, 0.3, 1);
	fitTheory->SetParameter(0, 0.12);
	fitTheory->SetParName(0, "#alpha_{s}");
	hist_woHadron->Fit("fitTheory", "RN");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_wiHadron->SetStats(kFALSE);
	hist_woHadron->SetStats(kFALSE);
	hist_HadrFact->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg->AddEntry(hist_wiHadron, "with hadronisation", "p");
	lg->AddEntry(hist_woHadron, "woth hadronisation", "p");
	lg->SetTextSize(0.03);

	// Create canvas
	TCanvas* cv = new TCanvas("cv", "FCC-ee Studies", 1200, 600);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv->Divide(2,1);
	cv->cd(1)->SetLeftMargin(0.15);
	cv->cd(1)->SetLogy();
	cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	cv->cd(2)->SetLeftMargin(0.15);
	// cv->cd(2)->SetLogy();
	cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
	
	// Draw
	cv->cd(1);
	hist_wiHadron->Draw("P");
	hist_woHadron->Draw("P SAME");
	lg->Draw("SAME");	
	cv->cd(2);
	hist_HadrFact->Draw("P");

	// Set limits
	// hist_wiHadron->GetYaxis()->SetRangeUser(1E-4,1E0);
	// hist_woHadron->GetYaxis()->SetRangeUser(1E-4,1E0);
	hist_HadrFact->GetYaxis()->SetRangeUser(0,2);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv->Modified();

	// Output alpha_s result
	std::cout << "\nExtracted alpha_s = " << fitTheory->GetParameter(0)
	          << " ± " << fitTheory->GetParError(0) << std::endl;

}