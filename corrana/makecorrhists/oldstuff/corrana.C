// #include "/net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src/CmsHi/JetAnalysis/macros/forest/hiForest_charge.h"
#include "/net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/hiForest_charge.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <math.h>

using namespace std;

const double pi = 3.1415926;
double maxetatrg = 2.4;
double maxetaass = 2.4;
int cent_index_start[41];
  
HiForest *c;
TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange = 15, int multcut = 0);
TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, double vzrange = 15, int multcut = 0, int statfactor = 20);
TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange = 15, double dijetdphicut = 2 * pi / 3.0);
// TH2D * JetTrackBackground(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, double vzrange, int statfactor, double vzbin);

void corrana(const char * infname = "/mnt/hadoop/cms/store/user/velicanu/mergedv1_sortedforest/mergesortv1_0.root")
{
  cout<<"initializing hiforest and building centrality index"<<endl;
  c = new HiForest(infname);
  Long64_t nentries = c->GetEntries();
  // cent_index_start[0]=0;
  // int thiscent = 0;
  // for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // c->GetEntry(jentry);
    // if(jentry%1000==0) cout<<jentry<<"/"<<nentries<<endl;
    // if(thiscent != c->evt->hiBin)
    // {
      // thiscent++;
      // cent_index_start[thiscent]=jentry;
      // cout<<thiscent<<" cent starts at: "<<cent_index_start[thiscent]<<endl;
    // }
  // }
  // cent_index_start[40] = nentries;
  // cout<<"done building centrality index"<<endl;
}


TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange, int multcut)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackSignal = new TH2D(Form("signal_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  
  double ntottrig = 0;
  int nmult = 0;
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];
  // for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%1000==0) 
    {
      cout<<jentry<<"/"<<nentries<<endl;
    }
    // if(jentry==9999) break;
    c->GetEntry(jentry);
    
    // if(c->evt->hiBin <  centmin) continue;
    // if(c->evt->hiBin >= centmax) break;
    if(fabs(c->evt->vz)>vzrange) continue;
    int thismult = 0;
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if(fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1) thismult++;
    }
    // cout<<thismult<<endl;
    if(thismult<90) continue;
    nmult++;
    
    int ntrig = 0 , nass = 0;
    vector<double> trigtrkEta;
    vector<double> trigtrkPhi;
    vector<double> trigtrkIndex;
    vector<double> asstrkEta;
    vector<double> asstrkPhi;
    vector<double> asstrkIndex;
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if( c->track->trkPt[i]<pttriglow || c->track->trkPt[i]>pttrighigh || fabs(c->track->trkEta[i])>maxetatrg ) continue;
      ++ntrig;
      trigtrkEta.push_back(c->track->trkEta[i]);
      trigtrkPhi.push_back(c->track->trkPhi[i]);
      trigtrkIndex.push_back(i);
    }
    for(int j = 0 ; j < c->track->nTrk ; ++j)
    {
      if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
      ++nass;
      asstrkEta.push_back(c->track->trkEta[j]);
      asstrkPhi.push_back(c->track->trkPhi[j]);
      asstrkIndex.push_back(j);
    }
    
    for(int i = 0 ; i < ntrig ; ++i)
    {
      ntottrig += 1;
      for(int j = 0 ; j < nass ; ++j)
      {
        if(trigtrkIndex[i]==asstrkIndex[j]) continue;
        double deta = fabs(trigtrkEta[i]-asstrkEta[j]);
        double dphi = fabs(trigtrkPhi[i]-asstrkPhi[j]);
        if( dphi > pi ) dphi = 2*pi - dphi;
        hTrackTrackSignal->Fill(deta,dphi);
        hTrackTrackSignal->Fill(-deta,dphi);
        hTrackTrackSignal->Fill(deta,-dphi);
        hTrackTrackSignal->Fill(-deta,-dphi);
        hTrackTrackSignal->Fill(deta,(2*pi)-dphi);
        hTrackTrackSignal->Fill(-deta,(2*pi)-dphi);
      }
    }

    // if(jentry>100) break;
  }
  hTrackTrackSignal->Scale(1/ntottrig);
  cout<<"nmult "<<nmult<<endl;
  return hTrackTrackSignal;
}


TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, double vzrange, int multcut, int statfactor)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackBackground = new TH2D(Form("background_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  
  //! loop through all events in the centrality range to fill the mixed event background distribution
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];
  // for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    int thismult = 0;
    if(jentry%1000==0)
    {
      cout<<jentry<<"/"<<nentries<<endl;
    }
    // if(jentry==9999) break;
    c->GetEntry(jentry);
  
    //! skip events outside our vz range
    if(fabs(c->evt->vz)>vzrange) continue;
    
    int ntrackinptrange = 0;
    
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if(fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1) thismult++;
    }
    // cout<<thismult<<endl;
    if(thismult<90) continue;
    
    //! construct vectors of all tracks passing our cuts in this event 
    vector<double> thistrkEta;
    vector<double> thistrkPhi;
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if( c->track->trkPt[i]<pttriglow || c->track->trkPt[i]>pttrighigh || fabs(c->track->trkEta[i])>maxetatrg ) continue;
      ++ntrackinptrange;
      thistrkEta.push_back(c->track->trkEta[i]);
      thistrkPhi.push_back(c->track->trkPhi[i]);
    }
    int thiscent = c->evt->hiBin;
    
    //! loop through the next n events to pair with this event
    int mixentry = jentry;
    for(int k = 0 ; k < statfactor ; ++k)
    {
      mixentry++;
      //! stop the loop when we reach the end of the file or of this centrality bin
      if(mixentry==nentries) break;
      c->GetEntry(mixentry);
      // if(c->evt->hiBin != thiscent) break;
      if(fabs(c->evt->vz)>vzrange) continue;
      int fillcount = 0;
      //! for each passed track in the original event pair all the passed tracks in the new event and fill deta dphi
      int ntrkhere = 0;
      for(int i = 0 ; i < ntrackinptrange ; ++i)
      {
        ntrkhere = 0;
        for(int j = 0 ; j < c->track->nTrk ; ++j)
        {
          if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
          double deta = fabs(thistrkEta[i] - c->track->trkEta[j]);
          double dphi = fabs(thistrkPhi[i] - c->track->trkPhi[j]);
          if( dphi > pi ) dphi = 2*pi - dphi;
          hTrackTrackBackground->Fill(deta,dphi);
          hTrackTrackBackground->Fill(-deta,dphi);
          hTrackTrackBackground->Fill(deta,-dphi);
          hTrackTrackBackground->Fill(-deta,-dphi);
          hTrackTrackBackground->Fill(deta,(2*pi)-dphi);
          hTrackTrackBackground->Fill(-deta,(2*pi)-dphi);
          fillcount++;
          ntrkhere++;
        }
      }
      // cout<<"stat "<<statfactor<<" ntrackinptrange "<<ntrackinptrange<<" ntrkhere "<<ntrkhere<<" fillcount "<<fillcount<<endl;
    }
  }
  return hTrackTrackBackground;
}


/*

TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange, double dijetdphicut)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hJetTrackSignal;
  cout<<"before first exit"<<endl;
  if(jetindex==0) //leading jet
  {
    hJetTrackSignal = new TH2D(Form("signal_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else if(jetindex==1) //subleading jet
  {
    hJetTrackSignal = new TH2D(Form("signal_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)subleadingjetptlow,(int)subleadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else //leading jet
  {
    cout<<"Error: only jetindex 0 and 1 currently supported (leading + subleading jet)"<<endl;
    exit(1);
  }
  
  double ntottrig = 0;
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];


  cout<<"before event for loop "<<n_entries_in_cent_range<<endl;
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%100==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    cout<<"after getentry "<<jentry<<endl;
    
    // if(c->evt->hiBin <  centmin) continue;
    // if(c->evt->hiBin >= centmax) break;
    if(fabs(c->evt->vz)>vzrange) continue;
    double dijetdphi = fabs(c->icPu5.jtphi[0] - c->icPu5.jtphi[1]);
    if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    cout<<"leading jet pt: "<< c->icPu5.jtpt[0] <<" sub leading jet pt: "<<c->icPu5.jtpt[1]<<" dphi: "<<dijetdphi<<endl;
    if( dijetdphi > (2 * pi) / 3.0 ) continue;
    if( c->icPu5.jtpt[0] > leadingjetpthigh || c->icPu5.jtpt[0] < leadingjetptlow ) continue;
    if( c->icPu5.jtpt[1] > subleadingjetpthigh || c->icPu5.jtpt[1] < subleadingjetptlow ) continue;
    
    double jeteta = c->icPu5.jteta[jetindex];
    double jetphi = c->icPu5.jtphi[jetindex];
    
    int ntrig = 1 , nass = 0;
    
    vector<double> asstrkEta;
    vector<double> asstrkPhi;
    vector<double> asstrkIndex;
    for(int j = 0 ; j < c->track->nTrk ; ++j)
    {
      if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
      ++nass;
      asstrkEta.push_back(c->track->trkEta[j]);
      asstrkPhi.push_back(c->track->trkPhi[j]);
      asstrkIndex.push_back(j);
    }
    
    for(int i = 0 ; i < ntrig ; ++i)
    {
      ntottrig += 1;
      for(int j = 0 ; j < nass ; ++j)
      {
        // if(trigtrkIndex[i]==asstrkIndex[j]) continue;
        double deta = fabs(jeteta-asstrkEta[j]);
        double dphi = fabs(jetphi-asstrkPhi[j]);
        if( dphi > pi ) dphi = 2*pi - dphi;
        hJetTrackSignal->Fill(deta,dphi);
        hJetTrackSignal->Fill(-deta,dphi);
        hJetTrackSignal->Fill(deta,-dphi);
        hJetTrackSignal->Fill(-deta,-dphi);
        hJetTrackSignal->Fill(deta,(2*pi)-dphi);
        hJetTrackSignal->Fill(-deta,(2*pi)-dphi);
      }
    }

    // if(jentry>100) break;
  }
  hJetTrackSignal->Scale(1/ntottrig);
  return hJetTrackSignal;
}

*/


