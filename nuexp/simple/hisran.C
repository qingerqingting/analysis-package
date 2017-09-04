void hisran(){

  TH1F *h = new TH1F("h","h",100,0,10);
  TRandom3 *r = new TRandom3();
  for(int i = 0;i<10000;i++)
  {
//    h->Fill(r->Gaus(5,1));
    h->Fill(r->Landau(5,1));
  }
  h->Draw();
}
