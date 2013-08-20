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
int ntottrig = 0;
int cent_index_start[41];
int mytrackquality = 0;
TH1D * hpttrg;
TH1D * hetatrg;
TH1D * hphitrg;
TH1D * hmulttrg;

HiForest *c;
TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, int nmin = 0, int nmax = 1000, double vzrange = 15);
TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, int nmin = 0, int nmax = 1000, double vzrange = 15, int statfactor = 20);
int GetNTotTrig();

void corrana(const char * infname = "/mnt/hadoop/cms/store/user/velicanu/mergedv1_sortedforest/mergesortv1_0.root", int trackquality = 0)
{
  mytrackquality = trackquality;
  cout<<"initializing hiforest and building centrality index"<<endl;
  cout<<"running on: "<<infname<<endl;
  c = new HiForest(infname);
  Long64_t nentries = c->GetEntries();
}


TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, int nmin, int nmax, double vzrange)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackSignal = new TH2D(Form("signal_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);

  hpttrg   = new TH1D(Form("hpttrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";p_{T}",100,0,10);
  hetatrg  = new TH1D(Form("hetatrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#eta",100,-2.5,2.5);
  hphitrg  = new TH1D(Form("hphitrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#phi",100,-2*pi,2*pi);
  hmulttrg = new TH1D(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#N in p_{T} range",300,0,300);

  

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
    
    int thismult = 0;
    for(int i = 0 ; i < c->genparticle->mult ; ++i)
    {
      if(c->genparticle->pt[i]>0.4 && fabs(c->genparticle->eta[i])<2.4 && c->genparticle->chg[i]!=0) thismult++;
    }
    // hmult->Fill(thismult);
    // cout<<thismult<<endl;
    if(thismult<nmin || thismult>=nmax) continue;
    nmult++;
    
    int ntrig = 0 , nass = 0;
    vector<double> trigtrkEta;
    vector<double> trigtrkPhi;
    vector<double> trigtrkIndex;
    vector<double> asstrkEta;
    vector<double> asstrkPhi;
    vector<double> asstrkIndex;
    for(int i = 0 ; i < c->genparticle->mult ; ++i)
    {
      
      // hetaphi->Fill(c->genparticle->eta[i],c->genparticle->phi[i]);
      // hdz->Fill(c->genparticle->trkDz1[i]);
      // hdxy->Fill(c->genparticle->trkDxy1[i]);
      // hdz_dzerr->Fill(c->genparticle->trkDz1[i]/c->genparticle->trkDzError1[i]);
      // hdxy_dxyerr->Fill(c->genparticle->trkDxy1[i]/c->genparticle->trkDxyError1[i]);
      // hpterr_pt->Fill(c->genparticle->ptError[i]/c->genparticle->pt[i]);
      // hnhits->Fill(c->genparticle->trkNHit[i]);
      // hchi2ndof->Fill(c->genparticle->trkChi2[i]/c->genparticle->trkNdof[i]);

      if( c->genparticle->pt[i]<pttriglow || c->genparticle->pt[i]>pttrighigh || fabs(c->genparticle->eta[i])>maxetatrg || c->genparticle->chg[i]==0) continue;
      bool considertrack = true;
      if(considertrack)
      {
        ++ntrig;
        trigtrkEta.push_back(c->genparticle->eta[i]);
        trigtrkPhi.push_back(c->genparticle->phi[i]);
        trigtrkIndex.push_back(i);
        hpttrg->Fill(c->genparticle->pt[i]);
        hetatrg->Fill(c->genparticle->eta[i]);
        hphitrg->Fill(c->genparticle->phi[i]);
      }
    }
    if(ntrig<2) continue;
    
    for(int j = 0 ; j < c->genparticle->mult ; ++j)
    {
      if( c->genparticle->pt[j]<ptasslow || c->genparticle->pt[j]>ptasshigh || fabs(c->genparticle->eta[j])>maxetaass || c->genparticle->chg[j]==0) continue;
      bool considertrack = true;
      
      if(considertrack)
      {
        ++nass;
        asstrkEta.push_back(c->genparticle->eta[j]);
        asstrkPhi.push_back(c->genparticle->phi[j]);
        asstrkIndex.push_back(j);
        // hptass->Fill(c->genparticle->pt[j]);
        // hetaass->Fill(c->genparticle->eta[j]);
        // hphiass->Fill(c->genparticle->phi[j]);
      }
    }
    hmulttrg->Fill(ntrig);
    for(int i = 0 ; i < ntrig ; ++i)
    {
      if(ntrig>1) ntottrig += 1;
      double double_ntrig = ntrig;
      for(int j = 0 ; j < nass ; ++j)
      {
        if(trigtrkIndex[i]==asstrkIndex[j]) continue;
        double deta = fabs(trigtrkEta[i]-asstrkEta[j]);
        double dphi = fabs(trigtrkPhi[i]-asstrkPhi[j]);
        if( dphi > pi ) dphi = 2*pi - dphi;
        hTrackTrackSignal->Fill(deta,dphi,1./double_ntrig);
        hTrackTrackSignal->Fill(-deta,dphi,1./double_ntrig);
        hTrackTrackSignal->Fill(deta,-dphi,1./double_ntrig);
        hTrackTrackSignal->Fill(-deta,-dphi,1./double_ntrig);
        hTrackTrackSignal->Fill(deta,(2*pi)-dphi,1./double_ntrig);
        hTrackTrackSignal->Fill(-deta,(2*pi)-dphi,1./double_ntrig);
      }
    }

    // if(jentry>100) break;
  }
  // if(ntottrig!=0) hTrackTrackSignal->Scale(1/ntottrig);
  hTrackTrackSignal->Scale(1/4.0); //! since we only fill one quadrant
  cout<<"nmult "<<nmult<<endl;
  return hTrackTrackSignal;
}


TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, int nmin, int nmax, double vzrange, int statfactor)
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
    // if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter)) continue;
    // if(fabs(c->evt->vz)>vzrange) continue;
    // if(c->evt->run!=202792) continue;
    // if(c->evt->lumi<317 || c->evt->lumi>1014) continue;
    
    int ntrackinptrange = 0;
    
    for(int i = 0 ; i < c->genparticle->mult ; ++i)
    {
      if(c->genparticle->pt[i]>0.4&&fabs(c->genparticle->eta[i])<2.4 && c->genparticle->chg[i]!=0) thismult++;
    }
    // cout<<thismult<<endl;
    // if(thismult<90) continue;
    if(thismult<nmin || thismult>=nmax) continue;
    
    //! construct vectors of all tracks passing our cuts in this event 
    vector<double> thistrkEta;
    vector<double> thistrkPhi;
    for(int i = 0 ; i < c->genparticle->mult ; ++i)
    {
      if( c->genparticle->pt[i]<pttriglow || c->genparticle->pt[i]>pttrighigh || fabs(c->genparticle->eta[i])>maxetatrg || c->genparticle->chg[i]==0) continue;
      bool considertrack = true;
      
      if(considertrack)
      {
        ++ntrackinptrange;
        thistrkEta.push_back(c->genparticle->eta[i]);
        thistrkPhi.push_back(c->genparticle->phi[i]);
      }
    }
    if(ntrackinptrange<1) continue;
    //! loop through the next n events to pair with this event
    int mixentry = jentry;
    int k = 0;
    // for(int k = 0 ; k < statfactor ; ++k)
    while(k<statfactor)
    {
      
      mixentry++;
      //! stop the loop when we reach the end of the file or of this centrality bin
      if(mixentry==nentries) break;
      
      c->GetEntry(mixentry);
      
      int thatmult = 0;
      for(int i = 0 ; i < c->genparticle->mult ; ++i)
      {
        if(c->genparticle->pt[i]>0.4&&fabs(c->genparticle->eta[i])<2.4 && c->genparticle->chg[i]!=0) thatmult++;
      }
      if(thatmult<nmin || thatmult>nmax) continue;
      
      // if(c->evt->hiBin != thiscent) break;
      
      // if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter)) continue;
      // if(fabs(c->evt->vz)>vzrange) continue;
      // if(c->evt->run!=202792) continue;
      // if(c->evt->lumi<317 || c->evt->lumi>1014) continue;
      
      int fillcount = 0;
      //! for each passed track in the original event pair all the passed tracks in the new event and fill deta dphi
      int ntrkhere = 0;
      for(int i = 0 ; i < ntrackinptrange ; ++i)
      {
        ntrkhere = 0;
        for(int j = 0 ; j < c->genparticle->mult ; ++j)
        {
          if( c->genparticle->pt[j]<ptasslow || c->genparticle->pt[j]>ptasshigh || fabs(c->genparticle->eta[j])>maxetaass || c->genparticle->chg[j]==0) continue;
          bool considertrack = true;
          if(considertrack)
          {
            double deta = fabs(thistrkEta[i] - c->genparticle->eta[j]);
            double dphi = fabs(thistrkPhi[i] - c->genparticle->phi[j]);
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
      }
      // cout<<"stat "<<statfactor<<" ntrackinptrange "<<ntrackinptrange<<" ntrkhere "<<ntrkhere<<" fillcount "<<fillcount<<endl;
      k++;
    }
  }
  return hTrackTrackBackground;
}

int GetNTotTrig()
{
  int tmp = ntottrig;
  ntottrig = 0;
  return tmp;
}
