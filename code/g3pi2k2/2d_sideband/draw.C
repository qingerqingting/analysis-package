#include "/afs/ihep.ac.cn/users/l/longyf/useful.h"

void draw(){

  //Control the style
  SetLyfStyle();

//Draw m_gam_rho vs m_2k
//Without the cut on m_gam_rho and m_2k.

  //The limits of signal region and sideband region.
  //x axis
    //Signal region
    //l means left limit, r means right limit.
  Double_t x_sig_l=1.01;
  Double_t x_sig_r=1.03;
    //Right sideband
    //First r means right sideband.
  Double_t x_sid_r_l=1.060;
  Double_t x_sid_r_r=1.080;

  //y axis
    //Signal redion
    //u means up limit, d means down limit.
  Double_t y_sig_u=0.981;
  Double_t y_sig_d=0.935;

    //Up sideband
    //First u means up sideband.
  Double_t y_sid_u_u=1.09;
  Double_t y_sid_u_d=1.05;

    //Down sideband
    //First d means down sideband.
  Double_t y_sid_d_u=0.82;
  Double_t y_sid_d_d=0.78;


  gStyle->SetOptStat(0);

  TH2F *h1=new TH2F ("h1",";m_{2K} [GeV];m_{#gamma#pi#pi} [GeV]",50,0.99,1.09,50,0.75,1.1);

  h1->GetXaxis()->SetNdivisions(505);
  h1->GetYaxis()->SetNdivisions(505);

  //phi
  Double_t m_2k;
  //eta'
  Double_t m_gam_rho;

  //The name of tree
  TChain *chain = new TChain("TreeRes");
  //The name of root file
  chain->Add("output_for_phi_etap.root");

  chain->SetBranchAddress("m_2k",&m_2k);
  chain->SetBranchAddress("m_gam_rho",&m_gam_rho);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    h1->Fill(m_2k,m_gam_rho);
  }

  TCanvas *c1=new TCanvas();
  h1->Draw("box");

  //Draw paves

    //Region1
  drawpave(x_sig_l,y_sid_u_d,x_sig_r,y_sid_u_u,4);
  Double_t x=(x_sig_l+x_sig_r)/2;
  Double_t y=(y_sid_u_d+y_sid_u_u)/2;
  TLatex *ltx=new TLatex(x,y,"1");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

    //Region3
  drawpave(x_sig_l,y_sid_d_d,x_sig_r,y_sid_d_u,4);
  Double_t x=(x_sig_l+x_sig_r)/2;
  Double_t y=(y_sid_d_d+y_sid_d_u)/2;
  TLatex *ltx=new TLatex(x,y,"3");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

    //Region5
  drawpave(x_sid_r_l,y_sig_d,x_sid_r_r,y_sig_u,4);
  Double_t x=(x_sid_r_l+x_sid_r_r)/2;
  Double_t y=(y_sig_d+y_sig_u)/2;
  TLatex *ltx=new TLatex(x,y,"5");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

    //Region2
  drawpave(x_sig_l,y_sig_d,x_sig_r,y_sig_u,2);
  Double_t x=(x_sig_l+x_sig_r)/2;
  Double_t y=(y_sig_d+y_sig_u)/2;
  TLatex *ltx=new TLatex(x,y,"2");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

    //Region4
  drawpave(x_sid_r_l,y_sid_u_d,x_sid_r_r,y_sid_u_u,3);
  Double_t x=(x_sid_r_l+x_sid_r_r)/2;
  Double_t y=(y_sid_u_d+y_sid_u_u)/2;
  TLatex *ltx=new TLatex(x,y,"4");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

    //Region6
  drawpave(x_sid_r_l,y_sid_d_d,x_sid_r_r,y_sid_d_u,3);
  Double_t x=(x_sid_r_l+x_sid_r_r)/2;
  Double_t y=(y_sid_d_d+y_sid_d_u)/2;
  TLatex *ltx=new TLatex(x,y,"6");
  ltx->SetTextSize(0.06);
  ltx->Draw("Same");

}

