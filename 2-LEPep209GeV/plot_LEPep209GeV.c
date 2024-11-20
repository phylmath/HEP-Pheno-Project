/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void plot_LEPep209GeV()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining Histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_z = new TH1F("hist_z", "Z0 Resonance (LEP-ee 209-GeV 500k-events)", 200, 75, 120);
	// Beautify
	hist_z->SetFillColor(kGreen-10);
	hist_z->GetXaxis()->SetTitle("Mass (GeV)");
	hist_z->GetXaxis()->SetTitleSize(0.05);
	hist_z->GetXaxis()->SetLabelSize(0.05);
	hist_z->GetYaxis()->SetTitle("Events");
	hist_z->GetYaxis()->SetTitleSize(0.05);
	hist_z->GetYaxis()->SetLabelSize(0.05);

	// Define hist object
	TH1F *hist_j = new TH1F("hist_j", "J/Psi Resonance (LEP-ee 209-GeV 500k-events)", 250, 3096, 3098);
	// Beautify
	hist_j->SetFillColor(kGreen-10);
	hist_j->GetXaxis()->SetTitle("Mass (keV)");
	hist_j->GetXaxis()->SetTitleSize(0.05);
	hist_j->GetXaxis()->SetLabelSize(0.05);
	hist_j->GetYaxis()->SetTitle("Events");
	hist_j->GetYaxis()->SetTitleSize(0.05);
	hist_j->GetYaxis()->SetLabelSize(0.05);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Populating Histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read output file
	TFile *input = new TFile("out_LEPep209GeV.root", "read");

	// Import tree file
	TTree *tree = (TTree*)input->Get("tree");

	// Branch params
	int id, event, size, no;
	double m, px, py, pz;

	// Define branches
	tree->SetBranchAddress("event", &event);	// event number
	tree->SetBranchAddress("size", &size);		// event size
	tree->SetBranchAddress("no", &no);			// particle no
	tree->SetBranchAddress("id", &id);			// particle id
	tree->SetBranchAddress("m", &m);			// particle mass
	tree->SetBranchAddress("px", &px);			// particle mom-x
	tree->SetBranchAddress("py", &py);			// particle mom-y
	tree->SetBranchAddress("pz", &pz);			// particle mom-z

	// Loop #iteration
	int entries = tree->GetEntries();

	// Read branches
	for (int i = 0; i < entries; i++)
	{
		// Load branch
		tree->GetEntry(i);
		// Plot Z res
		if(id == 23) hist_z->Fill(m);
		// Plot J/ψ res
		if(id == 443) hist_j->Fill(m*1e3);
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fitting Histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define canvas object
	TCanvas *cz = new TCanvas("","Z0 Resonance");
	// Beautify
	cz->SetTickx();
	cz->SetTicky();
	cz->SetGridx();
	cz->SetGridy();

	// Fitting function
	TF1 *fitz = new TF1("fitz", "breitwigner", 70, 120);
	// Beautify
	fitz->SetLineWidth(3);
	fitz->SetLineColor(kRed);
	fitz->SetLineStyle(2);
	// Input fit params
	fitz->SetParameters(91.1, 4.905);					// mass, width
	// Perform fitting
	hist_z->Fit("fitz", "RQ");							// R(range) Q(suppress terminal output) 0(fit display)

	// Define legend
	TLegend *legz = new TLegend(0.5,0.6,0.8,0.8);
	legz->AddEntry(hist_z, "Generated Data", "f");		// f(fill)
	legz->AddEntry(fitz, "Breit-Wigner Fitting", "l");	// l(line)
	legz->SetBorderSize(0);

	// Draw plots
	hist_z->Draw("hist_z");
	fitz->Draw("same");
	legz->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define canvas object
	TCanvas *cj = new TCanvas("","J/Psi Resonance");
	// Beautify
	cj->SetTickx();
	cj->SetTicky();
	cj->SetGridx();
	cj->SetGridy();

	// Fitting function
	TF1 *fitj = new TF1("fitj", "breitwigner", 3095, 3099);
	// Beautify
	fitj->SetLineWidth(3);
	fitj->SetLineColor(kRed);
	fitj->SetLineStyle(2);
	// Input fit params
	fitj->SetParameter(0,15.3);							// p0 - events
	fitj->SetParameter(1,3096.92);						// p1 - mean
	fitj->SetParameter(2,0.07);							// p2 - width
	// Perform fitting
	hist_j->Fit("fitj", "RQ");							// R(range) Q(suppress terminal output) 0(fit display)

	// Define legend 
	TLegend *legj = new TLegend(0.5,0.6,0.8,0.8);
	legj->AddEntry(hist_j, "Generated Data", "f");		// f(fill)
	legj->AddEntry(fitj, "Gaussian Fitting", "l");		// l(line)
	legj->SetBorderSize(0);

	// Draw plots
	hist_j->Draw("hist_j");
	fitj->Draw("same");
	legj->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}