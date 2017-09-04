//
//for d2-d3
//
const int nBe11=200;
const int nBe10=200;
const int nBe9=200;
double Be11x[nBe11];
double Be11y[nBe11];
double Be10x[nBe10];
double Be10y[nBe10];
double Be9x[nBe9];
double Be9y[nBe9];
void readpar(const char *filename,double *parx,double *pary,int n){
	ifstream in(filename);
	for(int i=0;i<n;i++){
		parx[i]=0;
		pary[i]=0;
	}
	if(!in.is_open()) {
		cout<<"cannot open the file: "<<filename<<endl;
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

int draw2(){
	TCanvas *cc = new TCanvas("cc","draw",10,10,2000,1000);
	cc->SetGrid();
	TMultiGraph *mg = new TMultiGraph();
	readpar("/home/zqchen/hw1/dE-E/Be11d2d3.txt",Be11y,Be11x,nBe11);
	readpar("/home/zqchen/hw1/dE-E/Be10d2d3.txt",Be10y,Be10x,nBe10);
	readpar("/home/zqchen/hw1/dE-E/Be9d2d3.txt",Be9y,Be9x,nBe9);
	TGraph *gr1 = new TGraph(nBe11,Be11x,Be11y);
	gr1->SetName("Be11d2-d3");
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerSize(1);
	gr1->SetMarkerColor(kRed);
	gr1->SetLineWidth(0);
	gr1->Draw("ap");
	mg->Add(gr1);

	TGraph *gr2 = new TGraph(nBe10,Be10x,Be10y);
	gr2->SetName("Be10d2-d3");
	gr2->SetMarkerStyle(22);
	gr2->SetMarkerSize(1);
	gr2->SetMarkerColor(kBlue);
	gr2->SetLineWidth(0);
	gr2->Draw("ap");
	mg->Add(gr2);

	TGraph *gr3 = new TGraph(nBe9,Be9x,Be9y);
	gr3->SetName("Be9d2-d3");
	gr3->SetMarkerStyle(21);
	gr3->SetMarkerSize(1);
	gr3->SetMarkerColor(kGreen);
	gr3->SetLineWidth(0);
	gr3->Draw("ap");
	mg->Add(gr3);

	mg->Draw("aqnp");
	mg->SetTitle("Be9,10,11");
	mg->GetYaxis()->SetTitle("d2(MeV)");
	mg->GetXaxis()->SetTitle("d3(MeV)");
	leg=new TLegend(0.7,0.7,0.9,0.9);
	leg->AddEntry(gr1,"Be11","lep");
	leg->AddEntry(gr2,"Be10","lep");
	leg->AddEntry(gr3,"Be9","lep");
	leg->Draw();
	cc->SaveAs("/home/zqchen/hw1/Bed2d3.png");
}
