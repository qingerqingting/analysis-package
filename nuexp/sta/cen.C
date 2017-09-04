cen(){
  
  TCanvas *c1 = new TCanvas("c1","c1",200,10,600,400);
  TH1F *h  = new TH1F("h","h",100,-1.5,1.5); 

  const int n=1;//change the number
  Float_t x[n];
  for ( Int_t i=0; i<10000; i++) 
  { 
     Float_t sum=0;
     for(Int_t j=0;j<n;j++)
     {       
     x[j] = gRandom->Uniform(-1,1);
     sum+=x[j];
     }
     h->Fill(sum);
  }  
  h->Draw();
  c1->Print("1num.jpg");
}

  


