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

// Code
void ImpactofExp()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Importing raw TEXT data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_Thr1999 = new TH1F("hist_Thr1999", "Inverse Thrust (wo top)", 500, 0, 0.4);
	// Beautify
	hist_Thr1999->SetStats(kFALSE);
	hist_Thr1999->SetTitle("Inverse Thrust wo Top wo ISR");
	hist_Thr1999->SetName("hist_Thr1999");
	hist_Thr1999->SetLineColor(kBlack);
	hist_Thr1999->SetMarkerColor(kBlack);
	hist_Thr1999->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr1999->GetXaxis()->SetTitle("1-T");
	hist_Thr1999->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_01("EXP_TES_500_THR_wot.txt");
	// Read through TXT
	while ( !infile_01.eof() ) {
		// Set reading order
		infile_01 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr1999->SetBinContent(hist_Thr1999->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr1999->SetBinError(hist_Thr1999->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_01.close();	

	// // Read Histogram
	TH1F *hist_Thr199T = new TH1F("hist_Thr199T", "Inverse Thrust (wi top)", 500, 0, 0.4);
	// Beautify
	hist_Thr199T->SetStats(kFALSE);
	hist_Thr199T->SetTitle("Inverse Thrust wi Top wo ISR");
	hist_Thr199T->SetName("hist_Thr199T");
	hist_Thr199T->SetLineColor(kBlack);
	hist_Thr199T->SetMarkerColor(kBlack);
	hist_Thr199T->SetMarkerStyle(kOpenTriangleUp);
	hist_Thr199T->GetXaxis()->SetTitle("1-T");
	hist_Thr199T->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_02("EXP_TES_500_THR_wit.txt");
	// Read through TXT
	while ( !infile_02.eof() ) {
		// Set reading order
		infile_02 >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_Thr199T->SetBinContent(hist_Thr199T->FindBin(Nch), Prb);
		// Populate error bar
		hist_Thr199T->SetBinError(hist_Thr199T->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_02.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Divide by area under hist
	hist_Thr1999->Scale(1.0/hist_Thr1999->Integral());
	hist_Thr199T->Scale(1.0/hist_Thr199T->Integral());

}