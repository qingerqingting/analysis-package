Double_t fitf(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
   if (par[2] != 0) arg = (x[0] - par[1])/par[2];

   Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}
void myfit(){
	TFile *f =new TFile ("output_mceagle.root");
	TH1F *h1 = (TH1F*)f->Get("h5");
	TF1 *func =new TF1("fit",fitf,-3,3,3);
	func->SetParameters(500,h1->GetMean(),h1->GetRMS());
	func->SetParNames("Constant","Mean Value","sigma");
	h1->Fit("fit");
}
