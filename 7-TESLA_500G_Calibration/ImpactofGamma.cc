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
void ImpactofGamma()
{

	TFile* input_365 = new TFile("cut_FCC365.root", "READ");
	TGraph *ISRvsEsprime = (TGraph*)input_365->Get("ISRvsEsprime");
	TCanvas* c_thr = new TCanvas("c_thr", "Impact of ISR on Effective COM", 1200, 480);
	ISRvsEsprime->Draw("P");

}