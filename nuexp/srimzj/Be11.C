//
//get d1-d2,d2-d3
//
const int parN=68;//numbers of par
const int Emax=330;//upper limit of Ein;MeV
const int totn=200;
double parE[parN];//MeV
double parR[parN];//um

void readpar(const char *Be11,double *parx,double *pary,int n=41){
	ifstream in(Be11);
	for(int i=0;i<n;i++){
		parx[i]=0;
		pary[i]=0;
	}
	if(!in.is_open()) {
		cout<<"cannot open the file: "<<Be11<<endl;
		return;
	}
	int cnt=0;
	while(1){
		double tmpx,tmpy;
		in>>tmpx>>tmpy;
		if(!in.good()) break;
		parx[cnt]=tmpx;
		pary[cnt]=tmpy;
		cnt++;
	}
}

void getdepE(double Ein,double *En,double *dL,double& depth,int& cnt,double thre,int thickness){
	if(Ein<thre) return;
	const double dE=0.001;//MeV
	int step=Ein/dE;
	En[0]=Ein;
	for(int s=0;s<step;++s){
		En[s+1]=En[s]-dE;
		dL[s]=f->Eval(En[s])-f->Eval(En[s+1]);
		depth=depth+dL[s];
		cnt++;
		if(depth>thickness) break;
	}
}

void clear(double *En,double *dL,double& depth,int& cnt){
	for(int i=0;i<300000;++i){
		dL[i]=0;
		En[i]=0;
	}
	depth=cnt=0;
}

void Be11(){
	TF1 *f = new TF1("f","pol4",1,300);
	TRandom3 *r=new TRandom3();
	int cnt;//counts
	int hit=0;
	const double thre=0.01;
	double Ein=0.0;//MeV
	double En[300000];
	double dL[300000];
	double depth;//um
	double Si1E[300000];//100um
	double Si2E[300000];//500um
	double Si3E[300000];//2500um
	for(int i=0;i<300000;++i) Si1E[i]=Si2E[i]=Si3E[i]=0;
	//*******************Ein-Range****************//
	erfit(parN);
	//*******************Get dE-E****************//
	for(int i=0;i<totn;++i){
		//****************1st Si******************//
		clear(En,dL,depth,cnt);
		Ein=r->Uniform(1,Emax);//1MeV--->270MeV
		getdepE(Ein,En,dL,depth,cnt,thre,100);
		if(En[cnt]<thre){
			Si1E[hit]=Ein;
			Ein=0;
		}
		else{
			Si1E[hit]=Ein-En[cnt];
			Ein=En[cnt];
		}
		//****************2nd Si******************//
		clear(En,dL,depth,cnt);
		getdepE(Ein,En,dL,depth,cnt,thre,500);
		if(En[cnt]<thre){
			Si2E[hit]=Ein;
			Ein=0;
		}
		else{
			Si2E[hit]=Ein-En[cnt];
			Ein=En[cnt];
		}
		//****************3rd Si******************//
		clear(En,dL,depth,cnt);
		getdepE(Ein,En,dL,depth,cnt,thre,2500);
		if(En[cnt]<thre){
			Si3E[hit]=Ein;
		}
		else{
			Si3E[hit]=Ein-En[cnt];
		}
		hit++;
		cout<<"working..."<<hit<<"/"<<totn<<endl;
	}
	//*******************Results output****************//
	ofstream optd1d2("./Be11d1d2.txt");
	//ofstream optd1d2("/home/zqchen/hw1/dE-E/Be11d1d2.txt");
	//ofstream optd2d3("/home/zqchen/hw1/dE-E/Be11d2d3.txt");
	ofstream optd2d3("./Be11d2d3.txt");
	for(int i=0;i<hit;++i){
		optd1d2<<Si1E[i]<<' '<<Si2E[i]<<endl;
		optd2d3<<Si2E[i]<<' '<<Si3E[i]<<endl;
	}
	delete r;
	delete f;
}
void erfit(int parN){
	//readpar("/home/zqchen/hw1/range2/1keV/Be11.txt",parE,parR,parN);
	readpar("./Be11",parE,parR,parN);
	draw(parN,parE,parR);
}
void draw(int n,double *x,double *y){
	TCanvas *cantem=new TCanvas("cantem","range",10,10,1100,1100);
	TGraph *g = new TGraph(n,x,y);
	g->SetMarkerSize(0.5);
	g->SetMarkerStyle(20);
	g->Draw("ap");
	g->SetTitle("Be11_Ein-Range");
	g->GetXaxis()->SetTitle("Ein(MeV)");
	g->GetYaxis()->SetTitle("Range(um)");
	TFitResultPtr *fh=g->Fit("f","S");//¡°S¡±save the function par
	double c2ndf=fh->Chi2()/fh->Ndf();
	ofstream optc2ndf("./Be11ch2ndf.txt");
	cantem->SaveAs("./Be11.root");
	//cantem->SaveAs("/home/zqchen/hw1/range2/Be11.root");
	optc2ndf<<"c2ndf="<<c2ndf<<endl;
	delete g;
	delete cantem;//delete
}
