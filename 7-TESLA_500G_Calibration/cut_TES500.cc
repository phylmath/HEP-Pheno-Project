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

// 
TH1F* ComputeKNOScaling(TH1F* inputHist, const std::string& outputName) {
    // Axes params
	double histNch = inputHist->GetMean();
    double histMax = inputHist->GetXaxis()->GetXmax()/histNch;
    double histMin = inputHist->GetXaxis()->GetXmin()/histNch;
    double histBin = inputHist->GetBinWidth(10)/histNch;
    int numBin = static_cast<int>(ceil(histMax/histBin));
    // KNO histogram
    TH1F* knoHist = new TH1F(outputName.c_str(), "KNO Charged Multiplicity", numBin, 0, histMax);
	// Beautify
    knoHist->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
    knoHist->GetYaxis()->SetTitle("P(N_{CH}) x <N_{CH}>");
    // Fill histogram
    for (int bin = 1; bin <= inputHist->GetNbinsX(); ++bin) {
        double nCh = inputHist->GetXaxis()->GetBinCenter(bin);
        double binContent = inputHist->GetBinContent(bin);
        double scaledNch = nCh / histNch;
        double scaledCon = inputHist->GetBinContent(bin)*histNch;
        double scaledErr = inputHist->GetBinError(bin)*histNch;
        knoHist->Fill(scaledNch, scaledCon);
        knoHist->SetBinError(knoHist->FindBin(scaledNch), scaledErr);
    }

    return knoHist;
}

// Divide histograms by bin width
void NormalizeByBinWidth(TH1* hist) {
    for (int i = 1; i <= hist->GetNbinsX(); ++i) {
        double content = hist->GetBinContent(i);
        double error = hist->GetBinError(i);
        double width = hist->GetBinWidth(i);
        if (width > 0) {
            hist->SetBinContent(i, content/width);
            hist->SetBinError(i, error/width);
        }
    }
}

// Import data, perform cuts, store data
void applyCuts( const std::string& inputFileName, const std::string& outputFileName ) {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file, Read TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// Read ROOT
	TFile *input = new TFile(inputFileName.c_str(), "READ");
	// Read TTree
	TTree *itree = (TTree*)input->Get("tree_raw");

	// Define file
	TFile *output = new TFile(outputFileName.c_str(), "RECREATE");
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

	TH1F *hist_Esprime_ZZWWtt = new TH1F("hist_Esprime_ZZWWtt", "Reduced centre-of-mass", 108, -1, 541);
	hist_Esprime_ZZWWtt->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_ZZWWtt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_ZZWWtt", &hist_Esprime_ZZWWtt, "hist_Esprime_ZZWWtt");

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nHadron_Zq = new TH1F("hist_nHadron_Zq", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_Zq->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_Zq->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_Zq", &hist_nHadron_Zq, "hist_nHadron_Zq");

	TH1F *hist_nHadron_ZZ = new TH1F("hist_nHadron_ZZ", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_ZZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_ZZ->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_ZZ", &hist_nHadron_ZZ, "hist_nHadron_ZZ");

	TH1F *hist_nHadron_WW = new TH1F("hist_nHadron_WW", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_WW->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_WW->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_WW", &hist_nHadron_WW, "hist_nHadron_WW");

	TH1F *hist_nHadron_tt = new TH1F("hist_nHadron_tt", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_tt->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_tt->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_tt", &hist_nHadron_tt, "hist_nHadron_tt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nJetTot = new TH1F("hist_nJetTot", "Jet Multiplicity", 100, -1, 20);
	hist_nJetTot->GetXaxis()->SetTitle("N_{JETS}");
	hist_nJetTot->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot", &hist_nJetTot, "hist_nJetTot");

	TH1F *hist_nJetTot_Zq = new TH1F("hist_nJetTot_Zq", "Jet Multiplicity", 100, -1, 20);
	hist_nJetTot_Zq->GetXaxis()->SetTitle("N_{JETS}");
	hist_nJetTot_Zq->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot_Zq", &hist_nJetTot_Zq, "hist_nJetTot_Zq");

	TH1F *hist_nJetTot_ZZ = new TH1F("hist_nJetTot_ZZ", "Jet Multiplicity", 100, -1, 20);
	hist_nJetTot_ZZ->GetXaxis()->SetTitle("N_{JETS}");
	hist_nJetTot_ZZ->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot_ZZ", &hist_nJetTot_ZZ, "hist_nJetTot_ZZ");

	TH1F *hist_nJetTot_WW = new TH1F("hist_nJetTot_WW", "Jet Multiplicity", 100, -1, 20);
	hist_nJetTot_WW->GetXaxis()->SetTitle("N_{JETS}");
	hist_nJetTot_WW->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot_WW", &hist_nJetTot_WW, "hist_nJetTot_WW");

	TH1F *hist_nJetTot_tt = new TH1F("hist_nJetTot_tt", "Jet Multiplicity", 100, -1, 20);
	hist_nJetTot_tt->GetXaxis()->SetTitle("N_{JETS}");
	hist_nJetTot_tt->GetYaxis()->SetTitle("P(N_{JETS})");
	otree->Branch("hist_nJetTot_tt", &hist_nJetTot_tt, "hist_nJetTot_tt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float xbin[] = {0.0E+00,1.0E-02,2.0E-02,3.0E-02,4.0E-02,5.0E-02,7.0E-02,9.0E-02,1.2E-01,1.5E-01,2.2E-01,3.0E-01,4.0E-01};
	
	TH1F *hist_ThrPyth = new TH1F("hist_ThrPyth", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth", &hist_ThrPyth, "hist_ThrPyth");

	TH1F *hist_ThrPyth_000 = new TH1F("hist_ThrPyth_000", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_000->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_000->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPyth_000", &hist_ThrPyth_000, "hist_ThrPyth_000");

	TH1F *hist_ThrPyth_300 = new TH1F("hist_ThrPyth_300", "Inverse Thrust", 100, 0, 0.4);
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
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPy99 = new TH1F("hist_ThrPy99", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPy99", &hist_ThrPy99, "hist_ThrPy99");

	TH1F *hist_ThrPy99_000 = new TH1F("hist_ThrPy99_000", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_000->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_000->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPy99_000", &hist_ThrPy99_000, "hist_ThrPy99_000");

	TH1F *hist_ThrPy99_300 = new TH1F("hist_ThrPy99_300", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_300->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_300->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPy99_300", &hist_ThrPy99_300, "hist_ThrPy99_300");

	TH1F *hist_ThrPy99_425 = new TH1F("hist_ThrPy99_425", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_425->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_425->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPy99_425", &hist_ThrPy99_425, "hist_ThrPy99_425");

	TH1F *hist_ThrPy99_500 = new TH1F("hist_ThrPy99_500", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_500->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_500->GetYaxis()->SetTitle("P(1-T)");
	otree->Branch("hist_ThrPy99_500", &hist_ThrPy99_500, "hist_ThrPy99_500");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_Zq = new TH1F("hist_ThrPyth_Zq", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_Zq->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_Zq->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPyth_Zq", &hist_ThrPyth_Zq, "hist_ThrPyth_Zq");

	TH1F *hist_ThrPyth_tt = new TH1F("hist_ThrPyth_tt", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_tt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_tt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPyth_tt", &hist_ThrPyth_tt, "hist_ThrPyth_tt");

	TH1F *hist_ThrPyth_WW = new TH1F("hist_ThrPyth_WW", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_WW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_WW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPyth_WW", &hist_ThrPyth_WW, "hist_ThrPyth_WW");

	TH1F *hist_ThrPyth_ZZ = new TH1F("hist_ThrPyth_ZZ", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_ZZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_ZZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPyth_ZZ", &hist_ThrPyth_ZZ, "hist_ThrPyth_ZZ");

	TH1F *hist_ThrPyth_Zt = new TH1F("hist_ThrPyth_Zt", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_Zt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_Zt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPyth_Zt", &hist_ThrPyth_Zt, "hist_ThrPyth_Zt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPy99_Zq = new TH1F("hist_ThrPy99_Zq", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_Zq->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_Zq->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPy99_Zq", &hist_ThrPy99_Zq, "hist_ThrPy99_Zq");

	TH1F *hist_ThrPy99_tt = new TH1F("hist_ThrPy99_tt", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_tt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_tt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPy99_tt", &hist_ThrPy99_tt, "hist_ThrPy99_tt");

	TH1F *hist_ThrPy99_WW = new TH1F("hist_ThrPy99_WW", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_WW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_WW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPy99_WW", &hist_ThrPy99_WW, "hist_ThrPy99_WW");

	TH1F *hist_ThrPy99_ZZ = new TH1F("hist_ThrPy99_ZZ", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_ZZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_ZZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPy99_ZZ", &hist_ThrPy99_ZZ, "hist_ThrPy99_ZZ");

	TH1F *hist_ThrPy99_Zt = new TH1F("hist_ThrPy99_Zt", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_Zt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_Zt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_ThrPy99_Zt", &hist_ThrPy99_Zt, "hist_ThrPy99_Zt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	int nCh=0, nCj=0, nParts=0, Pdg=0, Rad_000=0, Rad_300=0, Rad_425=0, Rad_500=0;
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

		// cout << "Event " << iEvent << " has " << particles.size() << " particles" << " / " << jets.size() << " jets" << endl;

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

		// 0% cut on √s'
		if ((*eveSpr)[0] >= 0){
			
			Rad_000++;
			hist_ThrPyth->Fill((*eveThr)[0]);
			hist_TaxPyth->Fill((*eveTax)[0]);
			hist_SphPyth->Fill((*eveSph)[0]);
			hist_SaxPyth->Fill((*eveSax)[0]);
			hist_nHadron->Fill(nCh);
			hist_nJetTot->Fill(nCj);
			
			hist_nHadron_000->Fill(nCh);
			hist_ThrPyth_000->Fill((*eveThr)[0]); hist_ThrPy99_000->Fill((*eveThr)[0]);

			// Process cuts
			if ((*eveCod)[0] == 221) {
				hist_Esprime_Zq->Fill((*eveSpr)[0]);
				hist_nHadron_Zq->Fill(nCh);
				hist_nJetTot_Zq->Fill(nCj);
			}
			if ((*eveCod)[0] == 231) {
				hist_Esprime_ZZ->Fill((*eveSpr)[0]);
				hist_nHadron_ZZ->Fill(nCh);
				hist_nJetTot_ZZ->Fill(nCj);
			}
			if ((*eveCod)[0] == 233) {
				hist_Esprime_WW->Fill((*eveSpr)[0]);
				hist_nHadron_WW->Fill(nCh);
				hist_nJetTot_WW->Fill(nCj);
			}
			if ((*eveCod)[0] == 604) {
				hist_Esprime_tt->Fill((*eveSpr)[0]);
				hist_nHadron_tt->Fill(nCh);
				hist_nJetTot_tt->Fill(nCj);
			} 

		}

		// 60% cut on √s'
		if ((*eveSpr)[0] >= 300) {
			Rad_300++;
			hist_ThrPyth_300->Fill((*eveThr)[0]); hist_ThrPy99_300->Fill((*eveThr)[0]);
			hist_nHadron_300->Fill(nCh);
		}

		// 85% cut on √s'
		if ((*eveSpr)[0] >= 425) {
			Rad_425++;
			hist_ThrPyth_425->Fill((*eveThr)[0]); hist_ThrPy99_425->Fill((*eveThr)[0]);
			hist_nHadron_425->Fill(nCh);
		}

		// 100% cut on √s'
		if ((*eveSpr)[0] >= 500) {
			Rad_500++;
			hist_ThrPyth_500->Fill((*eveThr)[0]); hist_ThrPy99_500->Fill((*eveThr)[0]);
			hist_nHadron_500->Fill(nCh);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		if ((*eveCod)[0] == 221) {
			hist_ThrPyth_Zq->Fill((*eveThr)[0]); hist_ThrPy99_Zq->Fill((*eveThr)[0]);
			hist_ThrPyth_Zt->Fill((*eveThr)[0]); hist_ThrPy99_Zt->Fill((*eveThr)[0]);			
		}
		if ((*eveCod)[0] == 231) {
			hist_ThrPyth_ZZ->Fill((*eveThr)[0]); hist_ThrPy99_ZZ->Fill((*eveThr)[0]);
		}
		if ((*eveCod)[0] == 233) {
			hist_ThrPyth_WW->Fill((*eveThr)[0]); hist_ThrPy99_WW->Fill((*eveThr)[0]);
		}
		if ((*eveCod)[0] == 604) {
			hist_ThrPyth_tt->Fill((*eveThr)[0]); hist_ThrPy99_tt->Fill((*eveThr)[0]);
			hist_ThrPyth_Zt->Fill((*eveThr)[0]); hist_ThrPy99_Zt->Fill((*eveThr)[0]);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Reset
		nCh=0; nCj=0; particles.clear(); jets.clear();
		/////////////////////////////////////////////////////////////////////////////////////////////////////

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Print info
	cout << "----------------------------------------" << endl;
	cout << "Radiative events < 000 GeV : " << Rad_000 << endl;
	cout << "Radiative events < 300 GeV : " << Rad_300 << endl;
	cout << "Radiative events < 425 GeV : " << Rad_425 << endl;
	cout << "Radiative events < 500 GeV : " << Rad_500 << endl;
	cout << "----------------------------------------" << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* KNOO_nHadron = ComputeKNOScaling(hist_nHadron_000, "KNOO_nHadron");
	TH1F* KNOO_nHadron_Zq = ComputeKNOScaling(hist_nHadron_Zq, "KNOO_nHadron_Zq");
	TH1F* KNOO_nHadron_ZZ = ComputeKNOScaling(hist_nHadron_ZZ, "KNOO_nHadron_ZZ");
	TH1F* KNOO_nHadron_WW = ComputeKNOScaling(hist_nHadron_WW, "KNOO_nHadron_WW");
	TH1F* KNOO_nHadron_tt = ComputeKNOScaling(hist_nHadron_tt, "KNOO_nHadron_tt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bin width normalising
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	NormalizeByBinWidth(hist_ThrPy99);
	NormalizeByBinWidth(hist_ThrPy99_000);
	NormalizeByBinWidth(hist_ThrPy99_300);
	NormalizeByBinWidth(hist_ThrPy99_425);
	NormalizeByBinWidth(hist_ThrPy99_500);
	NormalizeByBinWidth(hist_ThrPy99_Zq);
	NormalizeByBinWidth(hist_ThrPy99_tt);
	NormalizeByBinWidth(hist_ThrPy99_WW);
	NormalizeByBinWidth(hist_ThrPy99_ZZ);
	NormalizeByBinWidth(hist_ThrPy99_Zt);

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

}

// Code
int main() {

	// Call cut function
	// applyCuts("gen_TES50t_wiR.root", "cut_TES50t_wiR.root");
	applyCuts("gen_TES50t_noR.root", "cut_TES50t_noR.root");
	// applyCuts("gen_TES500_noR.root", "cut_TES500_noR.root");

	// Terminate
	return 0;

}