#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TF2.h"
#include "TMath.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"

void dh(int domc = 0 , int doptweight = 0 , int dotrkpt = 0 , int docent = 0 , int doaj = 0 , int doleadsubleading = 0)
{

  TFile * f1[2][2];  //! [data/mc][no pt weight/pt weight]
  // f1[0][0] = new TFile("roots/stdfrank_ptw0.root");
  // f1[0][1] = new TFile("roots/stdfrank_ptw1.root");
  // f1[1][0] = new TFile("roots/stdmc_ptw0.root");
  // f1[1][1] = new TFile("roots/stdmc_ptw1.root");
  
  // f1[0][0] = new TFile("roots/sstdfrank_ptw0.root");
  // f1[0][1] = new TFile("roots/stdfrank_ptw1.root");
  // f1[1][0] = new TFile("roots/sstdmc_ptw0.root");
  // f1[1][1] = new TFile("roots/stdmc_ptw1.root");
  
  f1[0][0] = new TFile("roots/inclusivejet.root");
  f1[0][1] = new TFile("roots/astdfrank_ptw1.root");
  f1[1][0] = new TFile("roots/sstdmc_ptw0.root");
  f1[1][1] = new TFile("roots/stdmc_ptw1.root");
  
  
  const int nptbins   = 3;
  const int ncentbins = 4;
  const int najbins   = 1;
  
  
  TH2D *             sig[2][nptbins][ncentbins][najbins];
  TH2D *             bak[2][nptbins][ncentbins][najbins];
  TH2D *            corr[2][nptbins][ncentbins][najbins];
  TH1D *            proj[2][nptbins][ncentbins][najbins];
  TH2D * subtracted_corr[2][nptbins][ncentbins][najbins];
  TH2D *          result[2][nptbins][ncentbins][najbins];

  // double leadingjetptlow[] =     {100,100,100,100,100,100,100,100,100};
  // double leadingjetpthigh[] =    {120,120,120,300,300,300,300,300,300};
  // double subleadingjetptlow[] =  {50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 };
  // double subleadingjetpthigh[] = {120,120,120,300,300,300,300,300,300};
  // double ptasslow[] =            {2  ,3  ,5  ,2  ,3  ,3  ,1  ,2  ,3  };
  // double ptasshigh[] =           {3  ,5  ,8  ,3  ,4  ,4  ,2  ,3  ,4  };
  
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
  TString datamclumi[] = { "L_{int} = 150 #mub^{-1} " , "MC #hat{p}_{T}=100 embedded 377K evts" };
  TString datamc[] = { "PbPb  #sqrt{s_{NN}} = 2.76 TeV " , "" };
  
  for(int dataset = 0 ; dataset < 2 ; ++dataset)
  {
    for(int ptw = 0 ; ptw < 2 ; ++ptw)
    {
      for(int ptbin = 0 ; ptbin < nptbins ; ++ptbin)
      {
        for(int cent = 0 ; cent < ncentbins ; ++cent)
        {
          for(int aj = 0 ; aj < najbins ; ++aj)
          {
            for(int jetindex = 0 ; jetindex < 2 ; ++jetindex)
            {
              cout<<Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw)<<endl;
              
              //! Define the latex
              TLatex * lpreliminary = new TLatex( 0.02 , 0.03, Form("CMS Preliminary   %s   %s",datamc[dataset].Data(),datamclumi[dataset].Data()) );
              lpreliminary->SetNDC(1);
              lpreliminary->SetTextSize(lpreliminary->GetTextSize()*1.1);
              
              TLatex * lsigtitle = new TLatex( 0.0073 ,0.9557, Form("signal %s",ljetname[jetindex].Data()));
              lsigtitle->SetNDC(1);
              lsigtitle->SetTextSize(lsigtitle->GetTextSize()*1.1);
              
              TLatex * lbaktitle = new TLatex( 0.0073 ,0.9557, Form("background %s",ljetname[jetindex].Data()));
              lbaktitle->SetNDC(1);
              lbaktitle->SetTextSize(lbaktitle->GetTextSize()*1.1);

              TLatex * lcorrtitle = new TLatex( 0.0073 ,0.9557, Form("correlation function %s",ljetname[jetindex].Data()));
              lcorrtitle->SetNDC(1);
              lcorrtitle->SetTextSize(lcorrtitle->GetTextSize()*1.1);

              TLatex * llrsubtitle = new TLatex( 0.0073 ,0.9557, Form("long range sub CF %s",ljetname[jetindex].Data()));
              llrsubtitle->SetNDC(1);
              llrsubtitle->SetTextSize(llrsubtitle->GetTextSize()*1.1);

              TLatex * ljtpt = new TLatex( 0.0073 ,0.9057, Form("jet p_{T} %d-%d GeV/c",(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin]));
              ljtpt->SetNDC(1);
              ljtpt->SetTextSize(ljtpt->GetTextSize()*1.1);

              TLatex * ltrkpt = new TLatex( 0.0073 ,0.8557, Form("track p_{T} %d-%d GeV/c",(int)ptasslow[ptbin],(int)ptasshigh[ptbin]));
              ltrkpt->SetNDC(1);
              ltrkpt->SetTextSize(ltrkpt->GetTextSize()*1.1);

              TLatex * laj = new TLatex( 0.7777 ,0.9557, Form("A_{J} %2.2f-%2.2f",ajmin[aj],ajmax[aj]));
              laj->SetNDC(1);
              laj->SetTextSize(laj->GetTextSize()*1.1);

              TLatex * lcent = new TLatex( 0.7777 ,0.9057, Form("%2.0f-%2.0f %%",2.5*centmin[cent],2.5*centmax[cent]));
              lcent->SetNDC(1);
              lcent->SetTextSize(lcent->GetTextSize()*1.1);

              TLatex * lptw = new TLatex( 0.7777 ,0.8557, Form("%s",ptweight[ptw].Data()));
              lptw->SetNDC(1);
              lptw->SetTextSize(lptw->GetTextSize()*1.1);

              //! extract the signal
              TCanvas * c1 = new TCanvas(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              sig[jetindex][ptbin][cent][aj] = (TH2D*)f1[dataset][ptw]->Get(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100)));
              sig[jetindex][ptbin][cent][aj]->Draw("surf1");

              lsigtitle->Draw("same");
              ljtpt->Draw("same");
              ltrkpt->Draw("same");
              // laj->Draw("same");
              lcent->Draw("same");
              lptw->Draw("same");
              lpreliminary->Draw("same");
              
              //! extract the background
              TCanvas * c2 = new TCanvas(Form("background_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              bak[jetindex][ptbin][cent][aj] = (TH2D*)f1[dataset][ptw]->Get(Form("background_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100)));
              bak[jetindex][ptbin][cent][aj]->Draw("surf1");
              
              lbaktitle->Draw("same");
              ljtpt->Draw("same");
              ltrkpt->Draw("same");
              // laj->Draw("same");
              lcent->Draw("same");
              lptw->Draw("same");
              lpreliminary->Draw("same");
              
              //! construct the correlation function by dividing sig / bak and normalize
              TCanvas * c3 = new TCanvas(Form("corr_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              corr[jetindex][ptbin][cent][aj] = (TH2D*)sig[jetindex][ptbin][cent][aj]->Clone(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              corr[jetindex][ptbin][cent][aj]->Divide(bak[jetindex][ptbin][cent][aj]);
              if(bak[jetindex][ptbin][cent][aj]->GetBinContent(bak[jetindex][ptbin][cent][aj]->FindBin(0,0)) != 0)
              {
                corr[jetindex][ptbin][cent][aj]->Scale(bak[jetindex][ptbin][cent][aj]->GetBinContent(bak[0][ptbin][cent][aj]->FindBin(0,0)));
              }
              corr[jetindex][ptbin][cent][aj]->GetXaxis()->SetRange(corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(-4.0),corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(4.0));
              corr[jetindex][ptbin][cent][aj]->GetYaxis()->SetRange(corr[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(-3.1415926/2.0),corr[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(3*3.1415926/2.0));
              corr[jetindex][ptbin][cent][aj]->Draw("surf1");
              
              lcorrtitle->Draw("same");
              ljtpt->Draw("same");
              ltrkpt->Draw("same");
              // laj->Draw("same");
              lcent->Draw("same");
              lptw->Draw("same");
              lpreliminary->Draw("same");
              
              //! Construct the long range projection to be subtracted
              int xmin = corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(1);
              int xmax = corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(1.6);
              proj[jetindex][ptbin][cent][aj] = corr[jetindex][ptbin][cent][aj]->ProjectionY(Form("proj_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw),xmin,xmax);
              double nbins = xmax - xmin + 1;
              proj[jetindex][ptbin][cent][aj]->Scale(1/nbins);
              
              //! Construct the long range subtracted CF
              TCanvas * c5 = new TCanvas(Form("result_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              subtracted_corr[jetindex][ptbin][cent][aj] = (TH2D*) corr[jetindex][ptbin][cent][aj]->Clone(Form("subtracted_corr_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              int xstart = corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(-4.0);
              int xend = corr[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(4.0);
              int ystart = corr[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(-TMath::Pi()/2.);
              int yend = corr[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(3*TMath::Pi()/2.);
              for(int m = ystart ; m < yend ; ++m)
              { 
                double ypos = corr[jetindex][ptbin][cent][aj]->GetYaxis()->GetBinCenter(m);
                int thisbin = proj[jetindex][ptbin][cent][aj]->FindBin(ypos);
                double meanvalue = proj[jetindex][ptbin][cent][aj]->GetBinContent(thisbin);
                
                for(int n = xstart ;n < xend ; ++n)
                {
                  subtracted_corr[jetindex][ptbin][cent][aj]->SetBinContent(n,m,meanvalue);
                }
              }
              result[jetindex][ptbin][cent][aj] = (TH2D*) corr[jetindex][ptbin][cent][aj]->Clone(Form("result_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              subtracted_corr[jetindex][ptbin][cent][aj]->Scale(-1);
              result[jetindex][ptbin][cent][aj]->Add(subtracted_corr[jetindex][ptbin][cent][aj]);
              result[jetindex][ptbin][cent][aj]->GetYaxis()->SetRange(result[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(-TMath::Pi()/2.),result[jetindex][ptbin][cent][aj]->GetYaxis()->FindBin(TMath::Pi()/2.));
              result[jetindex][ptbin][cent][aj]->GetXaxis()->SetRange(result[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(-1.6),result[jetindex][ptbin][cent][aj]->GetXaxis()->FindBin(1.6));
              result[jetindex][ptbin][cent][aj]->Draw("surf1");
              
              llrsubtitle->Draw("same");
              ljtpt->Draw("same");
              ltrkpt->Draw("same");
              // laj->Draw("same");
              lcent->Draw("same");
              lptw->Draw("same");
              lpreliminary->Draw("same");
              
              

              //! Save the plots
              // c1->SaveAs(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.png",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              // c2->SaveAs(Form("background_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.png",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              // c3->SaveAs(Form("corr_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.png",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              c5->SaveAs(Form("longrangesubCF_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.png",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              // c1->SaveAs(Form("signal_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.pdf",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              // c2->SaveAs(Form("background_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.pdf",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              // c3->SaveAs(Form("corr_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.pdf",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              c5->SaveAs(Form("longrangesubCF_%sjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d_ismc%d_isptweighted%d.pdf",jetname[jetindex].Data(),(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)(ajmax[aj]*100),dataset,ptw));
              
              if( doleadsubleading==0 ) break; //! jetindex
            }
            if( doaj==0 ) break; //! ajbin
          }
          if( docent==0 ) break; //! centbin
        }
        if( dotrkpt==0 ) break;  //! ass trk pt bin
      }
      if( doptweight==0 ) break;  //! pt weight
    }
    if( domc==0 ) break;  //! dataset
  }  
} 

