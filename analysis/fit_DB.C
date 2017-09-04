void fit_DB(){
  using namespace RooFit;

  //The range of m_phi_etap
  RooRealVar m_phi_etap("m_phi_etap","m_phi_etap [GeV]",1.9,2.7);

  //Read the root file.
  TFile *f1=new TFile ("output_sigmc_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet y2175("y2175","y2175",tree,m_phi_etap);

  //Signal: double gaussian.
  RooRealVar mean("mean","mean",2.175,1.9,2.7);
  RooRealVar sigma1("sigma1","sigma1",0.03,0.001,0.1);
  RooRealVar sigma2("sigma2","sigma2",0.5,0.001,1);
  RooRealVar frac ("frac","frac",0.5,0,1);
  RooGaussian sig1 ("sig1","sig1",m_phi_etap,mean,sigma1);
  RooGaussian sig2 ("sig2","sig2",m_phi_etap,mean,sigma2);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);

  //fit
  sig.fitTo(y2175);

  RooPlot * frame=m_phi_etap.frame();
  y2175.plotOn(frame);
  sig.plotOn(frame);
  //parameters
  sig.paramOn(frame,Layout(0.55,0.95));

  frame->Draw();
}
