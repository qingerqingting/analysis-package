void fit_final(){
  //Use voigtian function to fit signal.
  //BW(x)gaussian
  //Use the shape of bkg exclusivemc to fit bkg_phietaetap.

  using namespace RooFit;
  //The range of x
  RooRealVar m_phi_etap("m_phi_etap","m_{#phi+#eta'} [GeV]",1.9,2.6);

  //Read data.
  TFile *f1=new TFile ("output_data_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet data("data","data",tree,m_phi_etap);

  //Read the shape of Jpsi->phi eta etap.
  TFile *f2=new TFile ("output_bkg_phietaetap_g3pi2k2_0912.root");
  TTree *tree2 =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet phietaetap("phietaetap","phietaetap",tree2,m_phi_etap);
  RooKeysPdf bkg("bkg","bkg",m_phi_etap,phietaetap,RooKeysPdf::NoMirror,2);

  //The signal
  //Double gaussian
 /* RooRealVar mean("mean","mean",2.175,1.9,2.6);
  RooRealVar Gamma("Gamma","Gamma",0.5,0.001,1);
  RooRealVar sigma("sigma","sigma",0.01,0.001,1);
  RooRealVar frac ("frac","frac",0.5,0,1);
  
  RooGaussian sig1 ("sig1","sig1",m_phi_etap,mean,Gamma);
  RooGaussian sig2 ("sig2","sig2",m_phi_etap,mean,sigma);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);*/

  //BW(x)gaussian:voigtian.
  RooRealVar mean ("mean","mean",2.175,1.9,2.7);
  RooRealVar Gamma ("Gamma","Gamma",0.06,0,1);
  RooRealVar sigma ("sigma","sigma",0.0157,0,1);
  sigma.setConstant(kTRUE);

  RooVoigtian sig ("sig","sig",m_phi_etap,mean,Gamma,sigma);

  //Add signal and background
  RooRealVar nsig("nsig","nsig",300,0,1000);
  RooRealVar nbkg("nbkg","nbkg",1500,0,3000);
  
  RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(nsig,nbkg));
  model.fitTo(data,Extended());

  RooPlot * frame=m_phi_etap.frame();
 /* data.plotOn(frame);
  model.plotOn(frame);
  model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(bkg),LineStyle(kDashed),LineColor(kViolet));*/

  //Parameters
  model.paramOn(frame,Layout(0.2,0.6));

  //Statistic box in roofit.
  //data.statOn(frame,Layout(0.8,0.6));

  //Prepare for legend.
  //Data
  RooPlot *data_1= data.plotOn(frame,Binning(50));
  RooHist *h_data=data_1->getHist("h_data");

  //model
  RooPlot *model_1= model.plotOn(frame,LineColor(kRed));
  RooCurve *c_model=model_1->getCurve("model_Norm[m_phi_etap]");

  //sig
  RooPlot *sig_1= model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("model_Norm[m_phi_etap]_Comp[sig]");

  //bkg1
  RooPlot *bkg_1= model.plotOn(frame,Components(bkg),LineStyle(kDashed),LineColor(kViolet));
  RooCurve *c_bkg=bkg_1->getCurve("model_Norm[m_phi_etap]_Comp[bkg]");

  frame->Draw();

  //Draw the legend.
  TLegend *leg=new TLegend(0.65,0.2,0.95,0.5);
  leg->AddEntry(h_data,"Data","LPE");
  leg->AddEntry(c_model,"Model","L");
  leg->AddEntry(c_sig,"Signal","L");
  leg->AddEntry(c_bkg,"Phi eta etap","L");
  leg->Draw();

}
