void fit_sideband(){
//Fit to the mass spectrum of etap.
//Double CB function to fit signal.
//Chebychev function to fit background.

  using namespace RooFit;

  Double_t low=0.8;
  Double_t up=1.1;

  //Sideband

    //1 means the left sideband.
  Double_t left_1=0.862;
  Double_t right_1=0.882;

    //2 means the right sideband.
  Double_t left_2=1.022;
  Double_t right_2=1.042;

    //m means middle signal region.
  Double_t left_3=0.932;
  Double_t right_3=0.972;

  //The range of m_gam_rho
  RooRealVar m_gam_rho("m_gam_rho","m_gam_rho [GeV]",low,up);

  //Read the root file.
  TFile *f1=new TFile ("output_data_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet etap("etap","etap",tree,m_gam_rho);

  //The paremeters of signal function.
  //CB fuction.
  RooRealVar mean("mean","mean",0.958,low,up);
  RooRealVar sigma1("sigma1","sigma1",0.01,0.001,0.1);
  RooRealVar a1("a1","a1",1,0,1000);
  RooRealVar n1("n1","n1",1,0,1000);
  //Crystal Ball function 
  RooCBShape sig1("sig1","sig1",m_gam_rho,mean,sigma1,a1,n1);

  RooRealVar sigma2("sigma2","sigma2",0.05,0.001,0.1);
  RooRealVar a2("a2","a2",1,0,1000);
  RooRealVar n2("n2","n2",1,0,1000);
  //Crystal Ball function 
  RooCBShape sig2("sig2","sig2",m_gam_rho,mean,sigma2,a2,n2);

  //Double CB function
  RooRealVar frac("frac","frac",0.5,0,1);
  RooAddPdf sig("sig","sig",RooArgList(sig1,sig2),frac);

  //Background function
  RooRealVar c0("c0","coefficient #0", 0.1,-1.,1.) ;
  RooRealVar c1("c1","coefficient #1", 0.1,-1.,1.) ;
  RooRealVar c2("c2","coefficient #2",-0.1,-1.,1.) ;
  RooChebychev bkg("bkg","background p.d.f.",m_gam_rho,RooArgList(c0,c1,c2)) ;

  //Numbers of sig and bkg events.
  RooRealVar nsig("nsig","nsig",1000,0,2000);
  RooRealVar nbkg("nbkg","nbkg",1000,0,2000);

  RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(nsig,nbkg));

  model.fitTo(etap,Extended());

  RooPlot * frame=m_gam_rho.frame();

  model.paramOn(frame,Layout(0.65,0.95));

  /*etap.plotOn(frame,Binning(50));
  model.plotOn(frame,LineColor(kRed));
  model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(frame,Components(bkg),LineStyle(kDashed),LineColor(kGreen));*/

  //Prepare for legend.
  //The names of hist and curve are from c1.C
  //Prepare for legend.
  RooPlot *etap_1= etap.plotOn(frame,Binning(50));
  RooHist *h_etap=etap_1->getHist("h_etap");

  //model
  RooPlot *model_1= model.plotOn(frame,LineColor(kRed));
  RooCurve *c_model=model_1->getCurve("model_Norm[m_gam_rho]");

  //sig
  RooPlot *sig_1= model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("model_Norm[m_gam_rho]_Comp[sig]");

  //bkg1
  RooPlot *bkg_1= model.plotOn(frame,Components(bkg),LineStyle(kDashed),LineColor(kViolet));
  RooCurve *c_bkg=bkg_1->getCurve("model_Norm[m_gam_rho]_Comp[bkg]");

  //Draw arrows
  Double_t y_1=0;
  Double_t y_2=200;

    //1 sideband
  //left
  TArrow *ar_l_1=new TArrow(left_1,y_1,left_1,y_2,0.01,"<");
  ar_l_1->SetLineColor(kRed);
  ar_l_1->SetLineWidth(2);
  frame->addObject(ar_l_1);

  //right
  TArrow *ar_r_1=new TArrow(right_1,y_1,right_1,y_2,0.01,"<");
  ar_r_1->SetLineColor(kRed);
  ar_r_1->SetLineWidth(2);
  frame->addObject(ar_r_1);

    //2 sideband
  //left
  TArrow *ar_l_2=new TArrow(left_2,y_1,left_2,y_2,0.01,"<");
  ar_l_2->SetLineColor(kRed);
  ar_l_2->SetLineWidth(2);
  frame->addObject(ar_l_2);

  //right
  TArrow *ar_r_2=new TArrow(right_2,y_1,right_2,y_2,0.01,"<");
  ar_r_2->SetLineColor(kRed);
  ar_r_2->SetLineWidth(2);
  frame->addObject(ar_r_2);

    //3 signal region
  //left
  TArrow *ar_l_3=new TArrow(left_3,y_1,left_3,y_2,0.01,"<");
  ar_l_3->SetLineColor(kRed);
  ar_l_3->SetLineWidth(2);
  frame->addObject(ar_l_3);

  //right
  TArrow *ar_r_3=new TArrow(right_3,y_1,right_3,y_2,0.01,"<");
  ar_r_3->SetLineColor(kRed);
  ar_r_3->SetLineWidth(2);
  frame->addObject(ar_r_3);


  frame->Draw();

  //legend 
  TLegend *leg=new TLegend(0.2,0.7,0.5,0.95);
  leg->AddEntry(h_etap,"Data: etap","LPE");
  leg->AddEntry(c_model,"Model","L");
  leg->AddEntry(c_sig,"Sig: Double CB","L");
  leg->AddEntry(c_bkg,"Bkg: Chebychev","L");
  leg->Draw();

  //Integral

    //Left sideband
  m_gam_rho.setRange("cut1",left_1,right_1);
  RooAbsReal *n_bkg_1=bkg.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut1"));
  Double_t N_bkg_1= n_bkg_1->getVal();

    //Right sideband
  m_gam_rho.setRange("cut2",left_2,right_2);  
  RooAbsReal *n_bkg_2=bkg.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut2"));
  Double_t N_bkg_2= n_bkg_2->getVal();

    //Signal region
  m_gam_rho.setRange("cut3",left_3,right_3);
  RooAbsReal *n_bkg_3=bkg.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut3"));
  Double_t N_bkg_3= n_bkg_3->getVal();

  cout<<"Left sideband = "<<N_bkg_1<<endl;
  cout<<"Right sideband = "<<N_bkg_2<<endl;
  cout<<"Signal region = "<<N_bkg_3<<endl;

  Double_t ratio;
  ratio=N_bkg_3/(N_bkg_1+N_bkg_2);
  cout<<"ratio=N_sig/N_bkg="<<ratio<<endl;

}
