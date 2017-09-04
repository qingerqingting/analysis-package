void kkselect(){

	TChain *chain=new TChain("tree");
	chain->Add("rightcomb_ana_001.root");
	//chain.Draw("");
	//TFile *ofile=new TFile("rightcombi2_ana_001.root","RECREATE");
	
	TCanvas *c1=new TCanvas();
	TCanvas *c2=new TCanvas();

	c1->Divide(1,1);
	c2->Divide(1,1);

  	TH1F *h1=new TH1F ("h1","The mass spectrum of 2 k",40,0.9,1.1);
	h1->GetXaxis()->SetTitle("m_{2K} [GeV]");
  	setymass(h1);

	TH1F *h2=new TH1F ("h2","The mass spectrum of phi",40,0.9,1.1);
 	h2->GetXaxis()->SetTitle("m_{#phi} [GeV]");
  	setymass(h2);

	//Control the style of histos.
	setdivision(h1);
	setdivision(h2);

	Double_t m_2k;
	Double_t m_phi;
	TLorentzVector p_2k;
	TLorentzVector p_phi;

	 kp_f = new TLorentzVector();
	 km_f = new TLorentzVector();
	// phi_f = new TLorentzVector();
	 chain->SetBranchAddress("kp_f",&kp_f);
	 chain->SetBranchAddress("km_f",&km_f);
	// chain->SetBranchAddress("phi_f",&phi_f);

	  Long64_t nevent=chain->GetEntries();
	  for(Long64_t j=0;j<nevent;j++)
  	{
   	 chain->GetEntry(j);
	//phi
    	p_2k=*kp_f+ *km_f;
	m_2k=p_2k.M();
	
	p_phi=*kp_f+*km_f;
	m_phi=p_phi.M();

	 if (m_2k<1.01) continue;
	 if (m_2k>1.03) continue;
	
	h1->Fill(m_2k);
	h2->Fill(m_phi);

	 c1->cd(1);
  	 h1->Draw("pe");

 	 c2->cd(1);
	 h2->Draw("pe");

//	h1->Write();
//	h2->Write();

}
}
