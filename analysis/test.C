void test(){
  //Read the data from a root file.
  //Unbinned.
  
  using namespace RooFit;
  RooRealVar m_phi_etap("m_phi_etap","m_phi_etap",1.9,2.6);
  TFile *f1=new TFile ("output_bkg_phietaetap_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet phietaetap("phietaetap","phietaetap",tree,m_phi_etap);

  RooPlot *frame=m_phi_etap.frame();
  phietaetap.plotOn(frame);
  frame->Draw();
}
