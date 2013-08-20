#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TF2.h"
#include "TMath.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"



void dm(int domc = 0 , int doptweight = 0 , int dotrkpt = 0 , int docent = 0 , int doaj = 0 , int doleadsubleading = 0)
{
  TFile * f1[2][2];  //! [data/mc][no pt weight/pt weight]

  f1[0][0] = new TFile("roots/v29mcgen.root");
  f1[0][1] = new TFile("roots/astdfrank_ptw1.root");
  f1[1][0] = new TFile("roots/v29mcreco.root");
  f1[1][1] = new TFile("roots/stdmc_ptw1.root");


  const int nptbins   = 3;
  const int ncentbins = 4;
  const int najbins   = 1;
  const int nptw      = 1;
  const int ndataset  = 2;
  const int njetindex = 1;


  TH2D *             sig[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];
  TH2D *             bak[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];
  TH2D *            corr[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];
  TH1D *            proj[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];
  TH2D * subtracted_corr[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];
  TH2D *          result[njetindex][nptbins][ncentbins][najbins][ndataset][nptw];


  double leadingjetptlow[] =     {100,100,100,100,100,100,100,100,100};
  double leadingjetpthigh[] =    {300,300,300,300,300,300,300,300,300};
  double subleadingjetptlow[] =  {50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 };
  double subleadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double ptasslow[] =            {1,  2  ,4  ,5  ,3  ,3  ,1  ,2  ,3  };
  double ptasshigh[] =           {2,  4  ,8  ,8  ,4  ,4  ,2  ,3  ,4  };

  int centmin[] = {0,4,12,20};
  int centmax[] = {4,12,20,40};

  float ajmin[] = { 0.00, 0.13, 0.24, 0.35 };
  float ajmax[] = { 0.13, 0.24, 0.35, 1.00 };

  TString jetname[] = { "leading" , "subleading" };
  TString ljetname[] = { "inclusive" , "subleading" };
  TString ptweight[] = { "" , "p_{T} weighted" };
  TString datamclumi[] = { "L_{int} = 129 #mub^{-1} " , "MC #hat{p}_{T}=100 embedded 377K evts" };
  TString datamc[] = { "PbPb  #sqrt{s_{NN}} = 2.76 TeV " , "" };

  for(int dataset = 0 ; dataset < ndataset ; ++dataset)
  {
    for(int ptw = 0 ; ptw < nptw ; ++ptw)
    {
      for(int ptbin = 0 ; ptbin < nptbins ; ++ptbin)
      {
        for(int cent = 0 ; cent < ncentbins ; ++cent)
        {
          for(int aj = 0 ; aj < najbins ; ++aj)
          {
            for(int jetindex = 0 ; jetindex < njetindex ; ++jetindex)
            {
              if(cent==1) cout<<Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw)<<endl;
              sig[jetindex][ptbin][cent][aj][dataset][ptw] = (TH2D*)f1[dataset][ptw]->Get(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100)));
              bak[jetindex][ptbin][cent][aj][dataset][ptw] = (TH2D*)f1[dataset][ptw]->Get(Form("background_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100)));

              
              
              // if( doleadsubleading==0 ) break; //! jetindex
            }
            // if( doaj==0 ) break; //! ajbin
          }
          // if( docent==0 ) break; //! centbin
        }
        // if( dotrkpt==0 ) break;  //! ass trk pt bin
      }
      // if( doptweight==0 ) break;  //! pt weight
    }
    // if( domc==0 ) break;  //! dataset
  }
  int jetindex = 0 , ptbin = 0 , cent = 0 , aj = 0 , ptw = 0, dataset = 0;
  // cout<<Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw)<<endl;
  
  for(int i = 0 ; i < 1 ; ++i)
  {
    //! Define the latex
    TLatex * lpreliminary = new TLatex( 0.02 , 0.03, Form("CMS Preliminary   %s   %s",datamc[dataset].Data(),datamclumi[dataset].Data()) );
    lpreliminary->SetNDC(1);
    lpreliminary->SetTextSize(lpreliminary->GetTextSize()*1.1);
    
    TLatex * lsigtitle = new TLatex( 0.0073 ,0.9557, Form("gen signal / reco signal"));
    lsigtitle->SetNDC(1);
    lsigtitle->SetTextSize(lsigtitle->GetTextSize()*1.1);
    
    // TLatex * lbaktitle = new TLatex( 0.0073 ,0.9557, Form("background %s",ljetname[jetindex].Data()));
    // lbaktitle->SetNDC(1);
    // lbaktitle->SetTextSize(lbaktitle->GetTextSize()*1.1);

    // TLatex * lcorrtitle = new TLatex( 0.0073 ,0.9557, Form("correlation function %s",ljetname[jetindex].Data()));
    // lcorrtitle->SetNDC(1);
    // lcorrtitle->SetTextSize(lcorrtitle->GetTextSize()*1.1);

    // TLatex * llrsubtitle = new TLatex( 0.0073 ,0.9557, Form("long range sub CF %s",ljetname[jetindex].Data()));
    // llrsubtitle->SetNDC(1);
    // llrsubtitle->SetTextSize(llrsubtitle->GetTextSize()*1.1);

    TLatex * ljtpt = new TLatex( 0.0073 ,0.9057, Form("jet p_{T} %d-%d GeV/c",(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin]));
    ljtpt->SetNDC(1);
    ljtpt->SetTextSize(ljtpt->GetTextSize()*1.1);

    TLatex * ltrkpt = new TLatex( 0.0073 ,0.8557, Form("track p_{T} %d-%d GeV/c",(int)ptasslow[ptbin],(int)ptasshigh[ptbin]));
    ltrkpt->SetNDC(1);
    ltrkpt->SetTextSize(ltrkpt->GetTextSize()*1.1);

    TLatex * laj = new TLatex( 0.7777 ,0.9557, Form("A_{J} %2.2f-%2.2f",ajmin[aj],ajmax[aj]));
    laj->SetNDC(1);
    laj->SetTextSize(laj->GetTextSize()*1.1);

    TLatex * lcent = new TLatex( 0.6777 ,0.9557, Form("%2.0f-%2.0f %%",2.5*centmin[cent],2.5*centmax[cent]));
    lcent->SetNDC(1);
    lcent->SetTextSize(lcent->GetTextSize()*1.1);

    TLatex * lptw = new TLatex( 0.7777 ,0.8557, Form("%s",ptweight[ptw].Data()));
    lptw->SetNDC(1);
    lptw->SetTextSize(lptw->GetTextSize()*1.1);
    
    corr[jetindex][ptbin][cent][aj][dataset][ptw] = (TH2D*)sig[jetindex][ptbin][cent][aj][dataset][ptw]->Clone(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
    corr[jetindex][ptbin][cent][aj][dataset][ptw]->Divide(bak[jetindex][ptbin][cent][aj][dataset][ptw]);
    
    TCanvas * c1 = new TCanvas("c1");
    corr[jetindex][ptbin][cent][aj][dataset][ptw]->Draw("surf1");
  
    lsigtitle->Draw("same");
    ljtpt->Draw("same");
    ltrkpt->Draw("same");
    // laj->Draw("same");
    lcent->Draw("same");
    lptw->Draw("same");
    lpreliminary->Draw("same");
    c1->SaveAs(Form("signal_genreco_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.png",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
  }
} 

