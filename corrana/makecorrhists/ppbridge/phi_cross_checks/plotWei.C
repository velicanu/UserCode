// #include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
// #include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"
// #include "/net/hisrv0001/home/davidlw/useful_macros/DrawTick.C"
// #include "/net/hisrv0001/home/davidlw/useful_macros/GetGraphFromFile.C"
#include "TStyle.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "/net/hisrv0001/home/davidlw/useful_macros/Histograms.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"
//#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvasNew.C"
#include <fstream>

void plotWei()
{
  TString pttitle[4]={"0.1 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c"};
  TString ntitle[4]={"N<35","35 #leq N<90","90 #leq N<110","N #geq 110"};

  TCanvas* c = new TCanvas("c","",1000,800);
  makeMultiPanelCanvas(c,4,4,0.02,0.02,0.2,0.2,0.01);

  // TFile* fout_pPb = new TFile("results_INCLEFF1v4_4nbins.root");
  // TFile* fout_pPb = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_4_4_2_patch5_correlations/src/WeisQCDAna/DiHadronCorrelationAnalyzer/test/macros/flow_pp/results_INCLEFF1v4_4nbins.root");
  TFile* fout_pPb = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_4_4_2_patch5_correlations/src/WeisQCDAna/DiHadronCorrelationAnalyzer/test/macros/flow_pp/results_INCLv7_4nbins.root");
  // TFile* fout_pp = new TFile("results_pp_zyam.root");
  TFile* fout_pp = new TFile("projections.root");

  double ymin=0;
  double ymax=0;
  TH1D* h[4][4];
  TH1D* h_pp[4][4];
  TLatex* xlatex[4];
  TLatex* ylatex[4];
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  double nlow[] =            {0,   35  ,90   ,110 };
  double nhigh[] =           {35,  90  ,110  ,1000 };
  
  double PI=TMath::Pi();
  for(int ihist=0;ihist<4;ihist++)
    for(int iptbin=0;iptbin<4;iptbin++)
    {
      c->cd(ihist*4+iptbin+1); 
      h[ihist][iptbin]=(TH1D*)fout_pPb->Get(Form("corr_zyam_%d_%d",ihist,iptbin));
      h[ihist][iptbin]->SetMarkerColor(kRed);
      h_pp[ihist][iptbin]=(TH1D*)fout_pp->Get(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d",(int)nlow[ihist],(int)nhigh[ihist],(int)ptlow[iptbin],(int)pthigh[iptbin]));
      h_pp[ihist][iptbin]->SetMarkerStyle(24);
      if(iptbin==0)
      {
        ymin=-0.015;
        ymax=h[ihist][iptbin]->GetMaximum()*1.6;
      }
      if(ihist==0) h[ihist][iptbin]->SetAxisRange(ymin,ymax*1.3,"Y");
      else h[ihist][iptbin]->SetAxisRange(ymin,ymax,"Y");
      h[ihist][iptbin]->Draw("PE");

      // HistogramScaleShift(h_pp[ihist][iptbin],(2*PI)*4.8,0);      
     // h_pp->Scale((2*PI)*4.8);
	 h_pp[ihist][iptbin]->Draw("PESAME");

      if(ihist==0)
      {
        xlatex[iptbin] = new TLatex();
        xlatex[iptbin]->SetNDC();
        if(iptbin==0) xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        else xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        if(iptbin==0) xlatex[iptbin]->DrawLatex(0.25,0.8,pttitle[iptbin]);
        else xlatex[iptbin]->DrawLatex(0.15,0.85,pttitle[iptbin]);
      }

      if(iptbin==0)
      {
        ylatex[ihist] = new TLatex();
        ylatex[ihist]->SetNDC();
        if(ihist==0) ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        else ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        ylatex[ihist]->DrawLatex(0.25,0.7,ntitle[ihist]);
      }
    }      

  // SaveCanvas(c,"pPb/corr","corr1Ddphi_4by4_paper");
  c->SaveAs("WeiPlot.png");
}
