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
	// pythia.readString("Beams:frameType = 1"); 				// Symmetrical beams
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	double mZ = pythia.particleData.m0(23);						// Store Z0 mass
	pythia.settings.parm("Beams:eCM", mZ);						// Set energy = mZ
	pythia.readString("PDF:lepton = off");						// Disable beam substructure


	// Define physics
	// pythia.readString("HardQCD:all = on"); 					// All hard QCD processes
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee->gamma*/Z/W->ff
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5");				// turn on Z iff (duscb)

	// Set phase space cut
	// pythia.readString("PhaseSpace:pTHatMin = 20.");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();
	// Anti-crash
	if (!pythia.init()) return 1;

	// Define histogram
	Hist nCharge("charged multiplicity", 28, 2, 58);
	// Hist nCharge("charged multiplicity", 100, -0.5, 99.5);

	// Set # of events
	int nEvent = 2;

	// Study events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		// Hadron counters
		int nCh = 0;
		// Study particles
		for(int j = 0; j < pythia.event.size(); j++)
			// Check particle properties
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron()){
				// Update counter
				nCh++;
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
		nCharge.fill( nCh );
	}

	// Store histogram to txt
	nCharge.table("LEP912.txt", false, false, true);

	// Display statistics
	// pythia.stat();
	
	// Display histogram
	// cout << nCharge;

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
	
	// Study jet properties
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

		// Label columns
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
// Ending
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Write file
	output->Write();
	output->Close();
	delete output;
	// Terminate
	return 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}