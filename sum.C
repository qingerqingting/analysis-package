void sum(){
// compare sig + bkg with data

  gStyle->SetOptStat(0);
// The numbers of bin
  Int_t n_h1=40;
  Int_t n_h2=35;
  Int_t n_h3=30;
  Int_t n_h4=20;

  //Chisq_cut
  Double_t Chisq_low_sig;
  Double_t Chisq_low_bkg;
  Double_t Chisq_low_data;
  //Mass of particles.
    //eta
  Double_t m_2gam_sig;
  Double_t m_2gam_bkg;
  Double_t m_2gam_data;
    //phi
  Double_t m_2k_sig;
  Double_t m_2k_bkg;
  Double_t m_2k_data;
    //rho0
  Double_t m_2pi_sig;
  Double_t m_2pi_bkg;
  Double_t m_2pi_data;
    //eta'
  Double_t m_gam_rho_sig;
  Double_t m_gam_rho_bkg;
  Double_t m_gam_rho_data;
    //Y(2175)
  Double_t m_phi_etap_sig;
  Double_t m_phi_etap_bkg;
  Double_t m_phi_etap_data;

  Double_t m_phi_eta_sig;
  Double_t m_phi_eta_bkg;
  Double_t m_phi_eta_data;

  Double_t m_eta_etap_sig;
  Double_t m_eta_etap_bkg;
  Double_t m_eta_etap_data;

  //Read sig.
  //The name of tree
  TChain *chain1 = new TChain("TreeRes");
  //The name of root file
  chain1->Add("sig.root");

  chain1->SetBranchAddress("Chisq_low",&Chisq_low_sig);//h1
  chain1->SetBranchAddress("m_2gam",&m_2gam_sig);
  chain1->SetBranchAddress("m_2k",&m_2k_sig);
  chain1->SetBranchAddress("m_2pi",&m_2pi_sig);
  chain1->SetBranchAddress("m_gam_rho",&m_gam_rho_sig);
  chain1->SetBranchAddress("m_phi_etap",&m_phi_etap_sig);//h2
  chain1->SetBranchAddress("m_phi_eta",&m_phi_eta_sig);//h3
  chain1->SetBranchAddress("m_eta_etap",&m_eta_etap_sig);//h4

  //The histos;
  TH1F *h1_sig=new TH1F ("h1_sig","Chisq_4c",n_h1,0,40);
  h1_sig->GetXaxis()->SetTitle("Chisq_{4C}");
  h1_sig->GetYaxis()->SetTitle("Events/1");

  TH1F *h2_sig=new TH1F ("h2_sig","The mass spectrum of phi&etap",n_h2,1.9,2.6);
  h2_sig->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h2_sig);

  TH1F *h3_sig=new TH1F ("h3_sig","The mass spectrum of phi&eta",n_h3,1.4,2.4);
  h3_sig->GetXaxis()->SetTitle("m_{#phi+#eta} [GeV]");
  setymass(h3_sig);

  TH1F *h4_sig=new TH1F ("h4_sig","The mass spectrum of eta&etap",n_h4,1.4,2.2);
  h4_sig->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h4_sig);

  TH1F *h5_sig=new TH1F ("h5_sig","The mass spectrum of 2 gam",70,0.4,0.65);
  h5_sig->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h5_sig);

  TH1F *h6_sig=new TH1F ("h6_sig","The mass spectrum of 2 pi",50,0.2,1.2);
  h6_sig->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h6_sig);

  TH1F *h7_sig=new TH1F ("h7_sig","The mass spectrum of 2 k",50,0.97,1.07);
  h7_sig->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h7_sig);

  TH1F *h8_sig=new TH1F ("h8_sig","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h8_sig->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h8_sig);

  Long64_t nevent=chain1->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain1->GetEntry(j);
    h1_sig->Fill(Chisq_low_sig);
    h2_sig->Fill(m_phi_etap_sig);
    h3_sig->Fill(m_phi_eta_sig);
    h4_sig->Fill(m_eta_etap_sig);
    h5_sig->Fill(m_2gam_sig);
    h6_sig->Fill(m_2pi_sig);
    h7_sig->Fill(m_2k_sig);
    h8_sig->Fill(m_gam_rho_sig);
  }//End with sig.

  //Read bkg.
  //The name of tree
  TChain *chain2 = new TChain("TreeRes");
  //The name of root file
  chain2->Add("bkg.root");

  chain2->SetBranchAddress("Chisq_low",&Chisq_low_bkg);//h1
  chain2->SetBranchAddress("m_2gam",&m_2gam_bkg);
  chain2->SetBranchAddress("m_2k",&m_2k_bkg);
  chain2->SetBranchAddress("m_2pi",&m_2pi_bkg);
  chain2->SetBranchAddress("m_gam_rho",&m_gam_rho_bkg);
  chain2->SetBranchAddress("m_phi_etap",&m_phi_etap_bkg);//h2
  chain2->SetBranchAddress("m_phi_eta",&m_phi_eta_bkg);//h3
  chain2->SetBranchAddress("m_eta_etap",&m_eta_etap_bkg);//h4

  //The histos;
  TH1F *h1_bkg=new TH1F ("h1_bkg","Chisq_4c",n_h1,0,40);
  h1_bkg->GetXaxis()->SetTitle("Chisq_{4C}");
  h1_bkg->GetYaxis()->SetTitle("Events/1");

  TH1F *h2_bkg=new TH1F ("h2_bkg","The mass spectrum of phi&etap",n_h2,1.9,2.6);
  h2_bkg->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h2_bkg);

  TH1F *h3_bkg=new TH1F ("h3_bkg","The mass spectrum of phi&eta",n_h3,1.4,2.4);
  h3_bkg->GetXaxis()->SetTitle("m_{#phi+#eta} [GeV]");
  setymass(h3_bkg);

  TH1F *h4_bkg=new TH1F ("h4_bkg","The mass spectrum of eta&etap",n_h4,1.4,2.2);
  h4_bkg->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h4_bkg);

  TH1F *h5_bkg=new TH1F ("h5_bkg","The mass spectrum of 2 gam",70,0.4,0.65);
  h5_bkg->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h5_bkg);

  TH1F *h6_bkg=new TH1F ("h6_bkg","The mass spectrum of 2 pi",50,0.2,1.2);
  h6_bkg->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h6_bkg);

  TH1F *h7_bkg=new TH1F ("h7_bkg","The mass spectrum of 2 k",50,0.97,1.07);
  h7_bkg->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h7_bkg);

  TH1F *h8_bkg=new TH1F ("h8_bkg","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h8_bkg->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h8_bkg);

  Long64_t nevent=chain2->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain2->GetEntry(j);
    h1_bkg->Fill(Chisq_low_bkg);
    h2_bkg->Fill(m_phi_etap_bkg);
    h3_bkg->Fill(m_phi_eta_bkg);
    h4_bkg->Fill(m_eta_etap_bkg);
    h5_bkg->Fill(m_2gam_bkg);
    h6_bkg->Fill(m_2pi_bkg);
    h7_bkg->Fill(m_2k_bkg);
    h8_bkg->Fill(m_gam_rho_bkg);
  }//End with bkg.

  //Read data.
  //The name of tree
  TChain *chain3 = new TChain("TreeRes");
  //The name of root file
  chain3->Add("data.root");

  chain3->SetBranchAddress("Chisq_low",&Chisq_low_data);//h1
  chain3->SetBranchAddress("m_2gam",&m_2gam_data);
  chain3->SetBranchAddress("m_2k",&m_2k_data);
  chain3->SetBranchAddress("m_2pi",&m_2pi_data);
  chain3->SetBranchAddress("m_gam_rho",&m_gam_rho_data);
  chain3->SetBranchAddress("m_phi_etap",&m_phi_etap_data);//h2
  chain3->SetBranchAddress("m_phi_eta",&m_phi_eta_data);//h3
  chain3->SetBranchAddress("m_eta_etap",&m_eta_etap_data);//h4

  //The histos;
  TH1F *h1_data=new TH1F ("h1_data","Chisq_4c",n_h1,0,40);
  h1_data->GetXaxis()->SetTitle("Chisq_{4C}");
  h1_data->GetYaxis()->SetTitle("Events/1");

  TH1F *h2_data=new TH1F ("h2_data","The mass spectrum of phi&etap",n_h2,1.9,2.6);
  h2_data->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h2_data);

  TH1F *h3_data=new TH1F ("h3_data","The mass spectrum of phi&eta",n_h3,1.4,2.4);
  h3_data->GetXaxis()->SetTitle("m_{#phi+#eta} [GeV]");
  setymass(h3_data);

  TH1F *h4_data=new TH1F ("h4_data","The mass spectrum of eta&etap",n_h4,1.4,2.2);
  h4_data->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h4_data);

  TH1F *h5_data=new TH1F ("h5_data","The mass spectrum of 2 gam",70,0.4,0.65);
  h5_data->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h5_data);

  TH1F *h6_data=new TH1F ("h6_data","The mass spectrum of 2 pi",50,0.2,1.2);
  h6_data->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h6_data);

  TH1F *h7_data=new TH1F ("h7_data","The mass spectrum of 2 k",50,0.97,1.07);
  h7_data->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h7_data);

  TH1F *h8_data=new TH1F ("h8_data","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h8_data->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h8_data);

  Long64_t nevent=chain3->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain3->GetEntry(j);
    h1_data->Fill(Chisq_low_data);
    h2_data->Fill(m_phi_etap_data);
    h3_data->Fill(m_phi_eta_data);
    h4_data->Fill(m_eta_etap_data);
    h5_data->Fill(m_2gam_data);
    h6_data->Fill(m_2pi_data);
    h7_data->Fill(m_2k_data);
    h8_data->Fill(m_gam_rho_data);
  }//End with data.

  //Scale and sum
  Double_t n_sig=h1_sig->GetEntries();
  Double_t n_bkg=h1_bkg->GetEntries();

  //=**********************
  Double_t N_sig=247;
  Double_t N_bkg=1280;
  //=**********************

  Double_t sf_sig=N_sig/n_sig;
  Double_t sf_bkg=N_bkg/n_bkg;

  TH1F *h1_sum=new TH1F(*h1_sig);
  h1_sum->Add(h1_sig,h1_bkg,sf_sig,sf_bkg);

  TH1F *h2_sum=new TH1F(*h2_sig);
  h2_sum->Add(h2_sig,h2_bkg,sf_sig,sf_bkg);

  TH1F *h3_sum=new TH1F(*h3_sig);
  h3_sum->Add(h3_sig,h3_bkg,sf_sig,sf_bkg);

  TH1F *h4_sum=new TH1F(*h4_sig);
  h4_sum->Add(h4_sig,h4_bkg,sf_sig,sf_bkg);

  TH1F *h5_sum=new TH1F(*h5_sig);
  h5_sum->Add(h5_sig,h5_bkg,sf_sig,sf_bkg);

  TH1F *h6_sum=new TH1F(*h6_sig);
  h6_sum->Add(h6_sig,h6_bkg,sf_sig,sf_bkg);

  TH1F *h7_sum=new TH1F(*h7_sig);
  h7_sum->Add(h7_sig,h7_bkg,sf_sig,sf_bkg);

  TH1F *h8_sum=new TH1F(*h8_sig);
  h8_sum->Add(h8_sig,h8_bkg,sf_sig,sf_bkg);

  TCanvas *c1=new TCanvas();
  c1->Divide(2,2);

  c1->cd(1);
  h1_data->Draw("pe");
  h1_sum->SetLineColor(kRed);
  h1_sum->Draw("same");
  
  c1->cd(2);
  h2_data->Draw("pe");
  h2_sum->SetLineColor(kRed);
  h2_sum->Draw("same");

  c1->cd(3);
  h3_data->Draw("pe");
  h3_sum->SetLineColor(kRed);
  h3_sum->Draw("same");

  c1->cd(4);
  h4_data->Draw("pe");
  h4_sum->SetLineColor(kRed);
  h4_sum->Draw("same");

  TCanvas *c2=new TCanvas();
  c2->Divide(2,2);

  c2->cd(1);
  h5_data->Draw("pe");
  h5_sum->SetLineColor(kRed);
  h5_sum->Draw("same");

  c2->cd(2);
  h6_data->Draw("pe");
  h6_sum->SetLineColor(kRed);
  h6_sum->Draw("same");

  c2->cd(3);
  h7_data->Draw("pe");
  h7_sum->SetLineColor(kRed);
  h7_sum->Draw("same");

  c2->cd(4);
  h8_data->Draw("pe");
  h8_sum->SetLineColor(kRed);
  h8_sum->Draw("same");
}
