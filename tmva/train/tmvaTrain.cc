#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TFile.h>
#include <TString.h>
#include <TMVA/Factory.h>

int main(){
  
  TFile* outputFile = TFile::Open( "TMVA.root", "RECREATE" );
  TMVA::Factory* factory = new TMVA::Factory("tmvaTest", outputFile, "");
  TFile* trainingFile = new TFile("../generate/trainingData.root");
  TFile* testFile = new TFile("../generate/testData.root");

  TTree* cataTrain = (TTree*)trainingFile->Get("cata");
  TTree* catbTrain = (TTree*)trainingFile->Get("catb");
  int nCataTrain = cataTrain->GetEntries();
  int nCatbTrain = catbTrain->GetEntries();

  TTree* cataTest = (TTree*)testFile->Get("cata");
  TTree* catbTest = (TTree*)testFile->Get("catb");
  int nCataTest = cataTest->GetEntries();
  int nCatbTest = catbTest->GetEntries();

  double cataWeight = 1.0;
  double catbWeight = 1.0;
  factory->AddSignalTree(cataTrain, cataWeight, TMVA::Types::kTraining);
  factory->AddBackgroundTree(catbTrain, catbWeight, TMVA::Types::kTraining);
  factory->AddSignalTree(cataTest, cataWeight, TMVA::Types::kTesting);
  factory->AddBackgroundTree(catbTest, catbWeight, TMVA::Types::kTesting);

  factory->AddVariable("x", 'F');
  factory->AddVariable("y", 'F');

  factory->BookMethod(TMVA::Types::kFisher, "Fisher", "H:!V:Fisher");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  outputFile->Close();
  std::cout << "==> wrote root file TMVA.root" << std::endl;
  std::cout << "==> TMVAnalysis is done!" << std::endl;

  delete factory;
  return 0;

}
