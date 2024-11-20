// stnd plugins
#include <iostream>
// root plugins
#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"

// core func
int main(){

	// define file
	TFile *output = new TFile("out_LHCpp14TeV.root", "recreate");
	// define tree
	TTree *tree = new TTree("tree", "tree");

	// branch params
	int id, event, size, no;
	double m, px, py, pz;

	// define branches
	tree->Branch("event", &event, "event/I");	// event number
	tree->Branch("size", &size, "size/I");		// event size
	tree->Branch("no", &no, "no/I");			// particle no
	tree->Branch("id", &id, "id/I");			// particle id
	tree->Branch("m", &m, "m/D");				// particle mass
	tree->Branch("px", &px, "px/D");			// particle mom-x
	tree->Branch("py", &py, "py/D");			// particle mom-y
	tree->Branch("pz", &pz, "pz/D");			// particle mom-z

	// set # of events
	int nevents = 5e5;

	// define study object
	Pythia8::Pythia pythia;

	// proton proton collisions
	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = 2212");

	// centre of mass energy (GeV)
	pythia.readString("Beams:eCM = 13.8.e3");

	// study type
	pythia.readString("SoftQCD:all = on");
	pythia.readString("HardQCD:all = on");

	// define hist object
	Pythia8::Hist hpz("Momentum Distribution", 100, -10, 10);

	// initialise
	pythia.init();

	// study events
	for(int i = 0; i < nevents; i++ )
	{
		// anti-crash
		if(!pythia.next()) continue;

		// event data size
		int entries = pythia.event.size();

		// store event #
		event = i;
		size = entries;

		// print event # in terminal
		std::cout << "Event: " << i << std::endl;

		// study particles
		for(int j = 0; j < entries; j++)
		{
			// store particle #
			no = j;

			// store particle id
			id = pythia.event[j].id();

			// store particle mass
			m = pythia.event[j].m();

			// store momentums
			px = pythia.event[j].px();
			py = pythia.event[j].py();
			pz = pythia.event[j].pz();

			// populate branches
			tree->Fill();
		}
	}

	// write file
	output->Write();

	// close file
	output->Close();

	// terminate
	return 0;
}