/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and store data into TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"
// Header
using namespace Pythia8;

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("out_SPS900.root", "recreate");
	// Permission check
	if (!output->IsOpen()) {
		std::cerr << "Error opening output file!" << std::endl;
		return 1;
	}
	
	// Define tree
	TTree *tree = new TTree("tree", "tree");

	// Intialise tree branch vars
	int evenN, evenS, partN, partI;
	double partM, partPx, partPy, partPz, partPt, partEta, partPhi;

	// Define tree branch data types
	tree->Branch("evenN", &evenN, "evenN/I");
	tree->Branch("evenS", &evenS, "evenS/I");
	tree->Branch("partN", &partN, "partN/I");
	tree->Branch("partI", &partI, "partI/I");
	tree->Branch("partM", &partM, "partM/D");
	tree->Branch("partPx", &partPx, "partPx/D");
	tree->Branch("partPy", &partPy, "partPy/D");
	tree->Branch("partPz", &partPz, "partPz/D");
	tree->Branch("partPt", &partPt, "partPt/D");
	tree->Branch("partEta", &partEta, "partEta/D");
	tree->Branch("partPhi", &partPhi, "partPhi/D");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Define Beam params
	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = -2212");
	// Define centre GeV
	pythia.readString("Beams:eCM = 900.");
	// Define study types
	pythia.readString("HardQCD:all = on");
	pythia.readString("PhaseSpace:pTHatMin = 20.");

	// Initialise PYTHIA
	pythia.init();
	// Anti-crash
	if (!pythia.init()) return 1;

	// Set # of events
	int nEvents = 100;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Study events
	for(int iEvent = 0; iEvent < nEvents; iEvent++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;

		// Study particles
		for(int j = 0; j < pythia.event.size(); j++)
			
			// Check particle properties
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron())
			{
				// Store info in vars
				evenN = iEvent;
				evenS = pythia.event.size();
				partN = j;
				partI = pythia.event[j].id();
				partM = pythia.event[j].m();
				partPx = pythia.event[j].px();
				partPy = pythia.event[j].py();
				partPz = pythia.event[j].pz();
				partPt = pythia.event[j].pT();
				partEta = pythia.event[j].eta();
				partPhi = pythia.event[j].phi();
				// Populate branches
				tree->Fill();
			}

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// write file
	output->Write();

	// close file
	output->Close();

	// Terminate
	return 0;

}




// int main() {
//   // Generator. Process selection. LHC initialization. Histogram.

//   Pythia pythia;

//   pythia.readString("Beams:eCM = 8000.");
//   pythia.readString("HardQCD:all = on");
//   pythia.readString("PhaseSpace:pTHatMin = 20.");

//   // If Pythia fails to initialize, exit with error.
//   if (!pythia.init()) return 1;

//   Hist mult("charged multiplicity", 100, -0.5, 799.5);

//   // Begin event loop. Generate event. Skip if error. List first one.
//   for (int iEvent = 0; iEvent < 100; ++iEvent) {
//     if (!pythia.next()) continue;
//     // Find number of all final charged particles and fill histogram.
//     int nCharged = 0;
//     for (int i = 0; i < pythia.event.size(); ++i)
//       if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
//         ++nCharged;
//     mult.fill( nCharged );
//   // End of event loop. Statistics. Histogram. Done.
//   }
//   pythia.stat();
//   cout << mult;
//   return 0;
// }