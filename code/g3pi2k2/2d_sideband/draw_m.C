#include "/Users/long/workarea/Style/useful.h"
void draw_m(){
  //Draw the mass spectrum of phi+etap.
  //Draw sideband from phi and etap.

  SetLyfStyle();

  gStyle->SetOptStat(0);
  Double_t m_phi_etap;

  //Get m_{phi+etap} from data.
  //The name of tree
  TChain *chain = new TChain("TreeRes");
  //The name of root file
  chain->Add("../output_data_g3pi2k2_0912.root");

  TH1F *h1=new TH1F ("h1","The mass spectrum of phi&etap",35,1.9,2.6);
  h1->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h1);

  chain->SetBranchAddress("m_phi_etap",&m_phi_etap);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    h1->Fill(m_phi_etap);
  }//end with data.

  //Get m_{phi+etap} from sideband of phi.
  TFile *f2=new TFile("output_sideband.root");
  TH1F *h2=(TH1F*)f2->Get("h3");

  //Control the style of h2
  h2->SetLineColor(kGreen);
  h2->SetFillColor(kGreen);

  TCanvas *c1=new TCanvas();
 
  h1->Draw("pe");
  h2->Draw("same");

  //legend
  TLegend leg(.1,.7,.3,.9,"Sideband analysis:");
  leg.SetFillColor(0);
  leg.AddEntry(h1,"Data","lpe");
  leg.AddEntry(h2,"Sideband of eta and phi","l");
  leg.DrawClone("same");
}
