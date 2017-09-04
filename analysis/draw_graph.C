void draw_graph(){
//Draw the mass spectrum of data and inclusivemc

  gStyle->SetOptStat(0);

  Double_t m_phi_etap_data;
  Double_t m_phi_etap_inclusivemc;
  Double_t m_phi_etap_topo;
  Double_t m_phi_etap_phietaetap;
  Double_t m_phi_etap_phif01500;

  Int_t itopo; 
  Double_t n_phietaetap=1793; 
  Double_t n_phif01500=98; 

  //Read the leaf
  //=*********************************
  //Data
  TChain *chain1 = new TChain("TreeRes");
  chain1->Add("output_data_g3pi2k2_0912.root");
    //"name1",&name2
    // name1: from root-file.
    // name2: in this program. 
  chain1->SetBranchAddress("m_phi_etap",&m_phi_etap_data);

  //Inclusivemc
  TChain *chain2 = new TChain("TreeRes");
  chain2->Add("output_inclusivemc_g3pi2k2_0912.root");
  chain2->SetBranchAddress("m_phi_etap",&m_phi_etap_inclusivemc);

  //Inclusivemc after topology
  TChain *chain3 = new TChain("TreeRes");
  chain3->Add("output_topology_g3pi2k2_0912.root");
  chain3->SetBranchAddress("m_phi_etap",&m_phi_etap_topo);
  chain3->SetBranchAddress("itopo",&itopo);

  //Exclusivemc phietaetap
  TChain *chain4 = new TChain("TreeRes");
  chain4->Add("output_bkg_phietaetap_g3pi2k2_0912.root");
  chain4->SetBranchAddress("m_phi_etap",&m_phi_etap_phietaetap);

  //Exclusivemc phif01500
  TChain *chain5 = new TChain("TreeRes");
  chain5->Add("output_bkg_phif01500_g3pi2k2_0912.root");
  chain5->SetBranchAddress("m_phi_etap",&m_phi_etap_phif01500);

  //Histograms
  //=***********************************
  //Data
  TH1F *h1=new TH1F ("h1","The mass spectrum of phi&etap",70,1.9,2.6);
  h1->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h1);
  //Inclusivemc
  TH1F *h2=new TH1F ("h2","The mass spectrum of phi&etap",70,1.9,2.6);
  //phietaetap from inclusivemc
  TH1F *h3=new TH1F ("h3","The mass spectrum of phi&etap",70,1.9,2.6);
  h3->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h3);
  //phif0(1500) from inclusivemc
  TH1F *h4=new TH1F ("h4","The mass spectrum of phi&etap",70,1.9,2.6);
  //phietaetap from exclusivemc
  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",70,1.9,2.6);
  //phif01500 from exclusivemc
  TH1F *h6=new TH1F ("h6","The mass spectrum of phi&etap",70,1.9,2.6);

  //Data
  //=***********************************
  Long64_t nevent1=chain1->GetEntries();
  cout<<"nevent_data="<<nevent1<<endl;
  for(Long64_t j=0;j<nevent1;j++)
  {
    chain1->GetEntry(j);
    h1->Fill(m_phi_etap_data);
  }

  //Inclusivemc
  //=***********************************
  Long64_t nevent2=chain2->GetEntries();
  cout<<"nevent_inclusivemc="<<nevent2<<endl;
  for(Long64_t j=0;j<nevent2;j++)
  {
    chain2->GetEntry(j);
    h2->Fill(m_phi_etap_inclusivemc);
  }

  //Inclusivemc after topology
  //=***********************************
  Long64_t nevent3=chain3->GetEntries();
  cout<<"nevent_topo="<<nevent3<<endl;
  for(Long64_t j=0;j<nevent3;j++)
  {
    chain3->GetEntry(j);
    if (itopo==0) {
      h3->Fill(m_phi_etap_topo);
    }
    if (itopo==7) {
      h4->Fill(m_phi_etap_topo);
    }
  }

  //Exlusivemc phietaetap
  Long64_t nevent4=chain4->GetEntries();
  for(Long64_t j=0;j<nevent4;j++)
  {
    chain4->GetEntry(j);
    h5->Fill(m_phi_etap_phietaetap);
  }

  //Exlusivemc phietaetap
  Long64_t nevent5=chain5->GetEntries();
  for(Long64_t j=0;j<nevent5;j++)
  {
    chain5->GetEntry(j);
    h6->Fill(m_phi_etap_phif01500);
  }

  //Normlisation.
  h2->Scale(nevent1/h2->Integral());
  h3->Scale(nevent1*n_phietaetap/(h3->Integral()*nevent2));
  h4->Scale(nevent1*n_phif01500/(h4->Integral()*nevent2));
  h5->Scale(nevent1*n_phietaetap/(h5->Integral()*nevent2));
  h6->Scale(nevent1*n_phif01500/(h6->Integral()*nevent2));
    //Sum h5 and h6 to have h7.
  TH1F *h7=new TH1F(*h5);
  h7->Add(h5,h6,1,1);

  //Control the style of histograms.
  h2->SetLineColor(kRed);
  h3->SetLineColor(kBlue);
  h4->SetLineColor(kGreen);
  h5->SetLineColor(kRed);
  h6->SetLineColor(kGreen);
  h7->SetLineColor(kViolet);
  
 // h5->SetLineStyle(kDashed);
  h6->SetLineStyle(kDashed);
  //h7->SetLineStyle(kDashed);
  //Data
  //h1->Draw("pe");

  //Inclusivemc
  //h2->Draw("same");

  //phietaetap,inclusivemc
  h3->Draw();

  //phif01500,inclusivemc
  //h4->Draw();

  //phietaetap,exclusivemc
  h5->Draw("same");

  //phif01500,exclusivemc
  //h6->Draw("same");

  //sum of phietaetap and phif01500
  //h7->Draw("same");

  TLegend leg(.2,.7,.4,.9,"m_{#phi+#eta'}");
  leg.SetFillColor(0);
  leg.AddEntry(h3,"in.phietaetap","l");
  leg.AddEntry(h5,"ex.phietaetap","l");
  leg.DrawClone("same");
}


