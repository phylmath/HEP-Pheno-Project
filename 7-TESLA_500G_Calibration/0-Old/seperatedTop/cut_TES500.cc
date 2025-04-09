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
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file, Read TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile *input = new TFile("gen_TES500_woT.root", "READ");
	// Read TTree
	TTree *itree = (TTree*)input->Get("tree_raw");

	// Define file
	TFile *output = new TFile("cut_TES500_woT.root", "RECREATE");
	// Define tree
	TTree *otree = new TTree("tree_cut", "Cut Pythia data");

	// Intialise vecs
	vector<int> *eveNum=nullptr, *eveSiz=nullptr, *parNum=nullptr, *parPdg=nullptr;
	vector<float> *eveThT=nullptr, *eveTxT=nullptr, *eveTht=nullptr, *eveTxt=nullptr, *sigmaT=nullptr, \
	*parEto=nullptr, *parEtt=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr;

	// X-axis for thrust
	float xbin[] = {0.0E+00,1.0E-02,2.0E-02,3.0E-02,4.0E-02,5.0E-02,7.0E-02,9.0E-02,1.2E-01,1.5E-01,2.2E-01,3.0E-01,4.0E-01};

	// Set branches
	itree->SetBranchAddress("sigmaT", &sigmaT);											// Total sigma
	itree->SetBranchAddress("eveNum", &eveNum);											// Event number
	itree->SetBranchAddress("eveSiz", &eveSiz);											// Event size
	itree->SetBranchAddress("eveThT", &eveThT);											// Event thrust
	itree->SetBranchAddress("eveTxT", &eveTxT);											// Event thraxis
	itree->SetBranchAddress("eveTht", &eveTht);											// Event thrust
	itree->SetBranchAddress("eveTxt", &eveTxt);											// Event thraxis
	itree->SetBranchAddress("parNum", &parNum);											// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);											// Parts pdg id
	itree->SetBranchAddress("parEto", &parEto);											// Parts energy
	itree->SetBranchAddress("parEtt", &parEtt);											// Parts energy
	itree->SetBranchAddress("parPmx", &parPmx);											// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);											// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);											// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nHadron = new TH1F("hist_nHadron", "Charged Hadron Multiplicity", 50, 1, 101);
	hist_nHadron->GetXaxis()->SetTitle("N_{CH}>");
	hist_nHadron->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron", &hist_nHadron, "hist_nHadron");

	TH1F *hist_nJetTot = new TH1F("hist_nJetTot", "Jet Multiplicity", 10, 0, 11);
	hist_nJetTot->GetXaxis()->SetTitle("N_{JETS}>");
	hist_nJetTot->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot", &hist_nJetTot, "hist_nJetTot");

	TH1F *hist_ThPywiT = new TH1F("hist_ThPywiT", "Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThPywiT->GetXaxis()->SetTitle("(1-T)");
	hist_ThPywiT->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThPywiT", &hist_ThPywiT, "hist_ThPywiT");

	TH1F *hist_ThPywoT = new TH1F("hist_ThPywoT", "Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThPywoT->GetXaxis()->SetTitle("(1-T)");
	hist_ThPywoT->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThPywoT", &hist_ThPywoT, "hist_ThPywoT");

	TH1F *hist_TxPywiT = new TH1F("hist_TxPywiT", "Thrust axis", 100, -1., 1.);
	hist_TxPywiT->GetXaxis()->SetTitle("(1-T)>");
	hist_TxPywiT->GetYaxis()->SetTitle("cosΘ_{Thrust}");
	otree->Branch("hist_TxPywiT", &hist_TxPywiT, "hist_TxPywiT");

	TH1F *hist_TxPywoT = new TH1F("hist_TxPywoT", "Thrust axis", 100, -1., 1.);
	hist_TxPywoT->GetXaxis()->SetTitle("(1-T)>");
	hist_TxPywoT->GetYaxis()->SetTitle("cosΘ_{Thrust}");
	otree->Branch("hist_TxPywoT", &hist_TxPywoT, "hist_TxPywoT");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define
	int nCh=0, nCj=0, nParts=0, Pdg;
	float Pmx, Pmy, Pmz, Eto, Ett, Thr, Tax;
	
	Pythia8::Thrust thr;
	Pythia8::Event event;

	// FastJet params
	double R = 0.6, ptmin = 5.0;
	vector<fastjet::PseudoJet> particles;
	
	// Run through events
	for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {

		// Access
		itree->GetEntry(iEvent);

		// Reset
		event.init(); event.clear();

		// Run through particles
		for(int jParts = 0; jParts < (*eveSiz)[0]; jParts++) {
			
			////////////////////////// READING PARTS DATA ///////////////////////////////////////////////////
			Pdg = (*parPdg)[jParts]; Eto = (*parEto)[jParts]; Ett = (*parEtt)[jParts];
			Pmx = (*parPmx)[jParts]; Pmy = (*parPmy)[jParts]; Pmz = (*parPmz)[jParts];
			/////////////////////////////////////////////////////////////////////////////////////////////////
			
			Pythia8::Vec4 Pm4(Pmx, Pmy, Pmz, Eto);
 			event.append(Pdg, 1, 0, 0, Pm4);

			////////////////////////// STORING JETS PARAMS //////////////////////////////////////////////////
			
			fastjet::PseudoJet particle(Pmx,Pmy,Pmz,Eto);								// Particle vector
			particle.set_user_index(Pdg);												// Set particle id
			particles.push_back(particle);												// Add to particles
			/////////////////////////////////////////////////////////////////////////////////////////////////
			
			////////////////////////// COMPUTING NCH CURVE //////////////////////////////////////////////////
			nCh++;																		// Charged hadrons
			/////////////////////////////////////////////////////////////////////////////////////////////////

		}
		
		////////////////////////// CLUSTERING JET PARTICLES /////////////////////////////////////////////////
		fastjet::JetDefinition jet_def(antikt_algorithm, R);							// Jet definition
		fastjet::ClusterSequence cs(particles, jet_def);								// Run clustering
		vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store jets
		nCj = jets.size();																// Jet multiplicity
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////// PRINTING CLUSTERED INFO //////////////////////////////////////////////////

		cout << "Event " << iEvent << " has " << particles.size() << " particles" << " / " << jets.size() << " jets" << endl;

		// Run through jets
		for (int iJet = 0; iJet < jets.size(); iJet++) {
			
			vector<fastjet::PseudoJet> constituents = jets[iJet].constituents();		// Jet constituents		
			// cout << "Jet#" << iJet << " has " << constituents.size() << endl;			// Print info

			// Run through constituents
			for (int jJet = 0; jJet < constituents.size(); jJet++) {
				
				fastjet::PseudoJet constituent = jets[iJet].constituents()[jJet];		// Jet constituent
				// cout << jJet << "\t" << constituents[jJet].user_index() << endl;		// Print info

			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////////////////////////

		Thr = (*eveThT)[0];
		Tax = (*eveTxT)[0];
		hist_TxPywiT->Fill( Thr );
		hist_ThPywiT->Fill( Tax );
		Thr = (*eveTht)[0];
		Tax = (*eveTxt)[0];
		hist_TxPywoT->Fill( Thr );
		hist_ThPywoT->Fill( Tax );

		// thr.analyze(event);
		// hist_ThrPyth->Fill( 1.0-thr.thrust() );
		// hist_TaxPyth->Fill( thr.eventAxis(1).pz() );

		// cout << Thr << " " << 1.0-thr.thrust() << endl;

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////// POPULATING HISTOS WITH DATA //////////////////////////////////////////////
		hist_nHadron->Fill( nCh );
		hist_nJetTot->Fill( nCj );

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////// CLEARING VALUES OF TEMP VARS /////////////////////////////////////////////
		nCh=0; particles.clear(); jets.clear();
		/////////////////////////////////////////////////////////////////////////////////////////////////////

	}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// KNO params
	double histNch=0.0, histMax=0.0, histMin=0.0, histBin=0.0; int numBin=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nHadron->GetMean();
	histMax = hist_nHadron->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nHadron->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nHadron->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nHadron = new TH1D("KNOO_nHadron", "KNO Charged Hadron Multiplicity", numBin, 0, histMax);
	// Beautify
	KNOO_nHadron->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nHadron->GetYaxis()->SetTitle("P(N_{CH}) x <N_{CH}>");
	// Fill histogram
	for (int bin = 1; bin <= hist_nHadron->GetNbinsX(); ++bin) {
	double nCh = hist_nHadron->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nHadron->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nHadron->GetBinContent(bin) * histNch;
	double scaledError = hist_nHadron->GetBinError(bin) * histNch;
	KNOO_nHadron->Fill(scaledNch, scaledContent);
	KNOO_nHadron->SetBinError(KNOO_nHadron->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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