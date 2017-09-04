const int n=10000;//total enevts
Float_t D1[n]={0};
Float_t D2[n]={0};	
Float_t D3[n]={0};

Float_t E[n]={0};
Float_t R[n]={0};


void CalcDe(){
//fit the data
         TGraph *Data = new TGraph("C13.txt");
         TF1 *f2 = new TF1("f2"," [0]*pow(x,[1])  ",1,30);
              f2->SetParameters(0.1,1);
              Data->Fit(f2);
         double P0 = f2->GetParameter(0);
         double P1 = f2->GetParameter(1);
         TF1 f1("f1","pow( x /[0] ,1 /[1] )",0,4);
             f1.SetParameters(P0,P1);
//get 10000 the random data
         for(int i = 0;i<10000;i++){
             R[i] = gRandom->Rndm()*3.5;//(unit mm)
             E[i] = f1(R[i]);//(unit MeV )
         }      
//calculate the de
    for (int i = 0; i < n; ++i)
    {
    	if (R[i]<=0.1)
    	{
    		D3[i] = 0; D2[i] = 0; D1[i] = E[i];  
    	}
       if (R[i]>0.1 && R[i]<=0.6)
    	{
    		D3[i] = 0; D2[i] = f1(R[i]-0.1); D1[i] = E[i]-D2[i];  
    	}
    	if (R[i]>0.6 && R[i]<=3.1)
    	{
    		D3[i] = f1(R[i]-0.6); D2[i] = f1(R[i]-0.1) - D3[i]; D1[i] = E[i]-D3[i]- D2[i];  
    	}
    	if (R[i]>3.1)
    	{
    		D3[i] = f1(R[i]-0.6) - f1(R[i]-3.1); D2[i] = f1(R[i]-0.1) - f1(R[i]-0.6); D1[i] = E[i] - f1(R[i]-0.1);  
    	}
    }
//output the file
   freopen("C13_1.txt","w",stdout);
   for(int k=0;k<n;k++){
           std::cout<< D2[k]<<"  "<<D1[k]<<std::endl;
           }
   fclose (stdout);

   freopen("C13_2.txt","w",stdout);
   for(int j=0;j<n;j++){
           std::cout<< D3[j]<<"  "<<D2[j]<<std::endl;
           }
   fclose (stdout);
}
