#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TFile.h>
#include <TRandom2.h>
#include <TTree.h>
#include "Event.h"

using namespace std;

int main(){

  const int numFiles = 2;           // one for training, one for testing
  string fileName[numFiles];
  fileName[0] = "testData.root";
  fileName[1] = "trainingData.root";

  int seed = 12345;
  TRandom2* ran = new TRandom2(seed);
  const int numValues = 100;
  /*const double sigma1 = 0.5;
  const double sigma2 = 0.5;
  const double width1 = 0.5;
  const double width2 = 0.5;
*/

  for (int j=0; j<numFiles; j++){      // j = 0 test, j = 1 train

    TFile file(fileName[j].c_str(), "recreate");
    TTree cata("cata", "Tree for category a");
    TTree catb("catb", "Tree for category b");
    Event evt;
    cata.Branch("evt", &evt, "x/d:y/d");
    catb.Branch("evt", &evt, "x/d:y/d");

    for (int i=0; i<numValues; ++i){
      double x = ran->Gaus();
      double y = ran->Gaus();
      evt.x = x;
      evt.y = y;
      cata.Fill();
    }


    for (int i=0; i<numValues; ++i){
      double x = ran->Gaus(1,2);
      double y = ran->Gaus(1,2);
      evt.x = x;
      evt.y = y;
      catb.Fill();
    }


    file.Write();
    file.Close();
}
return 0;
}






