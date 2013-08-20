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
#include "TStyle.h"

using namespace std;

void SetDataStyle(TH1D *data_hist, const char* x_title="", const char* y_title="",Float_t label_size = 0.04)
{
	data_hist->SetLineColor(1);
	data_hist->SetLineWidth(2);
	data_hist->SetMarkerStyle(20);
	data_hist->SetStats(false);
	data_hist->GetXaxis()->SetTitle(x_title);
	data_hist->GetXaxis()->SetLabelSize(label_size);
	data_hist->GetYaxis()->SetTitle(y_title);
	data_hist->GetYaxis()->SetLabelSize(label_size);
	data_hist->GetYaxis()->SetTitleOffset(1.15);
	//data_hist->SetTitle(title);
}

void plot1D(){
  

  
  // For publishing:
  //gStyle->SetLineWidth(2.);
  //gStyle->SetTextSize(1.1);
  //gStyle->SetLabelSize(0.05,"xy");
  //gStyle->SetTitleSize(0.05,"xy");
  //gStyle->SetTitleOffset(0.9,"x");
  //gStyle->SetTitleOffset(0.5,"y");
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleFillColor(0);
  //gStyle->SetPadTopMargin(0.07);
  //gStyle->SetPadRightMargin(0.03);
  //gStyle->SetPadBottomMargin(0.11);
  //gStyle->SetPadLeftMargin(0.12);


  TH1D::SetDefaultSumw2();
  const int npt   = 4;
  const int nmult   = 4;  
  const int nphi = 8;
  
  double ptlow[] =            {0,  1  ,2  ,3 };
  double pthigh[] =           {1,  2  ,3  ,4 };

  double nlow[] =            {0,   35  ,90   ,110 };
  double nhigh[] =           {35,  90  ,110  ,1000 };
  
  // double shift[npt][nmult] = {{0, 0.64, 0.73, 0.75}, {0, 1.79, 2.20, 2.25}, {0, 2.79,3.62,3.73},{0,3.47,4.58,4.74}};
  string phi_range[] = {"-#pi#leq#phi_{1}<-3#pi/4","-3#pi/4#leq#phi_{1}<-#pi/2","-#pi/2#leq#phi_{1}<-#pi/4","-#pi/4#leq#phi_{1}<0", "0#leq#phi_{1}<#pi/4","#pi/4#leq#phi_{1}<#pi/2","#pi/2#leq#phi_{1}<3#pi/4","3#pi/4#leq#phi_{1}<#pi"};
  int phi_colors[] = {2,3,4,5,6,96,28,68};

  TFile *file[npt][nmult][nphi];
  TH2D * Sig[nmult][npt][nphi];
  TH2D * Back[nmult][npt][nphi];
  TH2D * Corr[nmult][npt][nphi];
  TH1I * Ntrig[nmult][npt][nphi];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TCanvas *c[nmult][npt];
  TH1D * Proj[nmult][npt][nphi];
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
  
  for(int iphi = 0; iphi < nphi; ++iphi){
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      for(int tqual = 0 ; tqual < 1 ; ++tqual)
      {
        
        //load and set
        // cout<<Form("input_hists/corrhists_trkqual%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        cout<<Form("input_hists/corrhistsvwei3_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        file[imult][ipt][iphi] = new TFile(Form("./merged/corrhists_trkqual%d_nmin%d_nmax%d_ptmin%d_ptmax%d_phibin%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], iphi));
        Sig[imult][ipt][iphi] = (TH2D*)file[imult][ipt][iphi]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Back[imult][ipt][iphi] = (TH2D*)file[imult][ipt][iphi]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Ntrig[imult][ipt][iphi] = (TH1I*)file[imult][ipt][iphi]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][iphi] = (TH2D*)Sig[imult][ipt][iphi]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][iphi]->Divide(Back[imult][ipt][iphi]);
        cout<<"after corr "<<imult<<" "<<ipt<<" "<<tqual<<endl;
        int x0 = Back[imult][ipt][iphi]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt][iphi]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][iphi]->GetBinContent(x0,y0);
        Corr[imult][ipt][iphi]->Scale(B0/(0.0595*Ntrig[imult][ipt][iphi]->GetBinContent(1)));
        Corr[imult][ipt][iphi]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt][iphi]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        int xmn = Corr[imult][ipt][iphi]->GetXaxis()->FindBin(2);
        int xmx = Corr[imult][ipt][iphi]->GetXaxis()->FindBin(4);
        double nbins = xmx - xmn + 1;
        Proj[imult][ipt][iphi] = Corr[imult][ipt][iphi]->ProjectionY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d_phibin%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt],iphi),xmn,xmx,"e");
		Proj[imult][ipt][iphi]->SetStats(0);
        Proj[imult][ipt][iphi]->Scale(1/nbins);
        // Proj[imult][ipt] = Corr[imult][ipt]->ProfileY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]),xmn,xmx);
        double shift = Proj[imult][ipt][iphi]->GetMinimum();
        int rangedown = Proj[imult][ipt][iphi]->FindBin(0);
        int rangeup = Proj[imult][ipt][iphi]->FindBin(TMath::Pi());
        
        for(int i = rangedown; i < rangeup + 1; i++){
          double value = Proj[imult][ipt][iphi]->GetBinContent(i);
          double error = Proj[imult][ipt][iphi]->GetBinError(i);
          value = value - shift;
          Proj[imult][ipt][iphi]->SetBinContent(i,value);		
          Proj[imult][ipt][iphi]->SetBinError(i,error);		
          // Proj[imult][ipt][iphi]->SetBinError(i,0/*error*/);		
        }
        
        
        Proj[imult][ipt][iphi]->SetAxisRange(0,TMath::Pi());
        Proj[imult][ipt][iphi]->SetMarkerColor(2);
        // Proj[imult][ipt]->SetMaximum(1.77);
        // Proj[imult][ipt]->SetMinimum(0);
        if (Proj[imult][ipt][iphi]->GetMaximum() > overallmax) overallmax = Proj[imult][ipt][iphi]->GetMaximum();
        if (Proj[imult][ipt][iphi]->GetMinimum() < overallmin) overallmin = Proj[imult][ipt][iphi]->GetMinimum();
      }
    }
  }
  }
  /*
  TCanvas *c1 = new TCanvas("c1","",1400,900);
  c1->SetFillColor(0);
  Float_t leftMargin=0.14,bottomMargin=0.25;
  makeMultiPanelCanvas(c1,npt,nmult,0.0,0.0,leftMargin,bottomMargin,0.02);
  */
  TLegend *leg = new TLegend(0.88,0.4,0.1,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  for(int iphi = 0; iphi < nphi; iphi++){
	leg->AddEntry(Proj[3][1][iphi],phi_range[iphi].data(),"p");
  }
  /*
  TFile *outf = new TFile("projections.root","recreate");
  for(int imult = 0; imult < nmult; imult++){
    for (int ipt = 0; ipt < npt; ipt++){
      c1->cd(imult*npt+ipt+1);
      Proj[imult][ipt][0]->SetMaximum(overallmax+0.01);
      Proj[imult][ipt][0]->SetMinimum(overallmin-0.01);
	  for(int iphi = 0; iphi < nphi; iphi++){
	    Proj[imult][ipt][iphi]->SetMarkerColor(phi_colors[iphi]);
	    Proj[imult][ipt][iphi]->SetLineWidth(2);
	    Proj[imult][ipt][iphi]->SetMarkerStyle(20);
	    Proj[imult][ipt][iphi]->GetXaxis()->SetLabelSize(0.1);
	    Proj[imult][ipt][iphi]->GetYaxis()->SetLabelSize(0.1);
	  }
      Proj[imult][ipt][0]->Draw("p");
	  for(int iphi = 1; iphi < nphi; iphi++)
		Proj[imult][ipt][iphi]->Draw("p same");
      Proj[imult][ipt][0]->Write();
	  for(int iphi = 1; iphi < nphi; iphi++)
		Proj[imult][ipt][iphi]->Write();
      if(ipt == 0) lmult[imult]->Draw("Same");
      if(imult==0) lpt[ipt]->Draw("Same");
	  if(ipt==0 && imult==0)leg->Draw("same");
      gPad->RedrawAxis();
    }
  }
  outf->Close();
  c1->SaveAs("projections.png");
  */
  
  gStyle->SetCanvasColor(kWhite);     // background is no longer mouse-dropping white
  //gStyle->SetPalette(1,0);            // blue to red false color palette. Use 9 for b/w
  gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
  gStyle->SetPadBorderMode(0);
  gStyle->SetPaintTextFormat("5.2f");  // What precision to put numbers if plotted with "TEXT"
  
  int imult = 3, ipt = 1;// the 110-1000 N and 1-2 GeV bins
  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetFillColor(0);
  SetDataStyle(Proj[imult][ipt][0],"#Delta#phi");
  Proj[imult][ipt][0]->SetMaximum(overallmax+0.01);
  Proj[imult][ipt][0]->SetMinimum(overallmin-0.01);
  Proj[imult][ipt][0]->GetXaxis()->SetRangeUser(0.0,3.14159265);
  Proj[imult][ipt][0]->SetTitle("Projected CF, 110#leq N < 1000, 1#leq p_{t}<2");
  Proj[imult][ipt][0]->Draw("p");
  for(int i = 1; i < nphi; i++){
	Proj[imult][ipt][i]->SetMarkerColor(phi_colors[i]);
	Proj[imult][ipt][i]->SetLineColor(phi_colors[i]);
    Proj[imult][ipt][i]->SetLineWidth(1);
	Proj[imult][ipt][i]->SetMarkerStyle(20);
	Proj[imult][ipt][i]->Draw("same p");
	}
	leg->Draw("same");
  
  TH1D *integrated_yield = new TH1D("integrated_yield","",nphi,-3.1415926,3.1415926);
  int first_bin = 1;
  int n_bins = Proj[0][0][0]->GetNbinsX();
  double bin_width = Proj[0][0][0]->GetBinWidth(1);
  while(first_bin <= n_bins){
	if(Proj[0][0][0]->GetBinCenter(first_bin)>0)break;
	first_bin++;
  }
  for(int iphi = 0; iphi < nphi; iphi++){
	double int_yield = 0.0;
	int last_bin = first_bin;
	int i = last_bin;
	while(i <= n_bins){
	  if(Proj[imult][ipt][iphi]->GetBinCenter(i)>1.5) break; // the upper limit on the extent of the ridge
	  if(Proj[imult][ipt][iphi]->GetBinContent(i)<Proj[imult][ipt][iphi]->GetBinContent(last_bin)) last_bin = i;
	  i++;
	}
	for(int i = first_bin; i <= last_bin; i++){
		int_yield += Proj[imult][ipt][iphi]->GetBinContent(i);
	}
	integrated_yield->SetBinContent(iphi+1,int_yield*bin_width);
  }
  
  TCanvas *d1 = new TCanvas("d1","",800,600);
  SetDataStyle(integrated_yield,"#phi");
  integrated_yield->SetTitle("Integrated ridge yield vs #phi, 110#leq N < 1000, 1#leq p_{t}<2");
  integrated_yield->SetMarkerColor(2);
  integrated_yield->SetMinimum(0);
  integrated_yield->Draw("p");
  
  
  
  
  
}