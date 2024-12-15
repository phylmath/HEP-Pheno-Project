/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and store data into TTree file
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
// #include "fastjet/PseudoJet.hh"
// #include "fastjet/ClusterSequence.hh"
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
// Header
using namespace Pythia8;
using namespace std;
using namespace fjcore;

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create a file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("out_LEP912.root", "recreate");
	// Anti-crash
	if (!output->IsOpen()) {
		std::cerr << "Error opening output file!" << std::endl;
		return 1;
	}
	
	// Define tree
	TTree *tree = new TTree("tree", "tree");

	// Intialise tree branch vars
	int eveNum, eveSiz, parNum, parPdg;
	double parMas, parPmx, parPmy, parPmz, parPmt, parEta, parPhi;

	// Define tree branch data types
	tree->Branch("eveNum", &eveNum, "eveNum/I");
	tree->Branch("eveSiz", &eveSiz, "evenS/I");
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
// Pythia code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;
	
	// Define Beam params
	pythia.readString("Beams:frameType = 1"); 				// Symmetrical beams
	pythia.readString("Beams:idA = 11"); 					// Beam A energy
	pythia.readString("Beams:idB = -11"); 					// Beam B energy
	// pythia.readString("Tune:pp = 14"); 					// Monash'13 tune
	
	// Define centre GeV
	pythia.readString("Beams:eA  = 45.6.");
	pythia.readString("Beams:eB  = 45.6.");
	pythia.readString("Beams:eCM = 91.2.");	
	
	// Define physics
	pythia.readString("HardQCD:all = on"); 						// All hard QCD processes
	// pythia.readString("HardQCD:gg2gg = on");					// gg2gg - Gluon Induced Events (code 111)
	// pythia.readString("HardQCD:gg2qqbar = on");				// gg2qqbar - (code 112)
	// pythia.readString("HardQCD:qg2qg = on");					// qg2qg - (code 113)
	// pythia.readString("HardQCD:qq2qq = on");					// qq2qq - Quark Induced Events (code 114)
	// pythia.readString("HardQCD:qqbar2gg = on");				// qqbar2gg - (code 115)
	// pythia.readString("HardQCD:qqbar2qqbarNew = on");		// qqbar2qqbarNew (code 116)

	// pythia.readString("WeakZ0:gmZmode = 1");					// control what Z should decay into
	// pythia.readString("WeakSingleBoson:all = on");
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee->gamma*/Z/W->ff
	// pythia.readString("WeakSingleBoson:ffbar2W = on");
	// pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm) = on");
	// pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gmZ) = on");
	// pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W) = on");

	// pythia.readString("PartonLevel:ISR = on"); 				// Initial-state radiation of qq->gluons
	// pythia.readString("PartonLevel:FSR = on"); 				// Final-state radiation of qq->gluons

	// pythia.readString("PartonLevel:MPI = on");				// multiparton interactions
	// pythia.readString("PartonLevel:all= on");				// parton event interactions

	// Set phase space cut
	// pythia.readString("PhaseSpace:pTHatMin = 20.");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();
	// Anti-crash
	if (!pythia.init()) return 1;

	// Define histogram
	Hist mult("charged multiplicity", 28, 2, 58);

	// Set # of events
	int nEvents = 1;

	// Study events
	for(int iEvent = 0; iEvent < nEvents; iEvent++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		// Hadron counters
		int Nch = 0;
		// Study particles
		for(int j = 0; j < pythia.event.size(); j++)
			// Check particle properties
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron()){
				// Update counter
				Nch++;
				// Store info in vars
				eveNum = iEvent;
				eveSiz = pythia.event.size();
				parNum = j;
				parPdg = pythia.event[j].id();
				parMas = pythia.event[j].m();
				parPmx = pythia.event[j].px();
				parPmy = pythia.event[j].py();
				parPmz = pythia.event[j].pz();
				parPmt = pythia.event[j].pT();
				parEta = pythia.event[j].eta();
				parPhi = pythia.event[j].phi();
				// Populate branches
				tree->Fill();
			}

		// Populate histogram
		mult.fill( Nch );
	}

	// Store histogram to txt
	// mult.table("LEP912_pen_H_W.txt", false, false, true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastJet code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Fill particles into a vector
	vector<PseudoJet> particles;
	// Loop #iteration
	int entries = tree->GetEntries();
	// Read branches
	for (int i = 0; i < entries; i++)
	{
		// Load branch
		tree->GetEntry(i);
		// Particle vector
		PseudoJet particle(parPmx, parPmy, parPmz, parMas);
		// Storing pdgID
		particle.set_user_index(parNum);
		// Add particle to vector
		particles.push_back(particle);
	}

	// Set jet radius
	double R = 0.6;
	// Set lower pT
	double ptmin = 5.0;
	
	// Create jet definition
	JetDefinition jet_def(antikt_algorithm, R);
	
	// Run clustering, sort/store results
	ClusterSequence cs(particles, jet_def);
	vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));

	// Print info
	cout << "Clustering with " << jet_def.description() << endl;
	
	// Study jets
	for (int i = 0; i < jets.size(); i++) 
	{
		// Label columns
		printf("%5s %15s %15s %15s %8s\n","jet #", "rapidity", "phi", "pt", "N");

		// Count jet particles
		int n_constituents = jets[i].constituents().size();

		// Print jet properties
		printf("%5u %15.8f %15.8f %15.8f %8u\n", i, jets[i].rap(), jets[i].phi(), jets[i].perp(), n_constituents);
		
		// Define constituents vector
		vector<PseudoJet> constituents = jets[i].constituents();

		printf("%5s %15s %15s %15s %8s\n","par #", "rapidity", "phi", "pt", "ID");
		// Study jet constituents
		for (int j = 0; j < constituents.size(); j++)
		{
			// Define constituent vector
			PseudoJet constituent = jets[i].constituents()[j];
			// Print constituent properties
			printf("%5u %15.8f %15.8f %15.8f %8i\n", j, constituents[j].rap(), constituents[j].phi(), constituents[j].perp(), constituent.user_index());
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Termination
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Display statistics
	pythia.stat();
	
	// Display histogram
	// cout << mult;

	// Terminate file
	output->Write();
	output->Close();
	delete output;



	// Terminate
	return 0;

}