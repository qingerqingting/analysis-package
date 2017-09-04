void mass_window_rf_DG(){
  using namespace RooFit;

  //Use double gaussian to fit phi.
  //Get the integral of function.
  //Get the mass windows ~ 3sigma.
  //Pay attention to low,up,the name of variables,the name of root file,the name of RooDataSet.
  
  //3 sigma.
  const Double_t f=0.9947;

  Double_t low=1.00;
  Double_t up=1.04;

  Double_t right_limit;
  Double_t left_limit;

  //The range of m_2k
  RooRealVar m_2k("m_2k","m_2k [GeV]",low,up);

  //Read the root file.
  TFile *f1=new TFile ("output_sigmc_g3pi2k2_0912.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");  
  RooDataSet phi("phi","phi",tree,m_2k);

  //Signal: double gaussian.
  RooRealVar mean("mean","mean",1.02,low,up);
  RooRealVar sigma1("sigma1","sigma1",0.03,0.001,0.1);
  RooRealVar sigma2("sigma2","sigma2",0.5,0.001,1);
  RooRealVar frac ("frac","frac",0.5,0,1);
  RooGaussian sig1 ("sig1","sig1",m_2k,mean,sigma1);
  RooGaussian sig2 ("sig2","sig2",m_2k,mean,sigma2);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);

  //fit
  sig.fitTo(phi);
 
  //=*******************************
  //Get the mass windows
  //=******************************* 

  //the MEAN of the curve.
 /* Double_t MEAN=mean.getVal();

  //the area of total range (right).
  m_2k.setRange("cut",MEAN,up);
  RooAbsReal* int_norm_r=sig.createIntegral(m_2k,NormSet(m_2k),Range("cut"));
  Double_t area_r=int_norm_r->getVal();

  for (Double_t i=MEAN;i<up;i=i+0.001) {
  m_2k.setRange("cut",MEAN,i);
  RooAbsReal* integral_r=sig.createIntegral(m_2k,NormSet(m_2k),Range("cut"));
  
  if ((integral_r->getVal())>area_r*f){
    cout<<"Right_limit:"<<endl;
    cout<<i<<endl;
    right_limit=i;
    break;
    }//end with if
  }//end with for

  //the area of total range (left).
  m_2k.setRange("cut",low,MEAN);
  RooAbsReal* int_norm_l=sig.createIntegral(m_2k,NormSet(m_2k),Range("cut"));
  Double_t area_l=int_norm_l->getVal();

  for (Double_t i=low;i<MEAN;i=i+0.001) {
  m_2k.setRange("cut",i,MEAN);
  RooAbsReal* integral_l=sig.createIntegral(m_2k,NormSet(m_2k),Range("cut"));
  
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
  Double_t left_limit=MEAN-3*SIGMA;
  Double_t right_limit=MEAN+3*SIGMA;
  cout<<"Sigma="<<SIGMA<<endl;

  cout<<"The left_limit="<<left_limit<<endl;
  cout<<"The right_limit="<<right_limit<<endl;

  //=*******************************
  //Draw legend and arrows
  //=*******************************

  RooPlot * frame=m_2k.frame();
 // phi.plotOn(frame);
 // sig.plotOn(frame);
  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));

  //Prepare for legend.
  //The names of hist and curve are from c1.C
  //Data
  RooPlot *phi_1= phi.plotOn(frame,Binning(40));
  RooHist *h_phi=phi_1->getHist("h_phi");
  //model
  RooPlot *sig_1= sig.plotOn(frame,LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_2k]");

  //Draw arrows.
  Double_t x_l=left_limit;
  Double_t x_r=right_limit;
  Double_t y_1=20;
  Double_t y_2=1000;

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
  TLegend *leg=new TLegend(0.7,0.7,0.9,0.95);
  leg->AddEntry(h_phi,"SigMC:phi","LPE");
  leg->AddEntry(c_sig,"2 gaussian","L");
  leg->Draw();
}//end of final
