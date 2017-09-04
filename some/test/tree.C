void tree()
{TFile *f1=new TFile("tree.root","RECREATE");
TTree *t1=new TTree("t1","t1");
Double_t gam1;
Double_t gam2;
t1->Branch("gam1",&gam1,"gam1/D");
t1->Branch("gam2",&gam2,"gam2/D");

TRandom3 *r3=new TRandom3();
for(int i=0;i<10000;i++)
{gam1=r3->Gaus(0,1);

gam2=r3->Gaus(0,0.5);

t1->Fill();
}
t1->Write();
f1->Close();
}

