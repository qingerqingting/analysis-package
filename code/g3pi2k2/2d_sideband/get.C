#include "/Users/long/workarea/Style/useful.h"
void get(){
// Get 2d sideband
//x: m_2k
//y: m_gam_rho
//Cuts on phi and etap are closed.

  //Control the style
  SetLyfStyle();

  //Scale factors
  //=******************************
  Double_t omega_horizontal=0.0165392;
  Double_t omega_vertical=0.373092;
  Double_t omega_diagonal=-0.00617063;
  //=******************************

  //The name of tree
  TChain *chain = new TChain("TreeRes");
  //The name of root file
  chain->Add("output_for_fit_2d.root");

  TH1F *h1=new TH1F ("h1","The mass spectrum of phi&etap",35,1.9,2.6);
  h1->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of phi&etap",35,1.9,2.6);
  h2->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of phi&etap",35,1.9,2.6);
  h3->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h3);

    //phi
  Double_t m_2k;
    //eta'
  Double_t m_gam_rho;
    //Y(2175)
  Double_t m_phi_etap;

  chain->SetBranchAddress("m_2k",&m_2k);
  chain->SetBranchAddress("m_gam_rho",&m_gam_rho);
  chain->SetBranchAddress("m_phi_etap",&m_phi_etap);

  //The limits of signal region and sideband region.
  //x axis
    //Signal region
    //l means left limit, r means right limit.
  Double_t x_sig_l=1.0126;
  Double_t x_sig_r=1.0264;
    //Right sideband
    //First r means right sideband.
  Double_t x_sid_r_l=1.060;
  Double_t x_sid_r_r=1.074;

  //y axis
    //Signal redion
    //u means up limit, d means down limit.
  Double_t y_sig_u=0.9719;
  Double_t y_sig_d=0.9343;

    //Up sideband
    //First u means up sideband.
  Double_t y_sid_u_u=1.09;
  Double_t y_sid_u_d=1.05;

    //Down sideband
    //First d means down sideband.
  Double_t y_sid_d_u=0.82;
  Double_t y_sid_d_d=0.78;

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    
    //Events in region5,horizontal
    if ((m_2k>x_sid_r_l)&&(m_2k<x_sid_r_r)&&(m_gam_rho>y_sig_d)&&(m_gam_rho<y_sig_u)) h1->Fill(m_phi_etap);

    //Events in region1 and region3,vertical
    if (((m_2k>x_sig_l)&&(m_2k<x_sig_r))&&(((m_gam_rho>y_sid_u_d)&&(m_gam_rho<y_sid_u_u))||((m_gam_rho>y_sid_d_d)&&(m_gam_rho<y_sid_d_u)))) h2->Fill(m_phi_etap);

    //Events in region4 and region6,diagonal
    if (((m_2k>x_sid_r_l)&&(m_2k<x_sid_r_r))&&(((m_gam_rho>y_sid_u_d)&&(m_gam_rho<y_sid_u_u))||((m_gam_rho>y_sid_d_d)&&(m_gam_rho<y_sid_d_u)))) h3->Fill(m_phi_etap);
  }

  //Get the numbers of events in different regions.
  Double_t num_horizontal=h1->GetEntries();
  Double_t num_vertical=h2->GetEntries();
  Double_t num_diagonal=h3->GetEntries();

  TH1F *h4=new TH1F(*h1);
  h4->Add(h1,h2,omega_horizontal,omega_vertical);
  TH1F *h5=new TH1F(*h3);
  h5->Add(h4,h3,1,omega_diagonal);

  //Draw the histogram
 // TCanvas *c1=new TCanvas();
 // h5->Draw();

  //Store the histo in root file.
  //Store h5, in the name of h3.
  TFile *ofile=new TFile("output_sideband.root","RECREATE");
  h5->Write();
  ofile->Close();

  //Get the number of sideband events and uncertainty.
  Double_t num_sid=h5->GetEntries();

  Double_t u_horizontal=TMath::Sqrt(num_horizontal);
  Double_t u_vertical=TMath::Sqrt(num_vertical);
  Double_t u_diagonal=TMath::Sqrt(num_diagonal);

  Double_t u_sid=TMath::Sqrt(omega_horizontal*u_horizontal*omega_horizontal*u_horizontal + omega_vertical*u_vertical*omega_vertical*u_vertical + omega_diagonal*u_diagonal*omega_diagonal*u_diagonal);

  cout<<"Num_[sid]="<<num_sid<<" +- "<<u_sid<<endl;
}

