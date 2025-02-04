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
	TH1D *hist_pen = new TH1D("hist_pen", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 60, 0, 60);
	// Beautify
	hist_pen->SetStats(kFALSE);
	hist_pen->SetLineColor(kBlue+1);
	hist_pen->SetMarkerColor(kBlue+1);
	hist_pen->SetMarkerStyle(21);
	hist_pen->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_pen->GetYaxis()->SetTitle("Probability Pn");
	hist_pen->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_pen->GetYaxis()->SetNdivisions(510, kTRUE);

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
		hist_pen->SetBinContent(hist_exp->FindBin(Nch), Prb);
		// Populate error bar
		hist_pen->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	}
	// Scale Probs
	// hist_pen->Scale(1.0/PrbTotal);
	cout << "Cumulative Probability (Ph1) : " << PrbTotal << endl;
	// Close file
	infile_pen_1.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Normalise probability
	hist_exp->Scale(1.0/hist_exp->Integral());
	hist_pen->Scale(1.0/hist_pen->Integral());
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

	// Fitting function
	TF1 *fist_pen = new TF1("fist_pen", "[0]*ROOT::Math::negative_binomial_pdf(x,[1],x)", 0, 60);
	// // Beautify
	fist_pen->SetLineWidth(3);
	fist_pen->SetLineColor(kBlue);
	fist_pen->SetLineStyle(2);
	// Input fit params
	fist_pen->SetParameter(0,1.6);			// Normalisation parameter
	// fist_pen->SetParameter(1,15);			// k - shape parameter
	fist_pen->SetParameter(1,0.5);			// p - probability parameter
	// fist_pen->SetParameter(3,18);		// n - number of trials (make independent)
	// Perform fitting
	hist_pen->Fit("fist_pen", "R0");		// R(range) Q(suppress terminal output) 0(fit display)

	// Fitting function
	TF1 *fist_exp = new TF1("fist_exp", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 0, 60);
	// // Beautify
	fist_exp->SetLineWidth(3);
	fist_exp->SetLineColor(kRed);
	fist_exp->SetLineStyle(2);
	// Input fit params
	fist_exp->SetParameter(0,1.6);			// Normalisation parameter
	fist_exp->SetParameter(1,15);			// k - shape parameter
	fist_exp->SetParameter(2,0.5);			// p - probability parameter
	// fist_exp->SetParameter(3,18);		// n - number of trials (make independent)
	// Perform fitting
	hist_exp->Fit("fist_exp", "R0");		// R(range) Q(suppress terminal output) 0(fit display)

	// Draw histogram
	hist_exp->Draw("c1");
	// hist_pen->Draw("same");
	// fist_pen->Draw("same");
	fist_exp->Draw("same");

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_exp, "Experimental data 284100 events", "p");
	legend->AddEntry(fist_exp, "NBD fit for Experimental data", "l");
	legend->AddEntry(hist_pen, "Pythia 8.312 data 284100 events", "p");
	legend->AddEntry(fist_pen, "NBD fit for Pythia data", "l");

	// legend->SetBorderSize(0);
	// legend->Draw();

	// Print area under the curves to confirm normalisation
	cout << "Integration (Exp) : " << hist_exp->Integral() << endl;
	cout << "Integration (Ph1) : " << hist_pen->Integral() << endl;
	cout << "HISTO-EXP (K/P/N) : " << fist_exp->GetParameter(0) << "/" << fist_exp->GetParameter(1) << "/" << fist_exp->GetParameter(2) << endl;
	cout << "HISTO-PEN (K/P/N) : " << fist_pen->GetParameter(0) << "/" << fist_pen->GetParameter(1) << "/" << fist_pen->GetParameter(2) << endl;


}