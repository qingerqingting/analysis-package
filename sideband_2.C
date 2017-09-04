void sideband_2(){
//Get the mass spectrum of sideband events.

  //=*************************************
  //MARK=1:draw the graphs
  //MARK=2:store the results of tree.
  //=*************************************
  Int_t MARK=2;

  //The name of tree
  TChain *chain = new TChain("TreeRes");
  //The name of root file
  chain->Add("output_data_g3pi2k2_0912.root");

  //Store the histograms.

  if (MARK==2){
    TFile *ofile=new TFile("./sideband_etap.root","RECREATE");
   // TTree *TreeSide=new TTree("TreeSide","Tree Sideband");
  }//end with if (MARK==2)

  if (MARK==1){
    //The canvas;
    TCanvas *c1=new TCanvas();
  }//end with if (MARK==1)

  TH1F *h1=new TH1F ("h1","The mass spectrum of phi&etap",35,1.9,2.6);
  h1->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h1);

  Double_t m_gam_rho;
  Double_t m_phi_etap;
  Double_t ratio=1.05568;

  chain->SetBranchAddress("m_gam_rho",&m_gam_rho);
  chain->SetBranchAddress("m_phi_etap",&m_phi_etap);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    if (!(((m_gam_rho>0.862)&&(m_gam_rho<0.882))||((m_gam_rho>1.022)&&(m_gam_rho<1.042)))) continue;
    h1->Fill(m_phi_etap);
 
  }

  if (MARK==1){
 // h1->Scale(ratio);
  h1->Draw();
  }

  if (MARK==2){
  h1->Write();
  ofile->Close();
  }//end with if (MARK==2)

}//final end



