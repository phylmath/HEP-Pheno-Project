void plot_LHCpp14TeV()
{
	// define hist object
	TH1F *hist_m = new TH1F("hist_m", "Delta Resonance (LHC-pp 13.8-TeV 500k-events)", 200, 1, 2);
	// beautify
	hist_m->SetFillColor(kGreen-10);
	// hist_m->SetStats(0);
	hist_m->GetXaxis()->SetTitle("Mass (GeV)");
	hist_m->GetXaxis()->SetTitleSize(0.05);
	hist_m->GetXaxis()->SetLabelSize(0.05);
	hist_m->GetYaxis()->SetTitle("Events");
	hist_m->GetYaxis()->SetTitleSize(0.05);
	hist_m->GetYaxis()->SetLabelSize(0.05);

	// // open file
	// fstream file;
	// file.open("trydata1.txt", ios::out);

	// read output file
	TFile *input = new TFile("out_LHCpp14TeV.root", "read");

	// import tree file
	TTree *tree = (TTree*)input->Get("tree");

	// branch params
	int id, event, size, no;
	double m, px, py, pz;

	// define branches
	tree->SetBranchAddress("event", &event);	// event number
	tree->SetBranchAddress("size", &size);		// event size
	tree->SetBranchAddress("no", &no);			// particle no
	tree->SetBranchAddress("id", &id);			// particle id
	tree->SetBranchAddress("m", &m);			// particle mass
	tree->SetBranchAddress("px", &px);			// particle mom-x
	tree->SetBranchAddress("py", &py);			// particle mom-y
	tree->SetBranchAddress("pz", &pz);			// particle mom-z

	// loop #iteration
	int entries = tree->GetEntries();

	// read branches
	for (int i = 0; i < entries; i++)
	{
		// load branch
		tree->GetEntry(i);
		// plot Δ- res
		if(id == 1114) hist_m->Fill(m);
	}

	// define canvas object
	TCanvas *c1 = new TCanvas();
	// beautify
	c1->SetTickx();
	c1->SetTicky();
	c1->SetGridx();
	c1->SetGridy();

	// fitting function
	TF1 *func = new TF1("fit", "landau", 0, 2);
	// beautify
	func->SetLineWidth(3);
	func->SetLineColor(kRed);
	func->SetLineStyle(2);
	// input fit params
	func->SetParameters(1.232, 0.1, 0.5);	// mpv, width, z
	// perform fitting
	hist_m->Fit("fit", "Q0");				// R(range) Q(suppress terminal output) 0(fit display)

	// define legend : l(line), p(point), f(fill)
	TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
	leg->AddEntry(hist_m, "Generated Data", "f");
	leg->AddEntry(func, "Landau Fitting", "l");
	leg->SetBorderSize(0);

	// draw plots
	hist_m->Draw("hist");
	func->Draw("same");
	leg->Draw();

	// store fit params
	double mean = func->GetParameter(1);
	double sigma = func->GetParameter(2);

	//print var coeff
	// cout << sigma << endl;
	// cout << mean << endl;
	// cout << sigma/mean*100 << endl;
}