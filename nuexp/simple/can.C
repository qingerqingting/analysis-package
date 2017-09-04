void can(){
  TCanvas *c = new TCanvas("c","my canvas");
  c->Divide(2,2);
 
  c->SetGridx();//x lower-case
  //c->SetGridy();
  c->cd(3); 
  TF1 *f =new TF1("f","sin(x)",0,10);
  f->SetNpx(1000);
  f->Draw();
 
  c->cd(2);
  TF1 *f2 =new TF1("f2","cos(x)",0,10);
  f2->SetNpx(1000);
  f2->Draw();
  c->SetLogy();
  c->SaveAs("can.pdf");
  delete can;
}

