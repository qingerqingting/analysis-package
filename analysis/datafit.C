void datafit(){
using namespace RooFit;

TFile *f =new TFile("output_y0912nh.root");
//TH1F *h1 = (TH1F*)f->Get("h5");
TTree *tree=(TTree*) gDirectory->Get("TreeRes");
RooRealVar m_phi_etap("m_phi_etap","m_{#phi+#eta'} [GeV]",1.9,2.6);
RooDataSet data("data","dataset with m_phi_etap",tree,m_phi_etap);

/*RooRealVar c0("c0","c0",1.0,-1,1);
RooRealVar c1("c1","c1",0.1,-1,1);
RooRealVar c2("c2","c2",-0.1,-1,1);
RooChebychev bkg("bkg","bkg",m_phi_etap,RooArgList(c0,c1,c2));*/

/*RooRealVar m ("m","m",1.9,2.6);
RooRealVar g ("g","g",1.9,2.6);
RooRealVar s ("s","s",1.9,2.6);
RooVoigtian sig ("sig","sig",m_phi_etap,m,g,s);*/

TFile *f2 =new TFile("output_bkg.root");
//TH1F *h1 = (TH1F*)f->Get("h5");
TTree *tree2=(TTree*) gDirectory->Get("TreeRes");
RooDataSet bkgdata("bkgdata","three_body_decay",tree2,m_phi_etap);
RooKeysPdf bkg("bkg","bkg",m_phi_etap,bkgdata,RooKeysPdf::NoMirror,2);


RooRealVar m ("m","m",2.175,1.9,2.2);
RooRealVar g ("g","g",0.06,0.,10);
RooRealVar s ("s","s",0.0238495,0.,1);
s.setConstant(kTRUE);
RooVoigtian sig ("sig","sig",m_phi_etap,m,g,s);
sig.fitTo(data);

//RooRealVar fbkg ("fbkg","fbkg",0.,1.);
//RooAddPdf model ("model","model",RooArgList(bkg,sig),fbkg);
RooRealVar nsig("nsig","#signal events",1,0,100);
RooRealVar nbkg("nbkg","#background events",100,0,200);
RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(nsig,nbkg));
model.fitTo(data);

RooPlot* frame=m_phi_etap.frame();
//model.plotOn(frame);
//frame->Draw();

model.paramOn(frame,Layout(0.2,0.6));

RooPlot *data_1= data.plotOn(frame,Binning(20));
RooHist *h_data=data_1->getHist("h_data");

RooPlot *model_1= model.plotOn(frame,LineColor(kRed));
RooCurve *c_model=model_1->getCurve("model_Norm[m_phi_etap]");

RooPlot *sig_1= model.plotOn(frame,Components(sig),LineStyle(kDashed),LineColor(kBlue));
RooCurve *c_sig=sig_1->getCurve("model_Norm[m_phi_etap]_Comp[sig]");

RooPlot *bkg_1= model.plotOn(frame,Components(bkg),LineStyle(kDashed),LineColor(kViolet));
RooCurve *c_bkg=bkg_1->getCurve("model_Norm[m_phi_etap]_Comp[bkg]");

frame->Draw();

  TLegend *leg=new TLegend(0.65,0.2,0.95,0.5);
  leg->AddEntry(h_data,"Data","LPE");
  leg->AddEntry(c_model,"Model","L");
  leg->AddEntry(c_sig,"Signal","L");
  leg->AddEntry(c_bkg,"Background","L");
  leg->Draw();

/*data.plotOn(frame,Binning(20));
//bkgdata.plotOn(frame,LineColor(kRed));
bkg.plotOn(frame,LineColor(kRed));
model.plotOn(frame);
frame->Draw();*/

}
