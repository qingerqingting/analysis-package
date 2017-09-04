void select_3(){
//Convert unbinned data to binned.

  //The name of tree
  TChain *chain = new TChain("TreeRes");
  //The name of root file
  chain->Add("output_inclusivemc_g3pi2k2_0912.root");
  TFile *ofile=new TFile("output_inclusivemc_g3pi2k2_0912_binned.root","RECREATE");

  Double_t m_phi_etap;

  TH1F *h1=new TH1F ("h1","The mass spectrum of phi&etap",70,1.9,2.6);
  h1->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h1);

  chain->SetBranchAddress("m_phi_etap",&m_phi_etap);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    h1->Fill(m_phi_etap);
  }

  h1->Write();
  ofile->Close();
}
