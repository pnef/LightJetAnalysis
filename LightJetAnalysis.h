#ifndef  LightJetAnalysis_H
#define  LightJetAnalysis_H

#include <vector>
#include <math.h>
#include <string>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"  
#include "fastjet/tools/Filter.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "LightJetAnalysisBase.h"

using namespace std;

class LightJetAnalysis: public LightJetAnalysisBase {
    public:
        LightJetAnalysis (TTree *tree);
        ~LightJetAnalysis ();
        
        void Begin();
        void End();
        void Loop();
        void Analyze();
        void Debug(int debug){
            debug_ = debug;
        }
        inline void SetOutName(string outname){
            outname_ = outname;
        }
        inline void SetNEvents(int nevents){
            nevents_ = nevents;
        }

    private:
        int  debug_;
        Long64_t nevents_;
        string outname_;
        TFile *outfile_;


        // histos and such
        TH1D* h_clpt;

};



#endif

