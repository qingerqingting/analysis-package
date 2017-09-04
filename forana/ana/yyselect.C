void yyselect(){

	TChain *chain=new TChain("tree");
	chain->Add("rightcomb_total.root");
	//chain.Draw("");
	//TFile *ofile=new TFile("rightcombi2_ana_001.root","RECREATE");
	
	TCanvas *c1=new TCanvas();
	TCanvas *c2=new TCanvas();

	c1->Divide(1,1);
	c2->Divide(1,1);

  	TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam1",60,0.4,0.7);
	h1->GetXaxis()->SetTitle("m_{2#gamma1} [GeV]");
  	setymass(h1);

	TH1F *h2=new TH1F ("h2","The mass spectrum of 2 gam2",60,0.4,0.7);
 	h2->GetXaxis()->SetTitle("m_{2#gamma2} [GeV]");
  	setymass(h2);

	//Control the style of histos.
	setdivision(h1);
	setdivision(h2);

	Double_t m_2gam1;
	Double_t m_2gam2;
	TLorentzVector p_2gam1;
	TLorentzVector p_2gam2;

	 gamma1_f = new TLorentzVector();
  	 gamma2_f = new TLorentzVector();
  	 gamma3_f = new TLorentzVector();
  	 gamma4_f = new TLorentzVector();


	chain->SetBranchAddress("gamma1_f",&gamma1_f);
  	chain->SetBranchAddress("gamma2_f",&gamma2_f);
  	chain->SetBranchAddress("gamma3_f",&gamma3_f);
	chain->SetBranchAddress("gamma4_f",&gamma4_f);	

	  Long64_t nevent=chain->GetEntries();
	  for(Long64_t j=0;j<nevent;j++)
  	{
   	 chain->GetEntry(j);
	  p_2gam1=*gamma1_f+ *gamma2_f;
	  m_2gam1=p_2gam1.M();

	  p_2gam2=*gamma3_f+ *gamma4_f;
   	  m_2gam2=p_2gam2.M();

	 if (m_2gam1<0.50) continue;
	 if (m_2gam1>0.57) continue;

   	 if (m_2gam2<0.50) continue;
    	 if (m_2gam2>0.57) continue;	 

	
	h1->Fill(m_2gam1);
	h2->Fill(m_2gam2);

	 c1->cd(1);
  	 h1->Draw("pe");

 	 c2->cd(1);
	 h2->Draw("pe");

//	h1->Write();
//	h2->Write();

}
}
