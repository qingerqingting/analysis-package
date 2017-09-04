void modi(){
  Int_t i;
  const Int_t n=79;
  Double_t x0[n],y0[n];
  ifstream myfile;
  myfile.open("data.txt");

  for(i=0;i<n;i++)
 {
  myfile>>x0[i]>>y0[i];
  cout<<x0[i]<<"and"<<y0[i]<<endl;
 }
  myfile.close();

 TGraph *gr = new TGraph(n,x0,y0);
 gr->Draw("ACP");
}
