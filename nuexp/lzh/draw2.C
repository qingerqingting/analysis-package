#include<TMath.h>
void draw2(){
	TCanvas *c = new TCanvas("c","");
        TGraph *C13 = new TGraph("C13_d2d3.txt");
                C13->SetLineColor(1);
                C13->SetMarkerColor(1);
                C13->SetLineWidth(1);
                C13->Draw("AP");
                C13->SetTitle("dE_{2}dE_{3}");
                C13->GetYaxis()->SetTitle(" dE_{2} (MeV)");
                C13->GetXaxis()->SetTitle(" dE_{3} (MeV)");
//                C13->GetXaxis()->SetRangeUser(-200,200);
//                C13->GetYaxis()->SetRangeUser(-5,80);
                //C13->GetXaxis()->SetRangeUser(-100,200);
        TGraph *C12 = new TGraph("C12_d2d3.txt");
                C12->SetLineColor(2);
                C12->SetMarkerColor(2);
                C12->SetLineWidth(1);
                C12->Draw("Psame");

        TGraph *C11 = new TGraph("C11_d2d3.txt");
                C11->SetLineColor(3);
                C11->SetMarkerColor(3);
                C11->SetLineWidth(1);
                C11->Draw("Psame");

        TGraph *Be11 = new TGraph("Be11_d2d3.txt");
                Be11->SetLineColor(4);
                Be11->SetMarkerColor(4);
                Be11->SetLineWidth(1);
                Be11->Draw("Psame");
        
        TGraph *Be10 = new TGraph("Be10_d2d3.txt");
                Be10->SetLineColor(5);
                Be10->SetMarkerColor(5);
                Be10->SetLineWidth(1);
                Be10->Draw("Psame");
        
        TGraph *Be9 = new TGraph("Be9_d2d3.txt");
                Be9->SetLineColor(6);
                Be9->SetMarkerColor(6);
                Be9->SetLineWidth(1);
                Be9->Draw("Psame");

        
        TGraph *Li9 = new TGraph("Li9_d2d3.txt");
                Li9->SetLineColor(7);
                Li9->SetMarkerColor(7);
                Li9->SetLineWidth(1);
                Li9->Draw("Psame");
        
        TGraph *Li8 = new TGraph("Li8_d2d3.txt");
                Li8->SetLineColor(8);
                Li8->SetMarkerColor(8);
                Li8->SetLineWidth(1);
                Li8->Draw("Psame");
        TGraph *Li7 = new TGraph("Li7_d2d3.txt");
                Li7->SetLineColor(9);
                Li7->SetMarkerColor(9);
                Li7->SetLineWidth(1);
                Li7->Draw("Psame");

        TGraph *He6 = new TGraph("He6_d2d3.txt");
                He6->SetLineColor(10);
                He6->SetMarkerColor(10);
                He6->SetLineWidth(1);
                He6->Draw("Psame");

        TGraph *He4 = new TGraph("He4_d2d3.txt");
                He4->SetLineColor(11);
                He4->SetMarkerColor(11);
                He4->SetLineWidth(1);
                He4->Draw("Psame");

        TGraph *He3 = new TGraph("He3_d2d3.txt");
                He3->SetLineColor(12);
                He3->SetMarkerColor(12);
                He3->SetLineWidth(1);
                He3->Draw("Psame");

        TGraph *H3 = new TGraph("H3_d2d3.txt");
                H3->SetLineColor(13);
                H3->SetMarkerColor(13);
                H3->SetLineWidth(1);
                H3->Draw("Psame");
                //H3->Draw("AP");

        TGraph *H2 = new TGraph("H2_d2d3.txt");
                H2->SetLineColor(14);
                H2->SetMarkerColor(14);
                H2->SetLineWidth(1);
                H2->Draw("Psame");

        TGraph *H1 = new TGraph("H1_d2d3.txt");
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
                 leg->SetTextSize(16);
                 leg->Draw();
	c->SaveAs("d2d3.jpg");
}
