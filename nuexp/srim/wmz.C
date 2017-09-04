
void ee(){
 double R,E,a,b,c,E1[5000],E2[5000],E3[5000];
 a=5.75;
 b=0.014;
 c=-1.27;
 int i;

 double step=0.1;
 double E_min=1.0,E_max=30;
 for(E=E_min;E<=E_max;E+=step){
      R=a*E*E+b*E+c;
 	
      if(R<100){E1[i]=E;E2[i]=E3[i]=0;}
	
	else if(R>100&&R<600){
		E2[i]=(-b+sqrt(b*b-4*a*(c+100-R)))/(2*a);	
		E1[i]=E-E2[i];
		E3[i]=0;}
	
	else if(R>600&&R<3100){
		E3[i]=(-b+sqrt(b*b-4*a*(c+600-R)))/(2*a);
 		E2[i]=(-b+sqrt(b*b-4*a*(c+100-R)))/(2*a)-E3[i];
		E1[i]=E-E3[i]-E2[i];}
	
	else if(R>3100){
		E3[i]=(-b+sqrt(b*b-4*a*(c+600-R)))/(2*a)-(-b+sqrt(b*b-4*a*(c+3100-R)))/(2*a);
		E2[i]=(-b+sqrt(b*b-4*a*(c+100-R)))/(2*a)-(-b+sqrt(b*b-4*a*(c+600-R)))/(2*a);
		E1[i]=E-(-b+sqrt(b*b-4*a*(c+100-R)))/(2*a);}
 	i++;
	}
 cout<<i<<endl;
 TCanvas *c1=new TCanvas("c1","dE1-dE2",200,10,700,500);
 TGraph *g1=new TGraph(i,E2,E1);
 g1->GetXaxis()->SetTitle("dE2:MeV");
 g1->GetYaxis()->SetTitle("dE1:MeV");
 g1->Draw();
}
