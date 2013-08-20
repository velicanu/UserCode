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
  const int nmult   = 4;  
  const int ntrkqual   = 1;  
  
  // const int npt   = 1;
  // const int nmult   = 4;  
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  // double ptlow[] =            {1,  1  ,2  ,3 };
  // double pthigh[] =           {3,  2  ,3  ,4 };

  double nlow[] =            {0,  35  ,90  ,110 };
  double nhigh[] =           {35,  90  ,110  ,1000 };

  
  TFile *file[npt][nmult][ntrkqual];
  TH2D * Sig[nmult][npt][ntrkqual];
  TH2D * Back[nmult][npt][ntrkqual];
  TH2D * Corr[nmult][npt][ntrkqual];
  TH1D * Ntrig[nmult][npt][ntrkqual];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TLatex * ltrackqual[ntrkqual];
  TCanvas *c[nmult][npt][ntrkqual];
  
  // string quality[] = {"GEN","no selection","inverted"};
  string quality[] = {"","no selection","inverted"};
  
  for(int imult = 0; imult < nmult; imult++){
    lmult[imult] = new TLatex(0.01, 0.95, Form("CMS pPb %d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    lmult[imult]->SetNDC(1);
    lmult[imult]->SetTextSize(lmult[imult]->GetTextSize()*1.5);
  }

  for(int imult = 0; imult < nmult; imult++){
    ltrackqual[imult] = new TLatex(0.8, 0.95, Form("%s", quality[imult].data()));
    ltrackqual[imult]->SetNDC(1);
    ltrackqual[imult]->SetTextSize(ltrackqual[imult]->GetTextSize()*1.5);
  }

  for (int ipt = 0; ipt < npt; ipt++){
    lpt[ipt] = new TLatex(0.5, 0.95, Form("%d #leq p_{T} < %d GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lpt[ipt]->SetNDC(1);
    lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.5);
  }
  
  int plotmult = 3;
  int plotpt = 1;
  
  for(int imult = plotmult; imult <= plotmult; imult++){
    for (int ipt = plotpt; ipt <= plotpt; ipt++){
      for(int tqual = 0 ; tqual < ntrkqual ; ++tqual)
      {
        // file[imult][ipt][tqual] = new TFile(Form("input_hists/corrhists_gen_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        file[imult][ipt][tqual] = new TFile(Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_newscale_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        Sig[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Back[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Ntrig[imult][ipt][tqual] = (TH1D*)file[imult][ipt][tqual]->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][tqual] = (TH2D*)Sig[imult][ipt][tqual]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
 
        // file[imult][ipt] = new TFile(Form("input_hists/corrhistsvwei0_trkqaul0_nmin%d_nmax%d_ptmin1_ptmax3.root", (int)nlow[imult], (int)nhigh[imult]));
        // Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][tqual]->Divide(Back[imult][ipt][tqual]);
        
        int x0 = Back[imult][ipt][tqual]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt][tqual]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][tqual]->GetBinContent(x0,y0);
        Corr[imult][ipt][tqual]->Scale(B0/(0.0595*Ntrig[imult][ipt][tqual]->Integral(2,300)));
        Corr[imult][ipt][tqual]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt][tqual]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        double max = Corr[imult][ipt][tqual]->GetMaximum();
        double min = Corr[imult][ipt][tqual]->GetMinimum();
        Corr[imult][ipt][tqual]->SetMaximum(((max+min)/2-min)/(2.3)+min);
        
        c[imult][ipt][tqual] = new TCanvas(Form("c_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]), "", 800, 600);
        Corr[imult][ipt][tqual] ->Draw("Surf1");
        lmult[imult]->Draw("Same");
        lpt[ipt]->Draw("Same");
        ltrackqual[tqual]->Draw("Same");
        c[imult][ipt][tqual]->SaveAs(Form("new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.png", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        // c[imult][ipt][tqual]->SaveAs(Form("single_plots/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.pdf", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        c[imult][ipt][tqual]->SaveAs(Form("ridgePA_2DCF.C"));
        break;
      }
      break;
    }
  break;
  }
}


