/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and store data into TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plugins
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Core
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	// Define file
  	TFile *output = new TFile("out_LEPep209GeV.root", "recreate");
	// Permission check
	if (!output->IsOpen()) {
		std::cerr << "Error opening output file!" << std::endl;
		return 1;
	}
	
	// Define tree
  TTree *tree = new TTree("tree", "tree");

	// Branch params
	int id, event, size, no;
	double m, px, py, pz, eta, phi, pt;

	// Define branches with correct data types
	tree->Branch("event", &event, "event/I");	// event number
	tree->Branch("size", &size, "size/I");		// event size
	tree->Branch("no", &no, "no/I");			// particle no
	tree->Branch("id", &id, "id/I");			// particle id
	tree->Branch("m", &m, "m/D");				// particle mass
	tree->Branch("px", &px, "px/D");			// particle px
	tree->Branch("py", &py, "py/D");			// particle py
	tree->Branch("pz", &pz, "pz/D");			// particle pz
	tree->Branch("pt", &pt, "pt/D");			// particle pt
	tree->Branch("eta", &eta, "eta/D");			// eta trajectory
	tree->Branch("phi", &phi, "phi/D");			// phi trajectory

	// Set # of events
	int nevents = 5e5;

	// Define study object
	Pythia8::Pythia pythia;

	// Electron positron collisions
	pythia.readString("Beams:idA = 11");
	pythia.readString("Beams:idB = -11");

	// Center of mass energy (GeV)
	pythia.readString("Beams:eCM = 209");

	// QCD studies
	pythia.readString("HardQCD:all = on");
	// WZ productions
	// pythia.readString("PhaseSpace:pTHatMin = 20");	// Set minimum pTHat for Z and W production
	pythia.readString("WeakSingleBoson:all = on");

	// Initialise PYTHIA
	pythia.init();

	// Study events
	for(int i = 0; i < nevents; i++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;

		// Event data size
		int entries = pythia.event.size();

		// Store event #
		event = i;
		size = entries;

		// Print event #
		std::cout << "Event: " << i << std::endl;

		// Study particles
		for(int j = 0; j < entries; j++)
		{
			no = j;						// particle #
			id = pythia.event[j].id();	// particle id
			m = pythia.event[j].m();	// particle m
			px = pythia.event[j].px();	// particle px
			py = pythia.event[j].py();	// particle py
			pz = pythia.event[j].pz();	// particle pz
			
			// Populate branches
			tree->Fill();
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ending
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// write file
	output->Write();

	// close file
	output->Close();

	// Terminate
	return 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}