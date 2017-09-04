void cal(){
  const Int_t n=10000;
  Double_t E[n]={0};
  Double_t R[n]={0};

  Double_t D1[n]={0};
  Double_t D2[n]={0};
  Double_t D3[n]={0};

  //TGraph *gr = new TGraph ("H1.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("H2.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("H3.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("He3.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("He4.txt");//x-E(MeV),y-R(mm)
 // TGraph *gr = new TGraph ("He6.txt");//x-E(MeV),y-R(mm)
//  TGraph *gr = new TGraph ("Li7.txt");//x-E(MeV),y-R(mm)
//  TGraph *gr = new TGraph ("Li8.txt");//x-E(MeV),y-R(mm)
//  TGraph *gr = new TGraph ("Li9.txt");//x-E(MeV),y-R(mm)
   //TGraph *gr = new TGraph ("Be9.txt");//x-E(MeV),y-R(mm)
//  TGraph *gr = new TGraph ("Be10.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("Be11.txt");//x-E(MeV),y-R(mm)
//  TGraph *gr = new TGraph ("C11.txt");//x-E(MeV),y-R(mm)
  //TGraph *gr = new TGraph ("C12.txt");//x-E(MeV),y-R(mm)
  TGraph *gr = new TGraph ("C13.txt");//x-E(MeV),y-R(mm)
 
  TF1 *f1 = new TF1("f1","[0]*pow(x,[1])",1,390);
	f1->SetParameters(0.01,1.7);
	gr->Fit(f1);
	/*gr->Draw("AP");//option attention!
	f1->Draw("same");*/

  Double_t p0=f1->GetParameter(0);
  Double_t p1=f1->GetParameter(1);
 
  TF1 *f2 = new TF1("f2","pow(x/[0],1/[1])",0,1.85);
	f2->SetParameters(p0,p1);

  TRandom3 *r = new TRandom3();
  for(Int_t i;i<10000;i++){
	R[i]=r->Uniform(0,1)*1.85;
	E[i]=f2(R[i]);
  } 

  for(Int_t i=0;i<n;i++)
  {
	if(R[i]<=0.1)
        {
	  D1[i]=E[i];D2[i]=0;D3[i]=0;
        }
	
	if(R[i]>0.1 && R[i]<0.6)
	{
	  D3[i]=0;D2[i]=f2(R[i]-0.1);D1[i]=E[i]-D2[i];
	}
	
	if(R[i]>0.6 && R[i]<=3.1)
	{
	  D3[i]=f2(R[i]-0.6);D2[i]=f2(R[i]-0.1)-D3[i];D1[i]=E[i]-f2(R[i]-0.1);
	}
	
	if(R[i]>3.1)
	{
	  D3[i]=f2(R[i]-0.6)-f2(R[i]-3.1);D2[i]=f2(R[i]-0.1)-f2(R[i]-0.6);D1[i]=E[i]-f2(R[i]-0.1);
	}
  }

  //output data
  freopen("C13_d1d2.txt","w",stdout);
  for(Int_t i=0;i<n;i++)
  {
    std::cout<< D2[i] << " " << D1[i] <<std::endl;
  }
  fclose(stdout);

  freopen("C13_d2d3.txt","w",stdout);
  for(Int_t i=0;i<n;i++)
  {
    std::cout<< D3[i] << " " << D2[i] <<std::endl;
  }
  fclose(stdout);
}

