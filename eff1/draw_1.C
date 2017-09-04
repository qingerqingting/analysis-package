void draw_1(){
// Draw eff vs E

  TCanvas *c1=new TCanvas();
  TGraphErrors *t1=new TGraphErrors("./eff1.txt","%lg %lg %lg");

  t1->SetTitle("Eff. vs E.; Energy [GeV]; Efficiency");
 // t1->SetMarkerStyle(kCircle);
 // t1->SetFillColor(0);
  t1->Draw("APE");
  t1->Print();
}

