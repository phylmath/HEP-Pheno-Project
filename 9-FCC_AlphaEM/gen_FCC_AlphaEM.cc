#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

using namespace Pythia8;

int main() {
    Pythia pythia;
    pythia.readString("Beams:idA = 11");
    pythia.readString("Beams:idB = -11");
    pythia.readString("Beams:eCM = 91.2");

    // Enable Z/γ* → e⁺e⁻ and μ⁺μ⁻ only
    pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
    pythia.readString("23:onMode = off");
    pythia.readString("23:onIfAny = 11 13");

    pythia.init();

    const int nBins = 50;
    const double cosMin = -1.0;
    const double cosMax = 1.0;

    TH1D* h_el = new TH1D("h_el", "cos#theta distribution", nBins, cosMin, cosMax);
    TH1D* h_mu = new TH1D("h_mu", "cos#theta distribution", nBins, cosMin, cosMax);
    TH1D* h_pos = new TH1D("h_pos", "cos#theta distribution", nBins, cosMin, cosMax);

    int nEvents = 5e6;

    // Run through events
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
        
        // Anti-crash
        if (!pythia.next()) continue;
        
        // Run through particles
        for (int i = 0; i < pythia.event.size(); ++i) {
            if (!pythia.event[i].isFinal()) continue;
            int id = pythia.event[i].id();

            Vec4 p = pythia.event[i].p();
            double cosTheta = p.pz() / p.pAbs();

            if (id == 11) h_el->Fill(cosTheta);
            if (id == -11) h_pos->Fill(cosTheta);
            if (id == 13) h_mu->Fill(cosTheta);
        }
    }

    // Compute ratios with error propagation
    TH1D* h_ratio_el_mu = (TH1D*) h_el->Clone("h_ratio_el_mu");
    h_ratio_el_mu->SetTitle("Angular ratios as a function of cos#theta");
    h_ratio_el_mu->Divide(h_el, h_mu, 1.0, 1.0, "B");

    TH1D* h_ratio_el_pos = (TH1D*) h_el->Clone("h_ratio_el_pos");
    h_ratio_el_pos->SetTitle("Angular ratios as a function of cos#theta");
    h_ratio_el_pos->Divide(h_el, h_pos, 1.0, 1.0, "B");

	h_el->SetLineColor(kRed);  
	h_el->SetLineWidth(2);  
	h_el->SetStats(kFALSE);

	h_mu->SetLineColor(kBlue);
	h_mu->SetLineWidth(2);
	h_mu->SetStats(kFALSE);

	h_pos->SetLineColor(kGreen+2);
	h_pos->SetLineWidth(2);
	h_pos->SetStats(kFALSE);

	h_ratio_el_mu->SetLineColor(kMagenta+2);
	h_ratio_el_mu->SetLineWidth(2);
	h_ratio_el_mu->SetStats(kFALSE);
    
	h_ratio_el_pos->SetLineColor(kOrange+7);
	h_ratio_el_pos->SetLineWidth(2);
	h_ratio_el_pos->SetStats(kFALSE);

	// === Canvas 1: Angular distributions ===
	TCanvas* c1 = new TCanvas("c1", "Angular Distributions", 800, 600);
	
	TLegend* legend1 = new TLegend(0.65, 0.75, 0.88, 0.88);
	legend1->AddEntry(h_el, "e^{-}", "l");
	legend1->AddEntry(h_mu, "#mu^{-}", "l");
	legend1->AddEntry(h_pos, "e^{+}", "l");
	
	TLegend* legend2 = new TLegend(0.60, 0.75, 0.88, 0.88);
	legend2->AddEntry(h_ratio_el_mu, "R_{e^{-}/#mu^{-}}", "l");
	legend2->AddEntry(h_ratio_el_pos, "R_{e^{-}/e^{+}}", "l");
	
	c1->Divide(1,2);
	c1->cd(1)->SetTickx(); c1->cd(1)->SetTicky();
	c1->cd(1)->SetGridx(); c1->cd(1)->SetGridy();
	c1->cd(2)->SetTickx(); c1->cd(2)->SetTicky();
	c1->cd(2)->SetGridx(); c1->cd(2)->SetGridy();
	
	c1->cd(1);
	h_el->Draw("HIST");
	h_mu->Draw("HIST SAME");
	h_pos->Draw("HIST SAME");
	legend1->Draw();
	c1->cd(2);
	h_ratio_el_mu->Draw("P");
	h_ratio_el_pos->Draw("P SAME");
	legend2->Draw();

	c1->SaveAs("angular_distributions.png");

    // Save to ROOT file
    TFile* outFile = new TFile("ratios.root", "RECREATE");
    h_el->Write();
    h_mu->Write();
    h_pos->Write();
    h_ratio_el_mu->Write();
    h_ratio_el_pos->Write();
	c1->Write("c1_AngularDistributions");
    outFile->Close();

    pythia.stat();
    return 0;
}