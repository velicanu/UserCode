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
#include "TStyle.h"

void plot2D(){
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetPalette(1,0);

  const int npt   = 4;
  const int nmult   = 4;  
  const int ntrkqual   = 1;
  const int nphi = 8;
  
  // const int npt   = 1;
  // const int nmult   = 4;  
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  // double ptlow[] =            {1,  1  ,2  ,3 };
  // double pthigh[] =           {3,  2  ,3  ,4 };

  double nlow[] =            {0,  35  ,90  ,110 };
  double nhigh[] =           {35,  90  ,110  ,1000 };
  

  
  TFile *file[npt][nmult][ntrkqual][nphi];
  TH2D * Sig[nmult][npt][ntrkqual][nphi];
  TH2D * Back[nmult][npt][ntrkqual][nphi];
  TH2D * Corr[nmult][npt][ntrkqual][nphi];
  TH1I * Ntrig[nmult][npt][ntrkqual][nphi];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  //TLatex * ltrackqual[ntrkqual];
  TLatex * lphibin[nphi];
  TCanvas *c[nmult][npt][ntrkqual][nphi];
  
  string quality[] = {"quality","no selection","inverted"};
  string phi_range[] = {"-#pi#leq#phi_{1}<-3#pi/4","-3#pi/4#leq#phi_{1}<-#pi/2","-#pi/2#leq#phi_{1}<-#pi/4","-#pi/4#leq#phi_{1}<0", "0#leq#phi_{1}<#pi/4","#pi/4#leq#phi_{1}<#pi/2","#pi/2#leq#phi_{1}<3#pi/4","3#pi/4#leq#phi_{1}<#pi"};
  
  for(int imult = 0; imult < nmult; imult++){
    lmult[imult] = new TLatex(0.01, 0.95, Form("CMS pPb %d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    lmult[imult]->SetNDC(1);
    //lmult[imult]->SetTextSize(lmult[imult]->GetTextSize()*1.);
  }
/*
  for(int imult = 0; imult < nmult; imult++){
    ltrackqual[imult] = new TLatex(0.8, 0.95, Form("%s", quality[imult].data()));
    ltrackqual[imult]->SetNDC(1);
    ltrackqual[imult]->SetTextSize(ltrackqual[imult]->GetTextSize()*1.);
  }
*/
  for(int iphi = 0; iphi < nphi; ++iphi){
    lphibin[iphi] = new TLatex(0.8, 0.95, phi_range[iphi].data());
	lphibin[iphi]->SetNDC(1);
	//lphibin[iphi]->SetTextSize(ltrackqual[imult]->GetTextSize()*1.);
  }

  for (int ipt = 0; ipt < npt; ipt++){
    lpt[ipt] = new TLatex(0.5, 0.95, Form("%d #leq p_{T} < %d GeV/c", (int)ptlow[ipt], (int)pthigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lpt[ipt]->SetNDC(1);
    //lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.);
  }
  for(int iphi = 0; iphi < nphi; ++iphi){
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      for(int tqual = 0 ; tqual < ntrkqual ; ++tqual)
      {
        file[imult][ipt][tqual][iphi] = new TFile(Form("./merged/corrhists_trkqual%d_nmin%d_nmax%d_ptmin%d_ptmax%d_phibin%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt],iphi));
        Sig[imult][ipt][tqual][iphi] = (TH2D*)file[imult][ipt][tqual][iphi]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Back[imult][ipt][tqual][iphi] = (TH2D*)file[imult][ipt][tqual][iphi]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Ntrig[imult][ipt][tqual][iphi] = (TH1I*)file[imult][ipt][tqual][iphi]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][tqual][iphi] = (TH2D*)Sig[imult][ipt][tqual][iphi]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41_phi%d",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt],iphi));
 
        // file[imult][ipt] = new TFile(Form("input_hists/corrhistsvwei0_trkqaul0_nmin%d_nmax%d_ptmin1_ptmax3.root", (int)nlow[imult], (int)nhigh[imult]));
        // Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][tqual][iphi]->Divide(Back[imult][ipt][tqual][iphi]);
		Corr[imult][ipt][tqual][iphi]->SetStats(0);
        
        int x0 = Back[imult][ipt][tqual][iphi]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt][tqual][iphi]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][tqual][iphi]->GetBinContent(x0,y0);
        Corr[imult][ipt][tqual][iphi]->Scale(B0/(0.0595*Ntrig[imult][ipt][tqual][iphi]->GetBinContent(1)));
        Corr[imult][ipt][tqual][iphi]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt][tqual][iphi]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        double max = Corr[imult][ipt][tqual][iphi]->GetMaximum();
        double min = Corr[imult][ipt][tqual][iphi]->GetMinimum();
        Corr[imult][ipt][tqual][iphi]->SetMaximum(((max+min)/2-min)/(2.3)+min);
        
        c[imult][ipt][tqual][iphi] = new TCanvas(Form("c_nmin%d_nmax%d_ptmin%d_ptmax%d_phibin%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt],iphi), "", 800, 600);
        Corr[imult][ipt][tqual][iphi] ->Draw("Surf1");
        lmult[imult]->Draw("Same");
        lpt[ipt]->Draw("Same");
        lphibin[iphi]->Draw("Same");
        c[imult][ipt][tqual][iphi]->SaveAs(Form("single_plots/phi%d/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.png", iphi,(int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        //c[imult][ipt][tqual]->SaveAs(Form("single_plots/phi%d/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.pdf", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual,iphi));
      }
    }
  }
  }
  cout << "the end\n";
}