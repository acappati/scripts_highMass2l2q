#include "category.h"



// ---------------------------
int selectCategory(bool foundZ2MergedCandidata,           
                   float particleNetZvsQCD,               
                   float KD_JVBF,                         
                   float particleNetZbbvslight,           
                   bool foundZ2JCandidate,                
                   float KD_jjVBF,                        
                   int jet_1_btag,                       
                   int jet_2_btag                        
                  )
{
  if( foundZ2MergedCandidata==true && particleNetZvsQCD>0.9 ){                  
                                                                                
    if( KD_JVBF > 0.5 ){                                                                                                                                     
      return MergedVBF;                                                                                                                                         
    }else if( particleNetZbbvslight>0.9 ){                                                                                                                     
        return MergedBTag; 
    }else{                                                                           
      return MergedUntag;                                                                                
    }                                                                                                                                                
  }else if( foundZ2JCandidate==true ){                                         
                                                                            
    if (KD_jjVBF > 0.5 ){                                                                                 
      return ResolvedVBF;                                                                                                             
    }else if( jet_1_btag==1 & jet_2_btag==1 ){                                                                            
      return ResolvedBTag;                                                                                      
    }else{                                                                                                                                              
      return ResolvedUntag;                                                   
    }                                                                                                                                                                          
  }else{
    return Unselected;
  }
}


// ---------------------------
int selectFinalState(bool isEE,
                     bool isMuMu
		     )
{
  if(isEE==true && isMuMu==false){
    return fs_2e;
  }else if(isMuMu==true && isEE==false){
      return fs_2mu;
  }else{
    return fs_other;
  }
}

