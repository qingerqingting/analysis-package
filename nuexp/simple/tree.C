void tree(){

  Double_t a,b;
  Float_t c;
  Int_t d;

  TTree *t = new TTree("t","t");
  t->Branch("a",&a,"a/D");
  t->Branch("b",&b,"b/D");
  t->Branch("c",&c,"c/F");
  t->Branch("d",&d,"d/I");// branch name.variableaddress,variablename/type

  a=10,b=20,c=30,d=40;
  t->Fill();
  t->Show(0);

  a=100,b=200,c=300,d=400;
  t->Fill();
  t->Show(1);

  a=1000,b=2000,c=3000,d=4000;
  t->Fill();
  t->Show(2);
}
