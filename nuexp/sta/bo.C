Double_t jiecheng(Int_t m){
  Int_t j;Double_t jc;
  if(j==0)jc=1;
  for(jc=1,j=m;j>0;--j)
  jc=jc*j;
  return jc;	
}

void bo(){
  Int_t N=15,r;
  const Int_t n=100;
  Double_t p0=0.75;
  Double_t x[n],p[n];
//  printf("%f\n",jiecheng(N));

  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  p[i]=pow(p0,i)*pow(1-p0,N-i)*jiecheng(N)/(jiecheng(N-i)*jiecheng(i));
  //p[i]=jiecheng(N)/(jiecheng(N-i)*jiecheng(i))*pow(p0,i)*pow(1-p0,N-i);
}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr =new TGraph(n,x,p);
  gr->GetXaxis()->SetRange(0,40);
  gr->GetXaxis()->SetTitle("n");
  gr->GetYaxis()->SetTitle("probability");
  gr->GetXaxis()->SetTitleOffset(0.8);
  gr->Draw("ACP");

  TH1F *h1 = new TH1F("h1","The Binomial Distribution;n;probability",100,0,40);
  for(Int_t i = 0; i< n; ++i){
  h1->Fill(x[i],p[i]); }
  h1->SetFillColor(2);
  h1->Draw();
  gr->Draw("same");
  c->Print("b0.75.jpg");
}
