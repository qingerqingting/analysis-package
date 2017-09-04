#include "/afs/ihep.ac.cn/users/l/longyf/useful.h"

void mass_window_rf_DG_eta_2(){
  SetLyfStyle();

  using namespace RooFit;

  //A better cut on m_eta from data.
  //Use double gaussian to fit eta.
  //Use 2nd chebychev to fit background.
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
  TFile *f1=new TFile ("output_for_mass_eta.root");
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

  //Background function
  RooRealVar c0("c0","coefficient #0", 0.1,-1.,1.) ;
  RooRealVar c1("c1","coefficient #1", 0.1,-1.,1.) ;
  RooRealVar c2("c2","coefficient #2",-0.1,-1.,1.) ;
  RooChebychev bkg("bkg","background p.d.f.",m_2gam,RooArgList(c0,c1,c2)) ;

  //Numbers of sig and bkg events.
  RooRealVar nsig("nsig","nsig",1000,0,2000);
  RooRealVar nbkg("nbkg","nbkg",1000,0,2000);

  RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(nsig,nbkg));

  //fit
  model.fitTo(eta,Extended());
 
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
  RooPlot *model_1= model.plotOn(frame,LineColor(kBlue));
  RooCurve *c_model=model_1->getCurve("model_Norm[m_2gam]");
  //sig
  RooPlot *sig_1= model.plotOn(frame,Components(sig),LineColor(kRed),LineStyle(kDashed));
  RooCurve *c_sig=sig_1->getCurve("model_Norm[m_2gam]_Comp[sig]");
  //bkg
  RooPlot *bkg_1= model.plotOn(frame,Components(bkg),LineColor(kGreen),LineStyle(kDashed));
  RooCurve *c_bkg=bkg_1->getCurve("model_Norm[m_2gam]_Comp[bkg]");

  //Draw arrows.
  Double_t x_l=left_limit;
  Double_t x_r=right_limit;
  Double_t y_1=20;
  Double_t y_2=200;

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
  leg->SetFillColor(0);
  leg->AddEntry(h_eta,"Data:eta","LPE");
  leg->AddEntry(c_model,"Model","L");
  leg->AddEntry(c_sig,"Sig: 2 gaussian","L");
  leg->AddEntry(c_bkg,"Bkg: 2nd chebychev","L");
  leg->Draw();
}//end of final
