#include<TMath.h>
void fit(){
	TCanvas *c =new TCanvas("c","");
	TGraph *gr = new TGraph("C13.txt");
	   gr->SetLineColor(4);
           gr->SetLineWidth(0.5);
	   gr->SetMarkerColor(4);
	   gr->SetMarkerStyle(20);
	   gr->SetMarkerSize(1);
	   gr->Draw("AP");

	   gr->GetYaxis()->SetTitle("Range(mm)");
           gr->GetXaxis()->SetTitle("Energy(MeV)");
//           gr->GetXaxis()->CenterTitle();
//           gr->GetYaxis()->CenterTitle();
    	   gr->GetYaxis()->SetTitleOffset(0.8);

         TF1 *f1 = new TF1("f1"," [0]*pow(x,[1])",1,500);
	      f1->SetParameters(0.1,1);
	      gr->Fit(f1);
	c->SaveAs("fitC13.jpg");
}

