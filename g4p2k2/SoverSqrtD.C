void SoverSqrtD(){
//Get S/sqrt(S+B)

  //Signal
 /* TFile *f1=new TFile("sigmc_g4pi2k2_0912.root");
  TTree *t1=(TTree*)f1->Get("TreeAna");
  TH1F *h1=new TH1F("h1","h1",200,0,200);
  t1->Draw("Chisq_low>>h1");

  //Data(signal+background)
  TFile *f2=new TFile("data_g4pi2k2_0912.root");
  TTree *t2=(TTree*)f2->Get("TreeAna");
  TH1F *h2=new TH1F("h2","h2",200,0,200);
  t2->Draw("Chisq_low>>h2");

  Double_t sum1,sum2,num1,num2,ratio;
  sum1=sum2=num1=num2=0;

  for (int i=1;i<201;i++){
    //signal
    num1=h1->GetBinContent(i);
    sum1=sum1+num1;
    //data
    num2=h2->GetBinContent(i);
    sum2=sum2+num2;
    //====S/sqrt(D),use inclusivemc to replace data.
    ratio=sum1/TMath::Sqrt(sum2);
    cout<<ratio<<endl;
  }//end with for*/

  //Draw the graph
  TCanvas *c1=new TCanvas();
  TGraphErrors *t1=new TGraphErrors("./chi2.txt","%lg %lg");
  //t1->GetXaxis()->CenterTitle(true);
  //t1->GetYaxis()->CenterTitle(true);
  t1->GetXaxis()->SetNdivisions(505);

  t1->SetTitle(";Chisq_cut;#frac{S}{#sqrt{S+B}}");
  t1->Draw("E3AL");
  drawarrow(80,1,7);
  t1->Print();

}//final end
