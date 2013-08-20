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
// double dijet_dphi_CUT = (2 * pi) / 3.0 ; 
double dijet_dphi_CUT = (7 * pi) / 8.0 ; 
double jet_eta_CUT = 2.0;
int cent_index_start[41];

HiForest *c;
// TH1D * GetNtrk(int centmin, int centmax);
TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange = 15);
TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, double vzrange = 15, int statfactor = 20);
TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin = 0.0, float ajmax = 1.0 , int doptweight = 0 , double vzrange = 15, double dijetdphicut = 2 * pi / 3.0);
TH2D * JetTrackBackground(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin = 0.0, float ajmax = 1.0 , int doptweight = 0 , double vzrange = 15, double dijetdphicut = 2 * pi / 3.0, int statfactor = 20);
void makestdhists();
// void makethisstdhists(double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin = 0.0 , float ajmax = 1.0);


void stdcorrana(const char * infname = "/mnt/hadoop/cms/store/user/velicanu/mergedv1_sortedforest/mergesortv1_0.root")
{
  cout<<"initializing hiforest and building centrality index"<<endl;
  c = new HiForest(infname);
  Long64_t nentries = c->GetEntries();
  cent_index_start[0]=0;
  int thiscent = 0;
  
  c->LoadNoTrees();
  c->hasEvtTree = true;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    c->GetEntry(jentry);
    if(jentry%1000==0) cout<<jentry<<"/"<<nentries<<endl;
    if(thiscent != c->evt->hiBin)
    {
      thiscent++;
      cent_index_start[thiscent]=jentry;
    }
    // break;
  }
  c->ResetBooleans();
  cent_index_start[40] = nentries;
  cout<<"done building centrality index"<<endl;
}


TH2D * TrackTrackSignal(double pttriglow , double pttrighigh , double ptasslow , double ptasshigh, int centmin, int centmax, double vzrange)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackSignal = new TH2D(Form("signal_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  
  double ntottrig = 0;
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%1000==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    
    // if(c->evt->hiBin <  centmin) continue;
    // if(c->evt->hiBin >= centmax) break;
    if(fabs(c->evt->vz)>vzrange) continue;
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
  return hTrackTrackSignal;
}


TH2D * TrackTrackBackground(double pttriglow , double pttrighigh , double ptasslow, double ptasshigh, int centmin, int centmax, double vzrange, int statfactor)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hTrackTrackBackground = new TH2D(Form("background_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow,(int)pttrighigh,(int)ptasslow,(int)ptasshigh,centmin,centmax),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  
  //! loop through all events in the centrality range to fill the mixed event background distribution
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%1000==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    
    //! skip events outside our vz range
    if(fabs(c->evt->vz)>vzrange) continue;
    
    int ntrackinptrange = 0;
    
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
      if(c->evt->hiBin != thiscent) break;
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



TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin , float ajmax , int doptweight , double vzrange, double dijetdphicut)
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hJetTrackSignal;
  cout<<"before first exit"<<endl;
  if(jetindex==0) //leading jet
  {
    hJetTrackSignal = new TH2D(Form("signal_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else if(jetindex==1) //subleading jet
  {
    hJetTrackSignal = new TH2D(Form("signal_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else //leading jet
  {
    cout<<"Error: only jetindex 0 and 1 currently supported (leading + subleading jet)"<<endl;
    exit(1);
  }
  
  double ntottrig = 0;
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];


  cout<<"before event for loop "<<n_entries_in_cent_range<<endl;
  // for (Long64_t jentry=0; jentry<10000;jentry++) {
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%1000==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    
    //! jet cuts, vz range, more than 2 jettss, dijetdphi 7/8 pi, both jet |eta| < 2, pt range cuts, aj cuts
    if( fabs(c->evt->vz) > vzrange ) continue;
    if( c->akPu3PF->nref < 2 )         continue;
    double dijetdphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    if( dijetdphi > dijet_dphi_CUT ) continue;
    if( fabs(c->akPu3PF->jteta[0]) > jet_eta_CUT || fabs(c->akPu3PF->jteta[1]) > jet_eta_CUT ) continue;
    if( c->akPu3PF->jtpt[0] > leadingjetpthigh || c->akPu3PF->jtpt[0] < leadingjetptlow ) continue;
    if( c->akPu3PF->jtpt[1] > subleadingjetpthigh || c->akPu3PF->jtpt[1] < subleadingjetptlow ) continue;
    double aj = ( c->akPu3PF->jtpt[0] - c->akPu3PF->jtpt[1] ) / ( c->akPu3PF->jtpt[0] + c->akPu3PF->jtpt[1] );
    if( aj < ajmin || aj > ajmax ) continue;
    
    double jeteta = c->akPu3PF->jteta[jetindex];
    double jetphi = c->akPu3PF->jtphi[jetindex];
    
    int ntrig = 1 , nass = 0;
    
    vector<double> asstrkEta;
    vector<double> asstrkPhi;
    vector<double> asstrkPt;
    vector<double> asstrkIndex;
    for(int j = 0 ; j < c->track->nTrk ; ++j)
    {
      if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
      if( c->track->trkAlgo[j]<4 || c->track->highPurity[j])
      {
        ++nass;
        asstrkEta.push_back(c->track->trkEta[j]);
        asstrkPhi.push_back(c->track->trkPhi[j]);
        asstrkPt.push_back(c->track->trkPt[j]);
        asstrkIndex.push_back(j);
      }
    }
    
    for(int i = 0 ; i < ntrig ; ++i)
    {
      ntottrig += 1;
      for(int j = 0 ; j < nass ; ++j)
      {
        double deta = fabs(jeteta-asstrkEta[j]);
        double dphi = fabs(jetphi-asstrkPhi[j]);
        double ptw = asstrkPt[j];
        if( dphi > pi ) dphi = 2*pi - dphi;
        if(doptweight==0)
        {
          hJetTrackSignal->Fill(deta,dphi);
          hJetTrackSignal->Fill(-deta,dphi);
          hJetTrackSignal->Fill(deta,-dphi);
          hJetTrackSignal->Fill(-deta,-dphi);
          hJetTrackSignal->Fill(deta,(2*pi)-dphi);
          hJetTrackSignal->Fill(-deta,(2*pi)-dphi);
        }
        else
        {
          hJetTrackSignal->Fill(deta,dphi,ptw);
          hJetTrackSignal->Fill(-deta,dphi,ptw);
          hJetTrackSignal->Fill(deta,-dphi,ptw);
          hJetTrackSignal->Fill(-deta,-dphi,ptw);
          hJetTrackSignal->Fill(deta,(2*pi)-dphi,ptw);
          hJetTrackSignal->Fill(-deta,(2*pi)-dphi,ptw);
        }
      }
    }

    // if(jentry>100) break;
  }
  if( ntottrig != 0 ) hJetTrackSignal->Scale(1/ntottrig);
  return hJetTrackSignal;
}


TH2D * JetTrackBackground(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin , float ajmax , int doptweight , double vzrange, double dijetdphicut, int statfactor )
{
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hJetTrackBackground;
  if(jetindex==0) //leading jet
  {
    hJetTrackBackground = new TH2D(Form("background_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else if(jetindex==1) //subleading jet
  {
    hJetTrackBackground = new TH2D(Form("background_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100,-5,5,75,-pi,2*pi);
  }
  else //leading jet
  {
    cout<<"Error: only jetindex 0 and 1 currently supported (leading + subleading jet)"<<endl;
    exit(1);
  }

  
  //! loop through all events in the centrality range to fill the mixed event background distribution
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];
  // for (Long64_t jentry=0; jentry<10000;jentry++) {
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%1000==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    
    //! skip events outside our vz range
    if(fabs(c->evt->vz)>vzrange) continue;
    
    int ntrackinptrange = 0;
    
    //! construct vectors of all tracks passing our cuts in this event 
    
    if( c->akPu3PF->nref < 2 )         continue;
    double dijetdphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    
    if( dijetdphi > dijet_dphi_CUT ) continue;
    if( fabs(c->akPu3PF->jteta[0]) > jet_eta_CUT || fabs(c->akPu3PF->jteta[1]) > jet_eta_CUT ) continue;
    
    if( c->akPu3PF->jtpt[0] > leadingjetpthigh || c->akPu3PF->jtpt[0] < leadingjetptlow ) continue;
    if( c->akPu3PF->jtpt[1] > subleadingjetpthigh || c->akPu3PF->jtpt[1] < subleadingjetptlow ) continue;
    double aj = ( c->akPu3PF->jtpt[0] - c->akPu3PF->jtpt[1] ) / ( c->akPu3PF->jtpt[0] + c->akPu3PF->jtpt[1] );
    // if( aj > 0.12 ) continue;
    double thisjeteta = c->akPu3PF->jteta[jetindex];
    double thisjetphi = c->akPu3PF->jtphi[jetindex];

    
    int thiscent = c->evt->hiBin;
    
    //! loop through the next n events to pair with this event
    int mixentry = jentry;
    for(int k = 0 ; k < statfactor ; ++k)
    {
      mixentry++;
      //! stop the loop when we reach the end of the file or of this centrality bin
      if(mixentry==nentries) break;
      c->GetEntry(mixentry);
      if(c->evt->hiBin != thiscent) break;
      if(fabs(c->evt->vz)>vzrange) continue;
      int fillcount = 0;
      //! for each passed track in the original event pair all the passed tracks in the new event and fill deta dphi
      for(int j = 0 ; j < c->track->nTrk ; ++j)
      {
        if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
        if( c->track->trkAlgo[j]<4 || c->track->highPurity[j])
        {
          double deta = fabs(thisjeteta - c->track->trkEta[j]);
          double dphi = fabs(thisjetphi - c->track->trkPhi[j]);
          double ptw = c->track->trkPt[j];
          if( dphi > pi ) dphi = 2*pi - dphi;
          if(doptweight==0)
          {
            hJetTrackBackground->Fill(deta,dphi);
            hJetTrackBackground->Fill(-deta,dphi);
            hJetTrackBackground->Fill(deta,-dphi);
            hJetTrackBackground->Fill(-deta,-dphi);
            hJetTrackBackground->Fill(deta,(2*pi)-dphi);
            hJetTrackBackground->Fill(-deta,(2*pi)-dphi);
          }
          else
          {
            hJetTrackBackground->Fill(deta,dphi,ptw);
            hJetTrackBackground->Fill(-deta,dphi,ptw);
            hJetTrackBackground->Fill(deta,-dphi,ptw);
            hJetTrackBackground->Fill(-deta,-dphi,ptw);
            hJetTrackBackground->Fill(deta,(2*pi)-dphi,ptw);
            hJetTrackBackground->Fill(-deta,(2*pi)-dphi,ptw);
          }
          fillcount++;
        }
      }
    }
  }
  return hJetTrackBackground;
}

void makestdhists()
{

  Long64_t nentries = c->GetEntries();
  
  TH1D * hleadingjeteta = new TH1D("hleadingjeteta",";leading jet #eta",44,-2.2,2.2);
  c->tree->Draw("(jteta[0])>>hleadingjeteta","abs(jteta[0])<2&&abs(jteta[1])<2","goff");

  TH1D * hsubleadingjeteta = new TH1D("hsubleadingjeteta",";subleading jet #eta",44,-2.2,2.2);
  c->tree->Draw("(jteta[1])>>hsubleadingjeteta","abs(jteta[0])<2&&abs(jteta[1])<2","goff");
  
  TH1D * hleadingjetphi = new TH1D("hleadingjetphi",";leading jet #phi",70,-3.5,3.5);
  c->tree->Draw("(jtphi[0])>>hleadingjetphi","abs(jteta[0])<2&&abs(jteta[1])<2","goff");

  TH1D * hsubleadingjetphi = new TH1D("hsubleadingjetphi",";subleading jet #phi",70,-3.5,3.5);
  c->tree->Draw("(jtphi[1])>>hsubleadingjetphi","abs(jteta[0])<2&&abs(jteta[1])<2","goff");
  
  TH1D * hleadingjetpt = new TH1D("hleadingjetpt",";leading jet p_{T}",100,0,300);
  c->tree->Draw("(jtpt[0])>>hleadingjetpt","abs(jteta[0])<2&&abs(jteta[1])<2","goff");

  TH1D * hsubleadingjetpt = new TH1D("hsubleadingjetpt",";subleading jet p_{T}",100,0,300);
  c->tree->Draw("(jtpt[1])>>hsubleadingjetpt","abs(jteta[0])<2&&abs(jteta[1])<2","goff");
  
  TH1D * haj = new TH1D("haj",";Aj",100,0,1);
  c->tree->Draw("(jtpt[0]-jtpt[1])/(jtpt[0]+jtpt[1])>>haj","abs(jteta[0])<2&&abs(jteta[1])<2","goff");
  
  TH1D * hjdphi = new TH1D("hjdphi",";dijet #Delta#phi",65,0,3.5);
  c->LoadNoTrees();
  c->hasAkPu3JetTree = true;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    c->GetEntry(jentry);
    if(fabs(c->akPu3PF->jteta[0])>2 || fabs(c->akPu3PF->jteta[1])>2) continue;
    double dphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    if( dphi > pi ) dphi = 2*pi - dphi;
    hjdphi->Fill(dphi);
  }
  c->ResetBooleans();
  
  TH1D * htrkpt = new TH1D("htrkpt",";trk p_{T}",200,0,200);
  c->tree->Draw("trkPt>>htrkpt","abs(jteta[0])<2&&abs(jteta[1])<2&&(trkAlgo<4||highPurity)&&abs(trkEta)<2.4","goff");
  
  TH1D * htrketa = new TH1D("htrketa",";trk #eta",50,-2.5,2.5);
  c->tree->Draw("trkEta>>htrketa","abs(jteta[0])<2&&abs(jteta[1])<2&&(trkAlgo<4||highPurity)&&abs(trkEta)<2.4","goff");
  
  TH1D * htrkphi = new TH1D("htrkphi",";trk #phi",70,-3.5,3.5);
  c->tree->Draw("trkPhi>>htrkphi","abs(jteta[0])<2&&abs(jteta[1])<2&&(trkAlgo<4||highPurity)&&abs(trkEta)<2.4","goff");
  
  TH1D * hcent = new TH1D("hcent",";centrality",40,0,40);
  c->tree->Draw("hiBin>>hcent","abs(jteta[0])<2&&abs(jteta[1])<2","goff");
  
}


// void makethisstdhists(double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin , float ajmax)
// {
  // TH1D * hthisleadingjeteta = new TH1D(Form("hthisleadingjeteta_trig%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";this leading jet #eta",44,-2.2,2.2);
  // c->tree->Draw(Form("(jteta[0])>>hthisleadingjeteta_trig%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),
                // Form("abs(jteta[0])<%2.1f&&abs(jteta[1])<%2.1f&&jtpt[0]>%2.1f&&jtpt[0]<%2.1f&&jtpt[1]>%2.1f&&jtpt[1]<%2.1f&&hiBin>=%d&&hiBin<%d&&((jtpt[0]-jtpt[1])/(jtpt[0]+jtpt[1]))>%2.1f&&((jtpt[0]-jtpt[1])/(jtpt[0]+jtpt[1]))<%2.1f&&",jet_eta_CUT,jet_eta_CUT,leadingjetptlow,leadingjetpthigh,subleadingjetptlow,subleadingjetpthigh,centmin,centmax,ajmin,ajmax),"goff");

  
  
      // if( fabs(c->evt->vz) > vzrange ) continue;
    // if( c->akPu3PF->nref < 2 )         continue;
    // double dijetdphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    // if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    // if( dijetdphi > dijet_dphi_CUT ) continue;
    // if( fabs(c->akPu3PF->jteta[0]) > jet_eta_CUT || fabs(c->akPu3PF->jteta[1]) > jet_eta_CUT ) continue;
    // if( c->akPu3PF->jtpt[0] > leadingjetpthigh || c->akPu3PF->jtpt[0] < leadingjetptlow ) continue;
    // if( c->akPu3PF->jtpt[1] > subleadingjetpthigh || c->akPu3PF->jtpt[1] < subleadingjetptlow ) continue;
    // double aj = ( c->akPu3PF->jtpt[0] - c->akPu3PF->jtpt[1] ) / ( c->akPu3PF->jtpt[0] + c->akPu3PF->jtpt[1] );
    // if( aj < ajmin || aj > ajmax ) continue;
// }




