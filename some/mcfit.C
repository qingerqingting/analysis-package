void mcfit(){
using namespace RooFit;

TFile *f =new TFile("output_mceaglenh.root");
//TH1F *h1 = (TH1F*)f->Get("h5");
TTree *tree=(TTree*) gDirectory->Get("TreeRes");

RooRealVar m_phi_etap("m_phi_etap","m_phi_etap",1.9,2.6);
RooDataSet data("data","dataset with m_phi_etap",tree,m_phi_etap);

RooRealVar m ("m","m",2.175,2.1,2.2);
RooRealVar g ("g","g",0.061,0.043.0.079);
RooRealVar s ("s","s",0.01,0,0.1);
g.setConstant(kTRUE);
RooVoigtian sig ("sig","sig",m_phi_etap,m,g,s);
sig.fitTo(data);

RooPlot* frame=m_phi_etap.frame();
data.plotOn(frame);
sig.plotOn(frame);
//data.plotOn(frame);
frame->Draw();

//RooPlot* frame2=m_phi_etap.frame();
//model.plotOn(frame);
//frame->Draw();

//sig.plotOn(frame);
//data.plotOn(frame);
//frame->Draw();
//frame2->Draw();


//sig.fitTo(data);
//sig.plotOn(frame);
//data.plotOn(frame2);
//frame->Draw();
//frame2->Draw();

//data.plotOn(frame);
//frame->Draw();
}
