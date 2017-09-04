#include "/afs/ihep.ac.cn/users/l/longyf/useful.h"

void draw_2gam(){
  SetLyfStyle();

//Draw m_2gam
//Before veto pi0.
//Show that vetoing pi0 is necessary

  gStyle->SetOptStat(0);

  //Veto pi0
  //=********************
  Double_t up_pi0=0.15;
  Double_t low_pi0=0.12;
    //MARK_pi0=1: veto pi0;
    //MARK_pi0=0: don't veto pi0;
  Int_t MARK_pi0=0;
  //=********************

  //The name of tree
  TChain *chain = new TChain("TreeAna");
  //The name of root file
  chain->Add("./data_g3pi2k2.root");

  TCanvas *c1=new TCanvas();
  c1->Divide(1,1);

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",1000,0.,1);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

    //eta
  Double_t m_2gam_1;
  Double_t m_2gam_2;
  Double_t m_2gam_3;

    //eta
  TLorentzVector p_2gam_1;
  TLorentzVector p_2gam_2;
  TLorentzVector p_2gam_3;

  gamma1 = new TLorentzVector();
  gamma2 = new TLorentzVector();
  gamma3 = new TLorentzVector();

  chain->SetBranchAddress("gamma1",&gamma1);
  chain->SetBranchAddress("gamma2",&gamma2);
  chain->SetBranchAddress("gamma3",&gamma3);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //eta
    p_2gam_1=*gamma2+ *gamma3;
    m_2gam_1=p_2gam_1.M();

    //veto pi0
    if ( MARK_pi0==1 ) {
      if ( (m_2gam_1>low_pi0)&&(m_2gam_1<up_pi0) ) continue;
    }//End with veto pi0.

    p_2gam_2=*gamma1+ *gamma3;
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ( MARK_pi0==1 ) {
      if ( (m_2gam_2>low_pi0)&&(m_2gam_2<up_pi0) ) continue;
    }//End with veto pi0.

    p_2gam_3=*gamma1+ *gamma2;
    m_2gam_3=p_2gam_3.M();

    //veto pi0
    if ( MARK_pi0==1 ) {
      if ( (m_2gam_3>low_pi0)&&(m_2gam_3<up_pi0) ) continue;
    }//End with veto pi0.

    h1->Fill(m_2gam_1);
    h1->Fill(m_2gam_2);
    h1->Fill(m_2gam_3);
  }

  c1->cd(1);
  h1->Draw("pe");

  //Draw arrow
  drawarrow(low_pi0,0,100000);
  drawarrow(up_pi0,0,100000);
}
