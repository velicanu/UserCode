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
// double jet_eta_CUT = 2.0;
int cent_index_start[41];

HiForest *c;
TH1D * hjetpt;
// TH1D * GetNtrk(int centmin, int centmax);
TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin = 0.0, float ajmax = 1.0 , int doeffweight = 0 , int mccommand = 0, double jetamin = 0.0, double jetamax = 2.0, double vzrange = 15, double dijetdphicut = 2 * pi / 3.0);
TH2D * JetTrackBackground(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin = 0.0, float ajmax = 1.0 , int doeffweight = 0 , int mccommand = 0, double jetamin = 0.0, double jetamax = 2.0, double vzrange = 15, double dijetdphicut = 2 * pi / 3.0, int statfactor = 20);
TH1D * JetPtDistribution();
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
  c->doTrackCorrections = true;
  c->doTrackingSeparateLeadingSubleading = false;
  c->InitTree();
  
  cent_index_start[40] = nentries;
  cout<<"done building centrality index"<<endl;
}


TH2D * JetTrackSignal(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin , float ajmax , int doeffweight , int mccommand , double jetamin , double jetamax , double vzrange, double dijetdphicut)
{
  if(mccommand>0 && mccommand%2==0)  doeffweight=0;
  TH2D::SetDefaultSumw2(true);
  c->LoadNoTrees();
  c->hasEvtTree = true;
  c->hasHltTree = true;
  c->hasTrackTree = true;
  c->hasAkPu3JetTree = true;
  c->hasSkimTree = true;

  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D * hJetTrackSignal;
  cout<<"before first exit"<<endl;
  // if(jetindex==0) //leading jet
  // {
    
    hJetTrackSignal = new TH2D(Form("signal_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100*3,-5,5,75*3,-pi,2*pi);
    hjetpt = new TH1D(Form("jetpt_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",(int)(leadingjetpthigh-leadingjetptlow),leadingjetptlow,leadingjetpthigh);
  // }
  // else if(jetindex==1) //subleading jet
  // {
    // hJetTrackSignal = new TH2D(Form("signal_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100*3,-5,5,75*3,-pi,2*pi);
  // }
  // else //leading jet
  // {
    // cout<<"Error: only jetindex 0 and 1 currently supported (leading + subleading jet)"<<endl;
    // exit(1);
  // }
  
  double ntottrig = 0;
  int n_entries_in_cent_range = cent_index_start[centmax] - cent_index_start[centmin];


  cout<<"before event for loop "<<n_entries_in_cent_range<<endl;
  // for (Long64_t jentry=0; jentry<10000;jentry++) {
  for (Long64_t jentry=cent_index_start[centmin]; jentry<cent_index_start[centmax];jentry++) {
    if(jentry%1000==0) cout<<jentry-cent_index_start[centmin]<<"/"<<n_entries_in_cent_range<<endl;
    c->GetEntry(jentry);
    
    //! jet cuts, vz range, more than 2 jettss, dijetdphi 7/8 pi, both jet |eta| < 2, pt range cuts, aj cuts
    // cout<<mccommand<<endl;
    if(mccommand==0)
    {
      if(!c->selectEvent()) continue; 
      if(!c->hlt->HLT_HIJet80_v1) continue; 
    }
    if( fabs(c->evt->vz) > vzrange ) continue;
    // if( c->akPu3PF->nref < 2 )         continue;
    // double dijetdphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    // if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    // if( dijetdphi > dijet_dphi_CUT ) continue;
    int jetindex = -1;
    while(true)
    {
      // cout<<"here"<<endl;
      jetindex++;
      if( jetindex == c->akPu3PF->nref ) break;
      if( c->akPu3PF->jtpt[jetindex] > leadingjetpthigh ) continue;
      if( c->akPu3PF->jtpt[jetindex] < leadingjetptlow ) break;
      if( fabs(c->akPu3PF->jteta[jetindex]) > jetamax || fabs(c->akPu3PF->jteta[jetindex]) < jetamin ) continue;
      if ((c->akPu3PF->trackMax[jetindex]/c->akPu3PF->jtpt[jetindex])<0.01) continue;
      // if(jentry%1000==0) cout<<"here"<<endl;
      
      double jeteta = c->akPu3PF->jteta[jetindex];
      double jetphi = c->akPu3PF->jtphi[jetindex];
      double jetpt = c->akPu3PF->jtpt[jetindex];
      
      int ntrig = 1 , nass = 0;
      
      vector<double> asstrkEta;
      vector<double> asstrkPhi;
      vector<double> asstrkPt;
      vector<double> asstrkIndex;
      if(mccommand<2)
      {
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
      }
      else
      {
        for(int j = 0 ; j < c->track->nParticle ; ++j)
        {
          if( c->track->pPt[j]<ptasslow || c->track->pPt[j]>ptasshigh || fabs(c->track->pEta[j])>maxetaass) continue;
          ++nass;
          asstrkEta.push_back(c->track->pEta[j]);
          asstrkPhi.push_back(c->track->pPhi[j]);
          asstrkPt.push_back(c->track->pPt[j]);
          asstrkIndex.push_back(j);
        }
      }
      
      for(int i = 0 ; i < ntrig ; ++i)
      {
        hjetpt->Fill(jetpt);
        ntottrig += 1;
        for(int j = 0 ; j < nass ; ++j)
        {
          double deta = fabs(jeteta-asstrkEta[j]);
          double dphi = fabs(jetphi-asstrkPhi[j]);
          // double ptw = asstrkPt[j];
          if( dphi > pi ) dphi = 2*pi - dphi;
          double effweight = 1;
          if(doeffweight!=0) effweight = c->getTrackCorrection(asstrkIndex[j]);
          // if(jentry%1000==0) cout<<effweight<<endl;
          // {
            hJetTrackSignal->Fill(deta,dphi,effweight);
            hJetTrackSignal->Fill(-deta,dphi,effweight);
            hJetTrackSignal->Fill(deta,-dphi,effweight);
            hJetTrackSignal->Fill(-deta,-dphi,effweight);
            hJetTrackSignal->Fill(deta,(2*pi)-dphi,effweight);
            hJetTrackSignal->Fill(-deta,(2*pi)-dphi,effweight);
          // }
          // else
          // {
            // hJetTrackSignal->Fill(deta,dphi,effweight);
            // hJetTrackSignal->Fill(-deta,dphi,effweight);
            // hJetTrackSignal->Fill(deta,-dphi,effweight);
            // hJetTrackSignal->Fill(-deta,-dphi,effweight);
            // hJetTrackSignal->Fill(deta,(2*pi)-dphi,effweight);
            // hJetTrackSignal->Fill(-deta,(2*pi)-dphi,effweight);
          // }
        }
      }
    }

    // if(jentry>100) break;
  }
  // if( ntottrig != 0 ) hJetTrackSignal->Scale(1/ntottrig);
  c->ResetBooleans();
  return hJetTrackSignal;
}


TH2D * JetTrackBackground(int jetindex, double leadingjetptlow , double leadingjetpthigh , double subleadingjetptlow , double subleadingjetpthigh , double ptasslow , double ptasshigh, int centmin, int centmax, float ajmin , float ajmax , int doeffweight , int mccommand , double jetamin , double jetamax , double vzrange, double dijetdphicut, int statfactor )
{
  if(mccommand==2)  doeffweight=0;
  Long64_t nentries = c->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  TH2D::SetDefaultSumw2(true);
  TH2D * hJetTrackBackground;
  if(jetindex==0) //leading jet
  {
    hJetTrackBackground = new TH2D(Form("background_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100*3,-5,5,75*3,-pi,2*pi);
  }
  else if(jetindex==1) //subleading jet
  {
    hJetTrackBackground = new TH2D(Form("background_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow,(int)leadingjetpthigh,(int)ptasslow,(int)ptasshigh,centmin,centmax,(int)(ajmin*100),(int)(ajmax*100)),";#Delta#eta;#Delta#phi",100*3,-5,5,75*3,-pi,2*pi);
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
    if(mccommand==0)
    {
      if(!c->selectEvent()) continue; 
      if(!c->hlt->HLT_HIJet80_v1) continue; 
    }
    if( fabs(c->evt->vz) > vzrange ) continue;
    // if( c->akPu3PF->nref < 2 )         continue;
    // double dijetdphi = fabs(c->akPu3PF->jtphi[0] - c->akPu3PF->jtphi[1]);
    // if( dijetdphi > pi ) dijetdphi = 2*pi - dijetdphi;
    // if( dijetdphi > dijet_dphi_CUT ) continue;
    int jetindex = -1;
    while(true)
    {
      jetindex++;
      if( jetindex == c->akPu3PF->nref ) break;
      if( c->akPu3PF->jtpt[jetindex] > leadingjetpthigh ) continue;
      if( c->akPu3PF->jtpt[jetindex] < leadingjetptlow ) break;
      if( fabs(c->akPu3PF->jteta[jetindex]) > jetamax || fabs(c->akPu3PF->jteta[jetindex]) < jetamin ) continue;
      if ((c->akPu3PF->trackMax[jetindex]/c->akPu3PF->jtpt[jetindex])<0.01) continue;
      
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
        if(mccommand<2)
        {
          for(int j = 0 ; j < c->track->nTrk ; ++j)
          {
            if( c->track->trkPt[j]<ptasslow || c->track->trkPt[j]>ptasshigh || fabs(c->track->trkEta[j])>maxetaass) continue;
            if( c->track->trkAlgo[j]<4 || c->track->highPurity[j])
            {
              double deta = fabs(thisjeteta - c->track->trkEta[j]);
              double dphi = fabs(thisjetphi - c->track->trkPhi[j]);
              // double effweight = c->getTrackCorrection(j);
              if( dphi > pi ) dphi = 2*pi - dphi;
              double effweight = 1;
              if(doeffweight!=0) effweight = c->getTrackCorrection(j);
              
              hJetTrackBackground->Fill(deta,dphi,effweight);
              hJetTrackBackground->Fill(-deta,dphi,effweight);
              hJetTrackBackground->Fill(deta,-dphi,effweight);
              hJetTrackBackground->Fill(-deta,-dphi,effweight);
              hJetTrackBackground->Fill(deta,(2*pi)-dphi,effweight);
              hJetTrackBackground->Fill(-deta,(2*pi)-dphi,effweight);
              fillcount++;
            }
          }
        }
        else
        {
          for(int j = 0 ; j < c->track->nParticle ; ++j)
          {
            if( c->track->pPt[j]<ptasslow || c->track->pPt[j]>ptasshigh || fabs(c->track->pEta[j])>maxetaass) continue;
            double deta = fabs(thisjeteta - c->track->pEta[j]);
            double dphi = fabs(thisjetphi - c->track->pPhi[j]);
            // double effweight = c->getTrackCorrection(j);
            if( dphi > pi ) dphi = 2*pi - dphi;
            if(doeffweight==0)
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
              // hJetTrackBackground->Fill(deta,dphi,effweight);
              // hJetTrackBackground->Fill(-deta,dphi,effweight);
              // hJetTrackBackground->Fill(deta,-dphi,effweight);
              // hJetTrackBackground->Fill(-deta,-dphi,effweight);
              // hJetTrackBackground->Fill(deta,(2*pi)-dphi,effweight);
              // hJetTrackBackground->Fill(-deta,(2*pi)-dphi,effweight);
            }
            fillcount++;
          }
        }
      }
    }
  }
  c->ResetBooleans();
  return hJetTrackBackground;
}


TH1D * JetPtDistribution()
{
  return hjetpt;
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

