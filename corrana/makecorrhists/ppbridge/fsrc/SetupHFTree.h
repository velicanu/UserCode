//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 29 08:06:05 2013 by ROOT version 5.32/00
// from TTree hf/v1
// found on file: /mnt/hadoop/cms/store/user/velicanu/WeiPUTest_ON_HM_1/pPb_hiForest2_HM_101_1_ZU6.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class HF {
public :
   HF(){};
   ~HF(){};

   // Declaration of leaf types
   Int_t           n;
   Float_t         e[4096];   //[n]
   Float_t         et[4096];   //[n]
   Float_t         eta[4096];   //[n]
   Float_t         phi[4096];   //[n]
   Float_t         perp[4096];   //[n]
   Int_t           depth[4096];   //[n]
   Bool_t          isjet[4096];   //[n]

   // List of branches
   TBranch        *b_n;   //!
   TBranch        *b_e;   //!
   TBranch        *b_et;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_perp;   //!
   TBranch        *b_depth;   //!
   TBranch        *b_isjet;   //!

};

void setupHFTree(TTree *t,HF &tHF,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   if (t->GetBranch("n")) t->SetBranchAddress("n", &tHF.n, &tHF.b_n);
   if (t->GetBranch("e")) t->SetBranchAddress("e", tHF.e, &tHF.b_e);
   if (t->GetBranch("et")) t->SetBranchAddress("et", tHF.et, &tHF.b_et);
   if (t->GetBranch("eta")) t->SetBranchAddress("eta", tHF.eta, &tHF.b_eta);
   if (t->GetBranch("phi")) t->SetBranchAddress("phi", tHF.phi, &tHF.b_phi);
   if (t->GetBranch("perp")) t->SetBranchAddress("perp", tHF.perp, &tHF.b_perp);
   if (t->GetBranch("depth")) t->SetBranchAddress("depth", tHF.depth, &tHF.b_depth);
   if (t->GetBranch("isjet")) t->SetBranchAddress("isjet", tHF.isjet, &tHF.b_isjet);
   if (doCheck) {
      if (t->GetMaximum("n")>4096) { cout <<"FATAL ERROR: Arrary size of HF n too small!!!  "<<t->GetMaximum("n")<<endl; exit(0);
 }   }
}
