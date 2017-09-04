void gaupo(){

  const Int_t n=100;
  Double_t x[n],p1[n],p2[n];
  Double_t u=20;

  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  p1[i]=exp(-1*pow(i-u,2)/(2*u))/pow((2*TMath::Pi()*u),0.5);
//  printf("%i %f %f \n",i,x[i],p[i]);
}
  TGraph *gr1 =new TGraph(n,x,p1);
  gr1->GetXaxis()->SetRange(0,40);
  gr1->SetLineColor(2);
  gr1->Draw("ACP");
  gr1->SetLineWidth(1.8);
  gr1->GetYaxis()->SetTitleOffset(1.2);

  Double_t jc=1;
  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  for(jc=1,Int_t j=i;j>0;--j)
  jc=jc*j;
  p2[i]=pow(u,x[i])*exp(-u)/jc;
}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr2 =new TGraph(n,x,p2);
  gr2->SetLineColor(4);
  gr2->Draw("SAME");
  gr2->SetLineWidth(1.8);

  TH1F *h1 = new TH1F("h1","The Gaussian&Possion Distribution;n;probability",100,5,40);
  TH1F *h2 = new TH1F("h2","The Poisson Distribution;n;probability",100,5,40);
  for(Int_t i = 0; i< n; ++i){
  h1->Fill(x[i],p1[i]); 
  h2->Fill(x[i],p2[i]); }

  h1->GetYaxis()->SetTitleOffset(1.2); 
  h1->SetFillColor(2);
  h2->SetFillColor(4);
  h1->Draw();
  h2->Draw("same");
  gr1->Draw("same");
  gr2->Draw("same");
  //TCanvas *c = new TCanvas("c","c");

  TLegend *legend = new TLegend(0.65,0.55,0.86,0.72);
  legend->AddEntry(h1,"Gaussian","f");
  legend->AddEntry(h2,"Poisson","f");
  legend->Draw();
  c->Print("20.jpg");
}
