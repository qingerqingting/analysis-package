void etapselect(){

	TChain *chain=new TChain("tree");
	chain->Add("rightcomb_total.root");
	//chain.Draw("");
	//TFile *ofile=new TFile("rightcombi2_ana_001.root","RECREATE");
	
	TCanvas *c1=new TCanvas();
	TCanvas *c2=new TCanvas();

	c1->Divide(1,1);
	c2->Divide(1,1);

  	TH1F *h1=new TH1F ("h1","The mass spectrum of eta&pip&pim",70,1.9,2.6);
	h1->GetXaxis()->SetTitle("m_{#eta+#pip+#pim} [GeV]");
  	setymass(h1);

	TH1F *h2=new TH1F ("h2","The mass spectrum of phi&etap",70,1.9,2.6);
 	h2->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  	setymass(h2);

	//Control the style of histos.
	setdivision(h1);
	setdivision(h2);

	Double_t m_2gam1;
	Double_t m_2gam2;
	TLorentzVector p_2gam1;
	TLorentzVector p_2gam2;
	Double_t m_2k;
  	Double_t m_2pi;
	Double_t m_eta_pip_pim;
	Double_t m_phi_etap;
	TLorentzVector p_2k;
	TLorentzVector p_2pi;	
	TLorentzVector p_eta_pip_pim;
	TLorentzVector p_phi_etap;

	 gamma1_f = new TLorentzVector();
  	 gamma2_f = new TLorentzVector();
	 pip_f = new TLorentzVector();
	 pim_f = new TLorentzVector();
 	 kp_f = new TLorentzVector();
 	 km_f = new TLorentzVector();

	chain->SetBranchAddress("gamma1_f",&gamma1_f);
  	chain->SetBranchAddress("gamma2_f",&gamma2_f);

	  chain->SetBranchAddress("pip_f",&pip_f);
	  chain->SetBranchAddress("pim_f",&pim_f);

	  chain->SetBranchAddress("kp_f",&kp_f);
	  chain->SetBranchAddress("km_f",&km_f);

	  Long64_t nevent=chain->GetEntries();
	  for(Long64_t j=0;j<nevent;j++)
  	{
   	 chain->GetEntry(j);
	 
	 p_2gam1=*gamma1_f+ *gamma2_f;
    	 m_2gam1=p_2gam1.M();

    	 p_2k=*kp_f+ *km_f;
	 m_2k=p_2k.M();

	 p_2pi=*pip_f+ *pim_f;
	 m_2pi=p_2pi.M();


	 //etap
	 p_eta_pip_pim=*gamma1_f+*gamma2_f+ *pip_f+ *pim_f;
    	 m_eta_pip_pim=p_eta_pip_pim.M();

	  //Y(2175)
	  p_phi_etap=*kp_f+ *km_f+ *gamma1_f+*gamma2_f+ *pip_f+ *pim_f;
	  m_phi_etap=p_phi_etap.M();

	 if (m_2gam1<0.50) continue;
	 if (m_2gam1>0.57) continue;

	if (m_2k<1.01) continue;
    	if (m_2k>1.03) continue;

    	if (m_2pi<0.45) continue;
    	if (m_2pi>0.95) continue;

		
	h1->Fill(m_eta_pip_pim);
	h2->Fill(m_phi_etap);

	 c1->cd(1);
  	 h1->Draw("pe");

 	 c2->cd(1);
	 h2->Draw("pe");

}
}
