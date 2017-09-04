#include "/afs/ihep.ac.cn/users/l/longyf/useful.h"

void mass_window_rf_DG_eta(){
  SetLyfStyle();

  using namespace RooFit;

  //Use double gaussian to fit eta.
  //Get the integral of function.
  //Get the mass windows ~ 3sigma.
  //Pay attention to low,up,the name of variables,the name of root file,the name of RooDataSet.
  
  //3 sigma.
  const Double_t f=0.9947;

  Double_t low=0.45;
  Double_t up=0.6;

  Double_t right_limit;
  Double_t left_limit;

  //The range of m_2gam
  RooRealVar m_2gam("m_2gam","m_2gam [GeV]",low,up);

  //Read the root file.
  TFile *f1=new TFile ("output_sigmc_g3pi2k2.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");  
  RooDataSet eta("eta","eta",tree,m_2gam);

  //Signal: double gaussian.
  RooRealVar mean("mean","mean",0.548,low,up);
  RooRealVar sigma1("sigma1","sigma1",0.03,0.001,0.1);
  RooRealVar sigma2("sigma2","sigma2",0.5,0.001,1);
  RooRealVar frac ("frac","frac",0.5,0,1);
  RooGaussian sig1 ("sig1","sig1",m_2gam,mean,sigma1);
  RooGaussian sig2 ("sig2","sig2",m_2gam,mean,sigma2);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);

  //fit
  sig.fitTo(eta);
 
  //=*******************************
  //Get the mass windows
  //=******************************* 

  //Method 2:3 sigmas .
  Double_t MEAN=mean.getVal();
  Double_t SIGMA1=sigma1.getVal();
  Double_t SIGMA2=sigma2.getVal();
  Double_t FRAC=frac.getVal();
  Double_t SIGMA=TMath::Sqrt(FRAC*SIGMA1*SIGMA1+(1-FRAC)*SIGMA2*SIGMA2);
  Double_t left_limit=MEAN-3*SIGMA;
  Double_t right_limit=MEAN+3*SIGMA;

  cout<<"Sigma="<<SIGMA<<endl;
  cout<<"The left_limit="<<left_limit<<endl;
  cout<<"The right_limit="<<right_limit<<endl;

  //=*******************************
  //Draw legend and arrows
  //=*******************************

  RooPlot * frame=m_2gam.frame();
  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));
  //Static box
 // eta.statOn(frame,Layout(0.2,0.55));

  //Prepare for legend.
  //The names of hist and curve are from c1.C
  //Data
  RooPlot *eta_1= eta.plotOn(frame,Binning(30));
  RooHist *h_eta=eta_1->getHist("h_eta");
  //model
  RooPlot *sig_1= sig.plotOn(frame,LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_2gam]");

  //Draw arrows.
  Double_t x_l=left_limit;
  Double_t x_r=right_limit;
  Double_t y_1=20;
  Double_t y_2=10000;

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
  leg->AddEntry(h_eta,"SigMC:eta","LPE");
  leg->AddEntry(c_sig,"2 gaussian","L");
  leg->Draw();
}//end of final
