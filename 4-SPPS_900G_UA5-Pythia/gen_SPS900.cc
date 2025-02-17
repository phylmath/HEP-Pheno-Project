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
  	TFile *output = new TFile("out_SPS900.root", "recreate");
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
	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = -2212");
	// Define centre GeV
	pythia.readString("Beams:eA  = 450.");
	pythia.readString("Beams:eB  = 450.");
	pythia.readString("Beams:eCM = 900.");
	// Define physics proc
	// pythia.readString("HardQCD:all = on");
	pythia.readString("SoftQCD:all = on");
	// pythia.readString("Top:all = on");
	// pythia.readString("WeakSingleBoson:all = on");
	// pythia.readString("WeakDoubleBoson:all = on");
	// Set phase space cut
	// pythia.readString("PhaseSpace:pTHatMin = 5.");
	// Set Monash'13 tune
	// pythia.readString("Tune:pp = 14");

	// Initialise PYTHIA
	pythia.init();
	// Anti-crash
	if (!pythia.init()) return 1;

	// Define histogram
	Hist mult("charged multiplicity", 54, 0, 130);

	// Set # of events
	int nEvents = 6839;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	mult.table("soft_ppb900_pen.txt", false, true, true);

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






















						// if (pythia.info.isNonDiffractive())



							// Print charged hadron
							// cout << "\tHadron is a " << pythia.event[j].id() << endl;
		// Print multiplicity
		// cout << "\t" << Nch << " charged hadrons in event#" << iEvent << endl;






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
// Find number of all final charged particles and fill histogram.
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


// string line;
// double Nch;
// double PrbTotal = 0, Prb = 0, Err_Nch = 0, Err_Prb = 0, normalised_Prb = 0, normalised_Err = 0;

// // Read the data from the input file and calculate the total probability
// ifstream infile_pen("ppb900_pen.txt");
// while (getline(infile_pen, line)) {
//     istringstream iss(line);
//     iss >> Nch >> Prb >> Err_Prb;
//     PrbTotal += Prb;
// }
// // Check before norm
// cout << "Total probability before normalisation: " << PrbTotal << endl;

// // Rewind the file pointer to the beginning
// infile_pen.clear();
// infile_pen.seekg(0, ios::beg);

// // Open the output file
// ofstream outfile_norm("normalised_ppb900_pen.txt");
// // Read the data again and write the normalised probabilities
// while (getline(infile_pen, line)) {
//     istringstream iss(line);
//     iss >> Nch >> Prb >> Err_Prb;
//     // Normalise the probability
//     normalised_Prb = Prb / PrbTotal;
// 	normalised_Err = Err_Prb / PrbTotal;
//     // Write the normalised data to the output file
//     outfile_norm << Nch << "\t" << normalised_Prb << "\t" << Err_Nch << "\t" << normalised_Err << endl;
// }

// infile_pen.close();
// outfile_norm.close();

// // Check after norm
// ifstream infile_norm("normalised_ppb900_pen.txt");
// // infile_norm.open("normalised_ppb900_pen.txt");
// Prb = 0; PrbTotal = 0;
// while (getline(infile_norm, line)) {
//     istringstream iss(line);
//     iss >> Nch >> Prb >> Err_Nch >> Err_Prb;
//     PrbTotal += Prb;
// }
// infile_norm.close();
// // Print after norm
// cout << "Total probability after normalisation: " << PrbTotal << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////