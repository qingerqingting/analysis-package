#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include "Event.h"
#include <TMVA/Reader.h>

using namespace std;

int main() {

  TFile* histFile = new TFile("analysis.root", "RECREATE");
  TH1D* hFishCata = new TH1D("hFishCata", "Fisher, category a", 100, -10.0, 10.0);
  TH1D* hFishCatb = new TH1D("hFishCatb", "Fisher, category b", 100, -10.0, 10.0);

  TMVA::Reader* reader = new TMVA::Reader();
  float x, y;                       // TMVA needs float, not double
  reader->AddVariable("x", &x);
  reader->AddVariable("y", &y);
  
  string dir    = "../train/weights/";
  string prefix = "tmvaTest";
  string weightFile = dir + prefix + "_Fisher.weights.xml";
  reader->BookMVA("Fisher", weightFile.c_str());

  TFile* inputFile = new TFile("../generate/testData.root");
  inputFile->ls();
  TTree* cata = dynamic_cast<TTree*>(inputFile->Get("cata"));
  TTree* catb = dynamic_cast<TTree*>(inputFile->Get("catb"));
  vector<TTree*> treeVec;
  treeVec.push_back(cata);
  treeVec.push_back(catb);

  int nCataAccFish = 0;
  int nCatbAccFish = 0;
  int nCata, nCatb;
  const double tCutFisher = 0.0;
  for (int i=0; i<treeVec.size(); i++){
    treeVec[i]->Print();
    Event evt;
    treeVec[i]->SetBranchAddress("evt", &evt);
    int numEntries = treeVec[i]->GetEntries();
    if ( i == 0 ) { nCata = numEntries; }
    if ( i == 1 ) { nCatb = numEntries; }
    cout << "number of entries = " << numEntries << endl;

  for (int j=0; j<numEntries; j++){
      treeVec[i]->GetEntry(j);                // sets evt
      x = evt.x;                              // set variables of reader
      y = evt.y;
  double tFisher = reader->EvaluateMVA("Fisher");
      if ( i == 0 ){                       // signal
        hFishCata->Fill(tFisher);
        if ( tFisher >= tCutFisher ) { nCataAccFish++; }
      }
      else if ( i == 1 ){                  // background
        hFishCatb->Fill(tFisher);
        if ( tFisher >= tCutFisher ) { nCatbAccFish++; }
      }

    }

  }

  double epsCataFish = static_cast<double>(nCataAccFish)/
                      static_cast<double>(nCata);
  double epsCatbFish = static_cast<double>(nCatbAccFish)/
                      static_cast<double>(nCatb);

  cout << "Fisher category a efficiency     = " << epsCataFish << endl;
  cout << "Fisher category b efficiency = " << epsCatbFish << endl;

  double lumi = 20.;         // fb-1
  double sigma_s = 0.2;       // fb
  double sigma_b = 10.;      // fb

  double s = epsCataFish * sigma_s * lumi;
  double b = epsCatbFish * sigma_b * lumi;
  double Z = sqrt( 2. * ( (s + b) * log(1. + s/b) - s) );
  cout << "s = " << s << endl;
  cout << "b = " << b << endl;
  cout << "Z = " << Z << endl;

  histFile->Write();
  histFile->Close();
  return 0;

}
