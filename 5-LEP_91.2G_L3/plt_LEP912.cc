/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
// Header
using namespace std;

// Code
void plt_LEP912()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Define histogram
    TH1D *hist_exp = new TH1D("hist_exp", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 60, 0, 60);
    // Beautify
	hist_exp->SetStats(kFALSE);
	hist_exp->SetLineColor(kRed+1);
	hist_exp->SetMarkerColor(kRed+1);
	hist_exp->SetMarkerStyle(20);
	hist_exp->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_exp->GetYaxis()->SetTitle("Probability Pn");
	hist_exp->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_exp->GetYaxis()->SetNdivisions(510, kTRUE);

    // Define histogram
	TH1D *hist_pen_1 = new TH1D("hist_pen_1", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 60, 0, 60);
	// Beautify
	hist_pen_1->SetStats(kFALSE);
	hist_pen_1->SetLineColor(kBlue+1);
	hist_pen_1->SetMarkerColor(kBlue+1);
	hist_pen_1->SetMarkerStyle(21);
	hist_pen_1->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_pen_1->GetYaxis()->SetTitle("Probability Pn");
	hist_pen_1->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_pen_1->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
	TH1D *hist_pen_2 = new TH1D("hist_pen_2", "Charged Hadron Multiplicity distributions [ 900 GeV / 6839 events ]", 60, 0, 60);
	// Beautify
	hist_pen_2->SetStats(kFALSE);
	hist_pen_2->SetLineColor(kGreen+1);
	hist_pen_2->SetMarkerColor(kGreen+1);
	hist_pen_2->SetMarkerStyle(22);
	hist_pen_2->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_pen_2->GetYaxis()->SetTitle("Probability Pn");
	hist_pen_2->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_pen_2->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
	TH1D *hist_pen_3 = new TH1D("hist_pen_3", "Charged Hadron Multiplicity distributions [ 900 GeV / 6839 events ]", 60, 0, 60);
	// Beautify
	hist_pen_3->SetStats(kFALSE);
	hist_pen_3->SetLineColor(kMagenta+2);
	hist_pen_3->SetMarkerColor(kMagenta+2);
	hist_pen_3->SetMarkerStyle(23);
	hist_pen_3->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_pen_3->GetYaxis()->SetTitle("Probability Pn");
	hist_pen_3->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_pen_3->GetYaxis()->SetNdivisions(510, kTRUE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Set reading
	string line;
	// Hadron counters
	double Nch; 
	double PrbTotal=0;
	double Prb, Err_Nch, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import experimental data
	ifstream infile_exp("LEP912_exp.txt");
	// Read through txt
	while (getline(infile_exp, line)) {
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Add prob counter
		PrbTotal += Prb;
		// Populate histogram
		hist_exp->SetBinContent(hist_exp->FindBin(Nch), Prb);
		// Populate error bar
		hist_exp->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	}
	// Scale Probs
	// hist_exp->Scale(1.0/PrbTotal);
	cout << "Cumulative Probability (Exp) : " << PrbTotal << endl;
	// Close file
	infile_exp.close();

//////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_pen_1("LEP912_pen.txt");
	// Read through txt
	while (getline(infile_pen_1, line)) {	
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Add prob counter
		PrbTotal += Prb;
		// Populate histogram
		hist_pen_1->SetBinContent(hist_exp->FindBin(Nch), Prb);
		// Populate error bar
		hist_pen_1->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	}
	// Scale Probs
	// hist_pen_1->Scale(1.0/PrbTotal);
	cout << "Cumulative Probability (Ph1) : " << PrbTotal << endl;
	// Close file
	infile_pen_1.close();

// //////////////////////////////////////////////////////

	// // Reset
	// PrbTotal=0;
	// // Import Pythia data
	// ifstream infile_pen_2("LEP912_pen_H_W_Zh_200k.txt");
	// // Read through txt hardsofttop
	// while (getline(infile_pen_2, line)) {	
	// 	// Set reading order
	// 	istringstream iss(line);
	// 	iss >> Nch >> Prb >> Err_Prb;
	// 	// Add prob counter
	// 	PrbTotal += Prb;
	// 	// Populate histogram
	// 	hist_pen_2->SetBinContent(hist_exp->FindBin(Nch), Prb);
	// 	// Populate error bar
	// 	hist_pen_2->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	// }
	// // Scale Probs
	// // hist_pen_2->Scale(1.0/PrbTotal);
	// cout << "Cumulative Probability (Ph2) : " << PrbTotal << endl;
	// // Close file
	// infile_pen_2.close();

// //////////////////////////////////////////////////////

// 	// Reset
// 	PrbTotal=0;
// 	// Import Pythia data
// 	ifstream infile_pen_3("hardsofttop_ppb900_pen.txt");
// 	// Read through txt
// 	while (getline(infile_pen_3, line)) {	
// 		// Set reading order
// 		istringstream iss(line);
// 		iss >> Nch >> Prb >> Err_Prb;
// 		// Add prob counter
// 		PrbTotal += Prb;
// 		// Populate histogram
// 		hist_pen_3->SetBinContent(Nch, Prb);
// 		// Populate error bar
// 		hist_pen_3->SetBinError(0, 0);
// 	}
// 	// Scale Probs
// 	// hist_pen_3->Scale(1.0/PrbTotal);
// 	cout << "Cumulative Probability (All) : " << PrbTotal << endl;
// 	// Close file
// 	infile_pen_3.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Normalise probability
	hist_exp->Scale(1.0/hist_exp->Integral());
	hist_pen_1->Scale(1.0/hist_pen_1->Integral());
	// hist_pen_2->Scale(1.0/hist_pen_2->Integral());
	// hist_pen_3->Scale(1.0/hist_pen_3->Integral());

	// Create canvas
	TCanvas* c1 = new TCanvas("c1", "Charged hadron multiplicity distributions", 800, 600);
	// Beautify
	c1->SetLogy();
	c1->SetTickx();
	c1->SetTicky();
	c1->SetGridx();
	c1->SetGridy();
	// Draw histogram
	hist_exp->Draw("c1");
	hist_pen_1->Draw("same");
	// hist_pen_2->Draw("same");
	// hist_pen_3->Draw("same");

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_exp, "Experimental data 284100 events", "lep");
	legend->AddEntry(hist_pen_1, "Pythia 8.312 data 284100 events", "lep");
	// legend->AddEntry(hist_pen_2, "Pythia 8.312 data (H/W/Zh) 200k events", "lep");
	// legend->AddEntry(hist_pen_3, "Pythia 8.312 (H+S+T)", "p");
	legend->Draw();

	cout << "Integration (Exp) : " << hist_exp->Integral() << endl;
	// cout << "Integration (Ph1) : " << hist_pen_1->Integral() << endl;
	// cout << "Integration (Ph2) : " << hist_pen_2->Integral() << endl;
	// cout << "Integration (Ph3) : " << hist_pen_3->Integral() << endl;

}