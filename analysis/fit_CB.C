void fit_CB(){
//use CB to fit

  using namespace RooFit;

  //The range of m_phi_etap
  RooRealVar m_phi_etap("m_phi_etap","m_{#phi+#eta'} [GeV]",1.9,2.7);

  //Read the root file.
  TFile *f1=new TFile ("output_bkg_phif01500_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet y2175("y2175","y2175",tree,m_phi_etap);

  //CB function
  RooRealVar mean("mean","mean",2.45,1.9,2.7);
  RooRealVar sigma("sigma","sigma",0.05,0.001,1);
  RooRealVar a("a","a",1,0,1000);
  RooRealVar n("n","n",1,0,1000);
  //Crystal Ball function1 
  RooCBShape sig("sig","sig",m_phi_etap,mean,sigma,a,n);

 /* RooRealVar sigma2("sigma2","sigma2",0.5,0.001,1);
  RooRealVar a2("a2","a2",1,0,1000);
  RooRealVar n2("n2","n2",1,0,1000);
  //Crystal Ball function2 
  RooCBShape sig2("sig2","sig2",m_phi_etap,mean,sigma2,a2,n2);

  RooRealVar frac("frac","frac",0.5,0,1);

  RooAddPdf sig("sig","sig",RooArgList(sig1,sig2),frac);*/

  sig.fitTo(y2175);

  RooPlot * frame=m_phi_etap.frame();
  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));

  //Prepare for legend.
  //bkg phi f0(1500): phi_etap
  RooPlot *y2175_1= y2175.plotOn(frame,Binning(40));
  RooHist *h_y2175=y2175_1->getHist("h_y2175");

  //Fit to the phi f0(1500)
  RooPlot *sig_1= sig.plotOn(frame,Components(sig),LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_phi_etap]_Comp[sig]");

  frame->Draw();

  //Draw the legend.
  TLegend *leg=new TLegend(0.75,0.7,0.95,0.95);
  leg->AddEntry(h_y2175,"Phi f_{0}(1500)","LPE");
  leg->AddEntry(c_sig,"CB function","L");
  leg->Draw();
}
