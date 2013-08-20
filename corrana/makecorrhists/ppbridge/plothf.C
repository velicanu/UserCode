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
#include "/net/hisrv0001/home/dav2105/useful_macros/FitHist.C"


void plothf(){

  const int npt   = 4;
  const int nmult   = 4;  
  const int neta   = 5;  
  const int ntrkqual   = 1;  
  
  // const int npt   = 1;
  // const int nmult   = 4;  
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  3  ,3  ,4 };

  // double ptlow[] =            {1,  1  ,2  ,3 };
  // double pthigh[] =           {3,  2  ,3  ,4 };

  double nlow[] =            {0,  35  ,90  ,190 };
  double nhigh[] =           {35,  90  ,110  ,1000 };
  
  double xaxis[] = {2.5,3.5,4.5,5.5,6.5};
  double xerr[] = {0,0,0,0,0};
  double v2[] = {0,0,0,0,0};
  double v2err[] = {0,0,0,0,0};
  double v3[] = {0,0,0,0,0};
  double v3err[] = {0,0,0,0,0};

  
  TFile *file[npt][nmult][ntrkqual];
  TH2D * Sig[nmult][npt][ntrkqual];
  TH2D * Back[nmult][npt][ntrkqual];
  TH2D * Corr[nmult][npt][ntrkqual];
  TH1D * Ntrig[nmult][npt][ntrkqual];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TLatex * lhfpt[npt];
  TLatex * ltrackqual[ntrkqual];
  TCanvas *c[nmult][npt][ntrkqual];
  TH1D * ProjSig[nmult][npt];
  TH1D * ProjBack[nmult][npt];
  TH1D * ProjCorr[nmult][npt][neta];
  TF1 * f1d_data1[neta];
  
  // string quality[] = {"GEN","no selection","inverted"};
  string quality[] = {"","no selection","inverted"};
  
  for(int imult = 0; imult < nmult; imult++){
    lmult[imult] = new TLatex(0.01, 0.95, Form("CMS pPb %d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    lmult[imult]->SetNDC(1);
    lmult[imult]->SetTextSize(lmult[imult]->GetTextSize()*1.5);
  }

  // for(int imult = 0; imult < nmult; imult++){
    // ltrackqual[imult] = new TLatex(0.8, 0.95, Form("%s", quality[imult].data()));
    // ltrackqual[imult]->SetNDC(1);
    // ltrackqual[imult]->SetTextSize(ltrackqual[imult]->GetTextSize()*1.5);
  // }

  for (int ipt = 0; ipt < npt; ipt++){
    lpt[ipt] = new TLatex(0.01, 0.095, Form("track %d #leq p_{T} < %d GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lpt[ipt]->SetNDC(1);
    lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.5);
  }
  
  for (int ipt = 0; ipt < npt; ipt++){
    lhfpt[ipt] = new TLatex(0.01, 0.03, Form("hf tower 0.25 #leq p_{T} < 3 GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lhfpt[ipt]->SetNDC(1);
    lhfpt[ipt]->SetTextSize(lhfpt[ipt]->GetTextSize()*1.5);
  }
  
  int plotmult = 3;
  int plotpt = 1;
  
  for(int imult = plotmult; imult <= plotmult; imult++){
    for (int ipt = plotpt; ipt <= plotpt; ipt++){
      for(int tqual = 0 ; tqual < ntrkqual ; ++tqual)
      {
        // file[imult][ipt][tqual] = new TFile(Form("input_hists/corrhists_gen_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        // file[imult][ipt][tqual] = new TFile(Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_trkhf_trkqaul0_nmin190_nmax1000_ptmin1_ptmax3.root"));
        // file[imult][ipt][tqual] = new TFile(Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_trkhfplus_trkqaul0_nmin190_nmax1000_ptmin1_ptmax3.root"));
        file[imult][ipt][tqual] = new TFile(Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_trkhfminus_trkqaul0_nmin190_nmax1000_ptmin1_ptmax3.root"));
        Sig[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        Back[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("background_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        Ntrig[imult][ipt][tqual] = (TH1D*)file[imult][ipt][tqual]->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        Corr[imult][ipt][tqual] = (TH2D*)Sig[imult][ipt][tqual]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
      cout<<"here"<<endl;
 
        // file[imult][ipt] = new TFile(Form("input_hists/corrhistsvwei0_trkqaul0_nmin%d_nmax%d_ptmin1_ptmax3.root", (int)nlow[imult], (int)nhigh[imult]));
        // Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        // Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        // Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        // Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin1_cmax1",1,3,0,3));
        Corr[imult][ipt][tqual]->Divide(Back[imult][ipt][tqual]);
        
        int x0 = Back[imult][ipt][tqual]->GetXaxis()->FindBin(4.0);
        int y0 = Back[imult][ipt][tqual]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][tqual]->GetBinContent(x0,y0);
        Corr[imult][ipt][tqual]->Scale(B0/(0.0595*Ntrig[imult][ipt][tqual]->Integral(2,300)));
        Corr[imult][ipt][tqual]->GetXaxis()->SetRangeUser(1,7);
        Corr[imult][ipt][tqual]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        double max = Corr[imult][ipt][tqual]->GetMaximum();
        double min = Corr[imult][ipt][tqual]->GetMinimum();
        // Corr[imult][ipt][tqual]->SetMaximum(((max+min)/2-min)/(2.3)+min);
        for(int ieta = 0 ; ieta < neta ; ++ieta)
        {
          
          int xmn = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(ieta+2);
          int xmx = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(ieta+3);
          cout<<"min: "<<xmn<<" max: "<<xmx<<endl;
          double nbins = xmx - xmn + 1;
          ProjCorr[imult][ipt][ieta] = Corr[imult][ipt][tqual]->ProjectionY(Form("projcorr_nmin%d_nmax%d_ptmin%d_ptmax%d_ieta_%d_%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt],ieta+2,ieta+3),xmn,xmx,"e");
          ProjCorr[imult][ipt][ieta]->Scale(1/nbins);
        }
        
        c[imult][ipt][tqual] = new TCanvas(Form("c_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]), "", 600, 600);
        Corr[imult][ipt][tqual] ->Draw("Surf1");
        lmult[imult]->Draw("Same");
        lpt[ipt]->Draw("Same");
        lhfpt[ipt]->Draw("Same");
        c[imult][ipt][tqual]->SetTheta(60.839);
        c[imult][ipt][tqual]->SetPhi(38.0172);
        // ltrackqual[tqual]->Draw("Same");
        // c[imult][ipt][tqual]->SaveAs("trk-hf-cf-plus.png");
        // c[imult][ipt][tqual]->SaveAs(Form("new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.png", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        // c[imult][ipt][tqual]->SaveAs(Form("single_plots/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.pdf", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        // c[imult][ipt][tqual]->SaveAs(Form("ridgePA_2DCF.C"));
        
        TCanvas * can = new TCanvas("can");
        // TH2D * dummy = new TH2D("dummy",";#Delta#phi",1,0,TMath::Pi(),1,2.95,3.15);
        // TH2D * dummy = new TH2D("dummy",";#Delta#phi",1,0,TMath::Pi(),1,0.74,0.78);
        TH2D * dummy = new TH2D("dummy",";#Delta#phi",1,0,TMath::Pi(),1,2.22,2.37);
        dummy->GetXaxis()->CenterTitle();
        dummy->GetYaxis()->CenterTitle();
        
        dummy->Draw();
        
        for(int ieta = 0 ; ieta < neta ; ++ieta)
        {
          ProjCorr[imult][ipt][ieta]->Draw("same");
          f1d_data1[ieta] = addFitToCanvas(ProjCorr[imult][ipt][ieta],5);
          f1d_data1[ieta]->Draw("same");
          v2[ieta]    = f1d_data1[ieta]->GetParameter(2);
          v2err[ieta] = f1d_data1[ieta]->GetParError(2);
          v3[ieta]    = f1d_data1[ieta]->GetParameter(3);
          v3err[ieta] = f1d_data1[ieta]->GetParError(3);
        }
        
        
        TGraphErrors * gv2 = new TGraphErrors(5,xaxis,v2,xerr,v2err);
        TGraphErrors * gv3 = new TGraphErrors(5,xaxis,v3,xerr,v3err);
      
        
        // TLatex * leta1 = new TLatex(0,3.1,"2<|#Delta#eta|<3");
        // TLatex * leta1 = new TLatex(0,0.76,"2<|#Delta#eta|<3");
        TLatex * leta1 = new TLatex(0,2.35,"2<|#Delta#eta|<3");
        leta1->SetTextSize(leta1->GetTextSize()*1.5);
        leta1->Draw("same");
        // TLatex * leta2 = new TLatex(0,3,"6<|#Delta#eta|<7");
        // TLatex * leta2 = new TLatex(0,0.745,"6<|#Delta#eta|<7");
        TLatex * leta2 = new TLatex(0,2.24,"6<|#Delta#eta|<7");
        leta2->SetTextSize(leta2->GetTextSize()*1.5);
        leta2->Draw("same");
        
        TCanvas * can1 = new TCanvas("can1");
        TH2D * dummy_vn = new TH2D("dummy_vn",";#Delta#eta;",1,1,8,1,0,0.008);
        dummy_vn->GetXaxis()->CenterTitle();
        dummy_vn->GetYaxis()->CenterTitle();
        dummy_vn->Draw();
        gv2->Draw("PEsame");
        gv3->SetMarkerColor(kRed);
        gv3->Draw("PEsame");
        
        
        TLegend * leg2 = new TLegend(0.33,0.48,0.87,0.68);
        leg2->SetFillColor(0);
        leg2->SetTextSize(0.07);
        leg2->SetFillStyle(0);
        leg2->SetTextFont(42);
        leg2->AddEntry(gv2,Form("V_{%d#Delta} ",2),"p");
        leg2->AddEntry(gv3,Form("V_{%d#Delta} ",3),"p");
        leg2->Draw("same");
        
        c[imult][ipt][tqual]->SaveAs("hfminus-2d.png");
        can->SaveAs("hfminus-proj.png");
        can1->SaveAs("hfminus-vn.png");
        
        break;
      }
      break;
    }
  break;
  }
}


