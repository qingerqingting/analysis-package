void po(){
  const Int_t n=100;
  Double_t x[n],p[n];
  Double_t u=20;
  Double_t jc=1;

//*********jiecheng
  for(Int_t i=0;i<=100;i++){
  x[i]=i;
  for(jc=1,Int_t j=i;j>0;--j)
  jc=jc*j;
//printf("%i %i %i\n",i,x[i],jc);

  p[i]=pow(u,x[i])*exp(-u)/jc;
//printf("%i %f %f \n",i,x[i],p[i]);
}
  TCanvas *c = new TCanvas("c","c");
  TGraph *gr =new TGraph(n,x,p);
  gr->GetXaxis()->SetTitle("n");
  gr->GetYaxis()->SetTitle("probability");
  gr->GetXaxis()->SetRange(0,35);
  gr->GetYaxis()->SetTitleOffset(1.2);
  gr->GetXaxis()->SetTitleOffset(0.8);
  gr->SetLineWidth(1.5);
  //gr->SetLineColor(4);
  //gr->GetYaxis()->SetTitleOffset(0.8);

//  TLatex text(8.2,7.5,"#splitline{Maximum}{Deviation}");
//    text.DrawClone();

  gr->Draw("ACP");
  TH1F *h1 = new TH1F("h1","The Poisson Distribution;n;probability",100,0,35);
  for(Int_t i = 0; i< n; ++i){
  h1->Fill(x[i],p[i]); }
  h1->SetFillColor(2);
  h1->Draw();
  gr->Draw("same");
  c->Print("20.jpg");
  
  /*TLegend *legend=new TLegend(0.6,0.7,0.88,0.85);
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->SetText("u=0.5");
  legend->Draw();
*/

}
