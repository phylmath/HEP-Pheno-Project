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
	vector<int> eveNum, eveSiz, parNum, parPdg, parFCH;
	vector<float> sigmaT, parMas, parPmx, parPmy, parPmz;

	// Define branches
	tree->Branch("sigmaT", "vector<float>", &sigmaT);					// Total sigma
	tree->Branch("eveNum", "vector<int>", &eveNum);						// Event number
	tree->Branch("eveSiz", "vector<int>", &eveSiz);						// Event size
	tree->Branch("parNum", "vector<int>", &parNum);						// Parts number
	tree->Branch("parPdg", "vector<int>", &parPdg);						// Parts pdg id
	tree->Branch("parMas", "vector<float>", &parMas);					// Parts mass
	tree->Branch("parPmx", "vector<float>", &parPmx);					// Parts mom-x
	tree->Branch("parPmy", "vector<float>", &parPmy);					// Parts mom-y
	tree->Branch("parPmz", "vector<float>", &parPmz);					// Parts mom-z
	tree->Branch("parFCH", "vector<int>", &parFCH);						// FCH flag

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 1e4;

	// Store masses
	float mZ = pythia.particleData.m0(23);								// Z0 mass
	float mW = pythia.particleData.m0(24);								// W+ mass

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
	pythia.readString("Beams:idA = 11"); 								// Beam A energy
	pythia.readString("Beams:idB = -11"); 								// Beam B energy
	pythia.settings.parm("Beams:eCM", 500);								// CM energy
	pythia.readString("PDF:lepton = off");								// Disable substructure

	// Suppress terminal text
	pythia.readString("Next:numberCount = 1000");						//
	pythia.readString("Next:numberShowProcess = 0");					//
	pythia.readString("Next:numberShowInfo = 0");						//
	pythia.readString("Next:numberShowEvent = 0");						//
	pythia.readString("Init:showMultipartonInteractions = off");		//
	pythia.readString("Init:showChangedSettings = off");				//
	pythia.readString("Init:showChangedParticleData = off");			//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;

		// Update
		sigmaT.push_back(pythia.info.sigmaGen());

		// Reset
		eveNum.clear(); 
		eveSiz.clear();
		parNum.clear();
		parPdg.clear();
		parMas.clear();
		parPmx.clear();
		parPmy.clear();
		parPmz.clear();
		parFCH.clear();

		// Run through particles
		for(int jParts = 0; jParts < pythia.event.size(); jParts++) {

			// FCH check
			if(pythia.event[jParts].isFinal() && pythia.event[jParts].isCharged()) {

				// Update
				eveNum.push_back(iEvent);										// Add event number
				eveSiz.push_back(pythia.event.size());							// Add event size
				parNum.push_back(jParts);										// Add particle number
				parPdg.push_back(pythia.event[jParts].id());					// Add particle pdg id
				parMas.push_back(pythia.event[jParts].m());						// Add particle mass
				parPmx.push_back(pythia.event[jParts].px());					// Add particle mom-x
				parPmy.push_back(pythia.event[jParts].py());					// Add particle mom-y
				parPmz.push_back(pythia.event[jParts].pz());					// Add particle mom-z
				if(pythia.event[jParts].isHadron()) parFCH.push_back(1);  		// Add positive FCH flag	
				else parFCH.push_back(0);										// Add negative FCH flag
			}
		}

		// Populate
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check cross-sections
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pythia.stat();
	// cout << "Total weighted sum:\t" << pythia.info.weightSum() << endl;					// total events 
	// cout << "Total crosssection:\t" << pythia.info.sigmaGen() << endl;					// total σ 
	// cout << pythia.info.nameProc(221) << "\t" << pythia.info.sigmaGen(221) << endl;		// ee'->γ*/Z
	// cout << pythia.info.nameProc(222) << "\t" << pythia.info.sigmaGen(222) << endl;		// ee'->W
	// cout << pythia.info.nameProc(231) << "\t" << pythia.info.sigmaGen(231) << endl;		// ee'->γ*Zγ*Z
	// cout << pythia.info.nameProc(232) << "\t" << pythia.info.sigmaGen(232) << endl;		// ee'->ZW
	// cout << pythia.info.nameProc(233) << "\t" << pythia.info.sigmaGen(233) << endl;		// ee'->WW
	// cout << pythia.info.nameProc(604) << "\t" << pythia.info.sigmaGen(604) << endl;		// ee'->tt'

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