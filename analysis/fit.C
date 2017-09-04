void fit(){
//fit to the mass spectrum of phi eta'
//use the shape of phi eta eta' from MC.
//use double gauss to describe signal.

  using namespace RooFit;
  RooRealVar x("x","m_{#phi+#eta'} [GeV]",1.9,2.6);

  //Data
  TFile *f1=new TFile ("data_g3pi2k2.root");
  TH1F *h1=(TH1F*) gDirectory->Get("h1");
  RooDataHist data("data","data",x,h1);

  //Background phi eta eta' from exclusive mc.
/*  TFile *f2=new TFile ("output_bkg_phietaetap_g3pi2k2_0912_binned.root");
  TH1F *h2=(TH1F*) gDirectory->Get("h1");
  RooDataHist bkg1("bkg1","bkg1",x,h2);
  RooHistPdf bkg1_("bkg1_","bkg1_",x,bkg1,1);

  //Background phi f01500 from exclusive mc.
  TFile *f3=new TFile ("output_bkg_phif01500_g3pi2k2_0912_binned.root");
  TH1F *h3=(TH1F*) gDirectory->Get("h1");
  RooDataHist bkg2("bkg2","bkg2",x,h3);
  RooHistPdf bkg2_("bkg2_","bkg2_",x,bkg2,0); */

  //Background from inclusivemc.
 /* TFile *f2=new TFile ("output_inclusivemc_g3pi2k2_0912_binned.root");
  TH1F *h2=(TH1F*) gDirectory->Get("h1");
  RooDataHist bkg("bkg","bkg",x,h2);
  RooHistPdf bkg_("bkg_","bkg_",x,bkg,1);*/

  //Signal
  RooRealVar mean ("mean","mean",2.1,2.0,2.2);
  RooRealVar sigma1 ("sigma1","sigma1",2,0,5);
  RooRealVar sigma2 ("sigma2","sigma2",0.5,0,5);
  RooRealVar frac ("frac","frac",0.5,0,1);
  RooGaussian sig1 ("sig1","sig1",x,mean,sigma1);
  RooGaussian sig2 ("sig2","sig2",x,mean,sigma2);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);

  RooRealVar nsig("nsig","nsig",100,0,1000);
  RooRealVar nbkg1("nbkg1","nbkg1",1000,0,3000);
  RooRealVar nbkg2("nbkg2","nbkg2",50,0,1000);
  RooRealVar nbkg("nbkg","nbkg",1000,0,3000);

  RooAddPdf model("model","model",RooArgList(sig,bkg1_,bkg2_),RooArgList(nsig,nbkg1,nbkg2));
 // RooAddPdf model("model","model",RooArgList(sig,bkg_),RooArgList(nsig,nbkg));
  model.fitTo(data,Extended());

  RooPlot *frame=x.frame();
  //The parameters
  model.paramOn(frame,Layout(0.8,0.7));

 /* data.plotOn(frame);
  model.plotOn(frame,LineColor(kRed));
  model.plotOn(frame,Components(bkg1_),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(bkg2_),LineStyle(kDashed),LineColor(kGreen));
 // model.plotOn(frame,Components(bkg_),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kViolet));
  frame->Draw();*/

  //Data
  RooPlot *data_1= data.plotOn(frame);
  RooHist *h_data=data_1->getHist("h_data1");

  //model
  RooPlot *model_1= model.plotOn(frame,LineColor(kRed));
  RooCurve *c_model=model_1->getCurve("model_Norm[x]");

  //bkg1
  RooPlot *bkg1_1= model.plotOn(frame,Components(bkg1_),LineStyle(kDashed),LineColor(kBlue));
  RooCurve *c_bkg1=bkg1_1->getCurve("model_Norm[x]_Comp[bkg1_]");

  //bkg2
  RooPlot *bkg2_1= model.plotOn(frame,Components(bkg2_),LineStyle(kDashed),LineColor(kGreen));  
  RooCurve *c_bkg2=bkg2_1->getCurve("model_Norm[x]_Comp[bkg2_]");

  //bkg
 // RooPlot *bkg_1= model.plotOn(frame,Components(bkg_),LineStyle(kDashed),LineColor(kBlue));
 // RooCurve *c_bkg=bkg_1->getCurve("model_Norm[x]_Comp[bkg_]");

  //sig
  RooPlot *sig_1= model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kViolet));
  RooCurve *c_sig=sig_1->getCurve("model_Norm[x]_Comp[sig]");

  frame->Draw();

  TLegend *leg=new TLegend(0.65,0.2,0.95,0.5);
  leg->AddEntry(h_data,"Data","LPE");
  leg->AddEntry(c_model,"Model","L");
  leg->AddEntry(c_bkg1,"Phi eta etap","L");
  leg->AddEntry(c_bkg2,"Phi f0(1500)","L");
 // leg->AddEntry(c_bkg,"InclusiveMC","L");
  leg->AddEntry(c_sig,"Signal","L");
  leg->Draw();

}//final



