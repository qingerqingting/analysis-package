#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit ;


//TH1* makeTH1() ;
//TTree* makeTTree() ;


void fit(){

TFile *f =new TFile("output_mceagle.root");
TH1F *h1 = (TH1F*)f->Get("h5");
//TH1* hh = (TH1*) gDirectory->Get("h5");
RooRealVar x("x","x",1.9,2.6);
RooDataHist data("data","dataset with x",x,h1);

RooPlot* frame=x.frame();
data.plotOn(frame);
frame->Draw();

RooRealVar mean ("mean","mean of gaussian",2.175,-10,10);
RooRealVar sigma ("sigma","sigma",3,-10,10);
RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);
gauss.fitTo(data);
gauss.plotOn(frame);
frame->Draw();
}
