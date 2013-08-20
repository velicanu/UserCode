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
#include "/net/hisrv0001/home/dav2105/useful_macros/CF.C"
#include "/net/hisrv0001/home/dgulhan/run/CMSSW_4_4_4/src/UserCode/HiForest/V2/commonUtility.h"

void dplotDebug(){
  TH1D::SetDefaultSumw2();
  const int npt   = 4;
  const int nmult   = 4;  
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  int nlow[] =            {0,   35  ,90   ,110 };
  int nhigh[] =           {35,  90  ,110  ,1000 };
  
  // int nlow[] =            {0,   40  ,100   ,119 };
  // int nhigh[] =           {40,  100  ,119  ,1000 };
  
  // double shift[npt][nmult] = {{0, 0.64, 0.73, 0.75}, {0, 1.79, 2.20, 2.25}, {0, 2.79,3.62,3.73},{0,3.47,4.58,4.74}};


  TFile *file[npt][nmult];
  TH2D * Sig[nmult][npt];
  TH2D * Back[nmult][npt];
  TH2D * Corr[nmult][npt];
  TH1I * Ntrig[nmult][npt];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TCanvas *c[nmult][npt];
  TH1D * ProjSig[nmult][npt];
  TH1D * ProjBack[nmult][npt];
  TH1D * ProjCorr[nmult][npt];
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
      //load and set
	  
      // file[imult][ipt] = new TFile(Form("input_hists/corrhists_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
      // file[imult][ipt] = new TFile(Form("input_hists/corrhists_4gen_trkqaul0_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
      file[imult][ipt] = new TFile(Form("input_hists/corrhists_2fixedscale_trkqaul0_nmin%d_nmax%d_ptmin%d_ptmax%d.root", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
	  cout << "1\n" << endl;
      Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
	  cout << "2\n" << endl;
      Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
	  cout << "3\n" << endl;
      Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
	  cout << "4\n" << endl;
	  int x0 = Back[imult][ipt]->GetXaxis()->FindBin(0.0);
	  int y0 = Back[imult][ipt]->GetYaxis()->FindBin(0.0);
      double B0 = Back[imult][ipt]->GetBinContent(x0,y0);
	  cout << "5\n" << endl;
	  Sig[imult][ipt]->Scale(B0/(0.0595*Ntrig[imult][ipt]->GetBinContent(1)));
	  	  cout << "6\n" << endl;
	  
	  

	   // TH1D* hcorr_phi_weighted = (TH1D*)hcorr_weighted->ProjectionY(Form("corr1D_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  // hcorr_phi_weighted->Scale(1.0/(xmax-xmin+1));
  // TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY(Form("background_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  // hbackground_phi->Scale(1.0/(xmax-xmin+1));
  // hcorr_phi_weighted->Divide(hbackground_phi);
  
	  int xmn = Sig[imult][ipt]->GetXaxis()->FindBin(2);
	  int xmx = Sig[imult][ipt]->GetXaxis()->FindBin(4);
      double nbins = xmx - xmn + 1;
      ProjSig[imult][ipt] = Sig[imult][ipt]->ProjectionY(Form("projsig_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]),xmn,xmx,"e");
      ProjSig[imult][ipt]->Scale(1/nbins);
      ProjBack[imult][ipt] = Back[imult][ipt]->ProjectionY(Form("projback_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]),xmn,xmx,"e");
      ProjBack[imult][ipt]->Scale(1/nbins);
	  ProjCorr[imult][ipt]=(TH1D*)ProjSig[imult][ipt]->Clone(Form("projcorr_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
	  cout<<"7\n"<<endl;
      ProjCorr[imult][ipt]->Divide(ProjBack[imult][ipt]);  

	  //! this part is to shift 
      // double shift = ProjCorr[imult][ipt]->GetMinimum();
	  // int rangedown = ProjCorr[imult][ipt]->FindBin(0);
	  // int rangeup = ProjCorr[imult][ipt]->FindBin(TMath::Pi());
	  
	  // for(int i = rangedown; i < rangeup + 1; i++){
	    // double value = ProjCorr[imult][ipt]->GetBinContent(i);
	    // double error = ProjCorr[imult][ipt]->GetBinError(i);
		   // value = value - shift;
        // ProjCorr[imult][ipt]->SetBinContent(i,value);		
        // ProjCorr[imult][ipt]->SetBinError(i,error);		
	  // }
    
    
      ProjCorr[imult][ipt]->SetAxisRange(0,TMath::Pi());
      ProjCorr[imult][ipt]->SetMarkerColor(2);
      // Proj[imult][ipt]->SetMaximum(1.77);
      // Proj[imult][ipt]->SetMinimum(0);
	  if (ProjCorr[imult][ipt]->GetMaximum() > overallmax) overallmax = ProjCorr[imult][ipt]->GetMaximum();
	  if (ProjCorr[imult][ipt]->GetMinimum() < overallmin) overallmin = ProjCorr[imult][ipt]->GetMinimum();
    }
  }
      
  // TCanvas *c1 = new TCanvas("c1","",1600,1200);
  // Float_t leftMargin=0.14,bottomMargin=0.25;
  // makeMultiPanelCanvas(c1,npt,nmult,0.0,0.0,leftMargin,bottomMargin,0.02);
  
  TFile *outf = new TFile("projections_newscale.root","recreate");
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
     // c1->cd(imult*npt+ipt+1);
     ProjCorr[imult][ipt]->SetMaximum(overallmax+0.01);
     ProjCorr[imult][ipt]->SetMinimum(overallmin-0.01);
     // ProjCorr[imult][ipt]->Draw();
     ProjCorr[imult][ipt]->Write();
     // if(ipt == 0) lmult[imult]->Draw("Same");
     // if(imult==0) lpt[ipt]->Draw("Same");
     // gPad->RedrawAxis();
    }
  }
  outf->Close();
  // c1->SaveAs("projections_debug.png");
}