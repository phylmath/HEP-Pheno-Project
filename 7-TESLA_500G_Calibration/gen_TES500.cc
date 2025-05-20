/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia
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
using namespace fjcore;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create output Tfile
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("gen_TES50t_noR.root", "RECREATE");
	
	// Define tree
	TTree *tree = new TTree("tree_raw", "Raw Pythia data");

	// Intialise vecs
	vector<int> eveNum, eveSiz, eveCod, parNum, parPdg;
	vector<float> eveSph, eveSax, eveThr, eveTax, eveSpr, sigmaT, parEto, parEtt, parPmx, parPmy, parPmz;

	// Define branches
	tree->Branch("sigmaT", "vector<float>", &sigmaT);										// Total sigma
	tree->Branch("eveNum", "vector<int>", &eveNum);											// Event number
	tree->Branch("eveSiz", "vector<int>", &eveSiz);											// Event size
	tree->Branch("eveCod", "vector<int>", &eveCod);											// Event process
	tree->Branch("eveSpr", "vector<float>", &eveSpr);										// Event √s'
	tree->Branch("eveSph", "vector<float>", &eveSph);										// Event spheric
	tree->Branch("eveSax", "vector<float>", &eveSax);										// Event sphaxis
	tree->Branch("eveThr", "vector<float>", &eveThr);										// Event thrust
	tree->Branch("eveTax", "vector<float>", &eveTax);										// Event thraxis
	tree->Branch("parNum", "vector<int>", &parNum);											// Parts number
	tree->Branch("parPdg", "vector<int>", &parPdg);											// Parts pdg id
	tree->Branch("parEto", "vector<float>", &parEto);										// Parts energy
	tree->Branch("parEtt", "vector<float>", &parEtt);										// Parts energy
	tree->Branch("parPmx", "vector<float>", &parPmx);										// Parts mom-x
	tree->Branch("parPmy", "vector<float>", &parPmy);										// Parts mom-y
	tree->Branch("parPmz", "vector<float>", &parPmz);										// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 5e5;

	// Store masses
	float mZ = pythia.particleData.m0(23);													// Z0 mass
	float mW = pythia.particleData.m0(24);													// W+ mass

///////////////////////////////PHYSICS SWITCHES FOR TESLA 500 GeV ///////////////////////////////////////////
	
	// Define Beam params
	pythia.readString("Beams:idA = 11"); 													// beam energy
	pythia.readString("Beams:idB = -11"); 													// beam energy
	pythia.settings.parm("Beams:eCM", 500);													// c-om energy
	pythia.readString("PDF:lepton = off");													// ISR toggle
	
	// EW boson processes
	pythia.readString("WeakZ0:gmZmode = 0");												// allow γ* or Z channels
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");									// (221) ee'->γ*/Z
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");									// (231) ee'->(γ*/Z)(γ*/Z)
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");										// (233) ee'->WW
	
	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");										// (604) ee'->tt'

	// Constrain decays
	pythia.readString("23:onMode = off");													// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5 6");											// turn on Z iff duscbt
	pythia.readString("24:onMode = off");													// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6 15 16");									// turn on W iff duscbt
	
	// Suppress terminal text
	pythia.readString("Print:quiet = on");													// print nothing
	pythia.readString("Next:numberCount = 1000");											// print #events updates
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Analyses
	Thrust thr; Sphericity sph; Event event_fch;
	float sigISR=0.0, sigmaE=0.0;
	int nCh=0, nISR=0, nC_ZZ=0, nC_WW=0;
	
	// Run through events
	for (int iEvent=0; iEvent<nEvent; iEvent++ ) {

		// Anti-crash
		if (!pythia.next()) continue;

		// Counter
		nCh=0; sigISR=0.0; sigmaE=0.0;

		// Reset event vectors
		event_fch.init(); event_fch.clear(); eveNum.clear(); sigmaT.clear();
		eveSpr.clear(); eveThr.clear(); eveTax.clear(); eveSiz.clear();
		eveCod.clear(); eveSph.clear(); eveSax.clear();
		// Reset part vectors
		parNum.clear(); parPdg.clear(); parEto.clear(); 
		parEtt.clear(); parPmx.clear(); parPmy.clear(); parPmz.clear();

		// Run through particles
		for (int jParts=0; jParts<pythia.event.size(); jParts++) {

			// Sum final energies
			if (pythia.event[jParts].isFinal()) sigmaE+=pythia.event[jParts].e();

			// Store particle info
			if (pythia.event[jParts].isFinal() && pythia.event[jParts].isCharged()) {
		
				nCh++;																		// Count FC particles
				eveNum.push_back(iEvent);													// Add event number
				parNum.push_back(jParts);													// Add particle number
				parPdg.push_back(pythia.event[jParts].id());								// Add particle pdg id
				parEto.push_back(pythia.event[jParts].e());									// Add particle energy
				parEtt.push_back(pythia.event[jParts].eT());								// Add particle energy
				parPmx.push_back(pythia.event[jParts].px());								// Add particle mom-x
				parPmy.push_back(pythia.event[jParts].py());								// Add particle mom-y
				parPmz.push_back(pythia.event[jParts].pz());								// Add particle mom-z
				event_fch.append(pythia.event[jParts]);										// Update event vector

			}

			// Search ISR photon
			if (pythia.event[jParts].isFinal() && pythia.event[jParts].id()==22) {
				
				// Store origins
				int idmom1 = pythia.event[jParts].mother1();
				int idmom2 = pythia.event[jParts].mother2();

				// ISR found
				if ( (abs(pythia.event[idmom1].id())==11 || abs(pythia.event[idmom2].id())==11) )
					if ( pythia.event[jParts].e()>0.001 ) if (pythia.event[jParts].e() > sigISR)
						sigISR=pythia.event[jParts].e();
				
			}

		}
		
		// Compute √s'
		sigISR = 500.0*sqrt(1.0-(2.0*sigISR)/500.0);

		// Store event info
		if (nCh!=0) {
			eveCod.push_back(pythia.info.code());											// Add proc code
			sigmaT.push_back(pythia.info.sigmaGen());										// Add event sigma
			eveSiz.push_back(nCh);															// Add event size
			eveSpr.push_back(sigISR);														// Add ISR energy
		}

		// Store thrust data
		if (nCh!=0) if (thr.analyze(event_fch)) {
			eveThr.push_back(1.0-thr.thrust());												// Add event thrust
			eveTax.push_back(thr.eventAxis(1).pz());										// Add event thrθ
		}

		// Store spheric data
		if (nCh!=0) if (sph.analyze(event_fch)) {
			eveSph.push_back(sph.sphericity());												// Add event spheric
			eveSax.push_back(sph.eventAxis(1).pz());										// Add event sphθ
		}

		// Populate
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-sections
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pythia.stat();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	output->Write();
	output->Close();
	delete output;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Terminate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

// // Search ISR photon
// if (pythia.event[jParts].isFinal() && pythia.event[jParts].id()==22 && pythia.event[jParts].e()>5) {
	
// 	// Run through particles to compare
// 	for(int isrcount=0; isrcount<pythia.event.size(); isrcount++) {

// 		// Check energy of compared particle
// 		if (pythia.event[isrcount].isFinal() && pythia.event[isrcount].e()>0.250) {

// 			// Neglect itself
// 			if ( isrcount==jParts ) continue;

// 			// Compute ΔR
// 			float deltaEta = pythia.event[isrcount].eta()-pythia.event[jParts].eta();
// 			float deltaPhi = pythia.event[isrcount].phi()-pythia.event[jParts].phi();
// 			float deltaR = sqrt( deltaEta*deltaEta + deltaPhi*deltaPhi ) * 180/M_PI;
			
// 			// cout << pythia.event[jParts].e() << "\t" << pythia.event[isrcount].e() << "\t" << deltaR << endl;
			
// 			// Check isolated
// 			if ( deltaR<15.0 ) {
// 				isrcheck = false;
// 				break;
// 			}
			
// 		}
// 	}

// 	// ISR photon found!
// 	if (isrcheck==true) {
// 		// cout << "ISR photon found at: " << jParts << endl;
// 		sigISR+=pythia.event[jParts].e();
// 	}

// }