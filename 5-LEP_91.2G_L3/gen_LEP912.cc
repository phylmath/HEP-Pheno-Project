/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and store data into TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
#include "Pythia8/Pythia.h"
#include "Pythia8/Basics.h"
#include "TFile.h"
#include "TTree.h"
// Header
using namespace Pythia8;
using namespace std;

// Code
int main(){

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
	int nEvents = 2e5;

	// Study events
	for(int iEvent = 0; iEvent < nEvents; iEvent++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;
		// Print event#
		cout << "\tEvent#" << iEvent << endl;
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
	mult.table("LEP912_pen_H_W.txt", false, false, true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Display statistics
	// pythia.stat();
	
	// Display histogram
	cout << mult;

	// write file
	output->Write();

	// close file
	output->Close();
	
	// Terminate
	return 0;

}