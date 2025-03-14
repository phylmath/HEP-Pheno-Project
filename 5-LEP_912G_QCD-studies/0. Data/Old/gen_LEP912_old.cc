/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and cluster particles with FastJet3
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
#include <TH1D.h>
#include "TGraph.h"
#include "TCanvas.h"
// Header
using namespace Pythia8;
using namespace std;
using namespace fjcore;
// Extras
void txtrim();

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

	TH1D *hist_nCh = new TH1D("hist_nCh", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 28, 1, 57);
	// Beautify
	// hist_exp->SetStats(kFALSE);
	hist_nCh->SetLineColor(kRed+1);
	hist_nCh->SetMarkerColor(kRed+1);
	hist_nCh->SetMarkerStyle(20);
	hist_nCh->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_nCh->GetYaxis()->SetTitle("Probability Pn");
	hist_nCh->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_nCh->GetYaxis()->SetNdivisions(510, kTRUE);
	tree->Branch("hist_nCh", &hist_nCh, "hist_nCh/H");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pythia code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 284100;

	// Define physics
	// pythia.readString("HardQCD:all = on"); 					// All hard QCD processes
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee->gamma*/Z/W->ff
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5");				// turn on Z iff (duscb)

	// Set phase space cut
	// pythia.readString("PhaseSpace:pTHatMin = 20.");

	// Define Beam params
	// pythia.readString("Beams:frameType = 1"); 				// Symmetrical beams
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	double mZ = pythia.particleData.m0(23);						// Store Z0 mass
	pythia.settings.parm("Beams:eCM", mZ);						// Set energy = mZ
	pythia.readString("PDF:lepton = off");						// Disable beam substructure

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Anti-crash
	if (!pythia.init()) return 1;

	// Define histograms
	Hist nCharge("charged had multiplicity", 28, 1, 57);
	Hist nChJets("charged jet multiplicity", 100, 0, 5);
	Hist nParton("intermediate parton multiplicity", 100, 0, 100);
	Hist nPQuark("intermediate quark multiplicity", 100, 0, 100);
	Hist nPGluon("intermediate gluon multiplicity", 100, 0, 100);
	Hist Spheric("sphericity", 100, 0., 1.);
	Hist Lineric("linearity", 100, 0., 1.);
	Hist Thrusty("thrust", 100, 0.5, 1.);
	Hist Oblatey("oblateness", 100, 0.5, 1.);
	Hist sphAxis("cos(theta)_Sphericity", 100, -1., 1.);
	Hist linAxis("cos(theta)_Linearity", 100, -1., 1.);
	Hist thrAxis("cos(theta)_Thrust", 100, -1., 1.);

	// Initialise analyses
	Sphericity sph;
	Sphericity lin(1.);
	Thrust thr;

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;
		
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		
		// Counters
		int nCh = 0;
		int nCj = 0;
		int nCp = 0;
		int nCq = 0;
		int nCg = 0;
		
		// FJ event vector
		vector<PseudoJet> particles;

		// Run through particles
		for(int j = 0; j < pythia.event.size(); j++) {
			
			// Hadron check
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron()) {
				
				////////////////////////// STORING TTREE FILES //////////////////////////
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
				/////////////////////////////////////////////////////////////////////////
				
				////////////////////////// COMPUTING NCH CURVE //////////////////////////
				// Update counter
				nCh++;
				/////////////////////////////////////////////////////////////////////////

				////////////////////////// STORING JETS PARAMS //////////////////////////
				// FJ particle vector
				PseudoJet particle(parPmx, parPmy, parPmz, parMas);
				// Storing pdgID
				particle.set_user_index(parNum);
				// Add particle to vector
				particles.push_back(particle);
				/////////////////////////////////////////////////////////////////////////

			}

			////////////////////////// COMPUTING PARTONIC NCHs //////////////////////////
			// Parton check
			if(pythia.event[j].isFinal()==false) {
				// Quark check
				if(pythia.event[j].id()==1||pythia.event[j].id()==2||pythia.event[j].id()==3||pythia.event[j].id()==4||pythia.event[j].id()==5) {
					// Update counter
					nCp++; nCq++;
				}
				// Gluon check
				if(pythia.event[j].id()==21) {
					// Update counter
					nCp++; nCg++;
				}
			}
			/////////////////////////////////////////////////////////////////////////////
		}

		////////////////////////// CLUSTERING AND PRINTING JET //////////////////////////
		// Cluster particles in the event
		double R = 0.4;															// Jet radius
		double ptmin = 5.0;														// Lower pT
		JetDefinition jet_def(antikt_algorithm, R);								// Create jet definition
		ClusterSequence cs(particles, jet_def);									// Run clustering
		vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store results
		nCj = jets.size();														// Jet multiplicity
		
		// // Print results
		// cout << "Clustering with " << jet_def.description() << endl;			// Print algo info
		// cout << "#Event " << iEvent << "\t" << "#Jet " << jets.size() << endl;	// Print jets info
		// // Run through jets
		// for (int i = 0; i < jets.size(); i++){
		
		// 	// Label columns
		// 	printf("%5s %15s %15s %15s %8s\n","jet #", "rapidity", "phi", "pt", "N");

		// 	// Count jet particles
		// 	int n_constituents = jets[i].constituents().size();

		// 	// Print jet properties
		// 	printf("%5u %15.8f %15.8f %15.8f %8u\n", i, jets[i].rap(), jets[i].phi(), jets[i].perp(), n_constituents);
			
		// 	// Define constituents vector
		// 	vector<PseudoJet> constituents = jets[i].constituents();

		// 	// Label columns
		// 	printf("%5s %15s %15s %15s %8s\n","par #", "rapidity", "phi", "pt", "ID");

		// 	// Study jet constituents
		// 	for (int j = 0; j < constituents.size(); j++){
		// 		// Define constituent vector
		// 		PseudoJet constituent = jets[i].constituents()[j];
		// 		// Print constituent properties
		// 		printf("%5u %15.8f %15.8f %15.8f %8i\n", j, constituents[j].rap(), constituents[j].phi(), constituents[j].perp(), constituent.user_index());
		// 	}
		// }
		/////////////////////////////////////////////////////////////////////////////////

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
		// Sphericity/cosθ_sphericity
		if (sph.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) sph.list();
			// Populate histogram
			Spheric.fill( sph.sphericity() );
			sphAxis.fill( sph.eventAxis(1).pz() );
			// Sanity check
			double e1 = sph.eigenValue(1);
			double e2 = sph.eigenValue(2);
			double e3 = sph.eigenValue(3);
			if (e2 > e1 || e3 > e2) cout << "eigenvalues out of order: "
			<< e1 << "  " << e2 << "  " << e3 << endl;
		  }

		// Linearity/cosθ_linearity
		if (lin.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) lin.list();
			// Populate histogram
			Lineric.fill( lin.sphericity() );
			linAxis.fill( lin.eventAxis(1).pz() );
			// Sanity check
			double e1 = lin.eigenValue(1);
			double e2 = lin.eigenValue(2);
			double e3 = lin.eigenValue(3);
			if (e2 > e1 || e3 > e2) cout << "eigenvalues out of order: "
			<< e1 << "  " << e2 << "  " << e3 << endl;
		  }

		// Thrust/cosθ_thrust/Oblateness
		if (thr.analyze( pythia.event )) {
			// // Print few info
			// if (iEvent < 3) thr.list();
			// Populate histogram
			Thrusty.fill( thr.thrust() );
			Oblatey.fill( thr.oblateness() );
			thrAxis.fill( thr.eventAxis(1).pz() );
			// Sanity check
			if ( abs(thr.eventAxis(1).pAbs() - 1.) > 1e-8
			  || abs(thr.eventAxis(2).pAbs() - 1.) > 1e-8
			  || abs(thr.eventAxis(3).pAbs() - 1.) > 1e-8
			  || abs(thr.eventAxis(1) * thr.eventAxis(2)) > 1e-8
			  || abs(thr.eventAxis(1) * thr.eventAxis(3)) > 1e-8
			  || abs(thr.eventAxis(2) * thr.eventAxis(3)) > 1e-8 ) {
			  cout << " suspicious Thrust eigenvectors " << endl;
			  thr.list();
			}
		  }

		////////////////////////// POPULATING HISTOS WITH DATA //////////////////////////
		// Populate Pythia histograms
		nCharge.fill( nCh );
		nChJets.fill( nCj );
		nParton.fill( nCp );
		nPQuark.fill( nCq );
		nPGluon.fill( nCg );

		// Populate ROOT histograms
		hist_nCh->Fill( nCh );
		tree->Fill();
		/////////////////////////////////////////////////////////////////////////////////
	}

	// Store histogram to txt
	// nCharge.table("LEP912_nCh.txt", false, true, true);
	// nChJets.table("LEP912_nCj.txt", false, true, true);
	// nParton.table("LEP912_nCp.txt", false, true, true);
	// nPQuark.table("LEP912_nCq.txt", false, true, true);
	// nPGluon.table("LEP912_nCg.txt", false, true, true);
	// Spheric.table("LEP912_sph.txt", false, true, true);
	// Lineric.table("LEP912_lin.txt", false, true, true);
	// Thrusty.table("LEP912_thr.txt", false, true, true);
	// Oblatey.table("LEP912_obl.txt", false, true, true);
	// sphAxis.table("LEP912_spA.txt", false, true, true);
	// linAxis.table("LEP912_lnA.txt", false, true, true);
	// thrAxis.table("LEP912_thA.txt", false, true, true);

	// Display statistics
	// pythia.stat();

	// Display histogram
	// cout << nCharge;
	// cout << nChJets;
	// cout << nParton;
	// cout << nPQuark;
	// cout << nPGluon;
	// cout << Spheric;
	// cout << Lineric;
	// cout << Thrusty;
	// cout << Oblatey;
	// cout << sphAxis;
	// cout << linAxis;
	// cout << thrAxis;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TXT conditioning
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Set reading
	string line;
    // Open new file
    ofstream otfile_pen;
    otfile_pen.open("LEP912_nCh_trim.txt");
	// Open txt file
	ifstream infile_pen("LEP912_nCh.txt");
	// Buffers
	double Nch, Err_Nch=0; float Prb, Err_Prb;
	// Read through txt
	while (getline(infile_pen, line)) {
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Write new data
		otfile_pen << std::fixed << std::setprecision(0) << Nch << "\t"
					<< std::scientific << std::setprecision(2) << Prb << "\t"
					<< std::fixed << std::setprecision(0) << Err_Nch << "\t"
					<< std::scientific << std::setprecision(2) << Err_Prb
					<< endl; 
	}
	// Close file
	infile_pen.close();
	otfile_pen.close();

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

// Function to condition txt file format
void txtrim(string name){

    // Open new file
    ofstream otfile;
    otfile.open(name+"_trim.txt");
	// Open txt file
	ifstream infile(name+".txt");

	// Buffers
	double Nch, Err_Nch=0; float Prb, Err_Prb;

	// Set reading
	string line;
	// Read through txt
	while (getline(infile, line)) {
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Write new data
		otfile << std::fixed << std::setprecision(0) << Nch << "\t"
				<< std::scientific << std::setprecision(2) << Prb << "\t"
				<< std::fixed << std::setprecision(0) << Err_Nch << "\t"
				<< std::scientific << std::setprecision(2) << Err_Prb
				<< endl; 
	}
	// Close file
	infile.close();
	otfile.close();

}