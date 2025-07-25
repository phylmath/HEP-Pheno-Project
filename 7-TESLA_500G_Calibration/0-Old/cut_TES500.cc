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
#include "TH2F.h"
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
#include "TEllipse.h"
#include "TText.h"
#include "TPolyLine3D.h"
#include <TVectorF.h>
// Header
using namespace Pythia8;
using namespace std;
using namespace fastjet;

void DrawJets3D_Combined(const vector<vector<PseudoJet>>& allJets, const vector<int>& processCodes, const string& cname = "Combined3D") {
    TCanvas* c3D = new TCanvas(cname.c_str(), "Combined Jets in 3D", 800, 600);
        c3D->cd();

    // Axes and 3D bounding box
    TPolyLine3D* xAxis = new TPolyLine3D(2);
    xAxis->SetPoint(0, -120, 0, 0);
    xAxis->SetPoint(1, 120, 0, 0);
    xAxis->SetLineColor(kBlack); xAxis->SetLineStyle(2); xAxis->Draw();
    TPolyLine3D* yAxis = new TPolyLine3D(2);
    yAxis->SetPoint(0, 0, -120, 0);
    yAxis->SetPoint(1, 0, 120, 0);
    yAxis->SetLineColor(kBlack); yAxis->SetLineStyle(2); yAxis->Draw();
    TPolyLine3D* zAxis = new TPolyLine3D(2);
    zAxis->SetPoint(0, 0, 0, -120);
    zAxis->SetPoint(1, 0, 0, 120);
    zAxis->SetLineColor(kBlack); zAxis->SetLineStyle(2); zAxis->Draw();

    // Draw bounding box
    double L = 120;
    double corners[8][3] = {
        {-L, -L, -L}, {L, -L, -L}, {L, L, -L}, {-L, L, -L},
        {-L, -L, L},  {L, -L, L},  {L, L, L},  {-L, L, L}
    };
    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},  // bottom
        {4,5},{5,6},{6,7},{7,4},  // top
        {0,4},{1,5},{2,6},{3,7}   // sides
    };
    for (int i = 0; i < 12; ++i) {
        TPolyLine3D* edge = new TPolyLine3D(2);
        edge->SetPoint(0, corners[edges[i][0]][0], corners[edges[i][0]][1], corners[edges[i][0]][2]);
        edge->SetPoint(1, corners[edges[i][1]][0], corners[edges[i][1]][1], corners[edges[i][1]][2]);
        edge->SetLineColor(kGray+1);
        edge->SetLineStyle(1);
        edge->Draw();
    }
	
    TLegend* legend = new TLegend(0.7, 0.7, 0.95, 0.9);
    TLatex* title = new TLatex(0.1, 0.95, "Combined Jet Visualization for 3 Events");
    title->SetNDC();
    title->SetTextSize(0.04);
    title->Draw();
    const int colors[5] = {kRed, kBlue, kGreen+2, kYellow+1, kMagenta};

    for (size_t e = 0; e < allJets.size(); ++e) {
        const vector<PseudoJet>& jets = allJets[e];
        int color = colors[e % 5];

        const char* label = "Unknown";
        switch (processCodes[e]) {
            case 221: label = "Zq"; break;
            case 231: label = "ZZ"; break;
            case 233: label = "WW"; break;
            case 604: label = "tt"; break;
            case 904: label = "HZ"; break;
            case 906: label = "hZ"; break;
            case 907: label = "hW"; break;
        }

        TPolyLine3D* legendLine = new TPolyLine3D(2);
        legendLine->SetLineColor(color);
        legendLine->SetLineWidth(2);
        legend->AddEntry(legendLine, Form("Event %lu: %s", e, label), "l");

        for (size_t i = 0; i < jets.size(); ++i) {
            TPolyLine3D* line = new TPolyLine3D(2);
            double px = jets[i].px();
            double py = jets[i].py();
            double pz = jets[i].pz();
            line->SetPoint(0, 0, 0, 0);
            line->SetPoint(1, px, py, pz);
            line->SetLineColor(color);
            line->SetLineWidth(2);
            line->Draw();
        }
    }

    // Add e+ and e- beam lines
    TPolyLine3D* ebeam = new TPolyLine3D(2);
    ebeam->SetPoint(0, 0, 0, 0);
    ebeam->SetPoint(1, 0, 0, 200);
    ebeam->SetLineColor(kBlack);
    ebeam->SetLineStyle(1);
    ebeam->SetLineWidth(2);
    ebeam->Draw();

    TPolyLine3D* epbeam = new TPolyLine3D(2);
    epbeam->SetPoint(0, 0, 0, 0);
    epbeam->SetPoint(1, 0, 0, -200);
    epbeam->SetLineColor(kBlack);
    epbeam->SetLineStyle(1);
    epbeam->SetLineWidth(2);
    epbeam->Draw();

    legend->AddEntry(ebeam, "e^{+} beam", "l");
    legend->AddEntry(epbeam, "e^{-} beam", "l");
    legend->SetTextSize(0.03);
    legend->Draw();

	// Axis labels
    TLatex* xlabel = new TLatex(0.92, 0.53, "X");
    xlabel->SetNDC();
    xlabel->SetTextSize(0.03);
    xlabel->Draw();

    TLatex* ylabel = new TLatex(0.53, 0.92, "Y");
    ylabel->SetNDC();
    ylabel->SetTextSize(0.03);
    ylabel->Draw();

    TLatex* zlabel = new TLatex(0.53, 0.08, "Z");
    zlabel->SetNDC();
    zlabel->SetTextSize(0.03);
    zlabel->Draw();
    c3D->Update();
    c3D->SaveAs((cname + ".png").c_str());
    delete c3D;
	
}

void DrawJetsEtaPhi(const vector<PseudoJet>& jets, double R, const string& cname = "cEtaPhi") {
    TCanvas* c = new TCanvas(cname.c_str(), "Jets in #eta-#phi", 800, 600);
    TH2F* frame = new TH2F("frame", "Jets in #eta-#phi;#eta;#phi", 1, -5, 5, 1, -TMath::Pi(), TMath::Pi());
    frame->Draw();

    for (size_t i = 0; i < jets.size(); ++i) {
        double eta = jets[i].eta();
        double phi = jets[i].phi_std();
        double pt = jets[i].pt();

        TEllipse* jetCone = new TEllipse(eta, phi, R, R);
        jetCone->SetLineColor(kBlue);
        jetCone->SetFillStyle(0);
        jetCone->Draw();

        TText* label = new TText(eta, phi + 0.2, Form("p_{T}=%.1f", pt));
        label->SetTextSize(0.02);
        label->Draw();
    }

    c->Update();
    c->SaveAs((cname + ".png").c_str());
    delete c;
}

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
void applyCuts( const std::string& inputFileName, const std::string& outputFileName, float nEnerg ) {

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
	vector<int> *eveNum=nullptr, *eveSiz=nullptr, *eveCod=nullptr, *parNum=nullptr, *parPdg=nullptr, \
	 *parChg=nullptr, *isrNum=nullptr;
	vector<float> *eveThr=nullptr, *eveTax=nullptr, *eveSph=nullptr, *eveSax=nullptr, *eveSpr=nullptr, \
	 *sigmaT=nullptr, *parEto=nullptr, *parEtt=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr, \
	 *isrMax=nullptr, *eveCpr=nullptr, *eveHjm=nullptr, *eveBto=nullptr, *eveBwi=nullptr;

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
	itree->SetBranchAddress("eveCpr", &eveCpr);  										// Event C-param
	itree->SetBranchAddress("eveHjm", &eveHjm);  										// Event rho
	itree->SetBranchAddress("eveBto", &eveBto);										// Event BTotal
	itree->SetBranchAddress("eveBwi", &eveBwi);										// Event Bwide
	itree->SetBranchAddress("isrNum", &isrNum);											// ISR γ number
	itree->SetBranchAddress("isrMax", &isrMax);											// ISR γ energy
	itree->SetBranchAddress("parNum", &parNum);											// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);											// Parts pdg id
	itree->SetBranchAddress("parChg", &parChg);											// Parts charge
	itree->SetBranchAddress("parEto", &parEto);											// Parts energy
	itree->SetBranchAddress("parEtt", &parEtt);											// Parts energy
	itree->SetBranchAddress("parPmx", &parPmx);											// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);											// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);											// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Esprime_norm = new TH1F("hist_Esprime_norm", "Reduced energy after ISR", 100, 0, 1);
	hist_Esprime_norm->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_norm->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_norm", &hist_Esprime_norm, "hist_Esprime_norm");

	TH1F *hist_Esprime_al = new TH1F("hist_Esprime_al", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_al->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_al->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_al", &hist_Esprime_al, "hist_Esprime_al");

	TH1F *hist_Esprime_HZ = new TH1F("hist_Esprime_HZ", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_HZ->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_HZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_HZ", &hist_Esprime_HZ, "hist_Esprime_HZ");

	TH1F *hist_Esprime_hZ = new TH1F("hist_Esprime_hZ", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_hZ->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_hZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_hZ", &hist_Esprime_hZ, "hist_Esprime_hZ");

	TH1F *hist_Esprime_hW = new TH1F("hist_Esprime_hW", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_hW->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_hW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_hW", &hist_Esprime_hW, "hist_Esprime_hW");

	TH1F *hist_Esprime_Zq = new TH1F("hist_Esprime_Zq", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_Zq->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_Zq->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_Zq", &hist_Esprime_Zq, "hist_Esprime_Zq");
	
	TH1F *hist_Esprime_tt = new TH1F("hist_Esprime_tt", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_tt->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_tt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_tt", &hist_Esprime_tt, "hist_Esprime_tt");

	TH1F *hist_Esprime_WW = new TH1F("hist_Esprime_WW", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_WW->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_WW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_WW", &hist_Esprime_WW, "hist_Esprime_WW");

	TH1F *hist_Esprime_ZZ = new TH1F("hist_Esprime_ZZ", "Reduced energy after ISR", 200, -1, 366);
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

	TH1F *hist_nHadron_060 = new TH1F("hist_nHadron_060", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_060->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_060->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_060", &hist_nHadron_060, "hist_nHadron_060");

	TH1F *hist_nHadron_085 = new TH1F("hist_nHadron_085", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_085->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_085->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_085", &hist_nHadron_085, "hist_nHadron_085");

	TH1F *hist_nHadron_100 = new TH1F("hist_nHadron_100", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_100->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_100->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_100", &hist_nHadron_100, "hist_nHadron_100");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nHadron_HZ = new TH1F("hist_nHadron_HZ", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_HZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_HZ->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_HZ", &hist_nHadron_HZ, "hist_nHadron_HZ");

	TH1F *hist_nHadron_hZ = new TH1F("hist_nHadron_hZ", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_hZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_hZ->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_hZ", &hist_nHadron_hZ, "hist_nHadron_hZ");

	TH1F *hist_nHadron_hW = new TH1F("hist_nHadron_hW", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_hW->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_hW->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_hW", &hist_nHadron_hW, "hist_nHadron_hW");

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

	TH1F *hist_nHadron_noH = new TH1F("hist_nHadron_noH", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_noH->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_noH->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_noH", &hist_nHadron_noH, "hist_nHadron_noH");

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
	
	float xbin1[] = {
		8.1526e+00, 8.1526e+00, 8.3521e+00, 8.5181e+00, 8.6545e+00, 8.7791e+00, 8.9004e+00, 9.0491e+00, 9.1940e+00, 9.3321e+00,
		9.4488e+00, 9.6281e+00, 9.7874e+00, 9.9461e+00, 1.0101e+01, 1.0273e+01, 1.0451e+01, 1.0627e+01, 1.0810e+01, 1.1002e+01,
		1.1197e+01, 1.1392e+01, 1.1608e+01, 1.1823e+01, 1.2046e+01, 1.2281e+01, 1.2524e+01, 1.2779e+01, 1.3039e+01, 1.3321e+01,
		1.3609e+01, 1.3915e+01, 1.4228e+01, 1.4572e+01, 1.4933e+01, 1.5312e+01, 1.5713e+01, 1.6145e+01, 1.6637e+01, 1.7152e+01,
		1.7710e+01, 1.8340e+01, 1.9042e+01, 1.9831e+01, 2.0774e+01, 2.1887e+01, 2.2369e+01, 2.5124e+01, 2.7963e+01, 3.5327e+01
	};


	TH1F *hist_ThrPyth = new TH1F("hist_ThrPyth", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth", &hist_ThrPyth, "hist_ThrPyth");

	TH1F *hist_ThrPyth_000 = new TH1F("hist_ThrPyth_000", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_000->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_000->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_000", &hist_ThrPyth_000, "hist_ThrPyth_000");

	TH1F *hist_ThrPyth_060 = new TH1F("hist_ThrPyth_060", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_060->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_060->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_060", &hist_ThrPyth_060, "hist_ThrPyth_060");

	TH1F *hist_ThrPyth_085 = new TH1F("hist_ThrPyth_085", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_085->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_085->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_085", &hist_ThrPyth_085, "hist_ThrPyth_085");

	TH1F *hist_ThrPyth_100 = new TH1F("hist_ThrPyth_100", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_100->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_100->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_100", &hist_ThrPyth_100, "hist_ThrPyth_100");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_HZ = new TH1F("hist_ThrPyth_HZ", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_HZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_HZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_HZ", &hist_ThrPyth_HZ, "hist_ThrPyth_HZ");

	TH1F *hist_ThrPyth_hZ = new TH1F("hist_ThrPyth_hZ", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_hZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_hZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_hZ", &hist_ThrPyth_hZ, "hist_ThrPyth_hZ");

	TH1F *hist_ThrPyth_hW = new TH1F("hist_ThrPyth_hW", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_hW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_hW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_hW", &hist_ThrPyth_hW, "hist_ThrPyth_hW");

	TH1F *hist_ThrPyth_Zq = new TH1F("hist_ThrPyth_Zq", "Inverse Thrust", 45, 0.0, 0.45);
	hist_ThrPyth_Zq->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_Zq->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_Zq", &hist_ThrPyth_Zq, "hist_ThrPyth_Zq");

	TH1F *hist_ThrPyth_tt = new TH1F("hist_ThrPyth_tt", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_tt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_tt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_tt", &hist_ThrPyth_tt, "hist_ThrPyth_tt");

	TH1F *hist_ThrPyth_WW = new TH1F("hist_ThrPyth_WW", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_WW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_WW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_WW", &hist_ThrPyth_WW, "hist_ThrPyth_WW");

	TH1F *hist_ThrPyth_ZZ = new TH1F("hist_ThrPyth_ZZ", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_ZZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_ZZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_ZZ", &hist_ThrPyth_ZZ, "hist_ThrPyth_ZZ");

	TH1F *hist_ThrPyth_Zt = new TH1F("hist_ThrPyth_Zt", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_Zt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_Zt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_Zt", &hist_ThrPyth_Zt, "hist_ThrPyth_Zt");

	TH1F *hist_ThrPyth_noH = new TH1F("hist_ThrPyth_noH", "Inverse Thrust", 100, 0, 0.4);
	hist_ThrPyth_noH->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_noH->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_noH", &hist_ThrPyth_noH, "hist_ThrPyth_noH");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float xbin[] = {0.0E+00,1.0E-02,2.0E-02,3.0E-02,4.0E-02,5.0E-02,7.0E-02,9.0E-02,1.2E-01,1.5E-01,2.2E-01,3.0E-01,4.0E-01};

	TH1F *hist_ThrPy99 = new TH1F("hist_ThrPy99", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99", &hist_ThrPy99, "hist_ThrPy99");

	TH1F *hist_ThrPy99_000 = new TH1F("hist_ThrPy99_000", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_000->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_000->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_000", &hist_ThrPy99_000, "hist_ThrPy99_000");

	TH1F *hist_ThrPy99_060 = new TH1F("hist_ThrPy99_060", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_060->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_060->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_060", &hist_ThrPy99_060, "hist_ThrPy99_060");

	TH1F *hist_ThrPy99_085 = new TH1F("hist_ThrPy99_085", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_085->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_085->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_085", &hist_ThrPy99_085, "hist_ThrPy99_085");

	TH1F *hist_ThrPy99_100 = new TH1F("hist_ThrPy99_100", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_100->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_100->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_100", &hist_ThrPy99_100, "hist_ThrPy99_100");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPy99_Zq = new TH1F("hist_ThrPy99_Zq", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_Zq->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_Zq->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_Zq", &hist_ThrPy99_Zq, "hist_ThrPy99_Zq");

	TH1F *hist_ThrPy99_tt = new TH1F("hist_ThrPy99_tt", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_tt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_tt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_tt", &hist_ThrPy99_tt, "hist_ThrPy99_tt");

	TH1F *hist_ThrPy99_WW = new TH1F("hist_ThrPy99_WW", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_WW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_WW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_WW", &hist_ThrPy99_WW, "hist_ThrPy99_WW");

	TH1F *hist_ThrPy99_ZZ = new TH1F("hist_ThrPy99_ZZ", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_ZZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_ZZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_ZZ", &hist_ThrPy99_ZZ, "hist_ThrPy99_ZZ");

	TH1F *hist_ThrPy99_Zt = new TH1F("hist_ThrPy99_Zt", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPy99_Zt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPy99_Zt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPy99_Zt", &hist_ThrPy99_Zt, "hist_ThrPy99_Zt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_CprPyth = new TH1F("hist_CprPyth", "C-Parameter", 100, 0, 0.4);
	hist_CprPyth->GetXaxis()->SetTitle("C");
	hist_CprPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth", &hist_CprPyth, "hist_CprPyth");

	TH1F *hist_CprPyth_HZ = new TH1F("hist_CprPyth_HZ", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_HZ->GetXaxis()->SetTitle("C");
	hist_CprPyth_HZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_HZ", &hist_CprPyth_HZ, "hist_CprPyth_HZ");

	TH1F *hist_CprPyth_hZ = new TH1F("hist_CprPyth_hZ", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_hZ->GetXaxis()->SetTitle("C");
	hist_CprPyth_hZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_hZ", &hist_CprPyth_hZ, "hist_CprPyth_hZ");

	TH1F *hist_CprPyth_hW = new TH1F("hist_CprPyth_hW", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_hW->GetXaxis()->SetTitle("C");
	hist_CprPyth_hW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_hW", &hist_CprPyth_hW, "hist_CprPyth_hW");

	TH1F *hist_CprPyth_Zq = new TH1F("hist_CprPyth_Zq", "C-parameter", 100, 0.0, 0.4);
	hist_CprPyth_Zq->GetXaxis()->SetTitle("C");
	hist_CprPyth_Zq->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_Zq", &hist_CprPyth_Zq, "hist_CprPyth_Zq");

	TH1F *hist_CprPyth_tt = new TH1F("hist_CprPyth_tt", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_tt->GetXaxis()->SetTitle("C");
	hist_CprPyth_tt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_tt", &hist_CprPyth_tt, "hist_CprPyth_tt");

	TH1F *hist_CprPyth_WW = new TH1F("hist_CprPyth_WW", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_WW->GetXaxis()->SetTitle("C");
	hist_CprPyth_WW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_WW", &hist_CprPyth_WW, "hist_CprPyth_WW");

	TH1F *hist_CprPyth_ZZ = new TH1F("hist_CprPyth_ZZ", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_ZZ->GetXaxis()->SetTitle("C");
	hist_CprPyth_ZZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_ZZ", &hist_CprPyth_ZZ, "hist_CprPyth_ZZ");

	TH1F *hist_CprPyth_Zt = new TH1F("hist_CprPyth_Zt", "C-parameter", 100, 0, 0.4);
	hist_CprPyth_Zt->GetXaxis()->SetTitle("C");
	hist_CprPyth_Zt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_Zt", &hist_CprPyth_Zt, "hist_CprPyth_Zt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_HjmPyth = new TH1F("hist_HjmPyth", "Heavy jet mass", 100, 0, 1.0);
	hist_HjmPyth->GetXaxis()->SetTitle("C");
	hist_HjmPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(M_{H})");
	otree->Branch("hist_HjmPyth", &hist_HjmPyth, "hist_HjmPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_BtoPyth = new TH1F("hist_BtoPyth", "Total jet broadening", 100, 0, 1.0);
	hist_BtoPyth->GetXaxis()->SetTitle("C");
	hist_BtoPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(B_{T})");
	otree->Branch("hist_BtoPyth", &hist_BtoPyth, "hist_BtoPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TH1F *hist_BwiPyth = new TH1F("hist_BwiPyth", "Wide jet broadening", 100, 0, 1.0);
	hist_BwiPyth->GetXaxis()->SetTitle("C");
	hist_BwiPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(B_{W})");
	otree->Branch("hist_BwiPyth", &hist_BwiPyth, "hist_BwiPyth");

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

	TH1F *hist_NumbISR = new TH1F("hist_NumbISR", "Number of ISR photons", 2, 0, 2);
	hist_NumbISR->GetXaxis()->SetTitle("#E_{#gamma}");
	hist_NumbISR->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_NumbISR", &hist_NumbISR, "hist_NumbISR");

	TH1F *hist_EmaxISR = new TH1F("hist_EmaxISR", "Energy of max ISR photons", 100, 0, 0.6);
	hist_EmaxISR->GetXaxis()->SetTitle("E_{#gamma}/#sqrt{s}");
	hist_EmaxISR->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_EmaxISR", &hist_EmaxISR, "hist_EmaxISR");
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define vars
	int nCh=0, nCj=0, nParts=0, Pdg=0, Rad_000=0, Rad_060=0, Rad_085=0, Rad_100=0;
	float Pmx, Pmy, Pmz, Eto, Ett, Thr, Tax, Sph, Sax, Spr;
	vector<vector<PseudoJet>> allJets;
    vector<int> procCodes;
	
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
			
			////////////////////////// COMPUTING NCH CURVE //////////////////////////////////////////////////
			if ((*parChg)[jParts]!=0) nCh++;											// Charged hadrons

		}
		
		////////////////////////// CLUSTERING JET PARTICLES /////////////////////////////////////////////////
		fastjet::JetDefinition jet_def(antikt_algorithm, R);							// Jet definition
		fastjet::ClusterSequence cs(particles, jet_def);								// Run clustering
		vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store jets
		nCj = jets.size();																// Jet multiplicity

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

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////////////////////////

		// 0% cut on √s'
		if ((*eveSpr)[0] >= 0){
			hist_Esprime_al->Fill((*eveSpr)[0]);
			hist_Esprime_norm->Fill((*eveSpr)[0]);

			hist_ThrPyth->Fill((*eveThr)[0]);
			hist_TaxPyth->Fill((*eveTax)[0]);
			hist_SphPyth->Fill((*eveSph)[0]);
			hist_SaxPyth->Fill((*eveSax)[0]);
			hist_nHadron->Fill(nCh);
			hist_nJetTot->Fill(nCj);

			// cout << (*isrNum)[0] << endl;
			hist_NumbISR->Fill((*isrNum)[0]);
			hist_EmaxISR->Fill((*isrMax)[0]);

			// Process cuts
			if ((*eveCod)[0] == 221) {
				hist_Esprime_Zq->Fill((*eveSpr)[0]);
				hist_nHadron_Zq->Fill(nCh);
				hist_nJetTot_Zq->Fill(nCj);

				hist_CprPyth->Fill((*eveCpr)[0]);
				// hist_HjmPyth->Fill((*eveHjm)[0]); 
				// hist_BtoPyth->Fill((*eveBto)[0]); 
				// hist_BwiPyth->Fill((*eveBwi)[0]);

				hist_ThrPyth_Zq->Fill((*eveThr)[0]); 
				hist_ThrPy99_Zq->Fill((*eveThr)[0]);
				hist_ThrPyth_Zt->Fill((*eveThr)[0]); 
				hist_ThrPy99_Zt->Fill((*eveThr)[0]);

				hist_nHadron_noH->Fill(nCh);
				hist_ThrPyth_noH->Fill((*eveThr)[0]);

				hist_nHadron_000->Fill(nCh);
				hist_ThrPyth_000->Fill((*eveThr)[0]); 
				hist_ThrPy99_000->Fill((*eveThr)[0]);
			}
			if ((*eveCod)[0] == 231) {
				hist_Esprime_ZZ->Fill((*eveSpr)[0]);
				hist_nHadron_ZZ->Fill(nCh);
				hist_nJetTot_ZZ->Fill(nCj);

				hist_ThrPyth_ZZ->Fill((*eveThr)[0]); 
				hist_ThrPy99_ZZ->Fill((*eveThr)[0]);

				hist_nHadron_noH->Fill(nCh);
				hist_ThrPyth_noH->Fill((*eveThr)[0]);
			}
			if ((*eveCod)[0] == 233) {
				hist_Esprime_WW->Fill((*eveSpr)[0]);
				hist_nHadron_WW->Fill(nCh);
				hist_nJetTot_WW->Fill(nCj);

				hist_ThrPyth_WW->Fill((*eveThr)[0]); 
				hist_ThrPy99_WW->Fill((*eveThr)[0]);

				hist_nHadron_noH->Fill(nCh);
				hist_ThrPyth_noH->Fill((*eveThr)[0]);
			}
			if ((*eveCod)[0] == 604) {
				hist_Esprime_tt->Fill((*eveSpr)[0]);
				hist_nHadron_tt->Fill(nCh);
				hist_nJetTot_tt->Fill(nCj);

				hist_ThrPyth_tt->Fill((*eveThr)[0]); 
				hist_ThrPy99_tt->Fill((*eveThr)[0]);
				hist_ThrPyth_Zt->Fill((*eveThr)[0]); 
				hist_ThrPy99_Zt->Fill((*eveThr)[0]);

				hist_nHadron_noH->Fill(nCh);
				hist_ThrPyth_noH->Fill((*eveThr)[0]);
			}

			//Higgs processes
			if ((*eveCod)[0] == 904) {
				hist_Esprime_HZ->Fill((*eveSpr)[0]);
				hist_nHadron_HZ->Fill(nCh);
				hist_ThrPyth_HZ->Fill((*eveThr)[0]);
			}
			if ((*eveCod)[0] == 906) {
				hist_Esprime_hZ->Fill((*eveSpr)[0]);
				hist_nHadron_hZ->Fill(nCh);
				hist_ThrPyth_hZ->Fill((*eveThr)[0]);
			}
			if ((*eveCod)[0] == 907) {
				hist_Esprime_hW->Fill((*eveSpr)[0]);
				hist_nHadron_hW->Fill(nCh);
				hist_ThrPyth_hW->Fill((*eveThr)[0]);
			}

		}

		// 60% cut on √s'
		if ((*eveSpr)[0] >= nEnerg*0.80 && (*eveCod)[0] == 221) {
			hist_ThrPyth_060->Fill((*eveThr)[0]);
			hist_ThrPy99_060->Fill((*eveThr)[0]);
			hist_nHadron_060->Fill(nCh);
		}

		// 85% cut on √s'
		if ((*eveSpr)[0] >= nEnerg-1.0 && (*eveCod)[0] == 221) {
			hist_ThrPyth_085->Fill((*eveThr)[0]); 
			hist_ThrPy99_085->Fill((*eveThr)[0]);
			hist_nHadron_085->Fill(nCh);
		}

		// 100% cut on √s'
		if ((*eveSpr)[0] >= nEnerg-0.5 && (*eveCod)[0] == 221) {
			hist_ThrPyth_100->Fill((*eveThr)[0]); 
			hist_ThrPy99_100->Fill((*eveThr)[0]);
			hist_nHadron_100->Fill(nCh);
		}

		// Radiative checks
		if ((*eveSpr)[0] >= nEnerg*0.00) Rad_000++;
		if ((*eveSpr)[0] >= nEnerg*0.60) Rad_060++;
		if ((*eveSpr)[0] >= nEnerg*0.85) Rad_085++;
		if ((*eveSpr)[0] >= nEnerg*1.00) Rad_100++;

		/////////////////////////////////////////////////////////////////////////////////////////////////////

        // if (iEvent < 5) {
        //     allJets.push_back(jets);
        //     procCodes.push_back((*eveCod)[0]);   
        // }

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Reset
		nCh=0; nCj=0; particles.clear(); jets.clear();
		/////////////////////////////////////////////////////////////////////////////////////////////////////

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// DrawJets3D_Combined(allJets, procCodes);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Print info
	cout << "----------------------------------------" << endl;
	cout << "Colliding at " << nEnerg << " GeV " << endl;
	cout << "----------------------------------------" << endl;
	cout << "Events ≥ " << nEnerg*0.00 << " GeV : " << Rad_000 << endl;
	cout << "Events ≥ " << nEnerg*0.80 << " GeV : " << Rad_060 << endl;
	cout << "Events ≥ " << nEnerg-2.00 << " GeV : " << Rad_085 << endl;
	cout << "Events ≥ " << nEnerg-1.00 << " GeV : " << Rad_100 << endl;
	cout << "----------------------------------------" << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO Scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* KNOO_nHadron = ComputeKNOScaling(hist_nHadron_000, "KNOO_nHadron");
	TH1F* KNOO_nHadron_Zq = ComputeKNOScaling(hist_nHadron_Zq, "KNOO_nHadron_Zq");
	TH1F* KNOO_nHadron_ZZ = ComputeKNOScaling(hist_nHadron_ZZ, "KNOO_nHadron_ZZ");
	TH1F* KNOO_nHadron_WW = ComputeKNOScaling(hist_nHadron_WW, "KNOO_nHadron_WW");
	TH1F* KNOO_nHadron_tt = ComputeKNOScaling(hist_nHadron_tt, "KNOO_nHadron_tt");

	TH1F* KNOO_nHadron_000 = ComputeKNOScaling(hist_nHadron_000, "KNOO_nHadron_000");
	TH1F* KNOO_nHadron_060 = ComputeKNOScaling(hist_nHadron_060, "KNOO_nHadron_060");
	TH1F* KNOO_nHadron_085 = ComputeKNOScaling(hist_nHadron_085, "KNOO_nHadron_085");
	TH1F* KNOO_nHadron_100 = ComputeKNOScaling(hist_nHadron_100, "KNOO_nHadron_100");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bin width normalising
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	NormalizeByBinWidth(hist_ThrPy99);
	NormalizeByBinWidth(hist_ThrPy99_000);
	NormalizeByBinWidth(hist_ThrPy99_060);
	NormalizeByBinWidth(hist_ThrPy99_085);
	NormalizeByBinWidth(hist_ThrPy99_100);
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

	// Extraction
	applyCuts("gen_FCC365.root", "cut_FCC365.root", 365.0);
	applyCuts("gen_FCC240.root", "cut_FCC240.root", 240.0);
	applyCuts("gen_FCC160.root", "cut_FCC160.root", 160.0);
	applyCuts("gen_FCC912.root", "cut_FCC912.root", 91.20);
	
	// Calibration
	applyCuts("gen_FCC183.root", "cut_FCC183.root", 183.0);
	applyCuts("gen_FCC161.root", "cut_FCC161.root", 161.0);

	// Hadronisation
	// applyCuts("gen_FCC912_wiHadron.root", "cut_FCC912_wiHadron.root", 91.2);
	// applyCuts("gen_FCC912_woHadron.root", "cut_FCC912_woHadron.root", 91.2);

	// Old	
	// applyCuts("gen_LEP912_wiR.root", "cut_LEP912_wiR.root", 91.0);
	// applyCuts("gen_TES50t_wiR.root", "cut_TES50t_wiR.root", 500.0);
	// applyCuts("gen_TES50t_noR.root", "cut_TES50t_noR.root", 500.0);
	// applyCuts("gen_TES50t_noR_noH.root", "cut_TES50t_noR_noH.root", 500.0);
	// applyCuts("gen_TES500_noR.root", "cut_TES500_noR.root", 500.0);

	// Terminate
	return 0;

}