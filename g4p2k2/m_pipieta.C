void m_pipieta(){
  //Jpsi->eta Y(2175),Y(2175)->phi etap,
  //eta->2gamma, etap->pi pi eta, phi->2K
  //=*****************************************************
  //Get the spectrum of etap. using MCTruth match method.
  //Prepare for the mass windows on etap.
  //=*****************************************************

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
  chain->Add("sigmc_g4pi2k2_0912.root");
  TFile *ofile=new TFile("m_pipieta.root","RECREATE");

  //Histograms.
    //Eta1.
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

    //Eta2.
    //MC Truth
  TH1F *h4=new TH1F("h4","m_{2#gamma}",70,0.4,0.65);
  h4->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h4);
    //After detection: MC Truth
  TH1F *h5=new TH1F("h5","m_{2#gamma}",70,0.4,0.65);
  h5->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h5);
    //After detection: delta2    
  TH1F *h6=new TH1F("h6","m_{2#gamma}",70,0.4,0.65);
  h6->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h6);

    //Etap.
    //MC Truth
  TH1F *h7=new TH1F("h7","m_{#pi+#pi+#eta}",50,0.85,1.05);
  h7->GetXaxis()->SetTitle("m_{#pi+#pi+#eta} [GeV]");
  setymass(h7);
    //After detection: MC Truth
  TH1F *h8=new TH1F("h8","m_{#pi+#pi+#eta}",50,0.85,1.05);
  h8->GetXaxis()->SetTitle("m_{#pi+#pi+#eta} [GeV]");
  setymass(h8);
    //After detection: delta2
  TH1F *h9=new TH1F("h9","m_{#pi+#pi+#eta}",50,0.85,1.05);
  h9->GetXaxis()->SetTitle("m_{#pi+#pi+#eta} [GeV]");
  setymass(h9);
 
    //Phi etap
    //Fake photon
  TH1F *h10=new TH1F ("h10","The mass spectrum of phi&etap",35,1.9,2.6);
  h10->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h10);
    //Fake photon + mis-combination
  TH1F *h11=new TH1F ("h11","The mass spectrum of phi&etap",35,1.9,2.6);
  h11->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h11);

  //Particles in truth level.
  TLorentzVector *p_g1_mctruth;
  TLorentzVector *p_g2_mctruth;
  TLorentzVector *p_g3_mctruth;
  TLorentzVector *p_g4_mctruth;
  TLorentzVector *p_pip_mctruth;
  TLorentzVector *p_pim_mctruth;
    //MC Truth
  TLorentzVector gm1;
  TLorentzVector gm2;
  TLorentzVector gm3;
  TLorentzVector gm4;
  TLorentzVector pp;
  TLorentzVector pm;

  //4-momentum of photons after detection.
  TLorentzVector *gamma1_unfitted;
  TLorentzVector *gamma2_unfitted;
  TLorentzVector *gamma3_unfitted;
  TLorentzVector *gamma4_unfitted;
    //After detector, remove "*".
  TLorentzVector g1;
  TLorentzVector g2;
  TLorentzVector g3;
  TLorentzVector g4;
    //After detector, use MC Truth.
  TLorentzVector g1_af;
  TLorentzVector g2_af;
  TLorentzVector g3_af;
  TLorentzVector g4_af;
    //After detector, use delta2.
  TLorentzVector gamma1_f;
  TLorentzVector gamma2_f;
  TLorentzVector gamma3_f;
  TLorentzVector gamma4_f;

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
  //Read Chisq.
  chain->SetBranchAddress("Chisq_low",&Chisq_low);
  //Read the P of particles.
  //MC Truth
  chain->SetBranchAddress("p_g1_mctruth",&p_g1_mctruth);
  chain->SetBranchAddress("p_g2_mctruth",&p_g2_mctruth);
  chain->SetBranchAddress("p_g3_mctruth",&p_g3_mctruth);
  chain->SetBranchAddress("p_g4_mctruth",&p_g4_mctruth);
  chain->SetBranchAddress("p_pip_mctruth",&p_pip_mctruth);
  chain->SetBranchAddress("p_pim_mctruth",&p_pim_mctruth);

  //The P of particles after detection.
  //Photons.
  chain->SetBranchAddress("gamma1_unfitted",&gamma1_unfitted);
  chain->SetBranchAddress("gamma2_unfitted",&gamma2_unfitted);
  chain->SetBranchAddress("gamma3_unfitted",&gamma3_unfitted);
  chain->SetBranchAddress("gamma4_unfitted",&gamma4_unfitted);
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
  Double_t ang14;
  Double_t ang21;
  Double_t ang22;
  Double_t ang23;
  Double_t ang24;
  Double_t ang31;
  Double_t ang32;
  Double_t ang33;
  Double_t ang34;
  Double_t ang41;
  Double_t ang42;
  Double_t ang43;
  Double_t ang44;

  //Cut on angle.
  const Double_t angle_cut=5;

  const Double_t pi=3.1415926;

  //Prepare for MC Truth method.
  //=*******************************************
  //After detection, using MC Truth,100% correct.
  Double_t m_2gam_1_th;
  Double_t m_2gam_2_th;
  Double_t m_pipieta_th;
  Double_t m_phi_etap_th;
  Double_t deltasq_th;

  //Prepare for delta2 method.
  //=*******************************
  Double_t deltasq;
  Double_t deltasq_low;

  Int_t mark1;
  //Mass of particles.
    //eta
  Double_t m_2gam_1;
  Double_t m_2gam_2;
    //phi
  Double_t m_2k;
    //rho0
  Double_t m_2pi;
    //eta'
  Double_t m_pipieta;
  Double_t m_pipieta_1;
  Double_t m_pipieta_2;
    //Y(2175)
  Double_t m_phi_etap;
  Double_t m_phi_etap_1;
  Double_t m_phi_etap_2;

  Double_t m_phi_eta;

  Double_t m_eta_etap;

  //P of particles;
    //eta
  TLorentzVector p_2gam_1;
  TLorentzVector p_2gam_2;
    //phi
  TLorentzVector p_2k;
    //rho0
  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_gam_rho;
  TLorentzVector p_gam_rho_1;
  TLorentzVector p_gam_rho_2;
    //Y(2175)
  TLorentzVector p_phi_etap;
  TLorentzVector p_phi_etap_1;
  TLorentzVector p_phi_etap_2;

  TLorentzVector p_phi_eta;

  TLorentzVector p_eta_etap;

  const Double_t m_eta=0.5479;
  const Double_t m_etap=0.9578;

  const Double_t w_eta=1;
  const Double_t w_etap=1;

  //end of prepare for delta2 method.
  //=*********************************

  //Calculate the number of mis-combination.
  //The number of all events.
  Double_t sum1;
  //The number of mis-combination.
  Double_t sum2;
  //The number of fake photon events.
  Double_t sum3;

  //Check fake photon.
  Int_t MARK;

  //Store tree.
  TTree *TreeRes=new TTree("TreeRes","mc truth");
  TreeRes->Branch("m_pipieta_th",&m_pipieta_th,"m_pipieta_th/D");
  TreeRes->Branch("m_phi_etap_th",&m_phi_etap_th,"m_phi_etap_th/D");

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
    gm4.SetPxPyPzE(p_g4_mctruth->Px(),p_g4_mctruth->Py(),p_g4_mctruth->Pz(),p_g4_mctruth->E());
    pp.SetPxPyPzE(p_pip_mctruth->Px(),p_pip_mctruth->Py(),p_pip_mctruth->Pz(),p_pip_mctruth->E());
    pm.SetPxPyPzE(p_pim_mctruth->Px(),p_pim_mctruth->Py(),p_pim_mctruth->Pz(),p_pim_mctruth->E());

    //After detector.
    g1.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
    g2.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
    g3.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
    g4.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
    pip_u.SetPxPyPzE(pip_unfitted->Px(),pip_unfitted->Py(),pip_unfitted->Pz(),pip_unfitted->E());
    pim_u.SetPxPyPzE(pim_unfitted->Px(),pim_unfitted->Py(),pim_unfitted->Pz(),pim_unfitted->E());
    kp_u.SetPxPyPzE(kp_unfitted->Px(),kp_unfitted->Py(),kp_unfitted->Pz(),kp_unfitted->E());
    km_u.SetPxPyPzE(km_unfitted->Px(),km_unfitted->Py(),km_unfitted->Pz(),km_unfitted->E());

    //=*************************************************
    //Use MC Truth to get the right photon combination.
    //g1_af + g2_af = eta(etap), g3_af + g4_af = eta(Jpsi)
    //=*************************************************
    MARK=0;
    //1st photon.
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
          if (ang13<angle_cut) {
            g1_af=g3;
          }
          else {
            ang14=gm1.Angle(g4.Vect())*180/pi;
            if (ang14>angle_cut) {
              MARK=1;
            }
            g1_af=g4;
          }
        }
      }//end with the 1st photon

    //2nd photon.
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
          if (ang23<angle_cut) {
            g2_af=g3;
          }
          else {
            ang24=gm2.Angle(g4.Vect())*180/pi;
            if (ang24>angle_cut) {
              MARK=1;
            }
            g2_af=g4;
          }
        }
      }//end with the 2nd photon

    //3rd photon.
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
          if (ang33<angle_cut) {
            g3_af=g3;
          }
          else {
            ang34=gm3.Angle(g4.Vect())*180/pi;
            if (ang34>angle_cut) {
              MARK=1;
            }
            g3_af=g4;
          }
        }
      }//end with the 3rd photon

    //4th photon.
    ang41=gm4.Angle(g1.Vect())*180/pi;
    if (ang41<angle_cut) {
      g4_af=g1;
    }
    else {
      ang42=gm4.Angle(g2.Vect())*180/pi;
      if (ang42<angle_cut) {
        g4_af=g2;
      }
      else {
          ang43=gm4.Angle(g3.Vect())*180/pi;
          if (ang43<angle_cut) {
            g4_af=g3;
          }
          else {
            g4_af=g4;
            ang44=gm4.Angle(g4.Vect())*180/pi;
            if (ang44>angle_cut) {
              MARK=1;
            }
          }
        }
      }//end with the 4th photon

    //=*************************************
    //g1_af+g2_af=eta(etap)
    //g3_af+g4_af=eta(Jpsi)
    //=*************************************

    //Get the delta2 of 100% right combination.
    m_2gam_1_th=(g1_af+g2_af).M();
    m_2gam_2_th=(g3_af+g4_af).M();
    m_pipieta_th=(g1_af+g2_af+pip_u+pim_u).M();
    m_phi_etap_th=(g1_af+g2_af+pip_u+pim_u+kp_u+km_u).M();
    deltasq_th=(m_2gam_2_th-m_eta)*(m_2gam_2_th-m_eta)/(w_eta*w_eta)+(m_pipieta_th-m_etap)*(m_pipieta_th-m_etap)/(w_etap*w_etap);

    //Cut on chisq.
    if (Chisq_low>80) continue;
   // if (MARK==1) continue;

    //Store the tree.
    TreeRes->Fill();

    //=*****************************************************
    //use delta2 method to get the right photon combination.
    //=*****************************************************
   /* mark1=0;
    deltasq_low=100000000;

    //=**1**
    //12+34
    p_pipieta= *gamma1_unfitted+ *gamma2_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma1_unfitted+ *gamma2_unfitted;

    p_2gam_2= *gamma3_unfitted+ *gamma4_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g1+g2+pip_u+pim_u).M()>0.90)&&((g1+g2+pip_u+pim_u).M()<0.98)&&((g3+g4+pip_u+pim_u).M()>0.90)&&((g3+g4+pip_u+pim_u).M()<0.98)) continue;

    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=1;
    }

    //=**2**
    //13+24
    p_pipieta= *gamma1_unfitted+ *gamma3_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma1_unfitted+ *gamma3_unfitted;

    p_2gam_2= *gamma2_unfitted+ *gamma4_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g1+g3+pip_u+pim_u).M()>0.90)&&((g1+g3+pip_u+pim_u).M()<0.98)&&((g2+g4+pip_u+pim_u).M()>0.90)&&((g2+g4+pip_u+pim_u).M()<0.98)) continue;
    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=2;
    }

    //=**3**
    //14+23
    p_pipieta= *gamma1_unfitted+ *gamma4_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma1_unfitted+ *gamma4_unfitted;

    p_2gam_2= *gamma2_unfitted+ *gamma3_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g1+g4+pip_u+pim_u).M()>0.90)&&((g1+g4+pip_u+pim_u).M()<0.98)&&((g2+g3+pip_u+pim_u).M()>0.90)&&((g2+g3+pip_u+pim_u).M()<0.98)) continue;
    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=3;
    }

    //=**4**
    //23+14
    p_pipieta= *gamma2_unfitted+ *gamma3_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma2_unfitted+ *gamma3_unfitted;

    p_2gam_2= *gamma1_unfitted+ *gamma4_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g2+g3+pip_u+pim_u).M()>0.90)&&((g2+g3+pip_u+pim_u).M()<0.98)&&((g1+g4+pip_u+pim_u).M()>0.90)&&((g1+g4+pip_u+pim_u).M()<0.98)) continue;
    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=4;
    }

    //=**5**
    //24+13
    p_pipieta= *gamma2_unfitted+ *gamma4_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma2_unfitted+ *gamma4_unfitted;

    p_2gam_2= *gamma1_unfitted+ *gamma3_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g2+g4+pip_u+pim_u).M()>0.90)&&((g2+g4+pip_u+pim_u).M()<0.98)&&((g1+g3+pip_u+pim_u).M()>0.90)&&((g1+g3+pip_u+pim_u).M()<0.98)) continue;
    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=5;
    }

    //=**6**
    //34+12
    p_pipieta= *gamma3_unfitted+ *gamma4_unfitted+ *pip_unfitted+ *pim_unfitted;
    p_2gam_1= *gamma3_unfitted+ *gamma4_unfitted;

    p_2gam_2= *gamma1_unfitted+ *gamma2_unfitted;

    m_pipieta=p_pipieta.M();
    m_2gam_1=p_2gam_1.M();
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    if (((g3+g4+pip_u+pim_u).M()>0.90)&&((g3+g4+pip_u+pim_u).M()<0.98)&&((g1+g2+pip_u+pim_u).M()>0.90)&&((g1+g2+pip_u+pim_u).M()<0.98)) continue;
    deltasq=(m_2gam_2-m_eta)*(m_2gam_2-m_eta)/(w_eta*w_eta)+(m_pipieta-m_etap)*(m_pipieta-m_etap)/(w_etap*w_etap);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=6;
    }

    switch (mark1)
    {
      case 1:
      gamma1_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma3_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 2:
      gamma1_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma3_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 3:
      gamma1_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma3_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 4:
      gamma3_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma1_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 5:
      gamma3_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma1_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 6:
      gamma3_f.SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma4_f.SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma1_f.SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma2_f.SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

    }//end with switch.  

      //eta
    m_2gam_1=(gamma1_f+gamma2_f).M();
    m_2gam_2=(gamma3_f+gamma4_f).M();

      //etap
    m_pipieta=(gamma1_f+gamma2_f+pip_u+pim_u).M();

      //phi
    m_2k=(kp_u+km_u).M();

      //Y(2175)
    m_phi_etap=(kp_u+km_u+gamma1_f+gamma2_f+pip_u+pim_u).M();

    //All cuts.
    //=***************************
    if (Chisq_low>40) continue;

    if (m_2gam_1<0.487) continue;
    if (m_2gam_1>0.576) continue;

    if (m_2gam_2<0.487) continue;
    if (m_2gam_2>0.576) continue;

    if (m_2k<1.013) continue;
    if (m_2k>1.027) continue;

    if (m_pipieta<0.9) continue;
    if (m_pipieta>1.0) continue;
    //=***************************

    h1->Fill((gm1+gm2).M());
    h2->Fill((g1_af+g2_af).M());
    h3->Fill((gamma1_f+gamma2_f).M());

    h4->Fill((gm3+gm4).M());
    h5->Fill((g3_af+g4_af).M());
    h6->Fill((gamma3_f+gamma4_f).M());

    h7->Fill((gm1+gm2+pp+pm).M());
    h8->Fill((g1_af+g2_af+pip_u+pim_u).M());
    h9->Fill((gamma1_f+gamma2_f+pip_u+pim_u).M());

    //The number of all events left.
    sum1=sum1+1;

  //Check fake photon
    if (MARK==1) {
      sum3=sum3+1;
      h10->Fill(m_phi_etap);
      continue;
    }

    //Counting the numbers of mis-combination.
    if (deltasq_th != deltasq_low) {
      sum2=sum2+1;
      h11->Fill(m_phi_etap);
    }*/

  }//end with all events

  //Get the ratio.
 /* Double_t ratio_fake;
  Double_t ratio_mis;
  ratio_fake=sum3/sum1;
  ratio_mis=sum2/sum1;
  cout<<"ratio_fake="<<sum3<<"/"<<sum1<<"="<<ratio_fake<<endl;
  cout<<"ratio_mis="<<sum2<<"/"<<sum1<<"="<<ratio_mis<<endl;

  //Draw the graph.
  TCanvas *c1=new TCanvas();
  c1->Divide(3,3);

  c1->cd(1);
  h1->Draw("pe");

  c1->cd(2);
  h2->Draw("pe");

  c1->cd(3);
  h3->Draw("pe");

  c1->cd(4);
  h4->Draw("pe");

  c1->cd(5);
  h5->Draw("pe");

  c1->cd(6);
  h6->Draw("pe");

  c1->cd(7);
  h7->Draw("pe");

  c1->cd(8);
  h8->Draw("pe");

  c1->cd(9);
  h9->Draw("pe");

  TCanvas *c2=new TCanvas();
  c2->Divide(1,2);

  c2->cd(1);
  h10->Draw("pe");

  c2->cd(2);
  h11->Draw("pe");*/

  //Store the tree.
  TreeRes->Write();
  ofile->Close();

}
