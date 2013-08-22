#include "/net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src/CmsHi/JetAnalysis/macros/forest/hiforest_dtest.h"
// #include "/net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

vector< pair<int,double> > evtCentVz;
int comparecentvz (const void * a, const void * b);
// void sortforestCentVz(int startline = 0);


// void sortforestCentVz(double etCut=40, char *infname = "/mnt/hadoop/cms/store/user/velicanu/forest/HiForestTrack_v3.root")
// void sortforestCentVz(double etCut=40, char *infname = "/mnt/hadoop/cms/store/user/velicanu/HIHighPt/HIRun2011_hiHighPtTrack_PromptSkim_forest_v0/9902eec616cc8b0649a7a8bb69754615/HiForest_998_1_rJ1.root")
// void sortforestCentVz(double etCut=40, char *infname = "/net/hisrv0001/home/dav2105/hdir/HIHighPt/HIRun2011_hiHighPtTrack_PromptSkim_forest_v0/9902eec616cc8b0649a7a8bb69754615/HiForest_1000_1_8wo.root")
// void sortforestCentVz(double etCut=40, char *infname = "/net/hisrv0001/home/dav2105/hdir/HIHighPt/HIRun2011_hiHighPtTrack_PromptSkim_forest_v0/9902eec616cc8b0649a7a8bb69754615/HiForest_1001_1_TRm.root")
void sortforestCentVz_dtest(int startline = 0)
{
  //! Define the input and output file and HiForest
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile("/net/hidsk0001/d00/scratch/dav2105/forest/jobsort/jet80sortlist.txt");
  // ifstream infile("/net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt");

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
  HiForest *c = new HiForest(listoffiles[startline].data());
  c->SetOutputFile(Form("sortedHiForest_%d.root",startline));

  
  //! loop through all the events once to construct the cent,vz pair array we'll be sorting over
  cout << "Constructing the cent:vz pair array..." << endl;
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(i);
    pair<int,double> centvz;
    centvz.first = c->evt.hiBin;
    centvz.second = c->evt.vz;
    evtCentVz.push_back(centvz);
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<" "<<c->setupOutput<<endl;
    // if (i > 1000) break;
  }
  
  //! Make the index array which will get sorted on first centrality
  int evtindecies[c->GetEntries()];
  for (int i=0;i<c->GetEntries();i++)
  {
    evtindecies[i] = i;
    // if (i > 1000) break;
	// cout << "In original loop | " << evtindecies[i] << " : (" << evtCentVz[evtindecies[i]].first <<" , "<<evtCentVz[evtindecies[i]].second << endl;
  }
  
  cout << "Sorting the cent:vz pair array..." << " "<<c->setupOutput<<endl;
  //! Sort the index array first on the centrality bin, then on the vz of the entry at that index
  qsort (evtindecies, c->GetEntries(), sizeof(int), comparecentvz);
  // qsort (evtindecies, 1000, sizeof(int), comparecentvz);
  
  //! Now fill the tree in the new order
  cout << "Filling the tree in the sorted order..." << " "<<c->setupOutput<<endl;
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(evtindecies[i]);
    c->FillOutput();
	// cout << "In fill loop | " << evtindecies[i] << " : (" << evtCentVz[evtindecies[i]].first <<" , "<<evtCentVz[evtindecies[i]].second << endl;
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<" "<<c->setupOutput<<endl;
    // if (i > 1000) break;
  }

  delete c;
}

//! The comparison function for qsort which compares two indecies by looking up their centbin and vz in
//! evtCentVz pair array
int comparecentvz (const void * a, const void * b)
{
  // if( ( evtCentVz[*(int*)a].first - evtCentVz[*(int*)b].first ) > 0)
    // return 1;
  // else if( ( evtCentVz[*(int*)a].first - evtCentVz[*(int*)b].first ) < 0)
    // return -1;
  // else
  // {
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) < 0 )
      return -1;
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) > 0 )
      return 1;
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) == 0 )
      return 0;
    
  // }
}

