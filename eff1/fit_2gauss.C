void fit_2gauss(){
  //fit to the mass spectrum of Y(2175) to get sigma
  //use double gaussian

  using namespace RooFit;

  Double_t low=2.0;
  Double_t up=2.2;

  //The range of m_phi_etap
  RooRealVar m_phi_etap("m_phi_etap","m_phi_etap [GeV]",low,up);

  //Read the root file.
  TFile *f1=new TFile ("output_eff_m1_21.root ");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet data("data","data",tree,m_phi_etap);

  //Signal: double gaussian.
  RooRealVar mean("mean","mean",2.1,low,up);
  RooRealVar sigma1("sigma1","sigma1",0.03,0.001,0.1);
  RooGaussian sig1 ("sig1","sig1",m_phi_etap,mean,sigma1);

  RooRealVar sigma2("sigma2","sigma2",0.5,0.001,1);
  RooGaussian sig2 ("sig2","sig2",m_phi_etap,mean,sigma2);

  RooRealVar frac ("frac","frac",0.5,0,1);
  RooAddPdf sig ("sig","sig",RooArgList(sig1,sig2),frac);

  //fit
  sig.fitTo(data);

  RooPlot * frame=m_phi_etap.frame();

  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));

  //Prepare for legend.
  //The names of hist and curve are from c1.C
  //Data
  RooPlot *data_1= data.plotOn(frame,Binning(40));
  RooHist *h_data=data_1->getHist("h_data");
  //model
  RooPlot *sig_1= sig.plotOn(frame,LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_phi_etap]");

  //Draw the frame
  frame->Draw();

  //legend 
  TLegend *leg=new TLegend(0.7,0.7,0.9,0.95);
  leg->AddEntry(h_data,"SigMC:Y(2175)","LPE");
  leg->AddEntry(c_sig,"gaussian","L");
  leg->Draw();

  //Get sigma.
  //sigma=sqrt(sigma1^2*frac+sigma2^2(1-frac)).

  Double_t SIGMA1=sigma1.getVal();
  Double_t SIGMA2=sigma2.getVal();
  Double_t FRAC=frac.getVal();
  Double_t SIGMA=TMath::Sqrt(FRAC*SIGMA1*SIGMA1+(1-FRAC)*SIGMA2*SIGMA2);

  cout<<"sigma="<<SIGMA<<endl;

}//end of final

