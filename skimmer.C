#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TPaletteAxis.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"

#include "category.cc" // to include the function in an unorthodox way, but it works without special compilation


using namespace std;



void doHistos(){

  TH1::SetDefaultSumw2(true);


  TString inFilePath    = "/eos/user/g/guoj/Sample/2L2Q/UL_Legacy/2016/";
  TString inputFileName = inFilePath + "GluGluHToZZTo2L2Q_M1000_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8__asymptotic_v17-v2_0.root";
  TFile*  inputFile;
  TTree*  inputTree;

  Float_t EventWeight;  
  Float_t SumWeight;  
  Bool_t foundZ1LCandidate;
  Bool_t foundZ2MergedCandidata;
  Bool_t foundZ2JCandidate;
  Float_t xsec;
  Float_t mass2l2jet;
  Float_t mass2lj;
  Double_t massmerged;
  Double_t mass2jet;
  Float_t particleNetZvsQCD;
  Float_t KD_JVBF;         
  Float_t particleNetZbbvslight;
  Float_t KD_jjVBF;
  Int_t jet_1_btag;
  Int_t jet_2_btag;  
  Bool_t isEE;
  Bool_t isMuMu;

  // auxiliary variables
  Float_t massZtoJets = -999.;
  Float_t massZZreco  = -999.;
  Int_t currentCategory = -999;
  Int_t currentFinalState = -999;


  // define some histos
  //TH1F* 

  // open input file
  cout<<"Opening file "<<inputFileName<<" ..."<<endl;
  inputFile = TFile::Open(inputFileName);
  inputTree = (TTree*)inputFile->Get("passedEvents");

  inputTree->SetBranchAddress("EventWeight", &EventWeight);
  inputTree->SetBranchAddress("SumWeight", &SumWeight);
  inputTree->SetBranchAddress("foundZ1LCandidate", &foundZ1LCandidate);
  inputTree->SetBranchAddress("foundZ2MergedCandidata", &foundZ2MergedCandidata);
  inputTree->SetBranchAddress("foundZ2JCandidate", &foundZ2JCandidate);
  inputTree->SetBranchAddress("mass2l2jet", &mass2l2jet);
  inputTree->SetBranchAddress("mass2lj", &mass2lj);
  inputTree->SetBranchAddress("massmerged", &massmerged);
  inputTree->SetBranchAddress("mass2jet", &mass2jet);
  inputTree->SetBranchAddress("particleNetZvsQCD", &particleNetZvsQCD);
  inputTree->SetBranchAddress("KD_JVBF", &KD_JVBF);
  inputTree->SetBranchAddress("particleNetZbbvslight", &particleNetZbbvslight);
  inputTree->SetBranchAddress("KD_jjVBF", &KD_jjVBF);
  inputTree->SetBranchAddress("jet_1_btag", &jet_1_btag);
  inputTree->SetBranchAddress("jet_2_btag", &jet_2_btag);
  inputTree->SetBranchAddress("isEE", &isEE);
  inputTree->SetBranchAddress("isMuMu", &isMuMu);


  // loop on events
  Long64_t entries = inputTree->GetEntries();
  cout<<"Processing file: "<< inputFileName  << " (" << entries <<" entries) ..."<< endl;   
  for(Long64_t z=0; z<entries; z++){
  
    inputTree->GetEntry(z);

    currentCategory = -999;
    currentFinalState = -999;

    if(foundZ1LCandidate==false) continue; // request of having a Z1 candidate (Z->ll)
    if((foundZ2MergedCandidata==false || particleNetZvsQCD<0.9) && foundZ2JCandidate==false) continue; // request of having a Z2 candidate (Z->J or Z->jj)

    if(foundZ2MergedCandidata==true){ // merged
      massZtoJets = massmerged;
      massZZreco  = mass2lj;
    }
    if(foundZ2JCandidate==true){ // resolved
      massZtoJets = mass2jet;
      massZZreco  = mass2l2jet;
    }


    // signal region
    if(massZtoJets > 70. && massZtoJets < 105.){

      currentCategory = selectCategory(foundZ2MergedCandidata,                    
                                       particleNetZvsQCD,                        
		                       KD_JVBF,                                  
			               particleNetZbbvslight,                    
			               foundZ2JCandidate,                         
			               KD_jjVBF,                                 
			               jet_1_btag,                                
                                       jet_2_btag
			              );  

      currentFinalState = selectFinalState(isEE,
                                           isMuMu
	                                  );

      // w = (EventWeight * lumi * 1000. * xsec) / SumWeight;
      cout<<foundZ1LCandidate<<endl;
      cout<<foundZ2MergedCandidata<<foundZ2JCandidate<<endl;
      cout<<"massZtoJets "<<massmerged<<" "<<mass2jet<<" "<<massZtoJets<<endl;
      cout<<"massZZreco "<<mass2lj<<" "<<mass2l2jet<<" "<<massZZreco<<endl;
      cout<<"category "<<currentCategory<<" final state "<<currentFinalState<<endl;
      cout<<"---"<<endl;

    }// end signal region



    
  } // end loop over entries 


}


// main
void skimmer(){

  doHistos();

}
