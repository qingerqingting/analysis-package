void po2(){

  TH1F *h =new TH1F("h","h",100,0,100);
  Float_t x;
  for(Int_t i=0;i<10000;i++){
  x=gRandom->Poisson(20);
  h->Fill(x);
}
  h->Draw();
}
