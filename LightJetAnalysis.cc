#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>


#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include "TH1D.h"


#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"  
#include "fastjet/tools/Filter.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"

#include "LightJetAnalysis.h"

using namespace std;
using namespace fastjet;


// Constructor 
LightJetAnalysis::LightJetAnalysis(TTree* tree){
    if(debug_) cout << "LightJetAnalysis::LightJetAnalysis Start " << endl;
    debug_   = false;
    outname_ = "test.root";

    Init(tree);

    if(debug_) cout << "LightJetAnalysis::LightJetAnalysis End " << endl;
}

// Destructor 
LightJetAnalysis::~LightJetAnalysis(){
}

// Begin method
void LightJetAnalysis::Begin(){
    
    // create output file 
    outfile_ = new TFile(outname_.c_str(), "recreate");

    // declare histos
    h_clpt    = new TH1D("cl_pt", "", 100, 0, 500);
    h_NJetsVsNPV = new TH2D("NJetsVsNPV", "", 30, 0, 50, 20, 0, 10);

   return;
}

// End
void LightJetAnalysis::End(){
    
    h_NJetsVsNPV->Write();
    outfile_->Write();

    delete h_NJetsVsNPV;
    delete outfile_;
    return;
}

// loop method
void LightJetAnalysis::Loop(){
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<min(nentries,nevents_);jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      // now call analyze method
      Analyze();
   }
   return;
}


// Analyze method, called for each event
// -> do event by event calculation and filling of histos here
void LightJetAnalysis::Analyze(){

    cout << "---------------------------- " << endl;
    cout << "Event Number " << EventNumber  << " NPV " << NPV << " NPVTruth " << NPVtruth << endl; 


    std::vector<fastjet::PseudoJet> clusters;
    for(int icl=0; icl<cl_lc_n; ++icl){
        fastjet::PseudoJet lv(cl_lc_px[icl], cl_lc_py[icl], cl_lc_pz[icl], cl_lc_E[icl]);
        clusters.push_back(lv);
    }


    JetMedianBackgroundEstimator bge(SelectorAbsRapMax(2.0), JetDefinition(kt_algorithm, 0.4), active_area_explicit_ghosts);  
    bge.set_particles(clusters); //vector
    float rho = bge.rho();

    vector<PseudoJet> jets;
    AreaDefinition area_def(active_area_explicit_ghosts, GhostedAreaSpec(5.0));  //is this value supposed to be 5.0 or 0.5?
    ClusterSequenceArea cs(clusters, JetDefinition(antikt_algorithm, 0.4), area_def);
    jets = sorted_by_pt(cs.inclusive_jets());  

    int njetspt20=0;
    for(int i=0; i<jets.size(); ++i){
        float pt = jets[i].pt() - rho*jets[i].area();
        jets[i].reset_momentum_PtYPhiM(pt, jets[i].rapidity(), jets[i].phi(), jets[i].m());

        if(jets[i].pt()> 20 ) {
            //cout << "jet with pT " << jets[i].pt() << endl;

            njetspt20++;
        }
    }
    h_NJetsVsNPV->Fill(NPV, njetspt20);



    return; 
}
