#include<TMath.h>
void fit(){
	  gStyle->SetCanvasBorderMode(0);
	  gStyle->SetCanvasBorderSize(0);
	  // White BG
	  gStyle->SetCanvasColor(10);
	  // Format for axes
	  gStyle->SetLabelFont(42,"xyz");
	  gStyle->SetLabelSize(0.03,"xyz");
	  gStyle->SetLabelOffset(0.01,"xyz");
	  gStyle->SetNdivisions(510,"xyz");
//	  gStyle->SetTitleFont(42,"xyz");
//	  gStyle->SetTitleColor(1,"xyz");
//	  gStyle->SetTitleSize(0.05,"xyz");
	  gStyle->SetTitleOffset(1.15,"xyz");
	  // No pad borders
	  gStyle->SetPadBorderMode(0);
	  gStyle->SetPadBorderSize(0);
	  // White BG
	  gStyle->SetPadColor(10);
	  // Margins for labels etc.
	  gStyle->SetPadLeftMargin(0.17);
	  gStyle->SetPadBottomMargin(0.17);
	  gStyle->SetPadRightMargin(0.05);
	  gStyle->SetPadTopMargin(0.05);
	  // No error bars in x direction
	  gStyle->SetErrorX(0);
	  // Format legend
	  gStyle->SetLegendBorderSize(0);
	  gStyle->SetOptTitle(0);
	//Set the value luminosity vs cross section 
        //Draw the plot of luminosity vs cross section
	TGraph *UL = new TGraph("H1.txt");
	   UL->SetLineColor(4);
           UL->SetLineWidth(2);
	   UL->SetMarkerColor(8);
	   UL->SetMarkerStyle(20);
	   UL->SetMarkerSize(1);
	   UL->Draw("AP");

           UL->GetYaxis()->SetLabelSize(0.05);
           UL->GetYaxis()->SetTitleSize(0.06);
           UL->GetYaxis()->SetLabelOffset(0.01);
           UL->GetYaxis()->SetNdivisions(510);
           UL->GetYaxis()->SetTitleFont(2);
           UL->GetYaxis()->SetTitleColor(1);
           UL->GetYaxis()->SetTitleOffset(1.15);
           UL->GetYaxis()->CenterTitle();

	   UL->GetXaxis()->SetLabelSize(0.05);
           UL->GetXaxis()->SetTitleSize(0.065);
  	   UL->GetXaxis()->SetLabelOffset(0.01);
	   UL->GetXaxis()->SetNdivisions(510);
	   UL->GetXaxis()->SetTitleFont(2);
	   UL->GetXaxis()->SetTitleColor(1);
	   UL->GetXaxis()->SetTitleOffset(1.2);
	   UL->GetXaxis()->CenterTitle();

           UL->GetYaxis()->SetTitle("distance (mm)");
           UL->GetXaxis()->SetTitle("Energy (MeV)");
//	   UL->GetYaxis()->SetRangeUser(0,2.5e-5);
	//Start the fit
//         TF1 *f2 = new TF1("f2","[0]*exp( [1]*pow(x,[2]) + [3]*x ) ",0,2);
         TF1 *f2 = new TF1("f2"," [0]*pow(x,[1])  ",1,500);
	      f2->SetParameters(0.1,1);
	      UL->Fit(f2);

         TLatex * prelim = new TLatex(0.5,0.7, "^{1}H");
         prelim->SetNDC();
         prelim->SetTextFont(62);
         prelim->SetTextSize(0.1);
         prelim->SetTextAlign(33);
         prelim->Draw();
}
