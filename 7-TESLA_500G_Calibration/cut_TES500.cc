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
#include "Pythia8/Event.h"
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
	vector<float> *eveThr=nullptr, *eveTax=nullptr, *sigmaT=nullptr, \
	 *parEto=nullptr, *parEtt=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr;

	// Set branches
	itree->SetBranchAddress("sigmaT", &sigmaT);				// Total sigma
	itree->SetBranchAddress("eveNum", &eveNum);				// Event number
	itree->SetBranchAddress("eveSiz", &eveSiz);				// Event size
	itree->SetBranchAddress("eveThr", &eveThr);				// Event thrust
	itree->SetBranchAddress("eveTax", &eveTax);				// Event thraxis
	itree->SetBranchAddress("parNum", &parNum);				// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);				// Parts pdg id
	itree->SetBranchAddress("parEto", &parEto);				// Parts energy
	itree->SetBranchAddress("parEtt", &parEtt);				// Parts energy
	itree->SetBranchAddress("parPmx", &parPmx);				// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);				// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);				// Parts mom-z
	itree->SetBranchAddress("parFCH", &parFCH);				// FCH flag

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1D *hist_nParton = new TH1D("hist_nParton", "Charged Multiplicity distribution", 50, 1, 101);
	otree->Branch("hist_nParton", &hist_nParton, "hist_nParton");

	TH1D *hist_nHadron = new TH1D("hist_nHadron", "Charged Hadron Multiplicity distribution", 50, 1, 101);
	otree->Branch("hist_nHadron", &hist_nHadron, "hist_nHadron");

	// float xbin[] = {0.00E+00,1.00E-02,2.00E-02,3.00E-02,4.00E-02,5.00E-02,7.00E-02,9.00E-02,1.20E-01,1.50E-01,2.20E-01,3.00E-01,4.00E-01};
	// TH1D *hist_ThrPyth = new TH1D("hist_ThrPyth", "Thrust distribution", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	TH1D *hist_ThrPyth = new TH1D("hist_ThrPyth", "Thrust distribution", 100, 0, 0.4);
	otree->Branch("hist_ThrPyth", &hist_ThrPyth, "hist_ThrPyth");

	TH1D *hist_TaxPyth = new TH1D("hist_TaxPyth", "Thrust axis distribution", 100, -1., 1.);
	otree->Branch("hist_TaxPyth", &hist_TaxPyth, "hist_TaxPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define
	int nCh = 0, nCp = 0, Pdg;
	float Pmx, Pmy, Pmz, Eto, Ett, Thr, Tax;

	// Run through events
	for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {

		// Access
		itree->GetEntry(iEvent);

		// Reset
		nCh=0; nCp=0;

		// Run through particles
		for(int jParts = 0; jParts < eveSiz->size(); jParts++) {
			
			// Read
			Pdg = (*parPdg)[jParts];
			Eto = (*parEto)[jParts];
			Ett = (*parEtt)[jParts];
			Pmx = (*parPmx)[jParts];
			Pmy = (*parPmy)[jParts];
			Pmz = (*parPmz)[jParts];
			
			// Define
			Pythia8::Vec4 Pm4(Pmx, Pmy, Pmz, Eto);

			// Count
			nCp++;

			// FCH flag
			if((*parFCH)[jParts] == 1) nCh++;

		}	
	
		// Read
		Thr = (*eveThr)[iEvent];
		Tax = (*eveTax)[iEvent];

		// Histogram
		hist_ThrPyth->Fill( Thr );
		hist_TaxPyth->Fill( Tax );
		hist_nHadron->Fill( nCh );
		hist_nParton->Fill( nCp );

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





















	// // Run through events
	// for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {

	// 	// Initiate
	// 	event.clear();
	// 	event.init();

	// 	// Access
	// 	itree->GetEntry(iEvent);

	// 	// Reset
	// 	nCh = 0;
	// 	nCp = 0;

	// 	// Run through particles
	// 	for(int jParts = 0; jParts < eveSiz->size(); jParts++) {
			
	// 		// Define
	// 		Pdg = (*parPdg)[jParts];
	// 		Egg = (*parEgg)[jParts];
	// 		Ett = (*parEtt)[jParts];
	// 		Mas = (*parMas)[jParts];
	// 		Pmx = (*parPmx)[jParts];
	// 		Pmy = (*parPmy)[jParts];
	// 		Pmz = (*parPmz)[jParts];
			
	// 		// Add event
	// 		Pythia8::Vec4 Pm4(Pmx, Pmy, Pmz, Egg);
	// 		event.append(Pdg, 1, 0, 0, Pm4, Mas);

	// 		// Check
	// 		cout << jParts \
	// 		<< "\t" << Pdg \
	// 		<< "\t" << Egg \
	// 		<< "\t" << Ett \
	// 		<< "\t" << Mas \
	// 		<< "\t" << Pmx \
	// 		<< "\t" << Pmy \
	// 		<< "\t" << Pmz \
	// 		<< endl;

	// 		cout << jParts \
	// 		<< "\t" << event[jParts].id() \
	// 		<< "\t" << event[jParts].e() \
	// 		<< "\t" << event[jParts].eT() \
	// 		<< "\t" << event[jParts].m() \
	// 		<< "\t" << event[jParts].px() \
	// 		<< "\t" << event[jParts].py() \
	// 		<< "\t" << event[jParts].pz() \
	// 		<< "\t" << event.size() \
	// 		<< endl;

	// 		cout << " " << endl;

	// 		// Count
	// 		nCp++;

	// 		// FCH flag
	// 		if((*parFCH)[jParts] == 1) {

	// 			// Count
	// 			nCh++;

	// 		}
	// 	}	
		
	// 	// Thrust analysis
	// 	thr.analyze(event);

	// 	// if (thr.analyze( pythia.event )) {
	// 	// 	hist_ThrustP->Fill( thr.thrust() );					// Thrust
	// 	// 	hist_thrAxis->Fill( thr.eventAxis(1).pz() );		// Cosθ
	// 	// 	hist_ThMajor->Fill( thr.tMajor() );					// Tmajor  
	// 	// 	hist_ThMinor->Fill( thr.tMinor() );					// Tminor
	// 	// 	hist_Oblatey->Fill( thr.oblateness() );				// Oblateness
	// 	// 	}

	// 	// Check
	// 	cout << " " << endl;
	// 	cout << "Event " << iEvent << " has " << event.size() << " particles before thrust analysis." << endl;
	// 	cout << iEvent << "\tTHRUST\t" << "\t" << thr.analyze(event) << "\t" << thr.thrust() << "\t" << thr.eventAxis(1).pz() << "\t" << thr.tMajor() << endl;
	// 	cout << " " << endl;

	// 	// Populate histogram
	// 	hist_nHadron->Fill( nCh );
	// 	hist_nParton->Fill( nCp );

	// }