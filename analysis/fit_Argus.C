void fit_Argus(){
  //Use Argus to fit

  //Read data
  RooRealVar m_phi_etap ("m_phi_etap","m_phi_etap [GeV]",0,3);
  TFile *f1=new TFile ("output_bkg_phietaetap_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet phietaetap("phietaetap","phietaetap",tree,m_phi_etap);

  //Argus Function.
 /* RooRealVar m("m","m",2,1,10);
  RooRealVar c("c","c",1,0,100);
  RooRealVar p("p","p",1,0,10);
  RooArgusBG bkg("bkg","bkg",m_phi_etap,m,c,p);*/

  RooRealVar c0("c0","c0",   0,-1,1);
  RooRealVar c1("c1","c1", 0,-1,1);
  RooRealVar c2("c2","c2", 0,-1,1);
  RooChebychev bkg("bkg","bkg",m_phi_etap,RooArgList(c0,c1,c2));
  bkg.fitTo(phietaetap);

  RooPlot *frame=m_phi_etap.frame();
  //bkg.paramOn(frame,Layout(0.2,0.6));
  phietaetap.plotOn(frame);
  bkg.plotOn(frame);

  frame->Draw();
}
