void myselect_2(){
  //Jpsi->eta phi eta'
  //  eta->2gamma phi->2K eta'->gamma rho0
  //    rho0->pi+ pi- 

  Int_t mark=2;

  TChain *chain = new TChain("tree");
  chain->Add("rightcomb_inclumc_g3pi2k2.root");

  if (mark==2){
  TFile *ofile=new TFile("output_inclumc_g3pi2k2.root","RECREATE");
  TTree *TreeRes=new TTree("TreeRes","Tree Result");
  }//end with if (mark==2)

  if (mark==1){
  TCanvas *c1=new TCanvas();
  TCanvas *c2=new TCanvas();
  TCanvas *c3=new TCanvas();
  TCanvas *c4=new TCanvas();
  TCanvas *c5=new TCanvas();
 
  c1->Divide(1,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
  }

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

  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",35,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h5);

  setdivision(h1);
  setdivision(h2);
  setdivision(h3);
  setdivision(h4);

  Double_t Chisq_low;
  Double_t m_2gam;
  Double_t m_2k;
  Double_t m_2pi;
  Double_t m_gam_rho;
  Double_t m_phi_etap;
  
  TLorentzVector p_2gam;
  TLorentzVector p_2k;
  TLorentzVector p_2pi;
  TLorentzVector p_gam_rho;
  TLorentzVector p_phi_etap;

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
  
  if (mark==2){
    TreeRes->Branch("m_2gam",&m_2gam,"m_2gam/D");
    TreeRes->Branch("m_2k",&m_2k,"m_2k/D");
    TreeRes->Branch("m_2pi",&m_2pi,"m_2pi/D");
    TreeRes->Branch("m_gam_rho",&m_gam_rho,"m_gam_rho/D");
    TreeRes->Branch("m_phi_etap",&m_phi_etap,"m_phi_etap/D");
    TreeRes->Branch("Chisq_low",&Chisq_low,"Chisq_low/D");

  Int_t indexmc;
  Int_t pdgid[500];
  Int_t motheridx[500];

  chain->SetBranchAddress("indexmc",&indexmc);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("motheridx",motheridx);

  TreeRes->Branch("indexmc",&indexmc,"indexmc/I");
  TreeRes->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
  TreeRes->Branch("motheridx",motheridx,"motheridx[indexmc]/I");
  }//end with if (mark==2)

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    p_2gam=*gamma2_f+ *gamma3_f;
    m_2gam=p_2gam.M();

    p_2k=*kp_f+ *km_f;
    m_2k=p_2k.M();

    p_2pi=*pip_f+ *pim_f;
    m_2pi=p_2pi.M();

    p_gam_rho=*gamma1_f+ *pip_f+ *pim_f;
    m_gam_rho=p_gam_rho.M();

    p_phi_etap=*kp_f+ *km_f+ *gamma1_f+ *pip_f+ *pim_f;
    m_phi_etap=p_phi_etap.M();


    //cut
    if (m_2gam<0.49) continue;
    if (m_2gam>0.57) continue;

    if (m_2k<1.01) continue;
    if (m_2k>1.03) continue;

    if (m_gam_rho<0.93) continue;
    if (m_gam_rho>0.97) continue;

    h1->Fill(m_2gam);
    h2->Fill(m_2pi);
    h3->Fill(m_2k);
    h4->Fill(m_gam_rho);
    h5->Fill(m_phi_etap);

    TreeRes->Fill();
  }

  if (mark==1){
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
  }//end with if (mark==1)

if (mark==2){
  TreeRes->Write();
  ofile->Close();
  }//end with if (mark==2)

}//final end

