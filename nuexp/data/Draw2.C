#include<TMath.h>
void Draw2(){
	  gStyle->SetCanvasBorderMode(0);
	  gStyle->SetCanvasBorderSize(0);
	  // White BG
	  gStyle->SetCanvasColor(10);
	  // Format for axes
	  gStyle->SetLabelFont(42,"xyz");
	  gStyle->SetLabelSize(0.03,"xyz");
	  gStyle->SetLabelOffset(0.01,"xyz");
	  gStyle->SetNdivisions(510,"xyz");
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
        TGraph *C13 = new TGraph("C13_2.txt");
                C13->SetLineColor(1);
                C13->SetMarkerColor(1);
                C13->SetLineWidth(1);
                C13->Draw("AP");
                C13->GetYaxis()->SetTitle("#Delta E_{2} (MeV)");
                C13->GetXaxis()->SetTitle("#Delta E_{3} (MeV)");
        TGraph *C12 = new TGraph("C12_2.txt");
                C12->SetLineColor(2);
                C12->SetMarkerColor(2);
                C12->SetLineWidth(1);
                C12->Draw("Psame");

        TGraph *C11 = new TGraph("C11_2.txt");
                C11->SetLineColor(3);
                C11->SetMarkerColor(3);
                C11->SetLineWidth(1);
                C11->Draw("Psame");

        TGraph *Be11 = new TGraph("Be11_2.txt");
                Be11->SetLineColor(4);
                Be11->SetMarkerColor(4);
                Be11->SetLineWidth(1);
                Be11->Draw("Psame");
        
        TGraph *Be10 = new TGraph("Be10_2.txt");
                Be10->SetLineColor(5);
                Be10->SetMarkerColor(5);
                Be10->SetLineWidth(1);
                Be10->Draw("Psame");
        
        TGraph *Be9 = new TGraph("Be9_2.txt");
                Be9->SetLineColor(6);
                Be9->SetMarkerColor(6);
                Be9->SetLineWidth(1);
                Be9->Draw("Psame");

        
        TGraph *Li9 = new TGraph("Li9_2.txt");
                Li9->SetLineColor(7);
                Li9->SetMarkerColor(7);
                Li9->SetLineWidth(1);
                Li9->Draw("Psame");
        
        TGraph *Li8 = new TGraph("Li8_2.txt");
                Li8->SetLineColor(8);
                Li8->SetMarkerColor(8);
                Li8->SetLineWidth(1);
                Li8->Draw("Psame");
        TGraph *Li7 = new TGraph("Li7_2.txt");
                Li7->SetLineColor(9);
                Li7->SetMarkerColor(9);
                Li7->SetLineWidth(1);
                Li7->Draw("Psame");

        TGraph *He6 = new TGraph("He6_2.txt");
                He6->SetLineColor(10);
                He6->SetMarkerColor(10);
                He6->SetLineWidth(1);
                He6->Draw("Psame");

        TGraph *He4 = new TGraph("He4_2.txt");
                He4->SetLineColor(11);
                He4->SetMarkerColor(11);
                He4->SetLineWidth(1);
                He4->Draw("Psame");

        TGraph *He3 = new TGraph("He3_2.txt");
                He3->SetLineColor(12);
                He3->SetMarkerColor(12);
                He3->SetLineWidth(1);
                He3->Draw("Psame");

        TGraph *H3 = new TGraph("H3_2.txt");
                H3->SetLineColor(13);
                H3->SetMarkerColor(13);
                H3->SetLineWidth(1);
                H3->Draw("Psame");

        TGraph *H2 = new TGraph("H2_2.txt");
                H2->SetLineColor(14);
                H2->SetMarkerColor(14);
                H2->SetLineWidth(1);
                H2->Draw("Psame");

        TGraph *H1 = new TGraph("H1_2.txt");
                H1->SetLineColor(15);
                H1->SetMarkerColor(15);
                H1->SetLineWidth(1);
                H1->Draw("Psame");

       TLegend * leg = new TLegend(0.75, 0.45, 0.9, 0.9);
                 leg->AddEntry(C13, "^{13}C", "L");
                 leg->AddEntry(C12, "^{12}C", "L");
                 leg->AddEntry(C11, "^{11}C", "L");
                 leg->AddEntry(Be11,"^{11}Be","L");
                 leg->AddEntry(Be10,"^{10}Be","L");
                 leg->AddEntry(Be9, "^{9}Be", "L");
                 leg->AddEntry(Li9, "^{9}Li", "L");
                 leg->AddEntry(Li8, "^{8}Li", "L");
                 leg->AddEntry(Li7, "^{7}Li", "L");
                 leg->AddEntry(He6, "^{6}He", "L");
                 leg->AddEntry(He4, "^{4}He", "L");
                 leg->AddEntry(He3, "^{3}He", "L");
                 leg->AddEntry(H3,  "^{3}H", "L");
                 leg->AddEntry(H2,  "^{2}H", "L");
                 leg->AddEntry(H1,  "^{1}H", "L");

                 leg->SetFillColor(0);
                 leg->SetTextFont(6);
                 leg->SetTextSize(18);
                 leg->Draw();
}
