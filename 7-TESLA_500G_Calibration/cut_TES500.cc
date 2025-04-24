/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to perform cuts on generated events and cluster particles with FastJet3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// Pythia
#include "Pythia8/Pythia.h"
#include "Pythia8/Basics.h"
#include "Pythia8/Event.h"
// Fastjet
#include "fastjet/ClusterSequence.hh"
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TList.h"
#include "TLorentzVector.h"
// Header
using namespace Pythia8;
using namespace std;
using namespace fastjet;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file, Read TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	// TFile *input = new TFile("gen_TES500_noR.root", "READ");
	// TFile *input = new TFile("gen_TES500_wiR.root", "READ");
	// TFile *input = new TFile("gen_TES50t_noR.root", "READ");
	TFile *input = new TFile("gen_TES50t_wiR.root", "READ");
	// TFile *input = new TFile("gen_LEP912_noR.root", "READ");
	// TFile *input = new TFile("gen_LEP912_wiR.root", "READ");
	
	// Read TTree
	TTree *itree = (TTree*)input->Get("tree_raw");

	// Define file
	// TFile *output = new TFile("cut_TES500_noR.root", "RECREATE");
	// TFile *output = new TFile("cut_TES500_wiR.root", "RECREATE");
	// TFile *output = new TFile("cut_TES50t_noR.root", "RECREATE");
	TFile *output = new TFile("cut_TES50t_wiR.root", "RECREATE");
	// TFile *output = new TFile("cut_LEP912_noR.root", "RECREATE");
	// TFile *output = new TFile("cut_LEP912_wiR.root", "RECREATE");
	
	// Define tree
	TTree *otree = new TTree("tree_cut", "Cut Pythia data");

	// Intialise vecs
	vector<int> *eveNum=nullptr, *eveSiz=nullptr, *eveCod=nullptr, *parNum=nullptr, *parPdg=nullptr;
	vector<float> *eveThr=nullptr, *eveTax=nullptr, *eveSph=nullptr, *eveSax=nullptr, *eveSpr=nullptr, \
	 *sigmaT=nullptr, *parEto=nullptr, *parEtt=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr;

	// Set branches
	itree->SetBranchAddress("sigmaT", &sigmaT);											// Total sigma
	itree->SetBranchAddress("eveNum", &eveNum);											// Event number
	itree->SetBranchAddress("eveSiz", &eveSiz);											// Event size
	itree->SetBranchAddress("eveCod", &eveCod);											// Event process
	itree->SetBranchAddress("eveSpr", &eveSpr);											// Event √s'
	itree->SetBranchAddress("eveSph", &eveSph);											// Event spheric
	itree->SetBranchAddress("eveSax", &eveSax);											// Event sphaxis
	itree->SetBranchAddress("eveThr", &eveThr);											// Event thrust
	itree->SetBranchAddress("eveTax", &eveTax);											// Event thraxis
	itree->SetBranchAddress("parNum", &parNum);											// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);											// Parts pdg id
	itree->SetBranchAddress("parEto", &parEto);											// Parts energy
	itree->SetBranchAddress("parEtt", &parEtt);											// Parts energy
	itree->SetBranchAddress("parPmx", &parPmx);											// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);											// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);											// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Esprime_Zq = new TH1F("hist_Esprime_Zq", "Reduced centre-of-mass", 108, -1, 541);
	hist_Esprime_Zq->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_Zq->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_Zq", &hist_Esprime_Zq, "hist_Esprime_Zq");
	
	TH1F *hist_Esprime_tt = new TH1F("hist_Esprime_tt", "Reduced centre-of-mass", 108, -1, 541);
	hist_Esprime_tt->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_tt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_tt", &hist_Esprime_tt, "hist_Esprime_tt");

	TH1F *hist_Esprime_WW = new TH1F("hist_Esprime_WW", "Reduced centre-of-mass", 108, -1, 541);
	hist_Esprime_WW->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_WW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_WW", &hist_Esprime_WW, "hist_Esprime_WW");

	TH1F *hist_Esprime_ZZ = new TH1F("hist_Esprime_ZZ", "Reduced centre-of-mass", 108, -1, 541);
	hist_Esprime_ZZ->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_ZZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_ZZ", &hist_Esprime_ZZ, "hist_Esprime_ZZ");

	TH1F *hist_nHadron = new TH1F("hist_nHadron", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron", &hist_nHadron, "hist_nHadron");

	TH1F *hist_nHadron_000 = new TH1F("hist_nHadron_000", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_000->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_000->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_000", &hist_nHadron_000, "hist_nHadron_000");

	TH1F *hist_nHadron_300 = new TH1F("hist_nHadron_300", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_300->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_300->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_300", &hist_nHadron_300, "hist_nHadron_300");

	TH1F *hist_nHadron_425 = new TH1F("hist_nHadron_425", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_425->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_425->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_425", &hist_nHadron_425, "hist_nHadron_425");

	TH1F *hist_nHadron_500 = new TH1F("hist_nHadron_500", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_500->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_500->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_500", &hist_nHadron_500, "hist_nHadron_500");

	TH1F *hist_nJetTot = new TH1F("hist_nJetTot", "Jet Multiplicity", 10, 0, 11);
	hist_nJetTot->GetXaxis()->SetTitle("N_{JETS}>");
	hist_nJetTot->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot", &hist_nJetTot, "hist_nJetTot");

	float xbin[] = {0.0E+00,1.0E-02,2.0E-02,3.0E-02,4.0E-02,5.0E-02,7.0E-02,9.0E-02,1.2E-01,1.5E-01,2.2E-01,3.0E-01,4.0E-01};
	TH1F *hist_ThrPyth = new TH1F("hist_ThrPyth", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	// TH1F *hist_ThrPyth = new TH1F("hist_ThrPyth", "Thrust", 100, 0, 0.4);
	hist_ThrPyth->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth", &hist_ThrPyth, "hist_ThrPyth");

	TH1F *hist_ThrPyth_000 = new TH1F("hist_ThrPyth_000", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_000->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_000->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth_000", &hist_ThrPyth_000, "hist_ThrPyth_000");

	TH1F *hist_ThrPyth_300 = new TH1F("hist_ThrPyth_300", "vThrust", 100, 0, 0.4);
	hist_ThrPyth_300->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_300->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth_300", &hist_ThrPyth_300, "hist_ThrPyth_300");

	TH1F *hist_ThrPyth_425 = new TH1F("hist_ThrPyth_425", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_425->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_425->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth_425", &hist_ThrPyth_425, "hist_ThrPyth_425");

	TH1F *hist_ThrPyth_500 = new TH1F("hist_ThrPyth_500", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_500->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_500->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth_500", &hist_ThrPyth_500, "hist_ThrPyth_500");

	TH1F *hist_TaxPyth = new TH1F("hist_TaxPyth", "Thrust axis", 100, -1., 1.);
	hist_TaxPyth->GetXaxis()->SetTitle("cosΘ_{Thrust}");
	hist_TaxPyth->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_TaxPyth", &hist_TaxPyth, "hist_TaxPyth");

	TH1F *hist_SphPyth = new TH1F("hist_SphPyth", "Sphericity", 100, 0, 1.0);
	hist_SphPyth->GetXaxis()->SetTitle("S");
	hist_SphPyth->GetYaxis()->SetTitle("P(S)");
	otree->Branch("hist_SphPyth", &hist_SphPyth, "hist_SphPyth");

	TH1F *hist_SaxPyth = new TH1F("hist_SaxPyth", "Thrust axis", 100, -1., 1.);
	hist_SaxPyth->GetXaxis()->SetTitle("cosΘ_{Sphericity}");
	hist_SaxPyth->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_SaxPyth", &hist_SaxPyth, "hist_SaxPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define
	int nCh=0, nCj=0, nParts=0, Pdg;
	float Pmx, Pmy, Pmz, Eto, Ett, Thr, Tax, Sph, Sax, Spr;
	
	Pythia8::Thrust thr;
	Pythia8::Event event;

	// FastJet params
	double R = 0.6, ptmin = 5.0;
	vector<fastjet::PseudoJet> particles;
	
	// Run through events
	for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {

		// Access
		itree->GetEntry(iEvent);

		// Reset
		event.init(); event.clear();

		// Run through particles
		for(int jParts = 0; jParts < (*eveSiz)[0]; jParts++) {
			
			////////////////////////// READING PARTS DATA ///////////////////////////////////////////////////
			Pdg = (*parPdg)[jParts]; Eto = (*parEto)[jParts]; Ett = (*parEtt)[jParts];
			Pmx = (*parPmx)[jParts]; Pmy = (*parPmy)[jParts]; Pmz = (*parPmz)[jParts];
			/////////////////////////////////////////////////////////////////////////////////////////////////
			
			Pythia8::Vec4 Pm4(Pmx, Pmy, Pmz, Eto);
 			event.append(Pdg, 1, 0, 0, Pm4);

			////////////////////////// STORING JETS PARAMS //////////////////////////////////////////////////
			fastjet::PseudoJet particle(Pmx,Pmy,Pmz,Eto);								// Particle vector
			particle.set_user_index(Pdg);												// Set particle id
			particles.push_back(particle);												// Add to particles
			/////////////////////////////////////////////////////////////////////////////////////////////////
			
			////////////////////////// COMPUTING NCH CURVE //////////////////////////////////////////////////
			nCh++;																		// Charged hadrons
			/////////////////////////////////////////////////////////////////////////////////////////////////

		}
		
		////////////////////////// CLUSTERING JET PARTICLES /////////////////////////////////////////////////
		fastjet::JetDefinition jet_def(antikt_algorithm, R);							// Jet definition
		fastjet::ClusterSequence cs(particles, jet_def);								// Run clustering
		vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store jets
		nCj = jets.size();																// Jet multiplicity
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////// PRINTING CLUSTERED INFO //////////////////////////////////////////////////

		cout << "Event " << iEvent << " has " << particles.size() << " particles" << " / " << jets.size() << " jets" << endl;

		// Run through jets
		for (int iJet = 0; iJet < jets.size(); iJet++) {
			
			vector<fastjet::PseudoJet> constituents = jets[iJet].constituents();		// Jet constituents		
			// cout << "Jet#" << iJet << " has " << constituents.size() << endl;		// Print info

			// Run through constituents
			for (int jJet = 0; jJet < constituents.size(); jJet++) {
				
				fastjet::PseudoJet constituent = jets[iJet].constituents()[jJet];		// Jet constituent
				// cout << jJet << "\t" << constituents[jJet].user_index() << endl;		// Print info

			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////////////////////////

		// No cut on √s'
		if ((*eveSpr)[0] >= 0){
			hist_ThrPyth->Fill((*eveThr)[0]);
			hist_TaxPyth->Fill((*eveTax)[0]);
			hist_SphPyth->Fill((*eveSph)[0]);
			hist_SaxPyth->Fill((*eveSax)[0]);
			hist_nHadron->Fill(nCh);
			hist_nJetTot->Fill(nCj);
		}
		// Cut on √s'
		if ((*eveSpr)[0] >= 0) {
			hist_ThrPyth_000->Fill((*eveThr)[0]);
			hist_nHadron_000->Fill(nCh);
		}
		// Cut on √s'
		if ((*eveSpr)[0] >= 300) {
			hist_ThrPyth_300->Fill((*eveThr)[0]);
			hist_nHadron_300->Fill(nCh);
		}
		// Cut on √s'
		if ((*eveSpr)[0] >= 425) {
			hist_ThrPyth_425->Fill((*eveThr)[0]);
			hist_nHadron_425->Fill(nCh);
		}
		// Cut on √s'
		if ((*eveSpr)[0] >= 500) {
			hist_ThrPyth_500->Fill((*eveThr)[0]);
			hist_nHadron_500->Fill(nCh);
		}

		// Store √s' according to processes
		if ((*eveCod)[0] == 221) hist_Esprime_Zq->Fill((*eveSpr)[0]);
		if ((*eveCod)[0] == 231) hist_Esprime_ZZ->Fill((*eveSpr)[0]);
		if ((*eveCod)[0] == 233) hist_Esprime_WW->Fill((*eveSpr)[0]);
		if ((*eveCod)[0] == 604) hist_Esprime_tt->Fill((*eveSpr)[0]);

		// Reset
		nCh=0; particles.clear(); jets.clear();
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// KNO params
	double histNch=0.0, histMax=0.0, histMin=0.0, histBin=0.0; int numBin=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Axes params
	histNch = hist_nHadron->GetMean();
	histMax = hist_nHadron->GetXaxis()->GetXmax()/histNch;
	histMin = hist_nHadron->GetXaxis()->GetXmin()/histNch;
	histBin = hist_nHadron->GetBinWidth(10)/histNch;
	numBin = static_cast<int>(ceil(histMax/histBin));
	// KNO histogram
	TH1D* KNOO_nHadron = new TH1D("KNOO_nHadron", "KNO Charged Hadron Multiplicity", numBin, 0, histMax);
	// Beautify
	KNOO_nHadron->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
	KNOO_nHadron->GetYaxis()->SetTitle("P(N_{CH})x<N_{CH}>");
	// Fill histogram
	for (int bin = 1; bin <= hist_nHadron->GetNbinsX(); ++bin) {
	double nCh = hist_nHadron->GetXaxis()->GetBinCenter(bin);
	double binContent = hist_nHadron->GetBinContent(bin);
	double scaledNch = nCh / histNch;
	double scaledContent = hist_nHadron->GetBinContent(bin) * histNch;
	double scaledError = hist_nHadron->GetBinError(bin) * histNch;
	KNOO_nHadron->Fill(scaledNch, scaledContent);
	KNOO_nHadron->SetBinError(KNOO_nHadron->FindBin(scaledNch), scaledError);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	output->Write();
	output->Close();
	input->Close();
	delete output;
	delete input;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Terminate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	return 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}