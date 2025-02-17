/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by FastJet from TTree file produced by Pythia 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plugins
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH3D.h>
#include <TCanvas.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void plot_LEPep91GeV()
{	
	// Define histogram
	TH3D* hist_jet = new TH3D("hist_jet", "Jet pT vs. eta vs. phi", 200, -6, 6, 200, -6, 6, 200, 0, 25);
	// Beautify
	hist_jet->GetXaxis()->SetTitle("#eta");
	hist_jet->GetYaxis()->SetTitle("#phi");
	hist_jet->GetZaxis()->SetTitle("pT [GeV]");
	hist_jet->SetTitle("Jet pT vs. eta vs. phi");

	// Read output file
	TFile *input = new TFile("jout_LEPep91GeV.root", "read");

	// Import tree file
	TTree *jetree = (TTree*)input->Get("jetree");

	// Branch params
	double eta, phi, pt, y;

	// Define branches
	jetree->Branch("pt", &pt, "pt/D");				// transverse mom
	jetree->Branch("eta", &eta, "eta/D");			// pseudorapidity
	jetree->Branch("phi", &phi, "phi/D");			// phi trajectory
	jetree->Branch("y", &y, "y/D");					// rapidity

	// Loop #iteration
	int entries = jetree->GetEntries();

	// Read branches
	for (int i = 0; i < entries; i++)
	{
		// Load branch
		jetree->GetEntry(i);
		// Plot jets
		jetree->Draw("eta:phi:pt>>hist_jet", "", "");
	}

	// Define canvas object
	TCanvas *c_jet = new TCanvas("c_jet", "Jet Plot", 800, 600);

	// Draw plots
	hist_jet->Draw("hist_jet");

}


// void plot_LEPep91GeV()
// {
// 	// Define Histogram
// 	TH3D* hist_jet = new TH3D("hist_jet", "Jet pT vs. eta vs. phi", 100, -6, 6, 100, -6, 6, 100, 0, 25);

// 	// Read output file
// 	TFile *input = new TFile("jout_LEPep91GeV.root", "read");

// 	// Import tree file
// 	TTree *jetree = (TTree*)input->Get("jetree");

// 	// Branch params
// 	double eta, phi, pt;

// 	// Define branches
// 	jetree->Branch("pt", &pt, "pt/D");				// particle pt
// 	jetree->Branch("eta", &eta, "eta/D");			// eta trajectory
// 	jetree->Branch("phi", &phi, "phi/D");			// phi trajectory

// 	// Loop #iteration
// 	int entries = jetree->GetEntries();

// 	// Read branches
// 	for (int i = 0; i < entries; i++)
// 	{
// 		// Load branch
// 		jetree->GetEntry(i);
// 		// Plot jets
// 		hist_jet->Fill(eta, phi, pt);
// 	}

// 	// Define canvas object
// 	TCanvas *c_jet = new TCanvas();

// 	// Draw plots
// 	hist_jet->Draw("hist_jet");
// 	c_jet->Update();

// }