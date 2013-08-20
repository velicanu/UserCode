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

const int phi_bin = 7;
const double phi_min[] = {-pi,-3.0*pi/4.0,-pi/2.0,-pi/4.0,0,pi/4.0,pi/2.0,3.0*pi/4.0};
const double phi_max[] = {-3.0*pi/4.0,-pi/2.0,-pi/4.0,0,pi/4.0,pi/2.0,3.0*pi/4.0,pi};

bool phi_out_of_range(double phi)
{
	return (phi < phi_min[phi_bin] || phi >= phi_max[phi_bin]);
}

TH1D * hmult;
TH1D * hpttrg;
TH1D * hetatrg;
TH1D * hphitrg;
TH1D * hptass;
TH1D * hetaass;
TH1D * hphiass;

TH2D * hetaphi;
TH1D * hdz;
TH1D * hdxy;
TH1D * hdz_dzerr;
TH1D * hdxy_dxyerr;
TH1D * hpterr_pt;
TH1D * hnhits;
TH1D * hchi2ndof;

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


TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, int nmin, int nmax, double vzrange)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackSignal = new TH2D(Form("signal_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  hmult   = new TH1D(Form("hmult_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";N",300,0,300);
  hpttrg  = new TH1D(Form("hpttrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";p_{T}",100,0,10);
  hetatrg = new TH1D(Form("hetatrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#eta",100,-2.5,2.5);
  hphitrg = new TH1D(Form("hphitrg_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#phi",100,-2*pi,2*pi);
  hptass  = new TH1D(Form("hptass_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";p_{T}",100,0,10);
  hetaass = new TH1D(Form("hetaass_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#eta",100,-2.5,2.5);
  hphiass = new TH1D(Form("hphiass_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#phi",100,-2*pi,2*pi);
 
  cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  hdz = new TH1D("hdz_highpurity",Form(";dz %d #leq N < %d",nmin,nmax),1000,-100,100);
  hdz_dzerr = new TH1D("hdz_dzerr_highpurity",Form(";dz/dzerr %d #leq N < %d",nmin,nmax),1000,-50,50);
  hdxy = new TH1D("hdxy_highpurity",Form(";dxy %d #leq N < %d",nmin,nmax),1000,-50,50);
  hdxy_dxyerr = new TH1D("hdxy_dxyerr_highpurity",Form(";dxy/dxyerr %d #leq N < %d",nmin,nmax),1000,-50,50);
  hpterr_pt = new TH1D("hpterr_pt_highpurity",Form(";pterror/pt %d #leq N < %d",nmin,nmax),1000,0,1);
  hnhits = new TH1D("hnhits_highpurity",Form(";nhits %d #leq N < %d",nmin,nmax),80,0,80);
  hchi2ndof = new TH1D("hchi2ndof_highpurity",Form(";chi2/ndof %d #leq N < %d",nmin,nmax),1000,0,10);
  hetaphi = new TH2D("hetaphi_highpurity",Form(";#eta %d #leq N < %d;#phi",nmin,nmax),50,-2.5,2.5,62,-pi,pi);
 


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
    if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter)) continue;
    if(fabs(c->evt->vz)>vzrange) continue;
    if(c->evt->run!=202792) continue;
    if(c->evt->lumi<317 || c->evt->lumi>1014) continue;
    int thismult = 0;
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if(c->track->trkPt[i]>0.4&&fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1) thismult++;
    }
    hmult->Fill(thismult);
    // cout<<thismult<<endl;
    // if(thismult<90) continue;
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
      
      hetaphi->Fill(c->track->trkEta[i],c->track->trkPhi[i]);
      hdz->Fill(c->track->trkDz1[i]);
      hdxy->Fill(c->track->trkDxy1[i]);
      hdz_dzerr->Fill(c->track->trkDz1[i]/c->track->trkDzError1[i]);
      hdxy_dxyerr->Fill(c->track->trkDxy1[i]/c->track->trkDxyError1[i]);
      hpterr_pt->Fill(c->track->trkPtError[i]/c->track->trkPt[i]);
      hnhits->Fill(c->track->trkNHit[i]);
      hchi2ndof->Fill(c->track->trkChi2[i]/c->track->trkNdof[i]);

      if( c->track->trkPt[i]<pttriglow || c->track->trkPt[i]>pttrighigh || fabs(c->track->trkEta[i])>maxetatrg ) continue;
      bool considertrack = false;
      if(mytrackquality==0&&fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1)
      {
        considertrack=true;
      }
      else if(mytrackquality==1)
      {
        considertrack=true;
      }
      else if(mytrackquality==2&&!(fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1))
      {
        considertrack=true;
      }
	  if(phi_out_of_range(c->track->trkPhi[i]))considertrack=false;
      if(considertrack)
      {
        ++ntrig;
        trigtrkEta.push_back(c->track->trkEta[i]);
        trigtrkPhi.push_back(c->track->trkPhi[i]);
        trigtrkIndex.push_back(i);
        hpttrg->Fill(c->track->trkPt[i]);
        hetatrg->Fill(c->track->trkEta[i]);
        hphitrg->Fill(c->track->trkPhi[i]);
      }
    }
    for(int j = 0 ; j < c->track->nTrk ; ++j)
    {
      if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
      bool considertrack = false;
      if(mytrackquality==0&&fabs(c->track->trkEta[j])<2.4&&c->track->highPurity[j]&&fabs(c->track->trkDz1[j]/c->track->trkDzError1[j])<3&&fabs(c->track->trkDxy1[j]/c->track->trkDxyError1[j])<3&&c->track->trkPtError[j]/c->track->trkPt[j]<0.1)
      {
        considertrack=true;
      }
      else if(mytrackquality==1)
      {
        considertrack=true;
      }
      else if(mytrackquality==2&&!(fabs(c->track->trkEta[j])<2.4&&c->track->highPurity[j]&&fabs(c->track->trkDz1[j]/c->track->trkDzError1[j])<3&&fabs(c->track->trkDxy1[j]/c->track->trkDxyError1[j])<3&&c->track->trkPtError[j]/c->track->trkPt[j]<0.1))
      {
        considertrack=true;
      }
      if(considertrack)
      {
        ++nass;
        asstrkEta.push_back(c->track->trkEta[j]);
        asstrkPhi.push_back(c->track->trkPhi[j]);
        asstrkIndex.push_back(j);
        hptass->Fill(c->track->trkPt[j]);
        hetaass->Fill(c->track->trkEta[j]);
        hphiass->Fill(c->track->trkPhi[j]);
      }
    }
    
    for(int i = 0 ; i < ntrig ; ++i)
    {
      if(ntrig>1) ntottrig += 1;
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
    if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter)) continue;
    if(fabs(c->evt->vz)>vzrange) continue;
    if(c->evt->run!=202792) continue;
    if(c->evt->lumi<317 || c->evt->lumi>1014) continue;
    
    int ntrackinptrange = 0;
    
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if(fabs(c->track->trkPt[i]>0.4&&c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1) thismult++;
    }
    // cout<<thismult<<endl;
    // if(thismult<90) continue;
    
    //! construct vectors of all tracks passing our cuts in this event 
    vector<double> thistrkEta;
    vector<double> thistrkPhi;
    for(int i = 0 ; i < c->track->nTrk ; ++i)
    {
      if( c->track->trkPt[i]<pttriglow || c->track->trkPt[i]>pttrighigh || fabs(c->track->trkEta[i])>maxetatrg ) continue;
      bool considertrack = false;
      if(mytrackquality==0&&fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1)
      {
        considertrack=true;
      }
      else if(mytrackquality==1)
      {
        considertrack=true;
      }
      else if(mytrackquality==2&&!(fabs(c->track->trkEta[i])<2.4&&c->track->highPurity[i]&&fabs(c->track->trkDz1[i]/c->track->trkDzError1[i])<3&&fabs(c->track->trkDxy1[i]/c->track->trkDxyError1[i])<3&&c->track->trkPtError[i]/c->track->trkPt[i]<0.1))
      {
        considertrack=true;
      }
	  if(phi_out_of_range(c->track->trkPhi[i]))considertrack=false;
      if(considertrack)
      {
        ++ntrackinptrange;
        thistrkEta.push_back(c->track->trkEta[i]);
        thistrkPhi.push_back(c->track->trkPhi[i]);
      }
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
      
      if(!(c->skim->phfPosFilter1&&c->skim->phfNegFilter1&&c->skim->phltPixelClusterShapeFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter&&c->skim->pprimaryvertexFilter&&c->skim->pHBHENoiseFilter)) continue;
      if(fabs(c->evt->vz)>vzrange) continue;
      if(c->evt->run!=202792) continue;
      if(c->evt->lumi<317 || c->evt->lumi>1014) continue;
      
      int fillcount = 0;
      //! for each passed track in the original event pair all the passed tracks in the new event and fill deta dphi
      int ntrkhere = 0;
      for(int i = 0 ; i < ntrackinptrange ; ++i)
      {
        ntrkhere = 0;
        for(int j = 0 ; j < c->track->nTrk ; ++j)
        {
          if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
          bool considertrack = false;
          if(mytrackquality==0&&fabs(c->track->trkEta[j])<2.4&&c->track->highPurity[j]&&fabs(c->track->trkDz1[j]/c->track->trkDzError1[j])<3&&fabs(c->track->trkDxy1[j]/c->track->trkDxyError1[j])<3&&c->track->trkPtError[j]/c->track->trkPt[j]<0.1)
          {
            considertrack=true;
          }
          else if(mytrackquality==1)
          {
            considertrack=true;
          }
          else if(mytrackquality==2&&!(fabs(c->track->trkEta[j])<2.4&&c->track->highPurity[j]&&fabs(c->track->trkDz1[j]/c->track->trkDzError1[j])<3&&fabs(c->track->trkDxy1[j]/c->track->trkDxyError1[j])<3&&c->track->trkPtError[j]/c->track->trkPt[j]<0.1))
          {
            considertrack=true;
          }
          if(considertrack)
          {
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
      }
      // cout<<"stat "<<statfactor<<" ntrackinptrange "<<ntrackinptrange<<" ntrkhere "<<ntrkhere<<" fillcount "<<fillcount<<endl;
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
