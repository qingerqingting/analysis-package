void test(){
  //Get the number of mis-combination of photons.
  //Check if the delta2 method is valid or not.
  //Jpsi -> phi eta etap.

  //=*******************************************************************************
  // *p_g1_mctruth, gm1    : photon, truth level
  // *gamma1_unfitted, g1  : photon, after detection
  // g1_af                 : photon, right combination using MC Truth, 100% correct.
  // gamma1_f              : photon, right combination using delta2, mostly correct.
  // pp                    : pion+,  truth level
  // pm                    : pion-.  truth level
  // *pip_unfitted, pip_u  : pion+,  after detection
  // *pim_unfitted, pim_u  : pion-,  after detection
  // *kp_unfitted,  kp_u   : kion+,  after detection
  // *km_unfitted,  km_u   : kion-,  after detection
  //=*******************************************************************************

  //The name of tree
  TChain *chain = new TChain("TreeAna");
  //The name of root file
  chain->Add("topo.root");

  //Histograms.
    //Eta
    //MC Truth
  TH1F *h1=new TH1F("h1","m_{2#gamma}",70,0.4,0.65);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);
    //After detection: MC Truth
  TH1F *h2=new TH1F("h2","m_{2#gamma}",70,0.4,0.65);
  h2->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h2);
    //After detection: delta2    
  TH1F *h3=new TH1F("h3","m_{2#gamma}",70,0.4,0.65);
  h3->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h3);

    //Etap
    //MC Truth
  TH1F *h4=new TH1F("h4","m_{#gamma+2#pi}",50,0.85,1.05);
  h4->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h4);
    //After detection: MC Truth
  TH1F *h5=new TH1F("h5","m_{#gamma+2#pi}",50,0.85,1.05);
  h5->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h5);
    //After detection: delta2
  TH1F *h6=new TH1F("h6","m_{#gamma+2#pi}",50,0.85,1.05);
  h6->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h6);

  TH1F *h7=new TH1F ("h7","The mass spectrum of 2 gam",70,0.4,0.65);
  h7->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h7);

  TH1F *h8=new TH1F ("h8","The mass spectrum of 2 pi",100,0.2,1.2);
  h8->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h8);

  TH1F *h9=new TH1F ("h9","The mass spectrum of 2 k",50,0.97,1.07);
  h9->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h9);

  TH1F *h10=new TH1F ("h10","The mass spectrum of gamma&rho0",50,0.85,1.05);
  h10->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h10);

  //Fake photon
  TH1F *h11=new TH1F ("h11","The mass spectrum of phi&etap",35,1.9,2.6);
  h11->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h11);

  //Mis-combination
  TH1F *h12=new TH1F ("h12","The mass spectrum of phi&etap",35,1.9,2.6);
  h12->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h12);

  TH1F *h13=new TH1F ("h13","The mass spectrum of phi&etap",35,1.9,2.6);
  h13->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h13);

  //SetNdivision
  setdivision(h4);
  setdivision(h5);
  setdivision(h6);
  setdivision(h8);
  setdivision(h9);
  setdivision(h10);

  //itopo
  Int_t itopo;
  //Particles in truth level.
  TLorentzVector *p_g1_mctruth;
  TLorentzVector *p_g2_mctruth;
  TLorentzVector *p_g3_mctruth;
  TLorentzVector *p_pip_mctruth;
  TLorentzVector *p_pim_mctruth;
    //MC Truth
  TLorentzVector gm1;
  TLorentzVector gm2;
  TLorentzVector gm3;
  TLorentzVector pp;
  TLorentzVector pm;

  //4-momentum of photons after detection.
  TLorentzVector *gamma1_unfitted;
  TLorentzVector *gamma2_unfitted;
  TLorentzVector *gamma3_unfitted;
    //After detector, remove "*".
  TLorentzVector g1;
  TLorentzVector g2;
  TLorentzVector g3;  
    //After detector, use MC Truth.
  TLorentzVector g1_af;
  TLorentzVector g2_af;
  TLorentzVector g3_af;
    //After detector, use delta2.
  TLorentzVector gamma1_f;
  TLorentzVector gamma2_f;
  TLorentzVector gamma3_f;

  //2 pi, after detection.
  TLorentzVector *pip_unfitted;
  TLorentzVector *pim_unfitted;
  TLorentzVector pip_u;
  TLorentzVector pim_u;
  
  //2 K, after detection.
  TLorentzVector *kp_unfitted;
  TLorentzVector *km_unfitted;
  TLorentzVector kp_u;
  TLorentzVector km_u;

  //Chi2
  Double_t Chisq_low;

  //=*********************

  chain->SetBranchAddress("itopo",&itopo);
  //Read Chisq.
  chain->SetBranchAddress("Chisq_low",&Chisq_low);
  //Read the P of particles.
  //MC Truth
  chain->SetBranchAddress("p_g1_mctruth",&p_g1_mctruth);
  chain->SetBranchAddress("p_g2_mctruth",&p_g2_mctruth);
  chain->SetBranchAddress("p_g3_mctruth",&p_g3_mctruth);
  chain->SetBranchAddress("p_pip_mctruth",&p_pip_mctruth);
  chain->SetBranchAddress("p_pim_mctruth",&p_pim_mctruth);

  //The P of particles after detection.
  //Photons.
  chain->SetBranchAddress("gamma1_unfitted",&gamma1_unfitted);
  chain->SetBranchAddress("gamma2_unfitted",&gamma2_unfitted);
  chain->SetBranchAddress("gamma3_unfitted",&gamma3_unfitted);
  //2 pi.
  chain->SetBranchAddress("pip_unfitted",&pip_unfitted);
  chain->SetBranchAddress("pim_unfitted",&pim_unfitted);
  //2 K.
  chain->SetBranchAddress("kp_unfitted",&kp_unfitted);
  chain->SetBranchAddress("km_unfitted",&km_unfitted);

  //The angles between gammas (truth level) and gammas (after detection).
  //ang12: the angle between p_g1_mctruth and gamma2_unfitted.
  Double_t ang11;
  Double_t ang12;
  Double_t ang13;
  Double_t ang21;
  Double_t ang22;
  Double_t ang23;
  Double_t ang31;
  Double_t ang32;
  Double_t ang33;

  //Cut on angle.
  const Double_t angle_cut=5;

  const Double_t pi=3.1415926;

  //Prepare for MC Truth method.
  //=*******************************************
  //After detection, using MC Truth,100% correct.
  Double_t m_2gam_th;
  Double_t m_gam_rho_th;
  Double_t deltasq_th;
  Double_t m_phi_etap_th;

  //Prepare for delta2 method.
  //=*******************************
  Double_t deltasq;
  Double_t deltasq_low;

  Int_t mark1;

  //Mass of particles.
    //eta
  Double_t m_2gam;
    //phi
  Double_t m_2k;
    //rho0
  Double_t m_2pi;
    //eta'
  Double_t m_gam_rho;
    //Y(2175)
  Double_t m_phi_etap;

  //P of particles;
    //eta
  TLorentzVector p_2gam;
    //phi
  TLorentzVector p_2k;

  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_gam_rho;

  const Double_t m_eta=0.5479;
  const Double_t m_etap=0.9578;

  const Double_t w_eta=0.0225;
  const Double_t w_etap=0.0171;
  //end of prepare for delta2 method.
  //=*********************************

  //Calculate the number of mis-combination.
  //The number of all events.
  Double_t sum1;
  //The number of mis-combination + fake photon events.
  Double_t sum2;
  //The number of fake photon events.
  Double_t sum3;
  
  Double_t ratio;

  //Check fake photon.
  Int_t MARK;

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //=*********************************************
    //Remove *
    //=*********************************************
    //MC Truth.
    gm1.SetPxPyPzE(p_g1_mctruth->Px(),p_g1_mctruth->Py(),p_g1_mctruth->Pz(),p_g1_mctruth->E());
    gm2.SetPxPyPzE(p_g2_mctruth->Px(),p_g2_mctruth->Py(),p_g2_mctruth->Pz(),p_g2_mctruth->E());
    gm3.SetPxPyPzE(p_g3_mctruth->Px(),p_g3_mctruth->Py(),p_g3_mctruth->Pz(),p_g3_mctruth->E());
    pp.SetPxPyPzE(p_pip_mctruth->Px(),p_pip_mctruth->Py(),p_pip_mctruth->Pz(),p_pip_mctruth->E());
    pm.SetPxPyPzE(p_pim_mctruth->Px(),p_pim_mctruth->Py(),p_pim_mctruth->Pz(),p_pim_mctruth->E());

    //After detector.
    g1.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
    g2.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
    g3.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
    pip_u.SetPxPyPzE(pip_unfitted->Px(),pip_unfitted->Py(),pip_unfitted->Pz(),pip_unfitted->E());
    pim_u.SetPxPyPzE(pim_unfitted->Px(),pim_unfitted->Py(),pim_unfitted->Pz(),pim_unfitted->E());
    kp_u.SetPxPyPzE(kp_unfitted->Px(),kp_unfitted->Py(),kp_unfitted->Pz(),kp_unfitted->E());
    km_u.SetPxPyPzE(km_unfitted->Px(),km_unfitted->Py(),km_unfitted->Pz(),km_unfitted->E());

    //=*************************************************
    //Use MC Truth to get the right photon combination.
    //g2_af + g3_af = eta, g1_af + pip_u + pim_u = etap
    //=*************************************************
    //1st photon.
    //=******************************
    MARK=0;
    ang11=gm1.Angle(g1.Vect())*180/pi;
    if (ang11<angle_cut) {
      g1_af=g1;
    }
    else {
      ang12=gm1.Angle(g2.Vect())*180/pi;
      if (ang12<angle_cut) {
        g1_af=g2;
      }
      else {
        ang13=gm1.Angle(g3.Vect())*180/pi;
        if (ang13>angle_cut) {
          MARK=1;
        }
        g1_af=g3;
      }
    }//end with 1st photon.

    //2nd photon.
    //=******************************
    ang21=gm2.Angle(g1.Vect())*180/pi;
    if (ang21<angle_cut) {
      g2_af=g1;
    }
    else {
      ang22=gm2.Angle(g2.Vect())*180/pi;
      if (ang22<angle_cut) {
        g2_af=g2;
      }
      else {
        ang23=gm2.Angle(g3.Vect())*180/pi;
        if (ang23>angle_cut) {
          MARK=1;
        }
        g2_af=g3;
      }
    }//end with 2nd photon

    //3rd photon.
    //=*******************************
    ang31=gm3.Angle(g1.Vect())*180/pi;
    if (ang31<angle_cut) {
      g3_af=g1;
    }
    else {
      ang32=gm3.Angle(g2.Vect())*180/pi;
      if (ang32<angle_cut) {
        g3_af=g2;
      }
      else {
        ang33=gm3.Angle(g3.Vect())*180/pi;
        if (ang33>angle_cut)  {
          MARK=1;
        }
        g3_af=g3;
      }
    }//end with 3rd photon

    //Get the delta2 of 100% right combination.
   /* m_2gam_th=(g2_af+g3_af).M();
    m_gam_rho_th=(g1_af+pip_u+pim_u).M();
    deltasq_th=(m_2gam_th-m_eta)*(m_2gam_th-m_eta)/(w_eta*w_eta)+(m_gam_rho_th-m_etap)*(m_gam_rho_th-m_etap)/(w_etap*w_etap);*/

    if (itopo != 0) continue;
    m_phi_etap_th=(kp_u+km_u+g1_af+pip_u+pim_u).M();
    h13->Fill(m_phi_etap_th);

    //=*****************************************************
    //use delta2 method to get the right photon combination.
    //=*****************************************************
   /* mark1=0;
    deltasq_low=100000000;
//=**1**
//1+23
    p_gam_rho= *gamma1_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam= *gamma2_unfitted+ *gamma3_unfitted;

    m_gam_rho=p_gam_rho.M();
    m_2gam=p_2gam.M();
    //veto pi0
   // if ((m_2gam>0.103)&&(m_2gam<0.148)) continue;

    deltasq=(m_2gam-m_eta)*(m_2gam-m_eta)/(w_eta*w_eta)+(m_gam_rho-m_etap)*(m_gam_rho-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=1;
    }

//=**2**
//2+13
    p_gam_rho= *gamma2_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam= *gamma1_unfitted+ *gamma3_unfitted;

    m_gam_rho=p_gam_rho.M();
    m_2gam=p_2gam.M();
    //veto pi0
   // if ((m_2gam>0.103)&&(m_2gam<0.148)) continue;

    deltasq=(m_2gam-m_eta)*(m_2gam-m_eta)/(w_eta*w_eta)+(m_gam_rho-m_etap)*(m_gam_rho-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=2;
    }

//=**3**
//3+12
    p_gam_rho= *gamma3_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam= *gamma1_unfitted+ *gamma2_unfitted;

    m_gam_rho=p_gam_rho.M();
    m_2gam=p_2gam.M();
    //veto pi0
   // if ((m_2gam>0.103)&&(m_2gam<0.148)) continue;

    deltasq=(m_2gam-m_eta)*(m_2gam-m_eta)/(w_eta*w_eta)+(m_gam_rho-m_etap)*(m_gam_rho-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=3;
    }

//=***********************************
//gamma1_f          : gamma from eta';
//gamma2_f&gamma3_f : gamma from eta;
//=***********************************

    switch (mark1)
    {
      case 1:
      gamma1_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma3_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      break;

      case 2:
      gamma2_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma1_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma3_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      break;

      case 3:
      gamma3_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma1_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      break;

    }//end with switch.
      //eta
    m_2gam=(gamma2_f+gamma3_f).M();
      //etap
    m_gam_rho=(gamma1_f+pip_u+pim_u).M();
      //phi
    m_2k=(kp_u+km_u).M();
      //rho0
    m_2pi=(pip_u+pim_u).M();
      //Y(2175)
    m_phi_etap=(kp_u+km_u+gamma1_f+pip_u+pim_u).M();

    //All cuts.
    //=***************************
    if (Chisq_low>40) continue;

    if (m_2gam<0.487) continue;
    if (m_2gam>0.576) continue;

    if (m_2pi>0.87) continue;

    if (m_2k<1.013) continue;
    if (m_2k>1.027) continue;

    if (m_gam_rho<0.939) continue;
    if (m_gam_rho>0.972) continue;
    //=****************************

  //Check fake photon
    if (MARK==1) {
      sum3=sum3+1;
      h11->Fill(m_phi_etap);
    }

    h1->Fill((gm2+gm3).M());
    h2->Fill((g2_af+g3_af).M());
    h3->Fill((gamma2_f+gamma3_f).M());

    h4->Fill((gm1+pp+pm).M());
    h5->Fill((g1_af+pip_u+pim_u).M());
    h6->Fill((gamma1_f+pip_u+pim_u).M());

    h7->Fill(m_2gam);
    h8->Fill(m_2pi);
    h9->Fill(m_2k);
    h10->Fill(m_gam_rho);

    //The number of all events left.
    sum1=sum1+1;
    //Counting the numbers of mis-combination.
    if (deltasq_th != deltasq_low) {
      sum2=sum2+1;
      h12->Fill(m_phi_etap);
    }*/
  //=********************
  }//end with all events.
  //=********************

  //=**************************
  TCanvas *c1=new TCanvas();
  h13->Draw("pe");

  //Get the ratio.
 /* Double_t ratio_fake;
  ratio_fake=sum3/sum1;
  ratio=sum2/sum1;
  cout<<"ratio_fake="<<sum3<<"/"<<sum1<<"="<<ratio_fake<<endl;
  cout<<"ratio_mis="<<sum2<<"/"<<sum1<<"="<<ratio<<endl;

  //Draw the graph.
  TCanvas *c1=new TCanvas();
  c1->Divide(3,2);
  Double_t x_value=0.7;
  Double_t y_value=0.85;

  c1->cd(1);
  h1->Draw();
  box(0.25,y_value,h1);
  c1->cd(2);
  h2->Draw();
  box(0.25,y_value,h2);
  c1->cd(3);
  h3->Draw();
  box(0.25,y_value,h3);
  c1->cd(4);
  h4->Draw();
  box(0.25,y_value,h4);
  c1->cd(5);
  h5->Draw();
  box(0.25,y_value,h5);
  c1->cd(6);
  h6->Draw();
  box(0.25,y_value,h6);

  TCanvas *c2=new TCanvas();
  c2->Divide(2,2);

  c2->cd(1);
  h7->Draw();
  box(x_value,y_value,h7);
  c2->cd(2);
  h8->Draw();
  box(x_value,y_value,h8);
  c2->cd(3);
  h9->Draw();
  box(x_value,y_value,h9);
  c2->cd(4);
  h10->Draw();
  box(x_value,y_value,h10);

  TCanvas *c3=new TCanvas();
  c3->Divide(1,1);

  c3->cd(1);
  h11->Draw("pe");
  box(0.25,y_value,h11);

  TCanvas *c4=new TCanvas();
  c4->Divide(1,1);

  c4->cd(1);
  h12->Draw("pe");
  box(0.25,y_value,h12);*/

//=******************
}//final end  
//=******************
