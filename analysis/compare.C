void compare(){
//compare between Data and MC.
  gStyle->SetOptStat(0);

  //1 stand for Data.
  Double_t m_2gam_1;
  Double_t m_2pi_1;
  Double_t m_2k_1;
  Double_t m_gam_rho_1;

  //2 stand for MC.
  Double_t m_2gam_2;
  Double_t m_2pi_2;
  Double_t m_2k_2;
  Double_t m_gam_rho_2;

  Double_t N=10000;

  //Read the leaf
  //=*********************************
  //Data
  TChain *chain1 = new TChain("TreeRes");
  chain1->Add("output_data_g3pi2k2_0912.root");
  chain1->SetBranchAddress("m_2gam",&m_2gam_1);
  chain1->SetBranchAddress("m_2pi",&m_2pi_1);
  chain1->SetBranchAddress("m_2k",&m_2k_1);
  chain1->SetBranchAddress("m_gam_rho",&m_gam_rho_1);

  //MC: Jpsi->phi eta etap.
  TChain *chain2 = new TChain("TreeRes");
  chain2->Add("output_bkg_phietaetap_g3pi2k2_0912.root");
  chain2->SetBranchAddress("m_2gam",&m_2gam_2);
  chain2->SetBranchAddress("m_2pi",&m_2pi_2);
  chain2->SetBranchAddress("m_2k",&m_2k_2);
  chain2->SetBranchAddress("m_gam_rho",&m_gam_rho_2);

  //Data
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",50,0.4,0.65);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 pi",50,0.2,1.2);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",40,0.98,1.06);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h4->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h4);

  //MC:
  TH1F *h5=new TH1F ("h5","The mass spectrum of 2 gam",50,0.4,0.65);
  h5->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h5);

  TH1F *h6=new TH1F ("h6","The mass spectrum of 2 pi",50,0.2,1.2);
  h6->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h7=new TH1F ("h7","The mass spectrum of 2 k",40,0.98,1.06);
  h7->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h8=new TH1F ("h8","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h8->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h8);

  //Data
  //=***********************************
  Long64_t nevent1=chain1->GetEntries();
  for(Long64_t j=0;j<nevent1;j++)
  {
    chain1->GetEntry(j);
    //fill eta, cut on rho, etap, phi
   /* if ((m_2pi_1<0.87)&&(m_2k_1>1.013)&&(m_2k_1<1.027)&&(m_gam_rho_1>0.939)&&(m_gam_rho_1<0.972)) h1->Fill(m_2gam_1);
    //fill rho, cut on eta, etap, phi
    if ((m_2gam_1>0.487)&&(m_2gam_1<0.576)&&(m_2k_1<1.027)&&(m_gam_rho_1>0.939)&&(m_gam_rho_1<0.972)) h2->Fill(m_2pi_1);
    //fill phi, cut on eta, rho, etap
    if ((m_2gam_1>0.487)&&(m_2gam_1<0.576)&&(m_2pi_1<0.87)&&(m_gam_rho_1>0.939)&&(m_gam_rho_1<0.972)) h3->Fill(m_2k_1);
    //fill etap, cut on eta, rho, phi
    if ((m_2gam_1>0.487)&&(m_2gam_1<0.576)&&(m_2pi_1<0.87)&&(m_2k_1>1.013)&&(m_2k_1<1.027)) h4->Fill(m_gam_rho_1);*/
    h1->Fill(m_2gam_1);
    h2->Fill(m_2pi_1);
    h3->Fill(m_2k_1);
    h4->Fill(m_gam_rho_1);

  }

  //MC
  //=***********************************
  Long64_t nevent2=chain2->GetEntries();
  for(Long64_t j=0;j<nevent2;j++)
  {
    chain2->GetEntry(j);
    //fill eta, cut on rho, etap, phi
   /* if ((m_2pi_2<0.87)&&(m_2k_2>1.013)&&(m_2k_2<1.027)&&(m_gam_rho_2>0.939)&&(m_gam_rho_2<0.972)) h5->Fill(m_2gam_2);
    //fill rho, cut on eta, etap, phi
    if ((m_2gam_2>0.487)&&(m_2gam_2<0.576)&&(m_2k_2<1.027)&&(m_gam_rho_2>0.939)&&(m_gam_rho_2<0.972)) h6->Fill(m_2pi_2);
    //fill phi, cut on eta, rho, etap
    if ((m_2gam_2>0.487)&&(m_2gam_2<0.576)&&(m_2pi_2<0.87)&&(m_gam_rho_2>0.939)&&(m_gam_rho_2<0.972)) h7->Fill(m_2k_2);
    //fill etap, cut on eta, rho, phi
    if ((m_2gam_2>0.487)&&(m_2gam_2<0.576)&&(m_2pi_2<0.87)&&(m_2k_2>1.013)&&(m_2k_2<1.027)) h8->Fill(m_gam_rho_2);
    */
    h5->Fill(m_2gam_2);
    h6->Fill(m_2pi_2);
    h7->Fill(m_2k_2);
    h8->Fill(m_gam_rho_2);
  }

  //Normlisation.
  h1->Scale(N/h1->Integral());
  h2->Scale(N/h2->Integral());
  h3->Scale(N/h3->Integral());
  h4->Scale(N/h4->Integral());
  h5->Scale(N/h5->Integral());
  h6->Scale(N/h6->Integral());
  h7->Scale(N/h7->Integral());
  h8->Scale(N/h8->Integral());

  //The style of histos.
  h5->SetLineColor(kRed);
  h6->SetLineColor(kRed);
  h7->SetLineColor(kRed);
  h8->SetLineColor(kRed);

  TCanvas *c1=new TCanvas();
  c1->Divide(2,2);

  c1->cd(1);
  h1->Draw("pe");
  h5->Draw("same");
  TLegend leg1(.2,.5,.5,.9,"m_{2#gamma}");
  leg1.SetFillColor(0);
  leg1.AddEntry(h1,"Data","lpe");
  leg1.AddEntry(h5,"MC:phi eta etap","l");
  leg1.DrawClone("same");

  c1->cd(2);
  h2->Draw("pe");
  h6->Draw("same");
  TLegend leg2(.2,.5,.5,.9,"m_{2#pi}");
  leg2.SetFillColor(0);
  leg2.AddEntry(h2,"Data","lpe");
  leg2.AddEntry(h6,"MC:phi eta etap","l");
  leg2.DrawClone("same");

  c1->cd(3);
  h3->Draw("pe");
  h7->Draw("same");
  TLegend leg3(.2,.5,.5,.9,"m_{2k}");
  leg3.SetFillColor(0);
  leg3.AddEntry(h3,"Data","lpe");
  leg3.AddEntry(h7,"MC:phi eta etap","l");
  leg3.DrawClone("same");

  c1->cd(4);
  h4->Draw("pe");
  h8->Draw("same");
  TLegend leg4(.2,.5,.5,.9,"m_{#gamma+#rho^{0}}");
  leg4.SetFillColor(0);
  leg4.AddEntry(h4,"Data","lpe");
  leg4.AddEntry(h8,"MC:phi eta etap","l");
  leg4.DrawClone("same");

}
