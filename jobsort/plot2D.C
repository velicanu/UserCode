#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TF2.h"
#include "TF1.h"
#include "TMath.h"
#include "TAttMarker.h"
#include "TH2D.h"
#include "TCanvas.h" 
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TLegend.h"
#include "/net/hisrv0001/home/dgulhan/run/CMSSW_4_4_4/src/UserCode/HiForest/V2/commonUtility.h"

void plot2D(){

  const int npt   = 4;
  const int nmult   = 3;  
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  // double nlow[] =            {0,  35  ,90  ,110 };
  double nlow[] =            {0,  35  ,110 };
  // double nhigh[] =           {35,  90  ,110  ,1000 };
  double nhigh[] =           {35,  90 ,1000 };
   
  TFile *file[npt][nmult];
  TH2D * Sig[nmult][npt];
  TH2D * Back[nmult][npt];
  TH2D * Corr[nmult][npt];
  TH1D * Ntrig[nmult][npt];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TCanvas *c[nmult][npt];
    
  for(int imult = 0; imult < nmult; imult++){
    lmult[imult] = new TLatex(0.01, 0.95, Form("CMS pPb %d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    lmult[imult]->SetNDC(1);
    lmult[imult]->SetTextSize(lmult[imult]->GetTextSize()*1.5);
  }
 
  for (int ipt = 0; ipt < npt; ipt++){
    lpt[ipt] = new TLatex(0.5, 0.95, Form("%d #leq p_{T} < %d GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lpt[ipt]->SetNDC(1);
    lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.5);
  }
  
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      file[imult][ipt] = new TFile(Form("input_hists/corrhists_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
      Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
      Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
      Ntrig[imult][ipt] = (TH1D*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
	  Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Divide(Back[imult][ipt]);
      int x0 = Back[imult][ipt]->GetXaxis()->FindBin(0);
	  int y0 = Back[imult][ipt]->GetYaxis()->FindBin(0);
      double B0 = Back[imult][ipt]->GetBinContent(x0,y0);
	  Corr[imult][ipt]->Scale(B0/Ntrig[imult][ipt]->GetBinContent(1));
	  double max = Corr[imult][ipt]->GetMaximum();
      double min = Corr[imult][ipt]->GetMinimum();
      Corr[imult][ipt]->SetMaximum(((max+min)/2-min)/(2.3)+min);
      c[imult][ipt] = new TCanvas(Form("c_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]), "", 800, 600);
      Corr[imult][ipt] ->Draw("Surf1");
      lmult[imult]->Draw("Same");
      lpt[ipt]->Draw("Same");
      c[imult][ipt]->SaveAs(Form("single_plots/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d.png", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
    }
  }

    
}