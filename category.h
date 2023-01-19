#ifndef CATEGORY_H
#define CATEGORY_H



// -------------------------
enum Categories{
  MergedVBF     = 0,         
  MergedBTag    = 1,
  MergedUntag   = 2,
  ResolvedVBF   = 3,
  ResolvedBTag  = 4,
  ResolvedUntag = 5,
  Unselected    = 6 //events not good for the analysis
}; 


int selectCategory(bool foundZ2MergedCandidata,
                   float particleNetZvsQCD,
                   float KD_JVBF, 
                   float particleNetZbbvslight,
                   bool foundZ2JCandidate,
                   float KD_jjVBF,
                   int jet_1_btag,
                   int jet_2_btag
		  );


// -------------------------
enum FinalStates{
  fs_2e    = 0,
  fs_2mu   = 1,
  fs_other = 2 //events not good for the analysis
};


int selectFinalState(bool isEE,
                     bool isMuMu
		    );


#endif
