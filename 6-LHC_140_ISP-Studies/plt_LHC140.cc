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
// Plotting Hadron Multiplicity
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Define histogram
    TH1D *hist_exp = new TH1D("hist_exp", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 28, 1, 57);
    // Beautify
	// hist_exp->SetStats(kFALSE);
	hist_exp->SetLineColor(kRed+1);
	hist_exp->SetMarkerColor(kRed+1);
	hist_exp->SetMarkerStyle(20);
	hist_exp->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_exp->GetYaxis()->SetTitle("Probability Pn");
	hist_exp->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_exp->GetYaxis()->SetNdivisions(510, kTRUE);

    // Define histogram
	TH1D *hist_pen = new TH1D("hist_pen", "Charged Hadron Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 28, 1, 57);
	// Beautify
	// hist_pen->SetStats(kFALSE);
	hist_pen->SetLineColor(kBlue+1);
	hist_pen->SetMarkerColor(kBlue+1);
	hist_pen->SetMarkerStyle(21);
	hist_pen->GetXaxis()->SetTitle("Charged Hadron Multiplicity Nch");
	hist_pen->GetYaxis()->SetTitle("Probability Pn");
	hist_pen->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_pen->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
    TH1D *hist_jet = new TH1D("hist_jet", "Hadronic Jet Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0, 5);
    // Beautify
	// hist_jet->SetStats(kFALSE);
	hist_jet->SetLineColor(kRed+1);
	hist_jet->SetMarkerColor(kRed+1);
	hist_jet->SetMarkerStyle(20);
	hist_jet->SetLineWidth(4);
	hist_jet->GetXaxis()->SetTitle("Hadronic Jet Multiplicity Ncj");
	hist_jet->GetYaxis()->SetTitle("Probability Pn");
	hist_jet->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_jet->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
    TH1D *hist_ncp = new TH1D("hist_ncp", "Intermediate Parton Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 25, 0, 100);
    // Beautify
	// hist_jet->SetStats(kFALSE);
	hist_ncp->SetLineColor(kRed+1);
	hist_ncp->SetMarkerColor(kRed+1);
	hist_ncp->SetMarkerStyle(20);
	hist_ncp->SetLineWidth(4);
	hist_ncp->GetXaxis()->SetTitle("Intermediate parton Multiplicity Ncp");
	hist_ncp->GetYaxis()->SetTitle("Probability Pn");
	hist_ncp->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_ncp->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
    TH1D *hist_ncq = new TH1D("hist_ncq", "Intermediate Quark Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 100, 0, 100);
    // Beautify
	// hist_jet->SetStats(kFALSE);
	hist_ncq->SetLineColor(kBlue+1);
	hist_ncq->SetMarkerColor(kBlue+1);
	hist_ncq->SetMarkerStyle(20);
	hist_ncq->SetLineWidth(4);
	hist_ncq->GetXaxis()->SetTitle("Intermediate parton Multiplicity Ncp");
	hist_ncq->GetYaxis()->SetTitle("Probability Pn");
	hist_ncq->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_ncq->GetYaxis()->SetNdivisions(510, kTRUE);

	// Define histogram
    TH1D *hist_ncg = new TH1D("hist_ncg", "Intermediate Gluon Multiplicity distributions [ LEP E^{+} E^{-} at 91.2 GeV ]", 25, 0, 100);
    // Beautify
	// hist_jet->SetStats(kFALSE);
	hist_ncg->SetLineColor(kGreen+1);
	hist_ncg->SetMarkerColor(kGreen+1);
	hist_ncg->SetMarkerStyle(20);
	hist_ncg->SetLineWidth(4);
	hist_ncg->GetXaxis()->SetTitle("Intermediate parton Multiplicity Ncp");
	hist_ncg->GetYaxis()->SetTitle("Probability Pn");
	hist_ncg->GetXaxis()->SetNdivisions(510, kTRUE);
	hist_ncg->GetYaxis()->SetNdivisions(510, kTRUE);

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
		// Populate histogram
		hist_exp->SetBinContent(hist_exp->FindBin(Nch), Prb);
		// Populate error bar
		hist_exp->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	}
	// cout << "Cumulative Probability (Exp) : " << PrbTotal << endl;
	// Close file
	infile_exp.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_pen("LEP912_nCh_trim.txt");
	// Read through txt
	while (getline(infile_pen, line)) {
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Nch >> Err_Prb;
		// Populate histogram
		hist_pen->SetBinContent(hist_exp->FindBin(Nch), Prb);
		// Populate error bar
		hist_pen->SetBinError(hist_exp->FindBin(Nch), Err_Prb);
	}
	// cout << "Cumulative Probability (Pen) : " << PrbTotal << endl;
	// Close file
	infile_pen.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_jet("LEP912_nCj.txt");
	// Read through txt
	while (getline(infile_jet, line)) {	
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Populate histogram
		hist_jet->SetBinContent(hist_jet->FindBin(Nch), Prb);
		// Populate error bar
		hist_jet->SetBinError(hist_jet->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_jet.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_ncp("LEP912_nCp.txt");
	// Read through txt
	while (getline(infile_ncp, line)) {
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Populate histogram
		hist_ncp->SetBinContent(hist_ncp->FindBin(Nch), Prb);
		// Populate error bar
		hist_ncp->SetBinError(hist_ncp->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_ncp.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_ncq("LEP912_nCq.txt");
	// Read through txt
	while (getline(infile_ncq, line)) {	
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Populate histogram
		hist_ncq->SetBinContent(hist_ncq->FindBin(Nch), Prb);
		// Populate error bar
		hist_ncq->SetBinError(hist_ncq->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_ncq.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset
	PrbTotal=0;
	// Import Pythia data
	ifstream infile_ncg("LEP912_nCg.txt");
	// Read through txt
	while (getline(infile_ncg, line)) {	
		// Set reading order
		istringstream iss(line);
		iss >> Nch >> Prb >> Err_Prb;
		// Populate histogram
		hist_ncg->SetBinContent(hist_ncg->FindBin(Nch), Prb);
		// Populate error bar
		hist_ncg->SetBinError(hist_ncg->FindBin(Nch), Err_Prb);
	}
	// Close file
	infile_ncg.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Normalise probability
	hist_exp->Scale(1.0/hist_exp->Integral());
	hist_pen->Scale(1.0/hist_pen->Integral());
	hist_jet->Scale(1.0/hist_jet->Integral());
	hist_ncp->Scale(1.0/hist_ncp->Integral());
	hist_ncq->Scale(1.0/hist_ncq->Integral());
	hist_ncg->Scale(1.0/hist_ncg->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* c_nch = new TCanvas("c_nch", "Charged hadron multiplicity distributions", 800, 600);
	// Beautify
	c_nch->SetLogy();
	c_nch->SetTickx();
	c_nch->SetTicky();
	c_nch->SetGridx();
	c_nch->SetGridy();

	// Fitting function
	TF1 *fist_pen = new TF1("fist_pen", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
	// // Beautify
	fist_pen->SetLineWidth(3);
	fist_pen->SetLineColor(kBlue);
	fist_pen->SetLineStyle(2);
	// Input fit params
	fist_pen->SetParameter(0,1.6);			// Normalisation parameter
	fist_pen->SetParameter(1,15);			// k - shape parameter
	fist_pen->SetParameter(2,0.5);			// p - probability parameter
	// fist_pen->SetParameter(3,18);		// n - number of trials (make independent)
	// Perform fitting
	hist_pen->Fit("fist_pen", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

	// Fitting function
	TF1 *fist_exp = new TF1("fist_exp", "[0]*ROOT::Math::negative_binomial_pdf([1],[2],x)", 2, 56);
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
	hist_exp->Fit("fist_exp", "RME");		// R(range) Q(suppress terminal output) 0(fit display)

	// Add legend
	TLegend* legend = new TLegend(0.4, 0.2, 0.85, 0.4);
	legend->AddEntry(hist_exp, "Experimental data 284100 events", "p");
	legend->AddEntry(fist_exp, "NBD fit for Experimental data", "l");
	legend->AddEntry(hist_pen, "Pythia 8.312 data 284100 events", "p");
	legend->AddEntry(fist_pen, "NBD fit for Pythia data", "l");

	// Draw histogram
	hist_exp->Draw("c_nch");
	// fist_exp->Draw("same");
	// hist_pen->Draw("sames");
	// fist_pen->Draw("same");
	// legend->Draw("same");
	// legend->SetBorderSize(0);

	// Print area under the curves to confirm normalisation
	cout << "Integration (Exp) : " << hist_exp->Integral() << endl;
	cout << "Integration (Pen) : " << hist_pen->Integral() << endl;
	// cout << "HISTO-EXP (K/P/N) : " << fist_exp->GetParameter(0) << "/" << fist_exp->GetParameter(1) << "/" << fist_exp->GetParameter(2) << endl;
	// cout << "HISTO-PEN (K/P/N) : " << fist_pen->GetParameter(0) << "/" << fist_pen->GetParameter(1) << "/" << fist_pen->GetParameter(2) << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* c_ncj = new TCanvas("c_ncj", "Hadronic jet multiplicity distributions", 800, 600);
	// // Beautify
	// c_ncj->SetLogy();
	// c_ncj->SetTickx();
	// c_ncj->SetTicky();
	// c_ncj->SetGridx();
	// c_ncj->SetGridy();

	// // Draw histogram
	// hist_jet->Draw("c_ncj");

	// // Print area under the curves to confirm normalisation
	// cout << "Integration (Pen) : " << hist_exp->Integral() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	// TCanvas* c_imp = new TCanvas("c_imp", "Intermediate Parton Multiplicity distributions", 800, 600);
	// // Beautify
	// c_imp->SetLogy();
	// c_imp->SetTickx();
	// c_imp->SetTicky();
	// c_imp->SetGridx();
	// c_imp->SetGridy();

	// // Add legend
	// TLegend* lege_imp = new TLegend(0.4, 0.2, 0.85, 0.4);
	// lege_imp->AddEntry(hist_ncp, "Intermediate parton multiplicity", "p");
	// lege_imp->AddEntry(hist_ncq, "Intermediate quarks multiplicity", "p");
	// lege_imp->AddEntry(hist_ncg, "Intermediate gluons multiplicity", "p");

	// // Draw histogram
	// hist_ncp->Draw("c_imp");
	// hist_ncq->Draw("sames");
	// hist_ncg->Draw("sames");
	// lege_imp->Draw("same");

	// // Print area under the curves to confirm normalisation
	// cout << "Integration (nCp) : " << hist_ncp->Integral() << endl;
	// cout << "Integration (nCq) : " << hist_ncq->Integral() << endl;
	// cout << "Integration (nCg) : " << hist_ncg->Integral() << endl;

}