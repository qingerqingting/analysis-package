void draw_2pi(){

  //Draw the mass spectrum of pi+ pi-.
  //Compare between sigmc and etaphif0(980).

  gStyle->SetOptStat(0);

  Double_t m_2pi_980;
  Double_t m_2pi_sigmc;

  //=**************************************
  //Read
  //=**************************************

  //etaphif0(980)
  TChain *chain1 = new TChain("TreeRes");
  chain1->Add("output_bkg_etaphif0980_g3pi2k2_0912.root");
  chain1->SetBranchAddress("m_2pi",&m_2pi_980);

  //Sigmc
  TChain *chain2 = new TChain("TreeRes");
  chain2->Add("output_sigmc_g3pi2k2_0912.root");
  chain2->SetBranchAddress("m_2pi",&m_2pi_sigmc);


  //=***************************************
  //Histos
  //=***************************************
  //f0(980)
  TH1F *h1=new TH1F ("h1","m_{2#pi}",100,0.2,1.2);
  h1->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h1);

  //Sigmc
  TH1F *h2=new TH1F ("h2","m_{2#pi}",100,0.2,1.2);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);


  //f0(980)
  //=***********************************
  Long64_t nevent1=chain1->GetEntries();
  //cout<<"nevent_data="<<nevent1<<endl;
  for(Long64_t j=0;j<nevent1;j++)
  {
    chain1->GetEntry(j);
    h1->Fill(m_2pi_980);
  }

  //Sigmc
  //=***********************************
  Long64_t nevent2=chain2->GetEntries();
  //cout<<"nevent_data="<<nevent1<<endl;
  for(Long64_t j=0;j<nevent2;j++)
  {
    chain2->GetEntry(j);
    h2->Fill(m_2pi_sigmc);
  }

  //Inclusivemc after topology
  //=***********************************
 /* Long64_t nevent3=chain3->GetEntries();
  //cout<<"nevent_topo="<<nevent3<<endl;
  for(Long64_t j=0;j<nevent3;j++)
  {
    chain3->GetEntry(j);
    if (itopo==4) {
      h3->Fill(m_2pi_inclusivemc);
    }
    if (itopo==18) {
      h4->Fill(m_2pi_inclusivemc);
    }
    h5->Fill(m_2pi_inclusivemc);
  }*/

  //Normlisation.
  //=************************************

  h2->Scale(10*nevent1/h2->Integral());
  
  TCanvas *c1=new TCanvas();
 
  h2->SetLineColor(kBlue);
  h2->Draw();
  drawarrow(0.87,4,40);

  h1->SetLineColor(kViolet);
  h1->Draw("same");

 /* h3->SetLineColor(kBlue);
  //h3->SetLineStyle(kDashed);
  h3->Draw("same");

  h4->SetLineColor(kGreen);
  //h4->SetLineStyle(kDashed);
  h4->Draw("same");
 
  h5->SetLineColor(kViolet);
  h5->Draw("same");*/

  TLegend leg(.25,.5,.5,.9,"m_{2#pi}");
  leg.SetFillColor(0);
  leg.AddEntry(h1,"Eta phi f0(980)","l");
  leg.AddEntry(h2,"Signal MC","l");
  leg.DrawClone("same");
}
