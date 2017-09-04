void draw_dalitz(){
  //Draw dalitz plot.

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("rightcomb_data_g3pi2k2_0912.root");

  TCanvas *c1=new TCanvas();

  //Dalitz plot
  TH2F *h1=new TH2F ("h1","Dalitz plot;#phi+#eta' [GeV^{2}];#phi+#eta [GeV^{2}]",35,3.5,7,70,1,8);

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
    //P
  TLorentzVector p_phi_etap;
  TLorentzVector p_phi_eta;

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

    p_phi_eta=*kp_f+ *km_f+ *gamma2_f+ *gamma2_f;
    m_phi_eta=p_phi_eta.M();

    //cut
    if (m_2gam<0.50) continue;
    if (m_2gam>0.57) continue;

    if (m_2k<1.01) continue;
    if (m_2k>1.03) continue;

    if (m_2pi<0.45) continue;
    if (m_2pi>0.87) continue;

    if (m_gam_rho<0.93) continue;
    if (m_gam_rho>0.98) continue;

    //Dalitz plot
    h1->Fill(m_phi_etap*m_phi_etap,m_phi_eta*m_phi_eta);
  }

  c1->cd(1);
  h1->Draw("coltz");
}

