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
	vector<float> eveThr, eveTax, eveSpr, sigmaT, parEto, parEtt, parPmx, parPmy, parPmz;

	// Define branches
	tree->Branch("sigmaT", "vector<float>", &sigmaT);										// Total sigma
	tree->Branch("eveNum", "vector<int>", &eveNum);											// Event number
	tree->Branch("eveSiz", "vector<int>", &eveSiz);											// Event size
	tree->Branch("eveSpr", "vector<float>", &eveSpr);										// Event √s'
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
	int nEvent = 2;

	// Store masses
	float mZ = pythia.particleData.m0(23);													// Z0 mass
	float mW = pythia.particleData.m0(24);													// W+ mass

///////////////////////////////PHYSICS SWITCHES FOR TESLA 500 GeV ///////////////////////////////////////////
	
	// QCD processes
	pythia.readString("HardQCD:all = off");													// master switch
	// EW boson processes
	pythia.readString("WeakZ0:gmZmode = 0");												// allow γ* or Z channels
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");									// ee'->γ*/Z
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");									// ee'->γ*γ*ZZ
	pythia.readString("WeakDoubleBoson:ffbar2ZW = off");									// ee'->ZW
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");										// ee'->WW
	// EW boson decays
	pythia.readString("23:onMode = off");													// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 6 5");											// turn on Z iff (duscbt)
	pythia.readString("24:onMode = off");													// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6 15");										// turn on W iff (duscbt and τν)
	// EW photon-parton processes
	pythia.readString("PhotonParton:ggm2qqbar = off");										// gγ->qq' (uds)
	pythia.readString("PhotonParton:ggm2ccbar = off");										// gγ->cc'
	pythia.readString("PhotonParton:ggm2bbbar = off");										// gγ->bb'
	pythia.readString("PhotonParton:qgm2qg = off");											// gγ->qq'
	pythia.readString("PhotonParton:qgm2qgm = off");										// gγ->qq'
	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");										// ee'->tt'
	// Photon processes
	pythia.readString("PhotonCollision:all = off");
	pythia.readString("PhotonCollision:gmgm2qqbar = off");									// γγ->qq'
	pythia.readString("PhotonCollision:gmgm2ccbar = off");									// γγ->cc'
	pythia.readString("PhotonCollision:gmgm2bbbar = off");									// γγ->bb'
	pythia.readString("PhotonCollision:gmgm2ee = off");										// γγ->ee'
	pythia.readString("PhotonCollision:gmgm2mumu = off");									// γγ->μμ'
	pythia.readString("PhotonCollision:gmgm2tautau = off");									// γγ->ττ'
	// ISR processes
	pythia.readString("PartonLevel:ISR = on");
	pythia.readString("SpaceShower:QEDshowerByL = on");										// ee->γee
	pythia.readString("SpaceShower:QEDshowerByQ = off");									// qq->γqq
	// FSR processes
	pythia.readString("PartonLevel:FSR = on");
	pythia.readString("TimeShower:QEDshowerByL = on");										// ee->γee
	pythia.readString("TimeShower:QEDshowerByQ = off");										// qq->γqq
	// Define Beam params
	pythia.readString("Beams:idA = 11"); 													// beam energy
	pythia.readString("Beams:idB = -11"); 													// beam energy
	pythia.settings.parm("Beams:eCM", 500);													// c-om energy
	// pythia.readString("PDF:lepton = off");												// disable ISR

	// Suppress terminal text
	pythia.readString("Print:quiet = on");
	pythia.readString("Next:numberCount = 1000");											//
	pythia.readString("Next:numberShowProcess = 0");										//
	pythia.readString("Next:numberShowInfo = 0");											//
	pythia.readString("Next:numberShowEvent = 0");											//
	pythia.readString("Init:showMultipartonInteractions = off");							//
	pythia.readString("Init:showChangedSettings = off");									//
	pythia.readString("Init:showChangedParticleData = off");								//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Analyses
	Thrust thr;
	Event event_fch;
	float sigISR=0.0, sigmaE=0.0;
	int nCh=0, nISR=0;
	
	// Run through events
	for (int iEvent=0; iEvent<nEvent; iEvent++ ) {

		// Anti-crash
		if (!pythia.next()) continue;

		// Counter
		nCh=0; sigISR=0.0; sigmaE=0.0;

		// Reset event vectors
		event_fch.init(); event_fch.clear(); eveNum.clear(); sigmaT.clear();
		eveSpr.clear(); eveThr.clear(); eveTax.clear(); eveSiz.clear();
		// Reset part vectors
		parNum.clear(); parPdg.clear(); parEto.clear(); 
		parEtt.clear(); parPmx.clear(); parPmy.clear(); parPmz.clear();

		// Run through particles
		for (int jParts=0; jParts<pythia.event.size(); jParts++) {

			// Sum final energies
			if (pythia.event[jParts].isFinal()) sigmaE+=pythia.event[jParts].e();

			// Store particle info
			if (pythia.event[jParts].isFinal() && pythia.event[jParts].isCharged() && pythia.event[jParts].isHadron()) {
		
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
				if ( (abs(pythia.event[idmom1].id())==11 || abs(pythia.event[idmom2].id())==11) && pythia.event[jParts].e()>0.001 ) {
					
					if (pythia.event[jParts].e() > sigISR) {
						cout << "ISR photon energy = " << pythia.event[jParts].e() << " with status " << pythia.event[jParts].status() << " and mother energy = " << pythia.event[idmom1].e() << " with status " << pythia.event[idmom1].status() << endl;
						sigISR=pythia.event[jParts].e();
					}
				}

			}

		}

		// Compute √s'
		sigISR = 500.0*sqrt(1.0-(2.0*sigISR)/500.0);

		// Store event info
		if (nCh!=0) if (thr.analyze(event_fch)) {
			eveThr.push_back(1.0-thr.thrust());												// Add event thrust
			eveTax.push_back(thr.eventAxis(1).pz());										// Add event Cosθ
			sigmaT.push_back(pythia.info.sigmaGen());										// Add event sigma
			eveSiz.push_back(nCh);															// Add event size
			eveSpr.push_back(sigISR);														// Add ISR energy
		}

		// Radiative events
		if (nCh!=0 && sigISR<500.0) nISR++;

		// Populate
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-sections
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Total radiative events : " << nISR << " out of " << nEvent << endl;
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