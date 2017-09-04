void his(){
  
   TH1F *h = new TH1F("h","fillhis",10,-10,10);
   h->Fill(0);
   h->Fill(2);
   h->Fill(0.2);
   h->Fill(8.9);
   h->Fill(-1.2);
   h->Fill(-2.3);
   h->Fill(-6);
   h->Draw();
   h->GetXaxis()->SetRange(2,9);//bin range  
//   h->GetXaxis()->SetRangeUser(2,9); //(2,9)x range 
// h->SaveAs("h.pdf");
  
}
