#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <TMath.h>
#include "CutAndBinCollection2011.h"
#include <time.h>
#include <TRandom3.h>

using namespace std;

#define PI 3.141592653589
static const int MAXTRK = 30000;

void combineSysErrors(TH1 * he1[3][5], TH1 * he2[3][5]) {
}

void drawDijetResultSys(int binMode =2, // 1 : aj, 2 : cent
  bool doEtaRef = true ) 
{  
  TH1::SetDefaultSumw2();
//   std::string Input_="dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut1_FinaletaCut2.00_pfJet.root";
  std::string Input_="dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut1_FinaletaCut2.00_pas.root";
//   std::string Input_="dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut1_FinaletaCut2.00_org.root";
  int refMode = 100; //0 reweight + smear, -1 no rewt, -2 no smear, -3 raw
  TString tag = Form("trkPtProj_binMode%d_ref%d",binMode,refMode);
  if (doEtaRef) tag += "_EtaRef";
  tag+=Form("_approval");
  TString outdir="plotsFinalFF";
  
  float xmin=-0.15, xmax=5.5;

  // Systematics
  const int Nerror = 6;
  const int NerrorHiFF = 8;
  const int NerrorPp = 6;

  TH1* jesError[3][5];
  TH1* jetResError[3][5];
  TH1* bkgSubError[3][5];
  TH1* trkError[3][5];
  TH1* genBkgSubError[3][5];
  TH1* jetAlgoError[3][5];
  TH1* constError[3][5];

  TH1* pyquenJetRecoRefPtError[3][5];
  TH1* pyquenGenJetSelError[3][5];

  TH1* vError[3][5][Nerror];
  TH1* vErrorHiFF[3][5][NerrorHiFF];
  TH1* vErrorPpFF[3][5][NerrorPp];

  // For Ratio
  const char* JESfile = "./systematics/jes_sys.root";
  const char* JetResfile = "./systematics/jetres_sys.root";
  const char* BkgSubfile = "./systematics/bkgsub_sys.root";
  const char* TrkClosurefile = "./systematics/closure_sys.root";
  const char* GenBkgSubfile = "./systematics/closure_bkgsub_sys.root";
  const char* JetAlgofile = "./systematics/systematics_calovspf.root";
  // For FF distribution
  const char* PyquenJetRecoRefPtfile = "./systematics/PYQUEN80_useGenJet0_closureTestRatio_between_100_103.root";
  const char* PyquenGenJetSelfile = "./systematics/closureTestRatio_pyquen80_genJet_recojet_selectionRatio.root";

  TString jname[3] = {"","lJet","slJet"};
  for ( int ijet=1; ijet<=1; ijet++){
    for ( int iaj=1;iaj<=4;iaj++) {
      if (binMode==1) {
        jesError[ijet][iaj] =  loadError(JESfile,Form("hpt_%s_sigTrk_hidata_icent999_iaj%d_fragMode2_closure0_sys2",jname[ijet].Data(),iaj));
        jetResError[ijet][iaj] =  loadError(JetResfile,Form("hpt_%s_sigTrk_hidata_icent999_iaj%d_fragMode2_closure0",jname[ijet].Data(),iaj));
        bkgSubError[ijet][iaj] = loadError(BkgSubfile,Form("hpt_%s_sigTrk_hidata_icent999_iaj%d_fragMode2_closure100",jname[ijet].Data(),iaj));
        trkError[ijet][iaj] = loadError(TrkClosurefile,Form("hpt_%s_sigTrk_himc_icent999_iaj%d_fragMode2_closure101",jname[ijet].Data(),iaj));
      } else if (binMode==2) {
        jesError[ijet][iaj] =  loadError(JESfile,Form("hpt_%s_sigTrk_hidata_icent2_irj999_fragMode2_closure100_sys7",jname[ijet].Data(),iaj));
        jetResError[ijet][iaj] =  loadError(JetResfile,Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure100",jname[ijet].Data(),iaj));
        bkgSubError[ijet][iaj] =  loadError(BkgSubfile,Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure0",jname[ijet].Data(),iaj));

        trkError[ijet][iaj] =  loadError(TrkClosurefile,Form("hpt_%s_sigTrk_himc_icent%d_irj999_fragMode2_closure100",jname[ijet].Data(),iaj));

        genBkgSubError[ijet][iaj] =  loadError(GenBkgSubfile,Form("hpt_%s_sigTrk_himc_icent%d_irj999_fragMode2_closure102",jname[ijet].Data(),iaj));
        
        // For FF distribution
        pyquenJetRecoRefPtError[ijet][iaj] = loadError(PyquenJetRecoRefPtfile,Form("hpt_%s_sigTrk_himc_icent%d_irj999_fragMode2_closure103",jname[ijet].Data(),iaj));
        pyquenGenJetSelError[ijet][iaj] = loadError(PyquenGenJetSelfile,Form("hpt_%s_sigTrk_himc_icent%d_irj999_fragMode2_closure100",jname[ijet].Data(),iaj));
      }
      
      // additional track error to be flat 4%
      constError[ijet][iaj] =  (TH1D*)jesError[ijet][iaj]->Clone(Form("%s_constsys",jesError[ijet][iaj]->GetName()));
      for(int i = 1; i <= constError[ijet][iaj]->GetNbinsX(); ++i){
        constError[ijet][iaj]->SetBinContent(i,1.10);
        constError[ijet][iaj]->SetBinError(i,0.1);
        constError[ijet][iaj]->SetBinError(i,0.1);
      }

      // Ratio
      vError[ijet][iaj][0] = jesError[ijet][iaj];
      vError[ijet][iaj][1] = jetResError[ijet][iaj];
      vError[ijet][iaj][2] = bkgSubError[ijet][iaj];
      vError[ijet][iaj][3] = trkError[ijet][iaj];
      vError[ijet][iaj][4] = constError[ijet][iaj];
      vError[ijet][iaj][5] = genBkgSubError[ijet][iaj];

      // HiFF
      vErrorHiFF[ijet][iaj][0] = jesError[ijet][iaj];
      vErrorHiFF[ijet][iaj][1] = jetResError[ijet][iaj];
      vErrorHiFF[ijet][iaj][2] = bkgSubError[ijet][iaj];
      vErrorHiFF[ijet][iaj][3] = trkError[ijet][iaj];
      vErrorHiFF[ijet][iaj][4] = constError[ijet][iaj];
      vErrorHiFF[ijet][iaj][5] = genBkgSubError[ijet][iaj];
      vErrorHiFF[ijet][iaj][6] = pyquenJetRecoRefPtError[ijet][iaj];
      vErrorHiFF[ijet][iaj][7] = pyquenGenJetSelError[ijet][iaj];
    }
  }
  
  TH2F * hPadFF, *hPadR, * hPadPt;;

  hPadFF = new TH2F("hPadFF",";#xi = ln(1/z);1/N_{ jet} dN_{ track} /d#xi",100,xmin,xmax,100,0.006,20);
  hPadPt = new TH2F("hPadPt",";p_{T}^{ jet} (GeV/c);1/N_{ jet} dN_{ jet} /dp_{T}",150,0,320,100,0.000002,300);
  hPadR = new TH2F("hPadR",";#xi = ln(1/z);PbPb/pp",100,xmin,xmax,20000,0,3.4);

  handsomeTH1(hPadFF,1,1.2);
  handsomeTH1(hPadR,1,1.2);
  handsomeTH1(hPadPt,1,1.2);

  fixedFontHist(hPadFF,2.5,3,25);
  fixedFontHist(hPadR,2.5,3,25);
  fixedFontHist(hPadPt);

   TCanvas * cerr = new TCanvas("cerr","cerr",4*300,300);
   cerr->Divide(4,1);

  TCanvas *c = new TCanvas("c","",1500,760);
  makeMultiPanelCanvasNew(c,4,2,0.0,0.0,0.22,0.22,0.01,1.0,0.95);

  /////////////////////////////////////////////////
  // Get Histogram
  /////////////////////////////////////////////////
  TFile* inf = new TFile(Input_.data());
  TH1D* ffhi[3][5]; // (leading, subleading),  (aj bin)
  TH1D* ffpp[3][5];
  TH1D* ffratio[3][5];
  // Analysis Histograms
  for ( int ijet=1; ijet<=1; ijet++){ 
    for ( int iaj=1;iaj<=4;iaj++) {
      if      ( binMode == 1 ) {
        if (!doEtaRef) ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent999_irj%d_fragMode2_closure0",jname[ijet].Data(),iaj));
        else ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent999_irj%d_fragMode2_closure100",jname[ijet].Data(),iaj));
        ffpp[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_ppdata_icent999_irj%d_fragMode2_closure%d",jname[ijet].Data(),iaj,refMode));
      }
      else if ( binMode == 2 ) {
//       	if (!doEtaRef) ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure0",jname[ijet].Data(),iaj));
//       	else ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure100",jname[ijet].Data(),iaj));
//         ffpp[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_ppdata_icent%d_irj999_fragMode2_closure%d",jname[ijet].Data(),iaj,refMode));
      	if (!doEtaRef) ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure0_wtmode0_pt1to500",jname[ijet].Data(),iaj));
      	else ffhi[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure100_wtmode0_pt1to500",jname[ijet].Data(),iaj));
        ffpp[ijet][iaj]  = (TH1D*)load(Input_.data(),Form("hpt_%s_sigTrk_ppdata_icent%d_irj999_fragMode2_closure%d_wtmode0_pt1to500",jname[ijet].Data(),iaj,refMode));
      } 
  
      handsomeTH1(ffpp[ijet][iaj],1,1.3);
      handsomeTH1(ffhi[ijet][iaj],1,1.3);

    }
  }

  // Compare Histograms
  TH1D* ffhicmp[3][5];
  TH1D* ffppcmp[3][5];
  TH1D* ffratiocmp[3][5];
//   TString cmpFile = "PbPbPP_ratio_dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut1_FinaletaCut2.00_calo.root";
  TString cmpFile = "dijetFF_output_histograms_trkPtProjectOnJetAxis_trackPtCut1_FinaletaCut0.80_pas.root";
  for ( int ijet=1; ijet<=1; ijet++){ 
    for ( int iaj=1;iaj<=4;iaj++) {
//       ffratiocmp[ijet][iaj] = (TH1D*)load(cmpFile.Data(),Form("ffRattio_ijet1_irj%d",iaj));
      ffhicmp[ijet][iaj]  = (TH1D*)load(cmpFile.Data(),Form("hpt_%s_sigTrk_hidata_icent%d_irj999_fragMode2_closure100_wtmode0_pt1to500",jname[ijet].Data(),iaj));
      ffppcmp[ijet][iaj]  = (TH1D*)load(cmpFile.Data(),Form("hpt_%s_sigTrk_ppdata_icent%d_irj999_fragMode2_closure100_wtmode0_pt1to500",jname[ijet].Data(),iaj));
      ffratiocmp[ijet][iaj]  = (TH1D*)ffhicmp[ijet][iaj]->Clone(Form("%s_ratcmp",ffhicmp[ijet][iaj]->GetName()));
      ffratiocmp[ijet][iaj]->Divide(ffppcmp[ijet][iaj]);
      handsomeTH1(ffratiocmp[ijet][iaj],kBlue,1.3,kOpenCircle);
    }
  }
  

  /////////////////////////////////////////////////
  // Monitor
  /////////////////////////////////////////////////
  TFile outf("finalSys.root","recreate");
  outf.Close();
  
  /////////////////////////////////////////////////
  // Draw Result
  /////////////////////////////////////////////////
  for ( int ijet=1; ijet>=1 ; ijet--) {
    for ( int iaj=1 ; iaj<=4 ; iaj++) {
      cout << "=============== " << Form("%.0f%% - %.0f%%", float(centBin1[iaj-1]*2.5), float(centBin1[iaj]*2.5)) << " ================" << endl;
      
      // Draw Distribution
      c->cd(5-iaj);
      bool doNorm=false;
      if (doNorm) {scaleInt(ffpp[ijet][iaj]); scaleInt(ffhi[ijet][iaj]);}
      if (doNorm) ffpp[ijet][iaj]->SetAxisRange(0.00025,1,"Y");
      
      if(ijet == 1){
        hPadFF->Draw();
      }
      
      int iajSys = iaj;
      if (binMode==1) iaj=5-iaj;
      gPad->SetLogy();      
      drawSysErr(ffhi[ijet][iaj],vErrorHiFF[ijet][iajSys],NerrorHiFF,ijet-1,1,2,1,ijet == 1,0,0,(TPad*)c->GetPad(5-iaj),(TPad*)cerr->GetPad(5-iaj));
      ffpp[ijet][iaj]->Draw(   "hist same");
      ffhi[ijet][iaj]->Draw("same");
      gPad->RedrawAxis();

      // Draw Ratio
      c->cd(9-iaj);
      ffratio[ijet][iaj]= (TH1D*)ffhi[ijet][iaj]->Clone(Form("ffRattio_ijet%d_iaj%d",ijet,iaj));
      ffratio[ijet][iaj]->Divide(ffpp[ijet][iaj]);
      ffratio[ijet][iaj]->SetAxisRange(0,3,"Y");
      ffratio[ijet][iaj]->SetAxisRange(0,5.8,"X");

      if(ijet == 1)hPadR->Draw();
      drawSysErr(ffratio[ijet][iaj],vError[ijet][iajSys],Nerror,ijet-1,1,2,1,ijet == 1,0,0);
//       drawSysErr(ffratiocmp[ijet][iaj],vError[ijet][iajSys],Nerror,ijet-1,1,2,1,0,0,0);
//       ffratiocmp[ijet][iaj]->Draw("sameE");
      ffratio[ijet][iaj]->Draw("same");
      jumSun(0,1,6,1);
      gPad->RedrawAxis();
      PrintHistogram(ffratio[ijet][iaj]);
    }
  }

  /////////////////////////////////////////////////
  // Annotate
  /////////////////////////////////////////////////
  TLegend* l2[3];
  for ( int ijet=1; ijet>=1 ; ijet--) {
    l2[ijet]  = new TLegend(0.04,0.77,0.77,1,NULL,"brNDC");
    if      ( ijet == 1 )     easyLeg(l2[ijet],"");
    l2[ijet]->AddEntry(ffhi[ijet][1],"PbPb","p");
//     l2[ijet]->AddEntry(ffratiocmp[ijet][1],"PbPb AkPu3Calo","p");
//     l2[ijet]->AddEntry(ffratiocmp[ijet][1],"Jet |#eta|<0.8","p");
    l2[ijet]->AddEntry(ffpp[ijet][1],"pp reference","l");
    
    for ( int iaj=1 ; iaj<=4 ; iaj++) {
      c->cd(5-iaj);
      if (iaj==3 && ijet == 1)  l2[ijet]->Draw();      
      if (iaj==4) drawText("CMS Preliminary",0.3,0.9);
      float legdx = 0.2;
      if (binMode==1&&iaj==4) legdx=+0.15;
      if (binMode==2&&iaj==4) legdx=+0.30;
      if ( binMode == 1 ) {
        drawText(Form("%.2f < x_{2,1} < %.2f", float(rjBin1[iaj-1]), float(rjBin1[iaj])), 0.2+legdx,0.18);
      } else if ( binMode == 2 ) drawText(Form("%.0f%% - %.0f%%", float(centBin1[iaj-1]*2.5), float(centBin1[iaj]*2.5)), 0.2+legdx,0.18,kBlack,24);

      if (iaj==2) {
      float ptx(0.08),pty1(0.89);
         drawText("Jet p_{T}  > 100GeV/c, |#eta| < 2",ptx,pty1,kBlack,23);
         drawText("Track p_{T}  > 1 GeV/c, r < 0.3",ptx,pty1-0.1,kBlack,23);
      }
    }
    c->SaveAs(outdir+Form("/FF_distribution_ijet%d_%s.gif",ijet,tag.Data()));
    c->SaveAs(outdir+Form("/FF_distribution_ijet%d_%s.pdf",ijet,tag.Data()));
  }
}

 
