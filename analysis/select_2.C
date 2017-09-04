void select_2(){
  //Jpsi->eta phi eta'
  //  eta->2gamma phi->2K eta'->gamma rho0
  //    rho0->pi+ pi- 

  //The final selection criteria and draw the graphs.
  //=**********************
  //MARK=1:draw the graphs
  //MARK=2:store the results of tree.
  //      :Data do not contain information about MCTruth.
  //      :Be careful with TreeRes->Fill()
  //=**********************
  Int_t MARK=2;

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("rightcomb_bkg_phietaetap_g3pi2k2_0912.root");

  //Store the histograms.

  if (MARK==2){
    TFile *ofile=new TFile("output_bkg_phietaetap_g3pi2k2_0912.root","RECREATE");
    TTree *TreeRes=new TTree("TreeRes","Tree Result");
  }//end with if (MARK==2)

  if (MARK==1){
    //The canvas;
    TCanvas *c1=new TCanvas();
    TCanvas *c2=new TCanvas();
    TCanvas *c3=new TCanvas();
    TCanvas *c4=new TCanvas();
    TCanvas *c5=new TCanvas();
    TCanvas *c6=new TCanvas();
    TCanvas *c7=new TCanvas();
    TCanvas *c8=new TCanvas();
 
    c1->Divide(1,1);
    c2->Divide(1,1);
    c3->Divide(1,1);
    c4->Divide(1,1);
    c5->Divide(1,1);
    c6->Divide(1,1);
    c7->Divide(2,2);
    c8->Divide(2,2);
  }//end with if (MARK==1)

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",70,0.4,0.65);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 pi",100,0.2,1.2);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",50,0.97,1.07);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h4->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h4);

  //=*********************************************************
  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",35,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h5);

  //Dalitz plot
  TH2F *h6=new TH2F ("h6","Dalitz plot;#phi+#eta' [GeV^{2}];#phi+#eta [GeV^{2}]",40,3,7,70,1,8);

  TH1F *h7=new TH1F ("h7","The mass spectrum of eta&etap",40,1.4,2.2);
  h7->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h7);
  
  TH1F *h8=new TH1F ("h8","The mass spectrum of phi&eta",50,1,3);
  h8->GetXaxis()->SetTitle("m_{#phi+#eta} [GeV]");
  setymass(h8);
  //=*********************************************************

  //Control the style of histos.
  setdivision(h1);
  setdivision(h2);
  setdivision(h3);
  setdivision(h4);

  //Chisq_cut
  Double_t Chisq_low;
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
  chain->SetBranchAddress("Chisq_low",&Chisq_low);

  if (MARK==2){
    TreeRes->Branch("m_2gam",&m_2gam,"m_2gam/D");
    TreeRes->Branch("m_2k",&m_2k,"m_2k/D");
    TreeRes->Branch("m_2pi",&m_2pi,"m_2pi/D");
    TreeRes->Branch("m_gam_rho",&m_gam_rho,"m_gam_rho/D");
    TreeRes->Branch("m_phi_etap",&m_phi_etap,"m_phi_etap/D");
    TreeRes->Branch("m_phi_eta",&m_phi_eta,"m_phi_eta/D");
    TreeRes->Branch("m_eta_etap",&m_eta_etap,"m_eta_etap/D");
    TreeRes->Branch("Chisq_low",&Chisq_low,"Chisq_low/D");

    //Store the results about MC Truth.
    //Data don't contain the information about MC Truth.
    Int_t indexmc;
    Int_t pdgid[500];
    Int_t motheridx[500];

    chain->SetBranchAddress("indexmc",&indexmc);
    chain->SetBranchAddress("pdgid",pdgid);
    chain->SetBranchAddress("motheridx",motheridx);

    TreeRes->Branch("indexmc",&indexmc,"indexmc/I");
    TreeRes->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
    TreeRes->Branch("motheridx",motheridx,"motheridx[indexmc]/I");

  }//end with if (MARK==2)

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

    //cut,3 sigma
    //=***************************
    if (m_2gam<0.487) continue;
    if (m_2gam>0.576) continue;

    if (m_2pi>0.87) continue;

    if (m_2k<1.013) continue;
    if (m_2k>1.027) continue;

    if (m_gam_rho<0.939) continue;
    if (m_gam_rho>0.972) continue;
    //=***************************

    h1->Fill(m_2gam);
    h2->Fill(m_2pi);
    h3->Fill(m_2k);
    h4->Fill(m_gam_rho);
    h5->Fill(m_phi_etap);

    //Dalitz plot
    h6->Fill(m_phi_etap*m_phi_etap,m_phi_eta*m_phi_eta);

    h7->Fill(m_eta_etap);
    h8->Fill(m_phi_eta);

    //=***************************************************
    //Store Tree Result, with if (MARK==2)
    TreeRes->Fill();
    //=***************************************************
  }

  if (MARK==1){
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

  c7->cd(1);
  h1->Draw("pe");
  box(0.25,0.85,h1);

  c7->cd(2);
  h3->Draw("pe");
  box(0.25,0.85,h3);

  c7->cd(3);
  h4->Draw("pe");
  box(0.25,0.85,h4);

  c8->cd(1);
  h5->Draw("pe");
  box(0.77,0.9,h5);

  c8->cd(2);
  h7->Draw("pe");
  box(0.77,0.9,h7);

  c8->cd(3);
  h8->Draw("pe");
  box(0.77,0.9,h8);

 /* c7->cd(4);
  h2->Draw("pe");
  box(0.77,0.9,h2);*/

  }//end with if (MARK==1)

//Store the tree results. 

  if (MARK==2){
  TreeRes->Write();
  ofile->Close();
  }//end with if (MARK==2)

}//final end
