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
#include "FitHist.C"

//./submit.sh 1 HIRun2013-PromptReco-v1-HLT_PAPixelTrackMultiplicity130_FullTrack12-sort.txt 
//            HIRun2013-PromptReco-v1-HLT_PAPixelTrackMultiplicity130_FullTrack12-sort 130 160 14 16 1 2
// void dplot(int ppt = 0, int ppm = 0 , string tag = "", string draw = "corr"){
void dplot(int trkqual = 1, string filename = "" , string tag = "", int nmin = 130, int nmax = 160, float tptmin = 14, float tptmax = 16, float aptmin = 1, float aptmax = 2, string draw = "corr")
{
	TFile * file = new TFile(filename.data());
	TH2D * Sig = (TH2D*)file->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax));
	TH2D * Back = (TH2D*)file->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax));
	TH1D * Ntrig = (TH1D*)file->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax));
	TH2D * Corr = (TH2D*)Sig->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax));
	Corr->Divide(Back);
	int x0 = Back->GetXaxis()->FindBin(0.0);
	int y0 = Back->GetYaxis()->FindBin(0.0);
	double B0 = Back->GetBinContent(x0,y0);
	double bwx = Sig->GetXaxis()->GetBinWidth(2);
	double bwy = Sig->GetYaxis()->GetBinWidth(2);
	Corr->Scale(B0/(bwx*bwy*Ntrig->Integral(2,300)));
	Corr->GetXaxis()->SetRangeUser(-4,4);
	Corr->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
	double max = Corr->GetMaximum();
	double min = Corr->GetMinimum();
	int xmn = Corr->GetXaxis()->FindBin(2);
	int xmx = Corr->GetXaxis()->FindBin(3.5);
	double nbins = xmx - xmn + 1;
	TH1D * Proj = Corr->ProjectionY(Form("projection_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax),xmn,xmx,"e");
	Proj->Scale(1/nbins);
	double shift = Proj->GetMinimum();
	int rangedown = Proj->FindBin(0);
	int rangeup = Proj->FindBin(TMath::Pi());
	//!
	// for(int i = rangedown; i < rangeup + 1; i++){
		// double value = Proj[imult][ipt]->GetBinContent(i);
		// double error = Proj[imult][ipt]->GetBinError(i)*0.001;
		
		// value = value - shift;
		// Proj[imult][ipt]->SetBinContent(i,value);		
		// Proj[imult][ipt]->SetBinError(i,error);		
	// }
	TF1 * fourier = addFitToCanvas(Proj);
	float v2_low = sqrt(fourier->GetParameter(2));
	cout<<"v2(1-2 GeV) = "<<v2_low<<endl;
	
	TCanvas * c1 = new TCanvas(Form("canvas_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)tptmin,(int)tptmax,(int)aptmin,(int)aptmax));
	if(draw.compare("corr")==0)
		Corr->Draw("Surf1");
	if(draw.compare("proj")==0)
	{
		Proj->Draw();
		fourier->Draw("same");
		// TLatex * lv2 = new TLatex(0.5, 0.77, Form("v_{2} = %2.2f", v2));
		// lv2->SetNDC(1);
		// lv2->SetTextSize(lv2->GetTextSize()*1.5);
	}
	// lmult[imult]->Draw("Same");
	// lpt[ipt]->Draw("Same");
	// lpta[ipt]->Draw("Same");
	// lv2->Draw("Same");
	
	//!
        

        // ltrackqual[tqual]->Draw("Same");
        // c[imult][ipt][tqual]->SaveAs(Form("%s_%s_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.png", draw.data(), tag.data(),
               // tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], 
               // (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        // c[imult][ipt][tqual]->SaveAs(Form("%s_%s_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.pdf", draw.data(), tag.data(),
               // tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], 
               // (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        // c[imult][ipt][tqual]->SaveAs(Form("single_plots/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.pdf", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        // c[imult][ipt][tqual]->SaveAs(Form("ridgePA_2DCF.C"));
        
        // c[imult][ipt][tqual]->SaveAs(Form("proj1D_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.png", (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], tqual));


/*
  TH1::SetDefaultSumw2(true);
  const int npt   = 4;
  const int nmult   = 4;  
  const int ntrkqual   = 2;  
  
  // const int npt   = 1;
  // const int nmult   = 4;  
  
  // double pttriglow[] =            {1,  14  ,2  ,3 };
  // double pttrighigh[] =           {2,  16  ,3  ,4 };
  // double ptasslow[] =            {1,  1  ,2  ,3 };
  // double ptasshigh[] =           {2,  2  ,3  ,4 };
   
  double pttriglow[] =  {14   ,16 ,20 ,1, 1};
  double pttrighigh[] = {16   ,20 ,24 ,2, 3};
  double ptasslow[] =   {1    ,1  ,1 ,1, 1};
  double ptasshigh[] =  {2    ,2  ,2 ,2, 3};
  
  // double ptlow[] =            {1,  1  ,2  ,3 };
  // double pthigh[] =           {3,  2  ,3  ,4 };

  double nlow[] =            {0,  35  ,90  ,130 };
  double nhigh[] =           {35,  90  ,110  ,160 };
  
  double overallmax = -100;
  double overallmin = 100;

  
  TFile *file[npt][nmult][ntrkqual];
  TH2D * Sig[nmult][npt][ntrkqual];
  TH2D * Back[nmult][npt][ntrkqual];
  TH2D * Corr[nmult][npt][ntrkqual];
  TH1D * Ntrig[nmult][npt][ntrkqual];
  TLatex * lmult[nmult];
  TLatex * lpt[npt];
  TLatex * lpta[npt];
  TLatex * lv2[npt];
  TLatex * ltrackqual[ntrkqual];
  TCanvas *c[nmult][npt][ntrkqual];
  
  TH1D * Proj[nmult][npt];
  
  // string quality[] = {"GEN","no selection","inverted"};
  string quality[] = {"","no selection","inverted"};
  
  for(int imult = 0; imult < nmult; imult++){
    if(tag.compare("PbPbUPC_pptracking_452p1_forest_sorted_v3")==0)
      lmult[imult] = new TLatex(0.01, 0.95, Form("CMS PbPb %d #leq N < %d", (int)nlow[imult], (int)nhigh[imult]));
    if(tag.compare("HIRun2013-PromptReco-v1-HLT_PAPixelTrackMultiplicity130_FullTrack12-sort")==0)
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
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int)pttriglow[ipt], (int)pttrighigh[ipt]));
    lpt[ipt] = new TLatex(0.01, 0.86, Form("%d #leq p_{T}^{trig} < %d GeV/c", (int)pttriglow[ipt], (int)pttrighigh[ipt]));
    lpta[ipt] = new TLatex(0.5, 0.86, Form("%d #leq p_{T}^{ass} < %d GeV/c", (int)ptasslow[ipt], (int)ptasshigh[ipt]));
    // lpt[ipt] = new TLatex(0.5, 0.95, Form("%.1f #leq p_{T} < %.1f GeV/c", 0.4, 1.0));
    lpt[ipt]->SetNDC(1);
    lpta[ipt]->SetNDC(1);
    lpt[ipt]->SetTextSize(lpt[ipt]->GetTextSize()*1.5);
    lpta[ipt]->SetTextSize(lpta[ipt]->GetTextSize()*1.5);
    
  }
  
  int plotmult = ppm;
  int plotpt = ppt;
  double v2_low = 0.0;
  
  // for(int imult = plotmult; imult <= plotmult; imult++){
    // for (int ipt = 3; ipt <= npt; ipt++){
      // for(int tqual = 1 ; tqual < ntrkqual ; ++tqual)
      // {
        file[imult][ipt][tqual] = new TFile(Form("input_hists/%s_%d_%d_%d_%d_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tag.data(), (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Sig[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Back[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Ntrig[imult][ipt][tqual] = (TH1D*)file[imult][ipt][tqual]->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Corr[imult][ipt][tqual] = (TH2D*)Sig[imult][ipt][tqual]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Corr[imult][ipt][tqual]->Divide(Back[imult][ipt][tqual]);
        int x0 = Back[imult][ipt][tqual]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt][tqual]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][tqual]->GetBinContent(x0,y0);
        double bwx = Sig[imult][ipt][tqual]->GetXaxis()->GetBinWidth(2);
        double bwy = Sig[imult][ipt][tqual]->GetYaxis()->GetBinWidth(2);
        Corr[imult][ipt][tqual]->Scale(B0/(bwx*bwy*Ntrig[imult][ipt][tqual]->Integral(2,300)));
        Corr[imult][ipt][tqual]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt][tqual]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        double max = Corr[imult][ipt][tqual]->GetMaximum();
        double min = Corr[imult][ipt][tqual]->GetMinimum();
        int xmn = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(2);
        int xmx = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(3.5);
        double nbins = xmx - xmn + 1;
        Proj[imult][ipt] = Corr[imult][ipt][tqual]->ProjectionY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt]),xmn,xmx,"e");
        Proj[imult][ipt]->Scale(1/nbins);
        double shift = Proj[imult][ipt]->GetMinimum();
        int rangedown = Proj[imult][ipt]->FindBin(0);
        int rangeup = Proj[imult][ipt]->FindBin(TMath::Pi());
        // for(int i = rangedown; i < rangeup + 1; i++){
          // double value = Proj[imult][ipt]->GetBinContent(i);
          // double error = Proj[imult][ipt]->GetBinError(i)*0.001;
          
          // value = value - shift;
          // Proj[imult][ipt]->SetBinContent(i,value);		
          // Proj[imult][ipt]->SetBinError(i,error);		
        // }
        TF1 * fourier = addFitToCanvas(Proj[imult][ipt]);
        v2_low = sqrt(fourier->GetParameter(2));
        cout<<"v2(1-2 GeV) = "<<v2_low<<endl;
        break;
      }
      break;
    }
  break;
  }
  
  for(int imult = plotmult; imult <= plotmult; imult++){
    for (int ipt = plotpt; ipt <= npt; ipt++){
      for(int tqual = 1 ; tqual < ntrkqual ; ++tqual)
      {
        // file[imult][ipt][tqual] = new TFile(Form("input_hists/corrhists_gen_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt]));
        // cout<<Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_newscale_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt])<<endl;
        // cout<<Form("/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/input_hists/corrhists_newscale_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt])<<endl;
        // cout<<Form("/net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/merged/ppb_corrhists_2fixedscale_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt])<<endl;
        cout<<Form("input_hists/%s_%d_%d_%d_%d_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tag.data(), (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt])<<endl;
        // break;
        // file[imult][ipt][tqual] = new TFile(Form("input_hists/PbPbUPC_pptracking_452p1_forest_sorted_v3_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        file[imult][ipt][tqual] = new TFile(Form("input_hists/%s_%d_%d_%d_%d_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tag.data(), (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        // file[imult][ipt][tqual] = new TFile(Form("/net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/merged/ppb_corrhists_2fixedscale_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.root", tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        // cout<<Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow1[ipt], (int)pthigh1[ipt])<<endl;
        // break;
        Sig[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Back[imult][ipt][tqual] = (TH2D*)file[imult][ipt][tqual]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Ntrig[imult][ipt][tqual] = (TH1D*)file[imult][ipt][tqual]->Get(Form("hmulttrg_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
        Corr[imult][ipt][tqual] = (TH2D*)Sig[imult][ipt][tqual]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)pttriglow[ipt], (int)pttrighigh[ipt],(int)ptasslow[ipt], (int)ptasshigh[ipt]));
 
        

        // file[imult][ipt] = new TFile(Form("input_hists/corrhistsvwei0_trkqaul0_nmin%d_nmax%d_ptmin1_ptmax3.root", (int)nlow[imult], (int)nhigh[imult]));
        // Sig[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("signal_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Back[imult][ipt] = (TH2D*)file[imult][ipt]->Get(Form("background_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Ntrig[imult][ipt] = (TH1I*)file[imult][ipt]->Get(Form("nttottrig_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        // Corr[imult][ipt] = (TH2D*)Sig[imult][ipt]->Clone(Form("correlation_trg%d_%d_ass%d_%d_cmin0_cmax41",(int)ptlow[ipt], (int)pthigh[ipt],(int)ptlow[ipt], (int)pthigh[ipt]));
        Corr[imult][ipt][tqual]->Divide(Back[imult][ipt][tqual]);
        int x0 = Back[imult][ipt][tqual]->GetXaxis()->FindBin(0.0);
        int y0 = Back[imult][ipt][tqual]->GetYaxis()->FindBin(0.0);
        double B0 = Back[imult][ipt][tqual]->GetBinContent(x0,y0);
        
        double testerror = Corr[imult][ipt][tqual]->GetBinError(x0,y0);
        cout<<testerror<<endl;
        
        double bwx = Sig[imult][ipt][tqual]->GetXaxis()->GetBinWidth(2);
        double bwy = Sig[imult][ipt][tqual]->GetYaxis()->GetBinWidth(2);
        Corr[imult][ipt][tqual]->Scale(B0/(bwx*bwy*Ntrig[imult][ipt][tqual]->Integral(2,300)));
        Corr[imult][ipt][tqual]->GetXaxis()->SetRangeUser(-4,4);
        Corr[imult][ipt][tqual]->GetYaxis()->SetRangeUser(-TMath::Pi()/2,3*TMath::Pi()/2);
        
        double max = Corr[imult][ipt][tqual]->GetMaximum();
        double min = Corr[imult][ipt][tqual]->GetMinimum();
        // Corr[imult][ipt][tqual]->SetMaximum(((max+min)/2-min)/(2.3)+min);
        Corr[imult][ipt][tqual]->SetMaximum(2.5);
        // Corr[imult][ipt][tqual]->SetMaximum(10);
        
        int xmn = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(2);
        int xmx = Corr[imult][ipt][tqual]->GetXaxis()->FindBin(3.5);
        double nbins = xmx - xmn + 1;
        Proj[imult][ipt] = Corr[imult][ipt][tqual]->ProjectionY(Form("proj_nmin%d_nmax%d_ptmin%d_ptmax%d", (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt]),xmn,xmx,"e");
        // Proj[imult][ipt]->Draw();
        // break;
        Proj[imult][ipt]->Scale(1/nbins);
        
        double shift = Proj[imult][ipt]->GetMinimum();
        int rangedown = Proj[imult][ipt]->FindBin(0);
        int rangeup = Proj[imult][ipt]->FindBin(TMath::Pi());
        
        for(int i = rangedown; i < rangeup + 1; i++){
          // double value = Proj[imult][ipt]->GetBinContent(i);
          double error = Proj[imult][ipt]->GetBinError(i)*0.001;
          
          // value = value - shift;
          // Proj[imult][ipt]->SetBinContent(i,value);		
          Proj[imult][ipt]->SetBinError(i,error);		
        }
        
        
        Proj[imult][ipt]->SetAxisRange(0,TMath::Pi());
        Proj[imult][ipt]->SetMarkerColor(2);
        // Proj[imult][ipt]->Sumw2();
        // Proj[imult][ipt]->SetMaximum(1.77);
        // Proj[imult][ipt]->SetMinimum(0);
        if (Proj[imult][ipt]->GetMaximum() > overallmax) overallmax = Proj[imult][ipt]->GetMaximum();
        if (Proj[imult][ipt]->GetMinimum() < overallmin) overallmin = Proj[imult][ipt]->GetMinimum();
        
        
        TF1 * fourier = addFitToCanvas(Proj[imult][ipt]);
        double v2 = fourier->GetParameter(2)/v2_low;
        cout<<"v2: "<<v2<<endl;
          
        c[imult][ipt][tqual] = new TCanvas(
          Form("c_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d", 
               tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], 
               (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt])
                  , "", 600, 600);
        
        if(draw.compare("corr")==0)
          Corr[imult][ipt][tqual]->Draw("Surf1");
        if(draw.compare("proj")==0)
        {
          Proj[imult][ipt]->Draw();
          fourier->Draw("same");
          lv2[ipt] = new TLatex(0.5, 0.77, Form("v_{2} = %2.2f", (int)ptasslow[ipt], v2));
          lv2[ipt]->SetNDC(1);
          lv2[ipt]->SetTextSize(lv2[ipt]->GetTextSize()*1.5);
        }
        lmult[imult]->Draw("Same");
        lpt[ipt]->Draw("Same");
        lpta[ipt]->Draw("Same");
        lv2[ipt]->Draw("Same");
        
        // ltrackqual[tqual]->Draw("Same");
        c[imult][ipt][tqual]->SaveAs(Form("%s_%s_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.png", draw.data(), tag.data(),
               tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], 
               (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        c[imult][ipt][tqual]->SaveAs(Form("%s_%s_trkqaul%d_nmin%d_nmax%d_tptmin%d_tptmax%d_aptmin%d_aptmax%d.pdf", draw.data(), tag.data(),
               tqual, (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], 
               (int)pttrighigh[ipt], (int)ptasslow[ipt], (int)ptasshigh[ipt]));
        // c[imult][ipt][tqual]->SaveAs(Form("single_plots/new_c_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.pdf", (int)nlow[imult], (int)nhigh[imult], (int)ptlow[ipt], (int)pthigh[ipt], tqual));
        // c[imult][ipt][tqual]->SaveAs(Form("ridgePA_2DCF.C"));
        
        // c[imult][ipt][tqual]->SaveAs(Form("proj1D_nmin%d_nmax%d_ptmin%d_ptmax%d_trkqual%d.png", (int)nlow[imult], (int)nhigh[imult], (int)pttriglow[ipt], (int)pttrighigh[ipt], tqual));
        
        break;
      }
      break;
    }
  break;
  }
	*/
}


