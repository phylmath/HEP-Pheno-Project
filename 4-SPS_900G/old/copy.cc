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
  	TFile *output = new TFile("out_LHC236.root", "recreate");
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Define Beam params
	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = 2212");
	// Define centre GeV
	pythia.readString("Beams:eCM = 2360.");
	// Define study types
	pythia.readString("HardQCD:all = on");
	pythia.readString("PhaseSpace:pTHatMin = 20.");

	// Initialise PYTHIA
	pythia.init();
	// Anti-crash
	if (!pythia.init()) return 1;

	// // Define histogram
	// Hist hist_mult("Charged multiplicity", 100, -0.5, 799.5);

	// Set # of events
	int nEvents = 100;
	int nCharge = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Study events
	for(int iEvent = 0; iEvent < nEvents; iEvent++ )
	{
		// Anti-crash
		if(!pythia.next()) continue;

		// Charge counter
		nCharge = 0;

		// Study particles
		for(int j = 0; j < pythia.event.size(); j++)
			
			// Check
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged())
			{
				// Add to counter
				nCharge++;

				// Store info


				// Populate branches
				tree->Fill();

			}

		// // Fill histogram
		// hist_mult.fill( nCharge );

		// // Print event #
		// std::cout << "Event: " << iEvent << "	Size: " << pythia.event.size() << "	Charged: " << nCharge << std::endl;

	}

	// // Print histogram
	// cout << hist_mult;

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