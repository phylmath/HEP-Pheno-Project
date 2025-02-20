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
  	TFile *output = new TFile("out_LEP912.root", "recreate");
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

	TH1F *hist_nChExpe = new TH1F("hist_nChExpe", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 28, 1, 57);
	tree->Branch("hist_nChExpe", &hist_nChExpe, "hist_nChExpe");

	TH1F *hist_nChPyth = new TH1F("hist_nChPyth", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 28, 1, 57);
	tree->Branch("hist_nChPyth", &hist_nChPyth, "hist_nChPyth");

	TH1F *hist_nChJets = new TH1F("hist_nChJets", "Hadronic Jet Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0, 5);
	tree->Branch("hist_nChJets", &hist_nChJets, "hist_nChJets");

	TH1F *hist_nParton = new TH1F("hist_nParton", "Intermediate Parton Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 25, 0, 100);
	tree->Branch("hist_nParton", &hist_nParton, "hist_nParton");

	TH1F *hist_nPQuark = new TH1F("hist_nPQuark", "Intermediate Quark Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0, 100);
	tree->Branch("hist_nPQuark", &hist_nPQuark, "hist_nPQuark");

	TH1F *hist_nPGluon = new TH1F("hist_nPGluon", "Intermediate Gluon Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 25, 0, 100);
	tree->Branch("hist_nPGluon", &hist_nPGluon, "hist_nPGluon");

	TH1F *hist_Spheric = new TH1F("hist_Spheric", "Event Sphericity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Spheric", &hist_Spheric, "hist_Spheric");

	TH1F *hist_Lineric = new TH1F("hist_Lineric", "Event Linearised Sphericity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0., 1.);
	tree->Branch("hist_Lineric", &hist_Lineric, "hist_Lineric");

	TH1F *hist_Thrusty = new TH1F("hist_Thrusty", "Event Thrust distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0.5, 1.);
	tree->Branch("hist_Thrusty", &hist_Thrusty, "hist_Thrusty");

	TH1F *hist_Oblatey = new TH1F("hist_Oblatey", "Event Oblateness distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0.5, 1.);
	tree->Branch("hist_Oblatey", &hist_Oblatey, "hist_Oblatey");

	TH1F *hist_sphAxis = new TH1F("hist_sphAxis", "Event Sphericity axis distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, -1., 1.);
	tree->Branch("hist_sphAxis", &hist_sphAxis, "hist_sphAxis");

	TH1F *hist_linAxis = new TH1F("hist_linAxis", "Event Linearity axis distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, -1., 1.);
	tree->Branch("hist_linAxis", &hist_linAxis, "hist_linAxis");

	TH1F *hist_thrAxis = new TH1F("hist_thrAxis", "Event Thrust axis distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, -1., 1.);
	tree->Branch("hist_thrAxis", &hist_thrAxis, "hist_thrAxis");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import Experimental data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Set reading
	string line;
	// Hadron counters
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

	// Import experimental data
	ifstream infile_exp("LEP912_exp.txt");
	// Read through txt
	while ( !infile_exp.eof() ) {
		// Set reading order
		infile_exp >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_nChExpe->SetBinContent(hist_nChExpe->FindBin(Nch), Prb);
		// Populate error bar
		hist_nChExpe->SetBinError(hist_nChExpe->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_exp.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 284100;

	// Define physics
	// pythia.readString("HardQCD:all = on"); 					// All hard QCD processes
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee->gamma*/Z/W->ff
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5");				// turn on Z iff (duscb)

	// Set phase space cut
	// pythia.readString("PhaseSpace:pTHatMin = 20.");

	// Define Beam params
	// pythia.readString("Beams:frameType = 1"); 				// Symmetrical beams
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	double mZ = pythia.particleData.m0(23);						// Store Z0 mass
	pythia.settings.parm("Beams:eCM", mZ);						// Set energy = mZ
	pythia.readString("PDF:lepton = off");						// Disable beam substructure

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

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;
		
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		
		// Counters
		int nCh = 0;
		int nCj = 0;
		int nCjq = 0;
		int nCjg = 0;
		int nCp = 0;
		int nCq = 0;
		int nCg = 0;

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

			}

			////////////////////////// COMPUTING PARTONIC NCHs //////////////////////////
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

		////////////////////////// CLUSTERING AND PRINTING JET //////////////////////////
		double R = 0.4;															// Jet radius
		double ptmin = 5.0;														// Lower pT
		JetDefinition jet_def(antikt_algorithm, R);								// Create jet definition
		ClusterSequence cs(particles, jet_def);									// Run clustering
		vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store results
		nCj = jets.size();														// Jet multiplicity
		
		// Run through jets
		for (int i = 0; i < jets.size(); i++) {
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

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
		// Sphericity/cosθ_sphericity
		if (sph.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) sph.list();
			// Populate histogram
			hist_Spheric->Fill( sph.sphericity() );
			hist_sphAxis->Fill( sph.eventAxis(1).pz() );
			// Sanity check
			double e1 = sph.eigenValue(1);
			double e2 = sph.eigenValue(2);
			double e3 = sph.eigenValue(3);
			if (e2 > e1 || e3 > e2) cout << "eigenvalues out of order: "
			<< e1 << "  " << e2 << "  " << e3 << endl;
		}

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
		// Linearity/cosθ_linearity
		if (lin.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) lin.list();
			// Populate histogram
			hist_Lineric->Fill( lin.sphericity() );
			hist_linAxis->Fill( lin.eventAxis(1).pz() );
			// Sanity check
			double e1 = lin.eigenValue(1);
			double e2 = lin.eigenValue(2);
			double e3 = lin.eigenValue(3);
			if (e2 > e1 || e3 > e2) cout << "eigenvalues out of order: "
			<< e1 << "  " << e2 << "  " << e3 << endl;
		}

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
		// Thrust/cosθ_thrust/Oblateness
		if (thr.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) thr.list();
			// Populate histogram
			hist_Thrusty->Fill( thr.thrust() );
			hist_Oblatey->Fill( thr.oblateness() );
			hist_thrAxis->Fill( thr.eventAxis(1).pz() );
			// Sanity check
			if ( abs(thr.eventAxis(1).pAbs() - 1.) > 1e-8
			|| abs(thr.eventAxis(2).pAbs() - 1.) > 1e-8
			|| abs(thr.eventAxis(3).pAbs() - 1.) > 1e-8
			|| abs(thr.eventAxis(1) * thr.eventAxis(2)) > 1e-8
			|| abs(thr.eventAxis(1) * thr.eventAxis(3)) > 1e-8
			|| abs(thr.eventAxis(2) * thr.eventAxis(3)) > 1e-8 ) {
			cout << " suspicious Thrust eigenvectors " << endl;
			//   thr.list();
			}
		}

		////////////////////////// POPULATING HISTOS WITH DATA //////////////////////////
		hist_nChPyth->Fill( nCh );
		hist_nChJets->Fill( nCj );
		hist_nParton->Fill( nCp );
		hist_nPQuark->Fill( nCq );
		hist_nPGluon->Fill( nCg );

		////////////////////////// FILLING DATA TO TREEBRANCHES //////////////////////////
		tree->Fill();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising all probabilities
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_nChExpe->Scale(1.0/hist_nChExpe->Integral());
	hist_nChPyth->Scale(1.0/hist_nChPyth->Integral());
	hist_nChJets->Scale(1.0/hist_nChJets->Integral());
	hist_nParton->Scale(1.0/hist_nParton->Integral());
	hist_nPQuark->Scale(1.0/hist_nPQuark->Integral());
	hist_nPGluon->Scale(1.0/hist_nPGluon->Integral());

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