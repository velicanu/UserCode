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
#include "TProfile.h"
#include "/net/hisrv0001/home/dgulhan/run/CMSSW_4_4_4/src/UserCode/HiForest/V2/commonUtility.h"

void dplotDragos(){
  TH1D::SetDefaultSumw2();
  const int npt   = 4;
  const int nmult   = 4;  
  
  double ptlow[] =            {0,  1  ,2  ,3, 1 };
  double pthigh[] =           {1,  2  ,3  ,4, 3 };

  double nlow[] =            {0,   35  ,90   ,110 };
  double nhigh[] =           {35,  90  ,110  ,1000 };
  
  // double nlow[] =            {0,   40  ,100   ,119 };
  // double nhigh[] =           {40,  100  ,119  ,1000 };
  
  // double shift[npt][nmult] = {{0, 0.64, 0.73, 0.75}, {0, 1.79, 2.20, 2.25}, {0, 2.79,3.62,3.73},{0,3.47,4.58,4.74}};


  TFile *file[npt][nmult];
  TH2D * Sig[nmult][npt];
  TH2D * Back[nmult][npt];
  TH2D * Corr[nmult][npt];
  TH1I * Ntrig[nmult][npt];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TCanvas *c[nmult][npt];
  TH1D * Proj[nmult][npt];
  // TProfile * Proj[nmult][npt];
  double overallmax = -100;
  double overallmin = 100;
  
  for(int imult = 0; imult < nmult; imult++){
    lmult[imult] = new TLatex(0.2, 0.80, Form("%d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    lmult[imult]->SetNDC(1);
    lmult[imult]->SetTextSize(lmult[imult]->GetTextSize()*1.5);
  }

  for (int ipt = 0; ipt < npt; ipt++){
    lpt[ipt] = new TLatex(0.2, 0.90, Form("%d #leq p_{T} < %d GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    lpt[ipt]->SetNDC(1);
    lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.5);
  }
  
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      for(int tqual = 0 ; tqual < 1 ; ++tqual)
      {
        
        //load and set
        // cout<<Form("input_hists/corrhists_trkqual%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        // cout<<Form("input_hists/corrhistsvwei3_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        cout<<Form("input_hists/corrhists_2fixedscale_trkqaul0_nmin%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        // file[imult][ipt] = new TFile(Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_tutorial_trkqaul0_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        file[imult][ipt] = new TFile(Form("input_hists/corrhists_2fixedscale_trkqaul0_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        
        Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Clone(Form("correlation_nmin%d_nmax%d_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt]->Divide(Back[imult][ipt]);
        cout<<"after corr "<<imult<<" "<<ipt<<" "<<tqual<<endl;
        int x0 = Back[imult][ipt]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt]->GetYaxis()->FindBin(0.0);
        float dx = Sig[imult][ipt]->GetXaxis()->GetBinWidth(1);
        float dy = Sig[imult][ipt]->GetYaxis()->GetBinWidth(1);
        double B0 = Back[imult][ipt]->GetBinContent(x0,y0);
        Corr[imult][ipt]->Scale(B0/(dx*dy*Ntrig[imult][ipt]->Integral(2,300)));
        cout<<Ntrig[imult][ipt]->Integral(2,300)<<endl;
        // Corr[imult][ipt]->Scale(B0/(0.0595*Ntrig[imult][ipt]->GetBinContent(1)));
        Corr[imult][ipt]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        int xmn = Corr[imult][ipt]->GetXaxis()->FindBin(2);
        int xmx = Corr[imult][ipt]->GetXaxis()->FindBin(4);
        double nbins = xmx - xmn + 1;
        Proj[imult][ipt] = Corr[imult][ipt]->ProjectionY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]),xmn,xmx,"e");
        Proj[imult][ipt]->Scale(1/nbins);
        // Proj[imult][ipt]->Scale(1/2.); //divide by eta range we project on since this is an average
        // Proj[imult][ipt] = Corr[imult][ipt]->ProfileY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]),xmn,xmx);
        // double shift = Proj[imult][ipt]->GetMinimum();
        // int rangedown = Proj[imult][ipt]->FindBin(0);
        // int rangeup = Proj[imult][ipt]->FindBin(TMath::Pi());
        
        // for(int i = rangedown; i < rangeup + 1; i++){
          // double value = Proj[imult][ipt]->GetBinContent(i);
          // double error = Proj[imult][ipt]->GetBinError(i);
          // value = value - shift;
          // Proj[imult][ipt]->SetBinContent(i,value);		
          // Proj[imult][ipt]->SetBinError(i,error);		
        // } 
        
        
        Proj[imult][ipt]->SetAxisRange(0,TMath::Pi());
        Proj[imult][ipt]->SetMarkerColor(2);
        // Proj[imult][ipt]->SetMaximum(1.77);
        // Proj[imult][ipt]->SetMinimum(0);
        if (Proj[imult][ipt]->GetMaximum() > overallmax) overallmax = Proj[imult][ipt]->GetMaximum();
        if (Proj[imult][ipt]->GetMinimum() < overallmin) overallmin = Proj[imult][ipt]->GetMinimum();
      }
    }
  }
  
  // TCanvas *c1 = new TCanvas("c1","",1400,900);
  // Float_t leftMargin=0.14,bottomMargin=0.25;
  // makeMultiPanelCanvas(c1,npt,nmult,0.0,0.0,leftMargin,bottomMargin,0.02);
  
  TFile *outf = new TFile("projections_new.root","recreate");
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      // c1->cd(imult*npt+ipt+1);
      // Proj[imult][ipt]->SetMaximum(overallmax+0.01);
      // Proj[imult][ipt]->SetMinimum(overallmin-0.01);
      // Proj[imult][ipt]->Draw();
      Proj[imult][ipt]->Write();
      Corr[imult][ipt]->Write();
      // if(ipt == 0) lmult[imult]->Draw("Same");
      // if(imult==0) lpt[ipt]->Draw("Same");
      // gPad->RedrawAxis();
    }
  }
  outf->Close();
  // c1->SaveAs("projections.png");
}