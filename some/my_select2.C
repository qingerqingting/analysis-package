void my_select2(){
  //Jpsi->eta phi eta'
  //  eta->2gamma phi->2K eta'->eta pip pim

  //The final selection criteria and draw the graphs.
  //=**********************
  //fight=1:draw the graphs
  //fight=2:store the histos
  //fight=3:MCtruth
  //       Be careful with TMCTruth->Fill()
  //=**********************
  Int_t fight=2;

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("rightcomb_mceagle.root");

  //Store the histograms.

  if (fight==2){
  TFile *ofile=new TFile("output_mceagle.root","RECREATE");
  }//end with if (fight==2)

  if (fight==3){
  TFile *ofile=new TFile("mctruth_inclusivemc_mceagle.root","RECREATE");
  }//end with if (fight==3)


  if (fight==1){
  //The canvas;
  TCanvas *c1=new TCanvas();
  TCanvas *c2=new TCanvas();
  TCanvas *c3=new TCanvas();
  TCanvas *c4=new TCanvas();
  TCanvas *c5=new TCanvas();
  TCanvas *c6=new TCanvas();
 
  c1->Divide(2,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
  c6->Divide(1,1);
  }//end with if (fight==1)

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam1",60,0.4,0.7);
  h1->GetXaxis()->SetTitle("m_{2#gamma1} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 gam2",60,0.4,0.7);
  h2->GetXaxis()->SetTitle("m_{2#gamma2} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",40,0.9,1.1);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of eta&pip&pim",50,0.7,1.2);
  h4->GetXaxis()->SetTitle("m_{#eta+#pi^{+}+#pi^{-}} [GeV]");
  setymass(h4);

  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",20,1.9,2.6);
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
  setdivision(h5);

  //Mass of particles.
    //eta
  Double_t m_2gam1;
  Double_t m_2gam2;
    //phi
  Double_t m_2k;
    //rho0
  Double_t m_2pi;
    //eta'
  Double_t m_gam_rho;
    //Y(2175)
  Double_t m_phi_etap1;
  Double_t m_phi_etap2;
  Double_t m_phi_etap;

  Double_t m_phi_eta;

  Double_t m_eta_pip_pim1;
  Double_t m_eta_pip_pim2;
  Double_t m_eta_pip_pim;

  //P of particles;
    //eta
  TLorentzVector p_2gam1;
  TLorentzVector p_2gam2;
    //phi
  TLorentzVector p_2k;
    //rho0
  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_gam_rho;
    //Y(2175)
  TLorentzVector p_phi_etap1;
  TLorentzVector p_phi_etap2;

  TLorentzVector p_phi_eta;

  TLorentzVector p_eta_pip_pim1;
  TLorentzVector p_eta_pip_pim2;

  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  gamma3_f = new TLorentzVector();
  gamma4_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  chain->SetBranchAddress("gamma1_f",&gamma1_f);
  chain->SetBranchAddress("gamma2_f",&gamma2_f);
  chain->SetBranchAddress("gamma3_f",&gamma3_f);
  chain->SetBranchAddress("gamma4_f",&gamma4_f);

  chain->SetBranchAddress("pip_f",&pip_f);
  chain->SetBranchAddress("pim_f",&pim_f);

  chain->SetBranchAddress("kp_f",&kp_f);
  chain->SetBranchAddress("km_f",&km_f);

/*  if (fight==2){
    TTree *TreeRes=new TTree("TreeRes","mc truth");
    TreeRes->Branch("m_2gam_1",&m_2gam_1,"m_2gam_1/D");
    TreeRes->Branch("m_2gam_2",&m_2gam_2,"m_2gam_2/D");
    TreeRes->Branch("m_2k",&m_2k,"m_2k/D");
    TreeRes->Branch("m_pipieta",&m_pipieta,"m_pipieta/D");
    TreeRes->Branch("m_phi_etap",&m_phi_etap,"m_phi_etap/D");}*/

  if (fight==3){
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
  }//end with if (fight==3)

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {// cout << j << endl;
    chain->GetEntry(j);

    //eta
    p_2gam1=*gamma1_f+ *gamma2_f;
    m_2gam1=p_2gam1.M();

    p_2gam2=*gamma3_f+ *gamma4_f;
    m_2gam2=p_2gam2.M();

    //phi
    p_2k=*kp_f+ *km_f;
    m_2k=p_2k.M();

    //eta'
    p_eta_pip_pim1=p_2gam1+*pip_f+ *pim_f;
    m_eta_pip_pim1=p_eta_pip_pim1.M();

    p_eta_pip_pim2=p_2gam2+*pip_f+ *pim_f;
    m_eta_pip_pim2=p_eta_pip_pim2.M();

    p_phi_etap1=p_2k+p_eta_pip_pim1;
    m_phi_etap1=p_phi_etap1.M();
    p_phi_etap2=p_2k+p_eta_pip_pim2;
    m_phi_etap2=p_phi_etap2.M();
    //cut
  /*  if (m_2gam1<0.50) continue;
    if (m_2gam1>0.57) continue;

    if (m_2gam2<0.50) continue;
    if (m_2gam2>0.57) continue;

    if (m_2k<1.01) continue;
    if (m_2k>1.03) continue;*/

    Double_t up=1.1;
    Double_t low=0.8;
    if (low<m_eta_pip_pim1&&m_eta_pip_pim1<up&&low<m_eta_pip_pim2&&m_eta_pip_pim2<up) continue;
    if (((low>m_eta_pip_pim1)||(m_eta_pip_pim1>up))&&((low>m_eta_pip_pim2)||(m_eta_pip_pim2>up))) continue;
    if ((low<m_eta_pip_pim1&&m_eta_pip_pim1<up)&&((low>m_eta_pip_pim2)||(m_eta_pip_pim2>up)))
    {
    m_eta_pip_pim=m_eta_pip_pim1;
    m_phi_etap=m_phi_etap1;
   // h4->Fill(m_eta_pip_pim);
   // h5->Fill(m_phi_etap);
    }
    if ((low<m_eta_pip_pim2&m_eta_pip_pim2<up)&&((low>m_eta_pip_pim1)||(m_eta_pip_pim1>up)))
    {
    m_eta_pip_pim=m_eta_pip_pim2;
    m_phi_etap=m_phi_etap2;
    //h4->Fill(m_eta_pip_pim);
    //h5->Fill(m_phi_etap);
    }

    h1->Fill(m_2gam1);
    h2->Fill(m_2gam2);
    h3->Fill(m_2k);
    h4->Fill(m_eta_pip_pim);
    h5->Fill(m_phi_etap);
    //=*****************
    //Store MC Truth
    //TMCTruth->Fill();
    //=*****************
  }

  if (fight==1){
  c1->cd(1);
  h1->Draw("pe");

  c1->cd(2);
  h2->Draw("pe");

  c3->cd(1);
  h3->Draw("pe");

  c4->cd(1);
  h4->Draw("pe");

  c5->cd(1);
  h5->Draw("pe");
 // box(0.77,0.9,h5);

  //c6->cd(1);
 // h7->Draw("pe");
 // box(0.77,0.9,h7);
  }//end with if (fight==1)

//Store the histograms. 
  if (fight==2){
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();
  h6->Write();
  h7->Write();
  ofile->Close();
  }//end with if(fight==2)

  if (fight==3){
  TMCTruth->Write();
  ofile->Close();
  }//end with if (fight==3)

}//final end
