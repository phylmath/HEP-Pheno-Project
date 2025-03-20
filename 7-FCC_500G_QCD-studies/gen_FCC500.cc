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
  	TFile *output = new TFile("out_FCC500.root", "recreate");
	// Anti-crash
	if (!output->IsOpen()) {
		cerr << "Error opening output file!" << endl;
		return 1;
	}
	
	// Define tree
	TTree *tree = new TTree("tree", "tree");

	// Intialise tree branch vars
	int eveNum, eveSiz, parNum, parPdg;
	double parMas, parPmx, parPmy, parPmz, parPmt, parEta, parPhi;

	// Define particle branches
	tree->Branch("eveNum", &eveNum, "eveNum/I");
	tree->Branch("eveSiz", &eveSiz, "eveSiz/I");
	tree->Branch("parNum", &parNum, "parNum/I");
	tree->Branch("parPdg", &parPdg, "parPdg/I");
	tree->Branch("parMas", &parMas, "parMas/D");
	tree->Branch("parPmx", &parPmx, "parPmx/D");
	tree->Branch("parPmy", &parPmy, "parPmy/D");
	tree->Branch("parPmz", &parPmz, "parPmz/D");
	tree->Branch("parPmt", &parPmt, "parPmt/D");
	tree->Branch("parEta", &parEta, "parEta/D");
	tree->Branch("parPhi", &parPhi, "parPhi/D");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1D *hist_nChPyth = new TH1D("hist_nChPyth", "Charged Hadron Multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 50, 0, 100);
	tree->Branch("hist_nChPyth", &hist_nChPyth, "hist_nChPyth");

	TH1D *hist_nJetsCh = new TH1D("hist_nJetsCh", "Hadronic Jet Multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0, 5);
	tree->Branch("hist_nJetsCh", &hist_nJetsCh, "hist_nJetsCh");

	TH1D *hist_nJetsFr = new TH1D("hist_nJetsFr", "Hadronic Jet Constituent multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 30, 0, 30);
	tree->Branch("hist_nJetsFr", &hist_nJetsFr, "hist_nJetsFr");

	TH1D *hist_nParton = new TH1D("hist_nParton", "Intermediate Parton Multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 25, 0, 100);
	tree->Branch("hist_nParton", &hist_nParton, "hist_nParton");

	TH1D *hist_nPQuark = new TH1D("hist_nPQuark", "Intermediate Quark Multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0, 100);
	tree->Branch("hist_nPQuark", &hist_nPQuark, "hist_nPQuark");

	TH1D *hist_nPGluon = new TH1D("hist_nPGluon", "Intermediate Gluon Multiplicity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 25, 0, 100);
	tree->Branch("hist_nPGluon", &hist_nPGluon, "hist_nPGluon");

	TH1D *hist_Spheric = new TH1D("hist_Spheric", "Sphericity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Spheric", &hist_Spheric, "hist_Spheric");

	TH1D *hist_Aplanar = new TH1D("hist_Aplanar", "Aplanarity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Aplanar", &hist_Aplanar, "hist_Aplanar");

	TH1D *hist_Lineric = new TH1D("hist_Lineric", "Linearised Sphericity distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Lineric", &hist_Lineric, "hist_Lineric");

	TH1D *hist_ThrustP = new TH1D("hist_ThrustP", "Thrust distributions [ FCC E^{+} E^{-} at 500 GeV ]", 17, 0.575, 1.);
	tree->Branch("hist_ThrustP", &hist_ThrustP, "hist_ThrustP");

	TH1D *hist_ThMajor = new TH1D("hist_ThMajor", "Thrust Major distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_ThMajor", &hist_ThMajor, "hist_ThMajor");

	TH1D *hist_ThMinor = new TH1D("hist_ThMinor", "Thrust Major distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_ThMinor", &hist_ThMinor, "hist_ThMinor");

	TH1D *hist_Oblatey = new TH1D("hist_Oblatey", "Oblateness distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Oblatey", &hist_Oblatey, "hist_Oblatey");

	TH1D *hist_sphAxis = new TH1D("hist_sphAxis", "Sphericity axis distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, -1., 1.);
	tree->Branch("hist_sphAxis", &hist_sphAxis, "hist_sphAxis");

	TH1D *hist_linAxis = new TH1D("hist_linAxis", "Linearity axis distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, -1., 1.);
	tree->Branch("hist_linAxis", &hist_linAxis, "hist_linAxis");

	TH1D *hist_thrAxis = new TH1D("hist_thrAxis", "Thrust axis distributions [ FCC E^{+} E^{-} at 500 GeV ]", 100, -1., 1.);
	tree->Branch("hist_thrAxis", &hist_thrAxis, "hist_thrAxis");

	TH1D *hist_nChLund = new TH1D("hist_nChLund", "Lund Jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChLund", &hist_nChLund, "hist_nChLund");

	TH1D *hist_nChJade = new TH1D("hist_nChJade", "Jade jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChJade", &hist_nChJade, "hist_nChJade");

	TH1D *hist_nChDurh = new TH1D("hist_nChDurh", "Durham jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChDurh", &hist_nChDurh, "hist_nChDurh");

	TH1D *hist_difLund = new TH1D("hist_difLund", "Lund e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difLund", &hist_difLund, "hist_difLund");

	TH1D *hist_difJade = new TH1D("hist_difJade", "Jade e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difJade", &hist_difJade, "hist_difJade");

	TH1D *hist_difDurh = new TH1D("hist_difDurh", "Durham e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difDurh", &hist_difDurh, "hist_difDurh");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 1e5;

	// QCD processes
	pythia.readString("HardQCD:all = off");						// hadronisation

	// Electroweak processes
	pythia.readString("WeakZ0:gmZmode = 0");
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee'->γ*/Z
	// pythia.readString("WeakSingleBoson:ffbar2W = on");			// ee'->W
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");		// ee'->γ*γ*ZZ
	pythia.readString("WeakDoubleBoson:ffbar2ZW = on");			// ee'->ZW
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");			// ee'->WW

	// Boson hadronic decays
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5");				// turn on Z iff (duscb)
	pythia.readString("24:onMode = off");						// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 15");				// turn on W iff (duscb and τν)

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

	// Define Beam params
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	double mZ = pythia.particleData.m0(23);						// Store Z0 mass
	double mW = pythia.particleData.m0(24);						// Store W+ mass
	pythia.settings.parm("Beams:eCM", 500);						// Set centre-of-mass
	pythia.readString("PDF:lepton = off");						// Disable substructure

	// Suppress event listing
	pythia.readString("Init:showProcesses = false"); 
	pythia.readString("Next:numberShowEvent = 0"); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Anti-crash
	if (!pythia.init()) return 1;

	// Initialise analyses
	Sphericity sph;
	Sphericity lin(1.);
	Thrust thr;
	ClusterJet lund("Lund");
	ClusterJet jade("Jade");
	ClusterJet durham("Durham");

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;
		
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		
		// Counters
		int nCh = 0;		// Charged Hadron Multiplicity
		int nJc = 0;		// Jet multiplicity
		int nJf = 0;		// Jet fraction
		int nCp = 0;		// Intermediate parton
		int nCq = 0;		// Intermediate quarks
		int nCg = 0;		// Intermediate gluons

		// FJ event vector
		vector<PseudoJet> particles;

		// Run through particles
		for(int j = 0; j < pythia.event.size(); j++) {
			
			// Hadron check
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron()) {
				
				////////////////////////// STORING PARTS DATA //////////////////////////
				eveNum = iEvent;						// Store event number
				eveSiz = pythia.event.size();			// Store event size
				parNum = j;								// Store particle number
				parPdg = pythia.event[j].id();			// Store particle pdg id
				parMas = pythia.event[j].m();			// Store particle mass
				parPmx = pythia.event[j].px();			// Store particle momentum-x
				parPmy = pythia.event[j].py();			// Store particle momentum-y
				parPmz = pythia.event[j].pz();			// Store particle momentum-z
				parPmt = pythia.event[j].pT();			// Store particle momentum-t
				parEta = pythia.event[j].eta();			// Store particle rapidity
				parPhi = pythia.event[j].phi();			// Store particle azimuthal

				////////////////////////// COMPUTING NCH CURVE //////////////////////////
				nCh++;									// Update counter

				////////////////////////// STORING JETS PARAMS //////////////////////////
				PseudoJet particle(parPmx, parPmy, parPmz, parMas);		// FJ particle vector
				particle.set_user_index(parPdg);						// Store particle pdg
				particles.push_back(particle);							// Add particle to event

				////////////////////////// CLUSTERING AND PRINTING JET //////////////////////////
				double R = 0.4;															// Jet radius
				double ptmin = 5.0;														// Lower pT
				JetDefinition jet_def(antikt_algorithm, R);								// Create jet definition
				ClusterSequence cs(particles, jet_def);									// Run clustering
				vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store results
				nJc = jets.size();														// Jet multiplicity
				
				// Run through jets
				for (int i = 0; i < jets.size(); i++) {
					// Store jet fraction
					nJf = jets[i].constituents().size();
					// Count jet particles
					int n_constituents = jets[i].constituents().size();
					// Define constituents vector
					vector<PseudoJet> constituents = jets[i].constituents();
					// Study jet constituents
					for (int j = 0; j < constituents.size(); j++) {
						// Define constituent vector
						PseudoJet constituent = jets[i].constituents()[j];
					}
				}
			}
			
			////////////////////////// COMPUTING PARTON NCH CURVE //////////////////////////
			// Parton check
			if(pythia.event[j].isFinal()==false) {
				// Quark check
				if(pythia.event[j].id()==1||pythia.event[j].id()==2||pythia.event[j].id()==3||pythia.event[j].id()==4||pythia.event[j].id()==5) {
					nCp++; nCq++;	// Update counter
				}
				// Gluon check
				if(pythia.event[j].id()==21) {
					nCp++; nCg++;	// Update counter
				}
			}		
		}

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
		// Populate histogram
		if (sph.analyze( pythia.event )) {
			
			hist_Spheric->Fill( sph.sphericity() );				// Sphericity = (sum_i p_i^a p_i^b)/(sum_i p_i^2)
			hist_sphAxis->Fill( sph.eventAxis(1).pz() );		// Cosθ
			hist_Aplanar->Fill( sph.aplanarity() );				// Aplanarity
		}
		// Populate histogram
		if (lin.analyze( pythia.event )) {
			hist_Lineric->Fill( lin.sphericity() );				// Linear.Sph = (sum_i p_i^a p_i^b p_i^{r-2})/(sum_i p_i^r)
			hist_linAxis->Fill( lin.eventAxis(1).pz() );		// Cosθ
		}
		// Populate histogram
		if (thr.analyze( pythia.event )) {
			hist_ThrustP->Fill( thr.thrust() );					// Thrust
			hist_thrAxis->Fill( thr.eventAxis(1).pz() );		// Cosθ
			hist_ThMajor->Fill( thr.tMajor() );					// Tmajor  
			hist_ThMinor->Fill( thr.tMinor() );					// Tminor
			hist_Oblatey->Fill( thr.oblateness() );				// Oblateness
			}

		// Populate histogram
		if (lund.analyze( pythia.event, 0.01, 0.)) {
			hist_nChLund->Fill( lund.size() );
			for (int k = 0; k < lund.size() - 1; ++k)
			hist_difLund->Fill( lund.p(k).e() - lund.p(k+1).e() );
		}

		if (jade.analyze( pythia.event, 0.01, 0.)) {
			hist_nChJade->Fill( jade.size() );
			for (int k = 0; k < jade.size() - 1; ++k)
			hist_difJade->Fill( jade.p(k).e() - jade.p(k+1).e() );
		}
		
		if (durham.analyze( pythia.event, 0.01, 0.)) {
			hist_nChDurh->Fill( durham.size() );
			for (int k = 0; k < durham.size() - 1; ++k)
			hist_difDurh->Fill( durham.p(k).e() - durham.p(k+1).e() );
		}

		////////////////////////// POPULATING HISTOS WITH DATA //////////////////////////
		hist_nChPyth->Fill( nCh );
		hist_nJetsCh->Fill( nJc );
		hist_nJetsFr->Fill( nJf );
		hist_nParton->Fill( nCp );
		hist_nPQuark->Fill( nCq );
		hist_nPGluon->Fill( nCg );

		////////////////////////// FILLING DATA TO TREEBRANCHES //////////////////////////
		tree->Fill();
	}

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