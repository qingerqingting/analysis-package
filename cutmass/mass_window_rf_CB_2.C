void mass_window_rf_CB_2(){
  using namespace RooFit;

  //Use Double CB function to fit the mass spectrum of etapp.
  //Get the integral of function.
  //Get the mass windows ~ 3sigma.
  //                     ~ 5sigma.
  
  //3 sigma.
  const Double_t f=0.9947;

  Double_t low=0.9;
  Double_t up=1.0;

  Double_t right_limit;
  Double_t left_limit;

  //The range of m_gam_rho
  RooRealVar m_gam_rho("m_gam_rho","m_gam_rho [GeV]",low,up);

  //Read the root file.
  TFile *f1=new TFile ("output_sigmc_g3pi2k2_0912.root");
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

  RooRealVar frac("frac","frac",0.5,0,1);
  RooAddPdf sig("sig","sig",RooArgList(sig1,sig2),frac);

  sig.fitTo(etap);

  //=**************************************************
  //Get the mass windows of etap
  //=**************************************************

  //First method: use the area.
  //the MEAN of the curve.
 /* Double_t MEAN=mean.getVal();

  //the area of total range (right).
  m_gam_rho.setRange("cut",MEAN,up);
  RooAbsReal* int_norm_r=sig.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut"));
  Double_t area_r=int_norm_r->getVal();

  for (Double_t i=MEAN;i<up;i=i+0.001) {
  m_gam_rho.setRange("cut",MEAN,i);
  RooAbsReal* integral_r=sig.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut"));
  
  if ((integral_r->getVal())>area_r*f){
    cout<<"Right_limit:"<<endl;
    cout<<i<<endl;
    right_limit=i;
    break;
    }//end with if
  }//end with for

  //the area of total range (left).
  m_gam_rho.setRange("cut",low,MEAN);
  RooAbsReal* int_norm_l=sig.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut"));
  Double_t area_l=int_norm_l->getVal();

  for (Double_t i=low;i<MEAN;i=i+0.001) {
  m_gam_rho.setRange("cut",i,MEAN);
  RooAbsReal* integral_l=sig.createIntegral(m_gam_rho,NormSet(m_gam_rho),Range("cut"));
  
  if ((integral_l->getVal())<area_l*f){
    cout<<"Left_limit:"<<endl;
    cout<<i<<endl;
    left_limit=i;
    break;
    }//end with if
  }//end with for*/

  //Method 2:3 sigma ~ 5 sigma.
  Double_t MEAN=mean.getVal();
  Double_t SIGMA1=sigma1.getVal();
  Double_t SIGMA2=sigma2.getVal();
 // Double_t FRAC=frac.getVal();
  Double_t FRAC=1;
  Double_t SIGMA=TMath::Sqrt(FRAC*SIGMA1*SIGMA1+(1-FRAC)*SIGMA2*SIGMA2);
  Double_t left_limit=MEAN-5*SIGMA;
  Double_t right_limit=MEAN+3*SIGMA;

  cout<<"Sigma="<<SIGMA<<endl;
  cout<<"The left_limit="<<left_limit<<endl;
  cout<<"The right_limit="<<right_limit<<endl;

  //=*********************************
  //Draw legend and arrows
  //=*********************************
  RooPlot * frame=m_gam_rho.frame();

  //Prepare for legend.
  //The names of hist and curve are from c1.C
  //Data
  RooPlot *etap_1= etap.plotOn(frame,Binning(40));
  RooHist *h_etap=etap_1->getHist("h_etap");
  //model
  RooPlot *sig_1= sig.plotOn(frame,LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_gam_rho]");

  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));

  //Draw arrows.
  Double_t x_l=left_limit;
  Double_t x_r=right_limit;
  Double_t y_1=20;
  Double_t y_2=500;

  //left
  TArrow *ar_l=new TArrow(x_l,y_1,x_l,y_2,0.01,"<");
  ar_l->SetLineColor(kRed);
  ar_l->SetLineWidth(2);
  frame->addObject(ar_l);

  //right
  TArrow *ar_r=new TArrow(x_r,y_1,x_r,y_2,0.01,"<");
  ar_r->SetLineColor(kRed);
  ar_r->SetLineWidth(2);
  frame->addObject(ar_r);

  //Draw the frame
  frame->Draw();

  //legend 
  TLegend *leg=new TLegend(0.75,0.7,0.95,0.95);
  leg->AddEntry(h_etap,"SigMC:etap","LPE");
  leg->AddEntry(c_sig,"Double CB","L");
  leg->Draw();

}//end of final
