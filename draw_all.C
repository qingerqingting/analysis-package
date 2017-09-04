void draw_all(){
// Draw eff vs E
// Method 1 and method 2.

  TCanvas *c1=new TCanvas();

    //Method 1
  TGraphErrors *t1=new TGraphErrors("./eff1.txt","%lg %lg %lg");
    //Method 2
  TGraphErrors *t2=new TGraphErrors("./eff2.txt","%lg %lg %lg");

  t1->SetTitle("Eff. vs E.;Energy [GeV];Efficiency");
  t1->SetFillColor(kBlue);
  t1->Draw("E3AL");

  t2->Draw("PESame");

  //Legend
  TLegend leg(.25,.7,.5,.9,"Eff. vs E.");
  leg.SetFillColor(0);
  leg.AddEntry(t1,"Method 1");
  leg.AddEntry(t2,"Method 2");
  leg.DrawClone("Same");

  t2->Print();
}

