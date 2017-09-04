void gau(){
  const Int_t n=100;
  Double_t x[n],p[n];
  Double_t u=15;
  
  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  p[i]=exp(-1*pow(i-u,2)/(2*u))/pow((2*TMath::Pi()*u),0.5);
  //p[i]=1/(2*TMath::Pi()*u)*exp(-1*pow(i-u,2)/(2*u));
//  printf("%i %f %f \n",i,x[i],p[i]);
}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr =new TGraph(n,x,p);
  gr->GetXaxis()->SetRange(0,40);
  gr->GetXaxis()->SetTitle("n");
  gr->GetYaxis()->SetTitle("probability");
  gr->GetXaxis()->SetTitleOffset(0.8);
  gr->Draw("ACP");

  TH1F *h1 = new TH1F("h1","The Gaussian Distribution",100,0,40);
  for(Int_t i = 0; i< n+1; ++i){
  h1->Fill(x[i],p[i]); }
  h1->Draw();
  gr->Draw("same");
  c->Print("g15.jpg");
}
