/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to perform cuts on generated events and cluster particles with FastJet3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// Pythia
#include "Pythia8/Pythia.h"
#include "Pythia8/Basics.h"
// Fastjet
#include "fjcore.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
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
#include "TLorentzVector.h"
// Header
using namespace Pythia8;
using namespace std;
using namespace fastjet;
using namespace fjcore;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file, Read TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile *input = new TFile("gen_TES500.root", "READ");
	// Read TTree
	TTree *itree = (TTree*)input->Get("tree_raw");

	// Define file
	TFile *output = new TFile("cut_TES500.root", "RECREATE");
	// Define tree
	TTree *otree = new TTree("tree_cut", "Cut Pythia data");

	// Intialise vecs
	vector<int> *eveNum=nullptr, *eveSiz=nullptr, *parNum=nullptr, *parPdg=nullptr, *parFCH=nullptr;
	vector<float> *sigmaT=nullptr, *parMas=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr;

	// Set branches
	itree->SetBranchAddress("sigmaT", &sigmaT);				// Total sigma
	itree->SetBranchAddress("eveNum", &eveNum);				// Event number
	itree->SetBranchAddress("eveSiz", &eveSiz);				// Event size
	itree->SetBranchAddress("parNum", &parNum);				// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);				// Parts pdg id
	itree->SetBranchAddress("parMas", &parMas);				// Parts mass
	itree->SetBranchAddress("parPmx", &parPmx);				// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);				// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);				// Parts mom-z
	itree->SetBranchAddress("parFCH", &parFCH);				// FCH flag

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1D *hist_nCh = new TH1D("hist_nCh", "Charged Hadron Multiplicity distribution", 50, 0, 100);
	otree->Branch("hist_nCh", &hist_nCh, "hist_nCh");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Counters
	int nCh = 0;

	// Run through events
	for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {

		// Access
		itree->GetEntry(iEvent);

		// Reset
		nCh = 0;

		// Run through particles
		for(int jParts = 0; jParts < eveSiz->size(); jParts++) {
			
			// FCH flag
			if((*parFCH)[jParts] == 1) {

				nCh++;

			}
		}

		// Populate histogram
		hist_nCh->Fill( nCh );

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Write file
	output->Write();
	output->Close();
	input->Close();
	delete output;
	delete input;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Terminate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}