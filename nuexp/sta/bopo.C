Double_t jiecheng(Int_t m){
  Int_t j;Double_t jc;
  if(j==0)jc=1;
  for(jc=1,j=m;j>0;--j)
  jc=jc*j;
  return jc;
}

void bopo(){
  Int_t N=100,r;
  const Int_t n=100;
  Double_t p0=0.02;
  Double_t x[n],p1[n],p2[n];
  Double_t u=2;
  Double_t jc=1;

  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  p1[i]=pow(p0,i)*pow(1-p0,N-i)*jiecheng(N)/(jiecheng(N-i)*jiecheng(i));
//  printf("%i %f %f \n",i,x[i],p[i])

}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr1 =new TGraph(n,x,p1);
  gr1->GetXaxis()->SetRange(0,25);
  gr1->SetLineColor(2);
  gr1->Draw("ACP");
  gr1->SetLineWidth(1.8);
  gr1->GetYaxis()->SetTitleOffset(1.2);

  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  p2[i]=pow(u,x[i])*exp(-u)/jiecheng(i);
}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr2 =new TGraph(n,x,p2);
  gr2->SetLineColor(4);
  gr2->Draw("SAME");
  gr2->SetLineWidth(1.8);

  TH1F *h1 = new TH1F("h1","The Binomial&Possion Distribution;n;probability",100,0,15);
  TH1F *h2 = new TH1F("h2","The Poisson Distribution;n;probability",100,0,25);
  for(Int_t i = 0; i< n; ++i){
  h1->Fill(x[i],p1[i]);
  h2->Fill(x[i],p2[i]); }

  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->SetFillColor(2);
  h2->SetFillColor(4);

  h1->SetStats(0);
  h1->SetBarWidth(1.5);
  h1->SetBarOffset(0.1);
  TH1 *h11 = h1->DrawCopy("bar");
 
  h2->SetBarWidth(1);
  h2->SetBarOffset(1.1);
  TH1 *h22 = h2->DrawCopy("bar,same");
//  h2->DrawClone("same");

  TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
  legend->AddEntry(h1,"Binomial","f");
  legend->AddEntry(h2,"Poisson","f");
  legend->Draw();
  c->Print("0.2bp.jpg");

 

}
