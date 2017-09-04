
void gaus(){
using namespace RooFit;
TFile *f =new TFile("tree.root");
TTree *tree=(TTree*) gDirectory->Get("t1");
RooRealVar x("gam2","x",-5,5);
RooDataSet data("data","dataset with x",tree,x);

RooPlot* frame=x.frame();
data.plotOn(frame);
frame->Draw();

RooRealVar mean ("mean","mean of gaussian",0,-10,10);
RooRealVar sigma ("sigma","sigma",3,-10,10);
RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);
gauss.fitTo(data);
gauss.plotOn(frame);
gauss.paramOn(frame,Layout(0.6,0.95));
frame->Draw();
}



