//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  4 13:24:53 2014 by ROOT version 5.34/05
// from TTree EventTree/Tree with event-by-event variables
// found on file: /atlas/output/pnef/20140604.11.11_PileUpStudies_rev360615.PythJXmc12aJETMETshort.jetmet2012pileupcustom.root
//////////////////////////////////////////////////////////

#ifndef LightJetAnalysisBase_h
#define LightJetAnalysisBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class LightJetAnalysisBase {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Float_t         Weight;
   Float_t         Mu;
   Int_t           NPVtruth;
   Int_t           NPV;
   Int_t           NJets;
   Int_t           NJetsFilled;
   Float_t         Jpt[17];   //[NJetsFilled]
   Float_t         Jeta[17];   //[NJetsFilled]
   Float_t         Jphi[17];   //[NJetsFilled]
   Int_t           JisPU[17];   //[NJetsFilled]
   Int_t           JisHS[17];   //[NJetsFilled]
   Int_t           JisBtagged[17];   //[NJetsFilled]
   Float_t         JJVF[17];   //[NJetsFilled]
   Float_t         JRpT[17];   //[NJetsFilled]
   Float_t         JnPUTrkCorrJVF[17];   //[NJetsFilled]
   Float_t         Jtruthpt[17];   //[NJetsFilled]

   // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_Mu;   //!
   TBranch        *b_NPVtruth;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NJetsFilled;   //!
   TBranch        *b_Jpt;   //!
   TBranch        *b_Jeta;   //!
   TBranch        *b_Jphi;   //!
   TBranch        *b_JisPU;   //!
   TBranch        *b_JisHS;   //!
   TBranch        *b_JisBtagged;   //!
   TBranch        *b_JJVF;   //!
   TBranch        *b_JRpT;   //!
   TBranch        *b_JnPUTrkCorrJVF;   //!
   TBranch        *b_Jtruthpt;   //!

   LightJetAnalysisBase(TTree *tree=0);
   virtual ~LightJetAnalysisBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef LightJetAnalysisBase_cxx
LightJetAnalysisBase::LightJetAnalysisBase(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/atlas/output/pnef/20140604.11.11_PileUpStudies_rev360615.PythJXmc12aJETMETshort.jetmet2012pileupcustom.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/atlas/output/pnef/20140604.11.11_PileUpStudies_rev360615.PythJXmc12aJETMETshort.jetmet2012pileupcustom.root");
      }
      f->GetObject("EventTree",tree);

   }
   Init(tree);
}

LightJetAnalysisBase::~LightJetAnalysisBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t LightJetAnalysisBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t LightJetAnalysisBase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void LightJetAnalysisBase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("Mu", &Mu, &b_Mu);
   fChain->SetBranchAddress("NPVtruth", &NPVtruth, &b_NPVtruth);
   fChain->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsFilled", &NJetsFilled, &b_NJetsFilled);
   fChain->SetBranchAddress("Jpt", Jpt, &b_Jpt);
   fChain->SetBranchAddress("Jeta", Jeta, &b_Jeta);
   fChain->SetBranchAddress("Jphi", Jphi, &b_Jphi);
   fChain->SetBranchAddress("JisPU", JisPU, &b_JisPU);
   fChain->SetBranchAddress("JisHS", JisHS, &b_JisHS);
   fChain->SetBranchAddress("JisBtagged", JisBtagged, &b_JisBtagged);
   fChain->SetBranchAddress("JJVF", JJVF, &b_JJVF);
   fChain->SetBranchAddress("JRpT", JRpT, &b_JRpT);
   fChain->SetBranchAddress("JnPUTrkCorrJVF", JnPUTrkCorrJVF, &b_JnPUTrkCorrJVF);
   fChain->SetBranchAddress("Jtruthpt", Jtruthpt, &b_Jtruthpt);
   Notify();
}

Bool_t LightJetAnalysisBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void LightJetAnalysisBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t LightJetAnalysisBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef LightJetAnalysisBase_cxx
