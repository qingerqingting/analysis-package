#include "/afs/ihep.ac.cn/users/l/longyf/useful.h"

void fit(){
//fit to the mass spectrum of 2_k vs gam_rho
//Before the cut on m_2k and m_gam_rho

  //Use double gaussian to fit phi.
  //Use double CB to fit etap.
  //Use 2nd Chebychev to fit bkg.
  using namespace RooFit;

  //Control the style
  SetLyfStyle();

  //The ranges of fit
  //phi, in x axis
  Double_t low_x=0.99;
  Double_t up_x=1.1;

  //etap, in y axis
  Double_t low_y=0.75;
  Double_t up_y=1.1;

  //The number of bins
  Double_t nbin_x=55;
  Double_t nbin_y=70;

  //The range of m_2k
  RooRealVar m_2k("m_2k","m_2k [GeV]",low_x,up_x);

  //The range of m_gam_rho
  RooRealVar m_gam_rho("m_gam_rho","m_gam_rho [GeV]",low_y,up_y);

  //Read the root file.
  TFile *f1=new TFile ("output_for_phi_etap.root");
  TTree *tree1 =(TTree*) gDirectory->Get("TreeRes");

  //Data: 2d (x is phi ,y is etap)
  RooDataSet data("data","data",tree1,RooArgSet(m_2k,m_gam_rho));

  //Signal
  //=***********
  //Signal: double gaussian, to describe phi in x.
  RooRealVar mean_x("mean_x","mean_x",1.02,low_x,up_x);
  RooRealVar sigma1_x("sigma1_x","sigma1_x",0.03,0.001,0.1);
  RooRealVar sigma2_x("sigma2_x","sigma2_x",0.5,0.001,1);
  RooRealVar frac_x ("frac_x","frac_x",0.5,0,1);
  RooGaussian sig1_x ("sig1_x","sig1_x",m_2k,mean_x,sigma1_x);
  RooGaussian sig2_x ("sig2_x","sig2_x",m_2k,mean_x,sigma2_x);
  RooAddPdf sig_x ("sig_x","sig_x",RooArgList(sig1_x,sig2_x),frac_x);

  //Singal: double CB function, to describe etap in y.
  RooRealVar mean_y("mean_y","mean_y",0.958,low_y,up_y);
  RooRealVar sigma1_y("sigma1_y","sigma1_y",0.01,0.001,0.1);
  RooRealVar a1_y("a1_y","a1_y",1,0,1000);
  RooRealVar n1_y("n1_y","n1_y",1,0,1000);
  RooRealVar sigma2_y("sigma2_y","sigma2_y",0.05,0.001,0.1);
  RooRealVar a2_y("a2_y","a2_y",1,0,1000);
  RooRealVar n2_y("n2_y","n2_y",1,0,1000);
  RooCBShape sig1_y("sig1_y","sig1_y",m_gam_rho,mean_y,sigma1_y,a1_y,n1_y);
  RooCBShape sig2_y("sig2_y","sig2_y",m_gam_rho,mean_y,sigma2_y,a2_y,n2_y);
  RooRealVar frac_y("frac_y","frac_y",0.5,0,1);
  RooAddPdf sig_y("sig_y","sig_y",RooArgList(sig1_y,sig2_y),frac_y);

  //Background
  //=**********
  //Background of x
  RooRealVar c0_x("c0_x","coefficient #0_x", 0.1,-1.,1.) ;
  RooRealVar c1_x("c1_x","coefficient #1_x", 0.1,-1.,1.) ;
  RooRealVar c2_x("c2_x","coefficient #2_x",-0.1,-1.,1.) ;
  RooChebychev bkg_x("bkg_x","bkg p.d.f. x",m_2k,RooArgList(c0_x,c1_x,c2_x)) ;

  //Background of y
  RooRealVar c0_y("c0_y","coefficient #0_y", 0.1,-1.,1.) ;
  RooRealVar c1_y("c1_y","coefficient #1_y", 0.1,-1.,1.) ;
  RooRealVar c2_y("c2_y","coefficient #2_y",-0.1,-1.,1.) ;  
  RooChebychev bkg_y("bkg_y","bkg p.d.f. y",m_gam_rho,RooArgList(c0_y,c1_y,c2_y)) ;

  //Get sig
  RooProdPdf sig("sig","sig_x * sig_y",RooArgSet(sig_x,sig_y)) ;
  //Get bkg
  RooProdPdf bkg1("bkg1","sig_x * bkg_y",RooArgSet(sig_x,bkg_y)) ;
  RooProdPdf bkg2("bkg2","bkg_x * sig_y",RooArgSet(bkg_x,sig_y)) ;
  RooProdPdf bkg3("bkg3","bkg_x * bkg_y",RooArgSet(bkg_x,bkg_y)) ;

  RooRealVar nsig("nsig","nsig",2000,0,5000);
  RooRealVar nbkg1("nbkg1","nbkg1",100,0,500);
  RooRealVar nbkg2("nbkg2","nbkg2",100,0,500);
  RooRealVar nbkg3("nbkg3","nbkg3",100,0,500);
  RooAddPdf model("model","model",RooArgList(sig,bkg1,bkg2,bkg3),RooArgList(nsig,nbkg1,nbkg2,nbkg3));

  model.fitTo(data,Extended());

  RooPlot* xframe = m_2k.frame() ;
  data.plotOn(xframe,Binning(nbin_x));
  model.plotOn(xframe);
  model.plotOn(xframe,Components(sig),LineStyle(kDashed),LineColor(kRed));
  model.plotOn(xframe,Components(bkg1),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(xframe,Components(bkg2),LineStyle(kDashed),LineColor(kGreen));
  model.plotOn(xframe,Components(bkg3),LineStyle(kDashed),LineColor(kViolet));

  RooPlot* yframe = m_gam_rho.frame() ;
  data.plotOn(yframe,Binning(nbin_y));
  model.plotOn(yframe);
  model.plotOn(yframe,Components(sig),LineStyle(kDashed),LineColor(kRed));
  model.plotOn(yframe,Components(bkg1),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(yframe,Components(bkg2),LineStyle(kDashed),LineColor(kGreen));
  model.plotOn(yframe,Components(bkg3),LineStyle(kDashed),LineColor(kViolet));

  //The limits of signal region and sideband region.
  //x axis
    //Signal region
    //l means left limit, r means right limit.
  Double_t x_sig_l=1.01;
  Double_t x_sig_r=1.03;
    //Right sideband
    //First r means right sideband.
  Double_t x_sid_r_l=1.06;
  Double_t x_sid_r_r=1.08;

  //y axis
    //Signal redion
    //u means up limit, d means down limit.
  Double_t y_sig_u=0.981;
  Double_t y_sig_d=0.935;

    //Up sideband
    //First u means up sideband.
  Double_t y_sid_u_u=1.09;
  Double_t y_sid_u_d=1.05;

    //Down sideband
    //First d means down sideband.
  Double_t y_sid_d_u=0.82;
  Double_t y_sid_d_d=0.78;

  //Draw arrows.
  //On m_2k: x.
  //=*******************
  Double_t y_1=0;
  Double_t y_2=200;
    //On signal region.
  //left
  TArrow *ar_sig_l_x=new TArrow(x_sig_l,y_1,x_sig_l,y_2,0.01,"<");
  ar_sig_l_x->SetLineColor(kRed);
  ar_sig_l_x->SetLineWidth(2);
  ar_sig_l_x->SetLineStyle(kDashed);
  xframe->addObject(ar_sig_l_x);
  //right
  TArrow *ar_sig_r_x=new TArrow(x_sig_r,y_1,x_sig_r,y_2,0.01,"<");
  ar_sig_r_x->SetLineColor(kRed);
  ar_sig_r_x->SetLineWidth(2);
  ar_sig_r_x->SetLineStyle(kDashed);
  xframe->addObject(ar_sig_r_x);

    //On sideband region.
  //left
  TArrow *ar_sid_l_x=new TArrow(x_sid_r_l,y_1,x_sid_r_l,y_2,0.01,"<");
  ar_sid_l_x->SetLineColor(kRed);
  ar_sid_l_x->SetLineWidth(2);
  xframe->addObject(ar_sid_l_x);
  //right
  TArrow *ar_sid_r_x=new TArrow(x_sid_r_r,y_1,x_sid_r_r,y_2,0.01,"<");
  ar_sid_r_x->SetLineColor(kRed);
  ar_sid_r_x->SetLineWidth(2);
  xframe->addObject(ar_sid_r_x);

  //On m_gam_rho: y.
  //=**********************
  Double_t y_2=200;

    //On signal region.
  //left
  TArrow *ar_sig_l_y=new TArrow(y_sig_d,y_1,y_sig_d,y_2,0.01,"<");
  ar_sig_l_y->SetLineColor(kRed);
  ar_sig_l_y->SetLineWidth(2);
  ar_sig_l_y->SetLineStyle(kDashed);
  yframe->addObject(ar_sig_l_y);
  //right
  TArrow *ar_sig_r_y=new TArrow(y_sig_u,y_1,y_sig_u,y_2,0.01,"<");
  ar_sig_r_y->SetLineColor(kRed);
  ar_sig_r_y->SetLineWidth(2);
  ar_sig_r_y->SetLineStyle(kDashed);
  yframe->addObject(ar_sig_r_y);

    //On left sideband region.
  //left
  TArrow *ar_sid_l_y_l=new TArrow(y_sid_d_d,y_1,y_sid_d_d,y_2,0.01,"<");
  ar_sid_l_y_l->SetLineColor(kRed);
  ar_sid_l_y_l->SetLineWidth(2);
  yframe->addObject(ar_sid_l_y_l);
  //right
  TArrow *ar_sid_r_y_l=new TArrow(y_sid_d_u,y_1,y_sid_d_u,y_2,0.01,"<");
  ar_sid_r_y_l->SetLineColor(kRed);
  ar_sid_r_y_l->SetLineWidth(2);
  yframe->addObject(ar_sid_r_y_l);

    //On right sideband region.
  //left
  TArrow *ar_sid_l_y_r=new TArrow(y_sid_u_d,y_1,y_sid_u_d,y_2,0.01,"<");
  ar_sid_l_y_r->SetLineColor(kRed);
  ar_sid_l_y_r->SetLineWidth(2);
  yframe->addObject(ar_sid_l_y_r);
  //right
  TArrow *ar_sid_r_y_r=new TArrow(y_sid_u_u,y_1,y_sid_u_u,y_2,0.01,"<");
  ar_sid_r_y_r->SetLineColor(kRed);
  ar_sid_r_y_r->SetLineWidth(2);
  yframe->addObject(ar_sid_r_y_r);

  TCanvas *c1=new TCanvas();
  c1->Divide(2,1);

  c1->cd(1);
  xframe->Draw();

  c1->cd(2);
  yframe->Draw();

  //Integral, get scale factors.

  //Get different regions.
  //Region1
  m_2k.setRange("region1",x_sig_l,x_sig_r);
  m_gam_rho.setRange("region1",y_sid_u_d,y_sid_u_u);
  //Region2
  m_2k.setRange("region2",x_sig_l,x_sig_r);
  m_gam_rho.setRange("region2",y_sig_d,y_sig_u);
  //Region3
  m_2k.setRange("region3",x_sig_l,x_sig_r);
  m_gam_rho.setRange("region3",y_sid_d_d,y_sid_d_u);
  //Region4
  m_2k.setRange("region4",x_sid_r_l,x_sid_r_r);
  m_gam_rho.setRange("region4",y_sid_u_d,y_sid_u_u);
  //Rgeion5
  m_2k.setRange("region5",x_sid_r_l,x_sid_r_r);
  m_gam_rho.setRange("region5",y_sig_d,y_sig_u);
  //Region6
  m_2k.setRange("region6",x_sid_r_l,x_sid_r_r);
  m_gam_rho.setRange("region6",y_sid_d_d,y_sid_d_u);

  //Get omega_horizontal.
  //=******
  //f(2,2)
  RooAbsReal* f_2_2 = bkg2.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region2"));
  cout << "fun2_region[2] = " << f_2_2->getVal() << endl ;

  //f(2,5)
  RooAbsReal* f_2_5 = bkg2.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region5"));
  cout << "fun2_region[5] = " << f_2_5->getVal() << endl ;

  //Get omega_vertical.
  //=******
  //f(1,1)
  RooAbsReal* f_1_1 = bkg1.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region1"));
  cout << "fun1_region[1] = " << f_1_1->getVal() << endl ;

  //f(1,2)
  RooAbsReal* f_1_2 = bkg1.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region2"));
  cout << "fun1_region[2] = " << f_1_2->getVal() << endl ;

  //f(1,3)
  RooAbsReal* f_1_3 = bkg1.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region3"));
  cout << "fun1_region[3] = " << f_1_3->getVal() << endl ;

  //Get omega_diagonal.
  //f(3,1)
  RooAbsReal* f_3_1 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region1"));
  cout << "fun3_region[1] = " << f_3_1->getVal() << endl ;

  //f(3,2)
  RooAbsReal* f_3_2 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region2"));
  cout << "fun3_region[2] = " << f_3_2->getVal() << endl ;

  //f(3,3)
  RooAbsReal* f_3_3 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region3"));
  cout << "fun3_region[3] = " << f_3_3->getVal() << endl ;

  //f(3,4)
  RooAbsReal* f_3_4 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region4"));
  cout << "fun3_region[4] = " << f_3_4->getVal() << endl ;

  //f(3,5)
  RooAbsReal* f_3_5 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region5"));
  cout << "fun3_region[5] = " << f_3_5->getVal() << endl ;

  //f(3,6)
  RooAbsReal* f_3_6 = bkg3.createIntegral(RooArgSet(m_2k,m_gam_rho),NormSet(RooArgSet(m_2k,m_gam_rho)),Range("region6"));
  cout << "fun3_region[6] = " << f_3_6->getVal() << endl ;

  Double_t F_2_2=f_2_2->getVal();
  Double_t F_2_5=f_2_5->getVal();

  Double_t F_1_1=f_1_1->getVal();
  Double_t F_1_2=f_1_2->getVal();
  Double_t F_1_3=f_1_3->getVal();

  Double_t F_3_1=f_3_1->getVal();
  Double_t F_3_2=f_3_2->getVal();
  Double_t F_3_3=f_3_3->getVal();
  Double_t F_3_4=f_3_4->getVal();
  Double_t F_3_5=f_3_5->getVal();
  Double_t F_3_6=f_3_6->getVal();

  Double_t omega_horizontal;
  Double_t omega_vertical;
  Double_t omega_diagonal;

  omega_horizontal=F_2_2 / F_2_5;
  omega_vertical=F_1_2 / (F_1_1 + F_1_3);
  omega_diagonal=( F_3_2 - omega_horizontal*F_3_5 - omega_vertical*(F_3_1 + F_3_3) ) / (F_3_4 + F_3_6);
  
  cout<<"omega_horizontal="<<omega_horizontal<<endl;
  cout<<"omega_vertical="<<omega_vertical<<endl;
  cout<<"omega_diagonal="<<omega_diagonal<<endl;

}
