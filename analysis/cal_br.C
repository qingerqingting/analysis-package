void cal_br(){
//Calculate the branching ratio of Jpsi->eta Y(2175),Y(2175)->phi etap.

  Double_t n_obs=225;
  Double_t n_obs_u=32;

  const Double_t br_eta_2gam=0.3941;
  const Double_t br_eta_2gam_u=0.0020;
  
  const Double_t br_etap_gampipi=0.291;
  const Double_t br_etap_gampipi_u=0.005;

  const Double_t br_phi_2k=0.489;
  const Double_t br_phi_2k_u=0.005;

  Double_t n_jpsi=1.3106*1000000000;
  Double_t n_jpsi_u=10.5*1000000;

  //Efficiency
  Double_t n_left=10182;
  Double_t n_tot=200000;
  Double_t eff=n_left/n_tot;

  Double_t br;
  br=n_obs/(n_jpsi*eff*br_eta_2gam*br_etap_gampipi*br_phi_2k);

  //Uncertainty
  Double_t br_u;
  Double_t u1sq=(n_jpsi_u/n_jpsi)*(n_jpsi_u/n_jpsi);
  Double_t u2sq=(br_eta_2gam_u/br_eta_2gam)*(br_eta_2gam_u/br_eta_2gam);
  Double_t u3sq=(br_phi_2k_u/br_phi_2k)*(br_phi_2k_u/br_phi_2k);
  Double_t u4sq=(br_etap_gampipi_u/br_etap_gampipi)*(br_etap_gampipi_u/br_etap_gampipi);
    //Uncertainty on efficiency.
  Double_t u5=TMath::Sqrt(eff*(1-eff)/n_tot)/eff;
  Double_t u5sq=u5*u5;
  Double_t br_u=TMath::Sqrt(u1sq+u2sq+u3sq+u4sq+u5sq)*br;
  cout<<"Br="<<br<<"+-"<<br_u<<endl;

  //=**************************
  //calculate the ratio of Br(Y->phi etap) and Br(Y->phi f0(980)).
  //=**************************
  Double_t br_pf=1.2/10000;
  Double_t br_pf_u=0.51/10000;
  Double_t ratio=br/(br_pf*1.5);
  Double_t ratio_u=TMath::Sqrt((br_pf_u/br_pf)*(br_pf_u/br_pf)+(br_u/br)*(br_u/br))*ratio;
  
  cout<<"ratio="<<ratio<<"+-"<<ratio_u<<endl;
}
