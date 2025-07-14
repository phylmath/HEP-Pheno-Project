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
double Thrust_LOOO(double *x, double *y) {
    
	// Vars
	double tau = x[0];
    double alp = y[0]/(2*TMath::Pi());
    
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
	double alps=0.118/(2*TMath::Pi());
	
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
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_wiHadron->Scale(1.0/hist_wiHadron->Integral());
	hist_woHadron->Scale(1.0/hist_woHadron->Integral());
	hist_LOOO->Scale(1.0/hist_LOOO->Integral());
	hist_NLOO->Scale(1.0/hist_NLOO->Integral());
	hist_NNLO->Scale(1.0/hist_NNLO->Integral());

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
	hist_LOOO->SetStats(kFALSE);
	hist_NLOO->SetStats(kFALSE);
	hist_NNLO->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg1 = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg1->AddEntry(hist_wiHadron, "with hadronisation", "p");
	lg1->AddEntry(hist_woHadron, "woth hadronisation", "p");
	lg1->SetTextSize(0.03);

	// Add legend
	TLegend *lg2 = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg2->AddEntry(hist_LOOO, "LO", "p");
	lg2->AddEntry(hist_NLOO, "NLO", "p");
	lg2->AddEntry(hist_NNLO, "NNLO", "p");
	lg2->SetTextSize(0.03);

	// Create canvas
	TCanvas* cv = new TCanvas("cv", "FCC-ee Studies", 1000, 800);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv->Divide(2,2);
	cv->cd(1)->SetLeftMargin(0.15);
	cv->cd(1)->SetLogy();
	cv->cd(1)->SetTickx(); cv->cd(1)->SetTicky();
	cv->cd(1)->SetGridx(); cv->cd(1)->SetGridy();
	cv->cd(2)->SetLeftMargin(0.15);
	cv->cd(2)->SetLogy();
	cv->cd(2)->SetTickx(); cv->cd(2)->SetTicky();
	cv->cd(2)->SetGridx(); cv->cd(2)->SetGridy();
	cv->cd(3)->SetLeftMargin(0.15);
	cv->cd(3)->SetTickx(); cv->cd(3)->SetTicky();
	cv->cd(3)->SetGridx(); cv->cd(3)->SetGridy();
	
	// Draw
	cv->cd(1);
	hist_wiHadron->Draw("P");
	hist_woHadron->Draw("P SAME");
	lg1->Draw("SAME");	
	cv->cd(2);
	hist_LOOO->Draw("P");
	hist_NLOO->Draw("P SAME");
	hist_NNLO->Draw("P SAME");
	hist_woHadron->Draw("P SAME");
	lg2->Draw("SAME");
	cv->cd(3);
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