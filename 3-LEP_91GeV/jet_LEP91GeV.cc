/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to construct jets of particles from TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plugins
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
using namespace fastjet;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TTree->FastJet
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	// Read output file
	TFile *input = new TFile("out_LEPep91GeV.root", "read");

	// Import tree file
	TTree *tree = (TTree*)input->Get("tree");

	// Branch params
	int id, event, size, no;
	double m, px, py, pz, eta, phi, pt, y;

	// Define branches
	tree->SetBranchAddress("id", &id);			// particle id
	tree->SetBranchAddress("m", &m);			// particle m
	tree->SetBranchAddress("px", &px);			// particle px
	tree->SetBranchAddress("py", &py);			// particle py
	tree->SetBranchAddress("pz", &pz);			// particle pz
	tree->SetBranchAddress("pt", &pt);			// particle pt
	tree->SetBranchAddress("eta", &eta);		// eta trajectory
	tree->SetBranchAddress("phi", &phi);		// phi trajectory

	// Loop #iteration
	int entries = tree->GetEntries();

	// Create a vector of PseudoJets
	vector<PseudoJet> particles;

	// Read branches
	for (int i = 0; i < entries; i++)
	{
		// Load branch
		tree->GetEntry(i);
		// Particle vector
		PseudoJet particle(px, py, pz, m);
		// Storing pdgID
		particle.set_user_index(id);
		// Add particle to vector
		particles.push_back(particle);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastJet analysis
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Set jet radius
	double R = 0.4;
	
	// Cluster with anti-kT
	JetDefinition jet_def(antikt_algorithm, R);
	
	// Run clustering, store results
	ClusterSequence cs(particles, jet_def);
	vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print results
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Print clustering info
	cout << "Clustering with " << jet_def.description() << endl;
	
	// Study jets
	for (int i = 0; i < jets.size(); i++) 
	{
		// Print jet properties
		cout << "jet " << i << ": "<< jets[i].pt() << " " << jets[i].rap() << " " << jets[i].phi() << endl;
		// Define constituents vector
		vector<PseudoJet> constituents = jets[i].constituents();
		// Study jet constituents
		for (int j = 0; j < constituents.size(); j++)
		{
			// Define constituent vector
			PseudoJet constituent = jets[i].constituents()[j];
			// Print constituent properties
			cout << "const. " << j << "	:	" << constituent.user_index() << "	" << constituents[j].pt() << endl;
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastJet->TTree
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("jout_LEPep91GeV.root", "recreate");
	// Permission check
	if (!output->IsOpen()) {
		std::cerr << "Error opening output file!" << std::endl;
		return 1;
	}

	// Define tree
	TTree *jetree = new TTree("jetree", "Jet Information");

	// Define branches
	jetree->Branch("pt", &pt, "pt/D");				// transverse mom
	jetree->Branch("eta", &eta, "eta/D");			// pseudorapidity
	jetree->Branch("phi", &phi, "phi/D");			// phi trajectory
	jetree->Branch("y", &y, "y/D");					// rapidity

	// Study jets
	for (int i = 0; i < jets.size(); i++) 
	{
		// Store jet data
		pt = jets[i].pt();
		eta = jets[i].eta();
		phi = jets[i].phi();
		// Populate branches
		jetree->Fill();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ending
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// write file
	output->Write();
	// Close file
	output->Close();
	// Terminate
	return 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}