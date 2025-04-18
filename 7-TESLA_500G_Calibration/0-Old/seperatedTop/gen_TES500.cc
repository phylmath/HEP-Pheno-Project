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
  	TFile *output = new TFile("gen_TES500.root", "RECREATE");
	
	// Define tree
	TTree *tree = new TTree("tree_raw", "Raw Pythia data");

	// Intialise vecs
	vector<int> eveNum, eveSiz, parNum, parPdg;
	vector<float> eveThT, eveTxT, eveTht, eveTxt, sigmaT, parEto, parEtt, parPmx, parPmy, parPmz;

	// Define branches
	tree->Branch("sigmaT", "vector<float>", &sigmaT);					// Total sigma
	tree->Branch("eveNum", "vector<int>", &eveNum);						// Event number
	tree->Branch("eveSiz", "vector<int>", &eveSiz);						// Event size
	tree->Branch("eveThT", "vector<float>", &eveThT);					// Event thrust
	tree->Branch("eveTxT", "vector<float>", &eveTxT);					// Event thraxis
	tree->Branch("eveTht", "vector<float>", &eveTht);					// Event thrust
	tree->Branch("eveTxt", "vector<float>", &eveTxt);					// Event thraxis
	tree->Branch("parNum", "vector<int>", &parNum);						// Parts number
	tree->Branch("parPdg", "vector<int>", &parPdg);						// Parts pdg id
	tree->Branch("parEto", "vector<float>", &parEto);					// Parts energy
	tree->Branch("parEtt", "vector<float>", &parEtt);					// Parts energy
	tree->Branch("parPmx", "vector<float>", &parPmx);					// Parts mom-x
	tree->Branch("parPmy", "vector<float>", &parPmy);					// Parts mom-y
	tree->Branch("parPmz", "vector<float>", &parPmz);					// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 1e3;

	// Store masses
	float mZ = pythia.particleData.m0(23);								// Z0 mass
	float mW = pythia.particleData.m0(24);								// W+ mass

///////////////////////////////PHYSICS SWITCHES FOR TESLA 500 GeV ///////////////////////////////////////////
	
	// QCD processes
	pythia.readString("HardQCD:all = off");								// master switch
	// EW boson processes
	pythia.readString("WeakZ0:gmZmode = 0");							// allow γ* or Z channels
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");				// ee'->γ*/Z
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");				// ee'->γ*γ*ZZ
	pythia.readString("WeakDoubleBoson:ffbar2ZW = off");				// ee'->ZW
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");					// ee'->WW
	// EW boson decays
	pythia.readString("23:onMode = off");								// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5 6");						// turn on Z iff (duscbt)
	pythia.readString("24:onMode = off");								// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6 15");					// turn on W iff (duscbt and τν)
	// EW photon-parton processes
	pythia.readString("PhotonParton:ggm2qqbar = off");					// gγ->qq' (uds)
	pythia.readString("PhotonParton:ggm2ccbar = off");					// gγ->cc'
	pythia.readString("PhotonParton:ggm2bbbar = off");					// gγ->bb'
	pythia.readString("PhotonParton:qgm2qg = off");						// gγ->qq'
	pythia.readString("PhotonParton:qgm2qgm = off");					// gγ->qq'
	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");					// ee'->tt'
	// Photon processes
	pythia.readString("PhotonCollision:all = off");
	pythia.readString("PhotonCollision:gmgm2qqbar = off");				// γγ->qq'
	pythia.readString("PhotonCollision:gmgm2ccbar = off");				// γγ->cc'
	pythia.readString("PhotonCollision:gmgm2bbbar = off");				// γγ->bb'
	pythia.readString("PhotonCollision:gmgm2ee = off");					// γγ->ee'
	pythia.readString("PhotonCollision:gmgm2mumu = off");				// γγ->μμ'
	pythia.readString("PhotonCollision:gmgm2tautau = off");				// γγ->ττ'
	// ISR processes
	pythia.readString("TimeShower:QEDshowerByL = on");					// ee->γee
	pythia.readString("TimeShower:QEDshowerByQ = off");					// qq->γqq
	pythia.readString("SpaceShower:QEDshowerByL = on");					// ee->γee
	pythia.readString("SpaceShower:QEDshowerByQ = off");				// qq->γqq
	// Define Beam params
	pythia.readString("Beams:idA = 11"); 								// beam energy
	pythia.readString("Beams:idB = -11"); 								// beam energy
	pythia.settings.parm("Beams:eCM", 500);								// c-om energy
	pythia.readString("PDF:lepton = off");								// disable substructure

	// Suppress terminal text
	pythia.readString("Next:numberCount = 1000");						//
	pythia.readString("Next:numberShowProcess = 0");					//
	pythia.readString("Next:numberShowInfo = 0");						//
	pythia.readString("Next:numberShowEvent = 0");						//
	pythia.readString("Init:showMultipartonInteractions = off");		//
	pythia.readString("Init:showChangedSettings = off");				//
	pythia.readString("Init:showChangedParticleData = off");			//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////PHYSICS SWITCHES FOR LEP 91.2 GeV ////////////////////////////////////////////

	// pythia.readString("HardQCD:all = off"); 							// master switch
	// pythia.readString("WeakSingleBoson:ffbar2gmZ = on");				// ee'->γ*/Z
	// pythia.readString("23:onMode = off");								// turn off Z production
	// pythia.readString("23:onIfAny = 1 2 3 4 5");						// turn on Z iff (duscb)

	// // Define Beam params
	// pythia.readString("Beams:idA = 11"); 								// beam energy
	// pythia.readString("Beams:idB = -11"); 								// beam energyy
	// pythia.settings.parm("Beams:eCM", mZ);								// c-om energy
	// pythia.readString("PDF:lepton = off");								// disable substructure

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Analyses
	Thrust thr_withTop;
	Thrust thr_wothTop;
	Event event_fch_withTop;
	Event event_fch_wothTop;
	
	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;

		// Initialise
		event_fch_withTop.init(); event_fch_wothTop.init();

		// Reset
		int nCh = 0;
		event_fch_withTop.clear(); event_fch_wothTop.clear();
		eveNum.clear(); parNum.clear(); parPdg.clear(); parEto.clear(); 
		parEtt.clear(); parPmx.clear(); parPmy.clear(); parPmz.clear();
		eveThT.clear(); eveTxT.clear(); eveTht.clear(); eveTxt.clear();
		eveSiz.clear(); sigmaT.clear();

		// Run through particles
		for(int jParts = 0; jParts < pythia.event.size(); jParts++) {

			//Store
			if(pythia.event[jParts].isFinal() && pythia.event[jParts].isCharged() && pythia.event[jParts].isHadron()) {
		
				nCh++;																		// Count FC particles
				eveNum.push_back(iEvent);													// Add event number
				parNum.push_back(jParts);													// Add particle number
				parPdg.push_back(pythia.event[jParts].id());								// Add particle pdg id
				parEto.push_back(pythia.event[jParts].e());									// Add particle energy
				parEtt.push_back(pythia.event[jParts].eT());								// Add particle energy
				parPmx.push_back(pythia.event[jParts].px());								// Add particle mom-x
				parPmy.push_back(pythia.event[jParts].py());								// Add particle mom-y
				parPmz.push_back(pythia.event[jParts].pz());								// Add particle mom-z
													

				// Update event vectors
				if (pythia.event[jParts].id() == 6)
					event_fch_withTop.append(pythia.event[jParts]);
				if (pythia.event[jParts].id() != 6) {
					event_fch_wothTop.append(pythia.event[jParts]);
					event_fch_withTop.append(pythia.event[jParts]);
				}
					

			}
		}

		cout << event_fch_withTop.size() << "\t" << event_fch_wothTop.size() << endl;

		// Compute
		if (nCh != 0) {

			sigmaT.push_back(pythia.info.sigmaGen());										// Add event sigma
			eveSiz.push_back(nCh);															// Add event size

			if (thr_withTop.analyze( event_fch_withTop )) {
				eveThT.push_back(1.0-thr_withTop.thrust());									// Add event thrust
				eveTxT.push_back(thr_withTop.eventAxis(1).pz());							// Add event Cosθ
			}

			if (thr_wothTop.analyze( event_fch_wothTop )) {
				eveTht.push_back(1.0-thr_wothTop.thrust());									// Add event thrust
				eveTxt.push_back(thr_wothTop.eventAxis(1).pz());							// Add event Cosθ
			}

		}

		// Populate
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check cross-sections
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