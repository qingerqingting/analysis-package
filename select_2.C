void select_2(){
  //Jpsi->eta phi eta'
  //  eta->2gamma phi->2K eta'->gamma rho0
  //    rho0->pi+ pi- 

  //The final selection criteria and draw the graphs.
  //=**********************
  //fuck=1:draw the graphs
  //fuck=2:store the histos
  //fuck=3:MCtruth
  //       Be careful with TMCTruth->Fill()
  //=**********************
  Int_t fuck=1;

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("rightcomb_bkg_phif01500_g3pi2k2_0912.root");

  //Store the histograms.

  if (fuck==2){
  TFile *ofile=new TFile("output_data_g3pi2k2_0912.root","RECREATE");
  }//end with if (fuck==2)

  if (fuck==3){
  TFile *ofile=new TFile("mctruth_inclusivemc_g3pi2k2_0912.root","RECREATE");
  }//end with if (fuck==3)


  if (fuck==1){
  //The canvas;
  TCanvas *c1=new TCanvas();
  TCanvas *c2=new TCanvas();
  TCanvas *c3=new TCanvas();
  TCanvas *c4=new TCanvas();
  TCanvas *c5=new TCanvas();
  TCanvas *c6=new TCanvas();
 
  c1->Divide(1,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
  c6->Divide(1,1);
  }//end with if (fuck==1)

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",60,0.4,0.7);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 pi",100,0.3,1.3);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",40,0.9,1.1);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of gamma&rho0",50,0.7,1.2);
  h4->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h4);

  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",70,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h5);

  //Dalitz plot
  TH2F *h6=new TH2F ("h6","Dalitz plot;#phi+#eta' [GeV^{2}];#phi+#eta [GeV^{2}]",40,3,7,70,1,8);

  TH1F *h7=new TH1F ("h7","The mass spectrum of eta&etap",80,1.4,2.2);
  h7->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h7);
  
  //Control the style of histos.
  setdivision(h1);
  setdivision(h2);
  setdivision(h3);
  setdivision(h4);

  //Mass of particles.
    //eta
  Double_t m_2gam;
    //phi
  Double_t m_2k;
    //rho0
  Double_t m_2pi;
    //eta'
  Double_t m_gam_rho;
    //Y(2175)
  Double_t m_phi_etap;

  Double_t m_phi_eta;

  Double_t m_eta_etap;

  //P of particles;
    //eta
  TLorentzVector p_2gam;
    //phi
  TLorentzVector p_2k;
    //rho0
  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_gam_rho;
    //Y(2175)
  TLorentzVector p_phi_etap;

  TLorentzVector p_phi_eta;

  TLorentzVector p_eta_etap;

  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  gamma3_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  chain->SetBranchAddress("gamma1_f",&gamma1_f);
  chain->SetBranchAddress("gamma2_f",&gamma2_f);
  chain->SetBranchAddress("gamma3_f",&gamma3_f);

  chain->SetBranchAddress("pip_f",&pip_f);
  chain->SetBranchAddress("pim_f",&pim_f);

  chain->SetBranchAddress("kp_f",&kp_f);
  chain->SetBranchAddress("km_f",&km_f);

  if (fuck==3){
  Int_t indexmc;
  Int_t pdgid[500];
  Int_t motheridx[500];

  chain->SetBranchAddress("indexmc",&indexmc);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("motheridx",motheridx);

  TTree *TMCTruth=new TTree("TMCTruth","mc truth");
  TMCTruth->Branch("indexmc",&indexmc,"indexmc/I");
  TMCTruth->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
  TMCTruth->Branch("motheridx",motheridx,"motheridx[indexmc]/I");
  }//end with if (fuck==3)

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //eta
    p_2gam=*gamma2_f+ *gamma3_f;
    m_2gam=p_2gam.M();

    //phi
    p_2k=*kp_f+ *km_f;
    m_2k=p_2k.M();

    //rho0
    p_2pi=*pip_f+ *pim_f;
    m_2pi=p_2pi.M();

    //eta'
    p_gam_rho=*gamma1_f+ *pip_f+ *pim_f;
    m_gam_rho=p_gam_rho.M();

    //Y(2175)
    p_phi_etap=*kp_f+ *km_f+ *gamma1_f+ *pip_f+ *pim_f;
    m_phi_etap=p_phi_etap.M();

    //phi + eta
    p_phi_eta=*kp_f+ *km_f+ *gamma2_f+ *gamma2_f;
    m_phi_eta=p_phi_eta.M();
    
    //eta + eta'
    p_eta_etap=*gamma2_f+ *gamma3_f+ *gamma1_f+ *pip_f+ *pim_f;
    m_eta_etap=p_eta_etap.M();

    //cut
    if (m_2gam<0.50) continue;
    if (m_2gam>0.57) continue;

    if (m_2k<1.01) continue;
    if (m_2k>1.03) continue;

    if (m_2pi<0.45) continue;
    if (m_2pi>0.87) continue;

    if (m_gam_rho<0.93) continue;
    if (m_gam_rho>0.98) continue;

    h1->Fill(m_2gam);
    h2->Fill(m_2pi);
    h3->Fill(m_2k);
    h4->Fill(m_gam_rho);
    h5->Fill(m_phi_etap);

    //Dalitz plot
    h6->Fill(m_phi_etap*m_phi_etap,m_phi_eta*m_phi_eta);

    h7->Fill(m_eta_etap);
    //=*****************
    //Store MC Truth
    //TMCTruth->Fill();
    //=*****************
  }

  if (fuck==1){
  c1->cd(1);
  h1->Draw("pe");

  c2->cd(1);
  h2->Draw("pe");

  c3->cd(1);
  h3->Draw("pe");

  c4->cd(1);
  h4->Draw("pe");

  c5->cd(1);
  h5->Draw("pe");
 // box(0.77,0.9,h5);

  c6->cd(1);
  h7->Draw("pe");
 // box(0.77,0.9,h7);
  }//end with if (fuck==1)

//Store the histograms. 
  if (fuck==2){
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();
  h6->Write();
  h6->Write();
  ofile->Close();
  }//end with if(fuck==2)

  if (fuck==3){
  TMCTruth->Write();
  ofile->Close();
  }//end with if (fuck==3)

}//final end
