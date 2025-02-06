/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plugins
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void plt_SPS900()
{

    // Create a histogram to store the data
    TH1D *hist = new TH1D("hist", "Multiplicity Distribution", 55, 0, 120);

    // Open the input file
    ifstream infile("ppbar_900.txt");

    // Read data from the file and fill the histogram
    string line;
    int N;
    double Prob, ErrN, ErrProb;
    while (getline(infile, line)) {
        istringstream iss(line);
        iss >> N >> Prob >> ErrN >> ErrProb;
        hist->SetBinContent(N, Prob);
        hist->SetBinError(N, ErrProb);
    }

    infile.close();

    // Create a canvas and draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Multiplicity Distribution", 800, 600);
    hist->Draw();
    c1->Update();

}


	// // Read output file
	// TFile *input = new TFile("out_SPS900.root", "read");

	// // Import tree file
	// TTree *tree = (TTree*)input->Get("tree");

	// // Intialise tree branch vars
	// int evenN, evenS, partN, partI;
	// double partM, partPx, partPy, partPz, partPt, partEta, partPhi;

	// // Define tree branch data types
	// tree->Branch("evenN", &evenN, "evenN/I");
	// tree->Branch("evenS", &evenS, "evenS/I");
	// tree->Branch("partN", &partN, "partN/I");
	// tree->Branch("partI", &partI, "partI/I");
	// tree->Branch("partM", &partM, "partM/D");
	// tree->Branch("partPx", &partPx, "partPx/D");
	// tree->Branch("partPy", &partPy, "partPy/D");
	// tree->Branch("partPz", &partPz, "partPz/D");
	// tree->Branch("partPt", &partPt, "partPt/D");
	// tree->Branch("partEta", &partEta, "partEta/D");
	// tree->Branch("partPhi", &partPhi, "partPhi/D");

	// // Loop #iteration
	// int entries = tree->GetEntries();

	// // Charged mult var
	// int Nch = 0;

	// // Define histogram
	// TH1D* hist_mult = new TH1D("hist_mult", "Charged Multiplicity", 100, 0, 100);

	// // Read branches
	// for (int i = 0; i < sizeof(evenN); i++){

	// 	// Load branch
	// 	tree->GetEntry(i);

	// 	//  Nch counter
	// 	Nch = 0;
	// 	for (int j = 0; j < evenS ; j++)
	// 		Nch++;

	// 	// Add to hist
	// 	hist_mult->Fill(Nch);

	// 	cout << "Event: " << i << "	Nch: " << Nch << endl;

	// }

	// // Create a canvas and draw the histogram
	// TCanvas* c_mult = new TCanvas("c_mult", "Charged Multiplicity", 800, 600);
	// hist_mult->Draw("hist_mult");


