// #include "/net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/hiForest_charge.h"
#include "HiForestAnalysis/hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>


void stdsort(int startline = 0, string flist = "", int nmin = 110, int nmax = 1000)
{
  //! Define the input and output file and HiForest
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile(flist.data());

  if (!infile.is_open()) {
    cout << "Error opening file. Exiting." << endl;
    return;
  } else {
    while (!infile.eof()) {
      infile >> buffer;
      listoffiles.push_back(buffer);
      nlines++;
    }
  }
  cout<<" here"<<endl;
  // HiForest *c = new HiForest(listoffiles[startline].data(),0,0,0,0,true);
  HiForest *c = new HiForest(listoffiles[startline].data(),"forest",cPPb);
  // TFile * outf = new TFile(Form("sortedHiForest_multbinned_nmin%d_nmax%d_%d.root",nmin,nmax,startline),"recreate");
  // c->outf = outf;
  // c->SetOutputFile("null",true);
  c->SetOutputFile(Form("sortedHiForest_multbinned_nmin%d_nmax%d_%d.root",nmin,nmax,startline));

  //! loop through all the events once to construct the cent,vz pair array we'll be sorting over
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(i);
    // if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter)) continue;
    // if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter)) continue;
    
    int thismult = 0;
    for(int itrk = 0 ; itrk < c->track.nTrk ; ++itrk)
    {
      if(c->track.trkPt[itrk]>0.4&&fabs(c->track.trkEta[itrk])<2.4&&c->track.highPurity[itrk]&&fabs(c->track.trkDz1[itrk]/c->track.trkDzError1[itrk])<3&&fabs(c->track.trkDxy1[itrk]/c->track.trkDxyError1[itrk])<3&&c->track.trkPtError[itrk]/c->track.trkPt[itrk]<0.1) thismult++;
    }
    if( thismult>=nmin && thismult<nmax )
    {
      cout<<thismult<<endl;
      c->FillOutput();
    }
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<" "<<c->setupOutput<<endl;
  }
  
  delete c;
}
