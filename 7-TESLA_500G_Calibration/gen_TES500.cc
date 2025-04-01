/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and cluster particles with FastJet3
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
// Create output TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("gen_TES500.root", "recreate");
	
	// Define tree
	TTree *tree = new TTree("tree", "tree");

	// Intialise tree branch vars
	int eveNum=0, eveSiz=0, parNum=0, parPdg=0;
	double parMas=0.0, parPmx=0.0, parPmy=0.0, parPmz=0.0;
	bool parFCH=false;

	// Define particle branches
	tree->Branch("eveNum", &eveNum, "eveNum/I");				// Event number
	tree->Branch("eveSiz", &eveSiz, "eveSiz/I");				// Event size
	tree->Branch("parNum", &parNum, "parNum/I");				// Particle number
	tree->Branch("parPdg", &parPdg, "parPdg/I");				// particle id
	tree->Branch("parMas", &parMas, "parMas/D");				// Particle mass
	tree->Branch("parPmx", &parPmx, "parPmx/D");				// Particle x-momentum
	tree->Branch("parPmy", &parPmy, "parPmy/D");				// Particle y-momentum
	tree->Branch("parPmz", &parPmz, "parPmz/D");				// Particle z-momentum
	tree->Branch("parFCH", &parFCH, "parFCH/B");				// Final-Charged-Hadron

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 1e4;

	// Store masses
	double mZ = pythia.particleData.m0(23);						// Z0 mass
	double mW = pythia.particleData.m0(24);						// W+ mass

	// QCD processes
	pythia.readString("HardQCD:all = off");						// master switch

	// Electroweak boson processes
	pythia.readString("WeakZ0:gmZmode = 0");					// allow γ* or Z channels
	// pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm));	// ee'->qq'
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee'->γ*/Z
	// pythia.readString("WeakSingleBoson:ffbar2W = on");		// ee'->W
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");		// ee'->γ*γ*ZZ
	pythia.readString("WeakDoubleBoson:ffbar2ZW = off");		// ee'->ZW
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");			// ee'->WW
	// Boson decays
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5 6");				// turn on Z iff (duscbt)
	pythia.readString("24:onMode = off");						// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6 15");			// turn on W iff (duscbt and τν)

	// Electroweak photon-parton processes
	pythia.readString("PhotonParton:ggm2qqbar = off");			// gγ->qq' (uds)
	pythia.readString("PhotonParton:ggm2ccbar = off");			// gγ->cc'
	pythia.readString("PhotonParton:ggm2bbbar = off");			// gγ->bb'
	pythia.readString("PhotonParton:qgm2qg = off");				// gγ->qq'
	pythia.readString("PhotonParton:qgm2qgm = off");			// gγ->qq'

	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");			// ee'->tt'

	// Photon processes
	pythia.readString("PhotonCollision:all = off");
	pythia.readString("PhotonCollision:gmgm2qqbar = off");		// γγ->qq'
	pythia.readString("PhotonCollision:gmgm2ccbar = off");		// γγ->cc'
	pythia.readString("PhotonCollision:gmgm2bbbar = off");		// γγ->bb'
	pythia.readString("PhotonCollision:gmgm2ee = off");			// γγ->ee'
	pythia.readString("PhotonCollision:gmgm2mumu = off");		// γγ->μμ'
	pythia.readString("PhotonCollision:gmgm2tautau = off");		// γγ->ττ'

	// ISR processes
	pythia.readString("TimeShower:QEDshowerByL = on");			// ee->γee
	pythia.readString("TimeShower:QEDshowerByQ = off");			// qq->γqq
	pythia.readString("SpaceShower:QEDshowerByL = on");			// ee->γee
	pythia.readString("SpaceShower:QEDshowerByQ = off");		// qq->γqq

	// Define Beam params
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	pythia.settings.parm("Beams:eCM", 500);						// Set centre-of-mass
	pythia.readString("PDF:lepton = off");						// Disable substructure

	// Suppress terminal text
	pythia.readString("Next:numberCount = 1000");
	pythia.readString("Next:numberShowProcess = 0");
	pythia.readString("Init:showMultipartonInteractions = off");
	pythia.readString("Init:showChangedSettings = off");
	pythia.readString("Init:showChangedParticleData = off");
	pythia.readString("Next:numberCount = 0");
	pythia.readString("Next:numberShowInfo = 0");
	pythia.readString("Next:numberShowEvent = 0");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Counters
	double sigmaTotal = 0.0;

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;

		// Run through particles
		for(int j = 0; j < pythia.event.size(); j++) {
			
			// Store vars
			eveNum = iEvent;									// Store event number
			eveSiz = pythia.event.size();						// Store event size
			parNum = j;											// Store particle number
			parPdg = pythia.event[j].id();						// Store particle pdg id
			parMas = pythia.event[j].m();						// Store particle mass
			parPmx = pythia.event[j].px();						// Store particle momentum-x
			parPmy = pythia.event[j].py();						// Store particle momentum-y
			parPmz = pythia.event[j].pz();						// Store particle momentum-z

			// FCH check
			if(pythia.event[j].isFinal())
				if(pythia.event[j].isCharged())
					if(pythia.event[j].isHadron())
						parFCH = true;
		}

		// Fill branches
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-section checks
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

	// Write file
	output->Write();
	output->Close();
	delete output;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Terminate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}