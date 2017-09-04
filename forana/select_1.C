//G4Pi2K2
//Just final state 1.
//Jpsi -> eta Y(2175)
//  Y(2175) -> phi etap
//    etap -> pi pi eta  phi -> 2K
//      eta -> 2 gamma
//1st stage, get the right photon combination.
void select_1(){

//Name of the tree in 1st file.
  TChain *chain = new TChain("TreeAna");
//Name of the file.
  chain->Add("mceagle.root");
//Name of the right-combined file.
  TFile *ofile=new TFile("rightcomb_mceagle.root","RECREATE");

  const Double_t m_eta=0.5479;

  //Flag, to choose final state 1.
 // Int_t flag;

  //To get right photon combination.
  Double_t deltasq;
  Double_t deltasq_low;
  Int_t mark1;

  //Chi2
  Double_t Chisq_low;

  //4-momentum of photons, from root file
  TLorentzVector *gamma1_unfitted;
  TLorentzVector *gamma2_unfitted;
  TLorentzVector *gamma3_unfitted;
  TLorentzVector *gamma4_unfitted;

  //2 pi
  TLorentzVector *pip_unfitted;
  TLorentzVector *pim_unfitted;

  //2 K
  TLorentzVector *kp_unfitted;
  TLorentzVector *km_unfitted;

  //After right combination:
  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  gamma3_f = new TLorentzVector();
  gamma4_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  //2 gamma
  TLorentzVector p_2gam_1, p_2gam_2;
  Double_t m_2gam_1, m_2gam_2;

  //Read the variables.
  //4-momentum of photons.
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

  //Chi2.
  chain->SetBranchAddress("Chisq_low",&Chisq_low);

  //Store the variables.
  TTree *tree=new TTree("tree","the right photon combination.");

  tree->Branch("gamma1_f",&gamma1_f,32000,0);
  tree->Branch("gamma2_f",&gamma2_f,32000,0);
  tree->Branch("gamma3_f",&gamma3_f,32000,0);
  tree->Branch("gamma4_f",&gamma4_f,32000,0);
  tree->Branch("pip_f",&pip_f,32000,0);
  tree->Branch("pim_f",&pim_f,32000,0);
  tree->Branch("kp_f",&kp_f,32000,0);
  tree->Branch("km_f",&km_f,32000,0);

  //MC Truth.
  Int_t indexmc;
  Int_t pdgid[500];
  Int_t motheridx[500];

  chain->SetBranchAddress("indexmc",&indexmc);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("motheridx",motheridx);

  tree->Branch("indexmc",&indexmc,"indexmc/I");
  tree->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
  tree->Branch("motheridx",motheridx,"motheridx[indexmc]/I");

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    //Cut on Chisq_4C
    if (Chisq_low>40) continue;

//Get the right photon combination;
//*****************************************************************************
    mark1=0;
    deltasq_low=100000000;

//**1**
//1 2 + 3 4
    p_2gam_1= *gamma1_unfitted+ *gamma2_unfitted;
    m_2gam_1=p_2gam_1.M();

    p_2gam_2= *gamma3_unfitted+ *gamma4_unfitted;
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    //if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    //if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    deltasq=(m_2gam_1-m_eta)*(m_2gam_1-m_eta)+(m_2gam_2-m_eta)*(m_2gam_2-m_eta);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=1;
    }

//**2**
//1 3 + 2 4
    p_2gam_1= *gamma1_unfitted+ *gamma3_unfitted;
    m_2gam_1=p_2gam_1.M();

    p_2gam_2= *gamma2_unfitted+ *gamma4_unfitted;
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    //if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    //if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    deltasq=(m_2gam_1-m_eta)*(m_2gam_1-m_eta)+(m_2gam_2-m_eta)*(m_2gam_2-m_eta);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=2;
    }

//**3**
//1 4 + 2 3
    p_2gam_1= *gamma1_unfitted+ *gamma4_unfitted;
    m_2gam_1=p_2gam_1.M();

    p_2gam_2= *gamma3_unfitted+ *gamma2_unfitted;
    m_2gam_2=p_2gam_2.M();

    //veto pi0
    //if ((m_2gam_1>0.103)&&(m_2gam_1<0.148)) continue;
    //if ((m_2gam_2>0.103)&&(m_2gam_2<0.148)) continue;

    deltasq=(m_2gam_1-m_eta)*(m_2gam_1-m_eta)+(m_2gam_2-m_eta)*(m_2gam_2-m_eta);

    if (deltasq_low>deltasq) {
        deltasq_low=deltasq;
        mark1=3;
    }

//=***********************
//gamma1_f&gamma2_f : gamma from eta;
//gamma3_f&gamma4_f : gamma from eta;
//=***********************

    switch (mark1)
    {
      case 1:
      gamma1_f->SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma2_f->SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma3_f->SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma4_f->SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 2:
      gamma1_f->SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma3_f->SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma2_f->SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma4_f->SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;

      case 3:
      gamma1_f->SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma4_f->SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());
      gamma3_f->SetPxPyPzE(gamma3_unfitted->Px(),gamma3_unfitted->Py(),gamma3_unfitted->Pz(),gamma3_unfitted->E());
      gamma2_f->SetPxPyPzE(gamma4_unfitted->Px(),gamma4_unfitted->Py(),gamma4_unfitted->Pz(),gamma4_unfitted->E());
      break;
    }

    pip_f->SetPxPyPzE(pip_unfitted->Px(),pip_unfitted->Py(),pip_unfitted->Pz(),pip_unfitted->E());
    pim_f->SetPxPyPzE(pim_unfitted->Px(),pim_unfitted->Py(),pim_unfitted->Pz(),pim_unfitted->E());
    kp_f->SetPxPyPzE(kp_unfitted->Px(),kp_unfitted->Py(),kp_unfitted->Pz(),kp_unfitted->E());
    km_f->SetPxPyPzE(km_unfitted->Px(),km_unfitted->Py(),km_unfitted->Pz(),km_unfitted->E());

    tree->Fill();

  }//end with for

  tree->Write();
  ofile->Close();

}//final end
                             
