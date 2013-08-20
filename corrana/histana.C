#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TF2.h"
#include "TMath.h"
#include "TH2D.h"
#include "TCanvas.h"

void histana()
{
  const double pi = 3.1415926;
  // TFile *_file0 = TFile::Open("corrhists.root");
  TFile *_file0 = TFile::Open("/net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/merged/mccorrhistsv0.root");
  
  
  
  
  
  TH2D * corr_trg2_3_ass1_2_cmin0_cmax4 = (TH2D*)_file0->Get("corr_trg2_3_ass1_2_cmin0_cmax4");
  
  int xmin_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(1);
  int xmax_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(1.6);
  // int xmin_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(2);
  // int xmax_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(4);
  cout << xmin_trg2_3_ass1_2_cmin0_cmax4 << " " << xmax_trg2_3_ass1_2_cmin0_cmax4 <<endl;
  TH1D * projx_corr_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->ProjectionY("projx_corr_trg2_3_ass1_2_cmin0_cmax4",xmin_trg2_3_ass1_2_cmin0_cmax4,xmax_trg2_3_ass1_2_cmin0_cmax4);
  double nbins_trg2_3_ass1_2_cmin0_cmax4 = xmax_trg2_3_ass1_2_cmin0_cmax4 - xmin_trg2_3_ass1_2_cmin0_cmax4 + 1;
  projx_corr_trg2_3_ass1_2_cmin0_cmax4->Scale(1/nbins_trg2_3_ass1_2_cmin0_cmax4);

  TH2D * subtracted_corr_trg2_3_ass1_2_cmin0_cmax4 = (TH2D*) corr_trg2_3_ass1_2_cmin0_cmax4->Clone("subtracted_corr_trg2_3_ass1_2_cmin0_cmax4");
  
  int xstart_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(-1.6);
  int xend_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetXaxis()->FindBin(1.6);

  int ystart_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->FindBin(-pi/2.);
  int yend_trg2_3_ass1_2_cmin0_cmax4 = corr_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->FindBin(3*pi/2.);
  
  for(int i = ystart_trg2_3_ass1_2_cmin0_cmax4 ; i < yend_trg2_3_ass1_2_cmin0_cmax4 ; ++i)
  {
    double ypos = corr_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->GetBinCenter(i);
    int thisbin = projx_corr_trg2_3_ass1_2_cmin0_cmax4->FindBin(ypos);
    double meanvalue = projx_corr_trg2_3_ass1_2_cmin0_cmax4->GetBinContent(thisbin);
    
    for(int j = xstart_trg2_3_ass1_2_cmin0_cmax4 ; j < xend_trg2_3_ass1_2_cmin0_cmax4 ; ++j)
    {
      subtracted_corr_trg2_3_ass1_2_cmin0_cmax4->SetBinContent(j,i,meanvalue);
    }
  }
  
  TH2D * result_trg2_3_ass1_2_cmin0_cmax4 = (TH2D*) corr_trg2_3_ass1_2_cmin0_cmax4->Clone("result_trg2_3_ass1_2_cmin0_cmax4");
  subtracted_corr_trg2_3_ass1_2_cmin0_cmax4->Scale(-1);
  result_trg2_3_ass1_2_cmin0_cmax4->Add(subtracted_corr_trg2_3_ass1_2_cmin0_cmax4);
  
  

  TCanvas * c1_trg2_3_ass1_2_cmin0_cmax4 = new TCanvas();
  corr_trg2_3_ass1_2_cmin0_cmax4->Draw("surf1");
  c1_trg2_3_ass1_2_cmin0_cmax4->SaveAs("MCc1_trg2_3_ass1_2_cmin0_cmax4.png");
  
  TCanvas * c2_trg2_3_ass1_2_cmin0_cmax4 = new TCanvas();
  projx_corr_trg2_3_ass1_2_cmin0_cmax4->Draw();
  c2_trg2_3_ass1_2_cmin0_cmax4->SaveAs("MCc2_trg2_3_ass1_2_cmin0_cmax4.png");
  TCanvas * c3_trg2_3_ass1_2_cmin0_cmax4 = new TCanvas();
  subtracted_corr_trg2_3_ass1_2_cmin0_cmax4->Draw("surf1");
  c3_trg2_3_ass1_2_cmin0_cmax4->SaveAs("MCc3_trg2_3_ass1_2_cmin0_cmax4.png");
  TCanvas * c4_trg2_3_ass1_2_cmin0_cmax4 = new TCanvas();
  result_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->SetRange(result_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->FindBin(-pi/2.),result_trg2_3_ass1_2_cmin0_cmax4->GetYaxis()->FindBin(pi/2.));
  result_trg2_3_ass1_2_cmin0_cmax4->Draw("surf1");
  c4_trg2_3_ass1_2_cmin0_cmax4->SaveAs("MCc4_trg2_3_ass1_2_cmin0_cmax4.png");
  // ====================================================
  // TF2 *fdasf2 = new TF2("f2","([0]*exp(-0.5*((x)/[1])**2)*exp(-0.5*((y)/[2])**2))",-1.6,1.6,-1.6,1.6);
  // fdasf2->SetParameters(0.1,0.1,0.1,0.1,0.1,0.1,0.1);
  // fdasf2->SetParameters(0.1,0.1,0.1,0.1,0.1,0.1);
  // fdasf2->SetParameters(0.1,0.1,0.1);
  // result_trg2_3_ass1_2_cmin0_cmax4->Fit(fdasf2,"N");
  // result_trg2_3_ass1_2_cmin0_cmax4->Scale(-1);
  // result_trg2_3_ass1_2_cmin0_cmax4->Add(fdasf2);
  // result_trg2_3_ass1_2_cmin0_cmax4->Scale(-1);
  
  // result_trg2_3_ass1_2_cmin0_cmax4->Draw("surf1");
  // fdasf2->Draw("surf same");
  
  
  // return;
  
  
  
  TH2D * corr_trg2_3_ass1_2_cmin28_cmax32 = (TH2D*)_file0->Get("corr_trg2_3_ass1_2_cmin28_cmax32");
  
  int xmin_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(1);
  int xmax_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(1.6);
  // int xmin_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(2);
  // int xmax_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(4);
  cout << xmin_trg2_3_ass1_2_cmin28_cmax32 << " " << xmax_trg2_3_ass1_2_cmin28_cmax32 <<endl;
  TH1D * projx_corr_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->ProjectionY("projx_corr_trg2_3_ass1_2_cmin28_cmax32",xmin_trg2_3_ass1_2_cmin28_cmax32,xmax_trg2_3_ass1_2_cmin28_cmax32);
  double nbins_trg2_3_ass1_2_cmin28_cmax32 = xmax_trg2_3_ass1_2_cmin28_cmax32 - xmin_trg2_3_ass1_2_cmin28_cmax32 + 1;
  projx_corr_trg2_3_ass1_2_cmin28_cmax32->Scale(1/nbins_trg2_3_ass1_2_cmin28_cmax32);

  TH2D * subtracted_corr_trg2_3_ass1_2_cmin28_cmax32 = (TH2D*) corr_trg2_3_ass1_2_cmin28_cmax32->Clone("subtracted_corr_trg2_3_ass1_2_cmin28_cmax32");
  
  int xstart_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(-1.6);
  int xend_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetXaxis()->FindBin(1.6);

  int ystart_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->FindBin(-pi/2.);
  int yend_trg2_3_ass1_2_cmin28_cmax32 = corr_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->FindBin(3*pi/2.);
  
  for(int i = ystart_trg2_3_ass1_2_cmin28_cmax32 ; i < yend_trg2_3_ass1_2_cmin28_cmax32 ; ++i)
  {
    double ypos = corr_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->GetBinCenter(i);
    int thisbin = projx_corr_trg2_3_ass1_2_cmin28_cmax32->FindBin(ypos);
    double meanvalue = projx_corr_trg2_3_ass1_2_cmin28_cmax32->GetBinContent(thisbin);
    
    for(int j = xstart_trg2_3_ass1_2_cmin28_cmax32 ; j < xend_trg2_3_ass1_2_cmin28_cmax32 ; ++j)
    {
      subtracted_corr_trg2_3_ass1_2_cmin28_cmax32->SetBinContent(j,i,meanvalue);
    }
  }
  
  TH2D * result_trg2_3_ass1_2_cmin28_cmax32 = (TH2D*) corr_trg2_3_ass1_2_cmin28_cmax32->Clone("result_trg2_3_ass1_2_cmin28_cmax32");
  subtracted_corr_trg2_3_ass1_2_cmin28_cmax32->Scale(-1);
  result_trg2_3_ass1_2_cmin28_cmax32->Add(subtracted_corr_trg2_3_ass1_2_cmin28_cmax32);
  
  

  TCanvas * c1_trg2_3_ass1_2_cmin28_cmax32 = new TCanvas();
  corr_trg2_3_ass1_2_cmin28_cmax32->Draw("surf1");
  TCanvas * c2_trg2_3_ass1_2_cmin28_cmax32 = new TCanvas();
  projx_corr_trg2_3_ass1_2_cmin28_cmax32->Draw();
  TCanvas * c3_trg2_3_ass1_2_cmin28_cmax32 = new TCanvas();
  subtracted_corr_trg2_3_ass1_2_cmin28_cmax32->Draw("surf1");
  TCanvas * c4_trg2_3_ass1_2_cmin28_cmax32 = new TCanvas();
  result_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->SetRange(result_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->FindBin(-pi/2.),result_trg2_3_ass1_2_cmin28_cmax32->GetYaxis()->FindBin(pi/2.));
  result_trg2_3_ass1_2_cmin28_cmax32->Draw("surf1");
      c4_trg2_3_ass1_2_cmin28_cmax32->SaveAs("MCc4_trg2_3_ass1_2_cmin28_cmax32.png");
  
  // TF2 *fdasf3 = new TF2("f2","([0]*exp(-0.5*((x)/[1])**2)*exp(-0.5*((y)/[2])**2))",-1.6,1.6,-1.6,1.6);
  // fdasf3->SetParameters(0.1,0.1,0.1);
  // result_trg2_3_ass1_2_cmin28_cmax32->Fit(fdasf3,"N");
  // fdasf2->SetParameters(0.1,0.1,0.1,0.1,0.1,0.1,0.1);
  // fdasf2->SetParameters(0.1,0.1,0.1,0.1,0.1,0.1);
  // result_trg2_3_ass1_2_cmin28_cmax32->Scale(-1);
  // result_trg2_3_ass1_2_cmin28_cmax32->Add(fdasf3);
  // result_trg2_3_ass1_2_cmin28_cmax32->Scale(-1);
  
  // result_trg2_3_ass1_2_cmin28_cmax32->Draw("surf1");
  // fdasf3->Draw("surf same");
  // ====================================================
  // ====================================================
  
  // return;
  
  TH2D * corr_trg4_8_ass2_3_cmin0_cmax4 = (TH2D*)_file0->Get("corr_trg4_8_ass2_3_cmin0_cmax4");
  
  int xmin_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(1);
  int xmax_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(1.6);
  // int xmin_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(2);
  // int xmax_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(4);
  cout << xmin_trg4_8_ass2_3_cmin0_cmax4 << " " << xmax_trg4_8_ass2_3_cmin0_cmax4 <<endl;
  TH1D * projx_corr_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->ProjectionY("projx_corr_trg4_8_ass2_3_cmin0_cmax4",xmin_trg4_8_ass2_3_cmin0_cmax4,xmax_trg4_8_ass2_3_cmin0_cmax4);
  double nbins_trg4_8_ass2_3_cmin0_cmax4 = xmax_trg4_8_ass2_3_cmin0_cmax4 - xmin_trg4_8_ass2_3_cmin0_cmax4 + 1;
  projx_corr_trg4_8_ass2_3_cmin0_cmax4->Scale(1/nbins_trg4_8_ass2_3_cmin0_cmax4);

  TH2D * subtracted_corr_trg4_8_ass2_3_cmin0_cmax4 = (TH2D*) corr_trg4_8_ass2_3_cmin0_cmax4->Clone("subtracted_corr_trg4_8_ass2_3_cmin0_cmax4");
  
  int xstart_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(-1.6);
  int xend_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetXaxis()->FindBin(1.6);

  int ystart_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->FindBin(-pi/2.);
  int yend_trg4_8_ass2_3_cmin0_cmax4 = corr_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->FindBin(3*pi/2.);
  
  for(int i = ystart_trg4_8_ass2_3_cmin0_cmax4 ; i < yend_trg4_8_ass2_3_cmin0_cmax4 ; ++i)
  {
    double ypos = corr_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->GetBinCenter(i);
    int thisbin = projx_corr_trg4_8_ass2_3_cmin0_cmax4->FindBin(ypos);
    double meanvalue = projx_corr_trg4_8_ass2_3_cmin0_cmax4->GetBinContent(thisbin);
    
    for(int j = xstart_trg4_8_ass2_3_cmin0_cmax4 ; j < xend_trg4_8_ass2_3_cmin0_cmax4 ; ++j)
    {
      subtracted_corr_trg4_8_ass2_3_cmin0_cmax4->SetBinContent(j,i,meanvalue);
    }
  }
  
  TH2D * result_trg4_8_ass2_3_cmin0_cmax4 = (TH2D*) corr_trg4_8_ass2_3_cmin0_cmax4->Clone("result_trg4_8_ass2_3_cmin0_cmax4");
  subtracted_corr_trg4_8_ass2_3_cmin0_cmax4->Scale(-1);
  result_trg4_8_ass2_3_cmin0_cmax4->Add(subtracted_corr_trg4_8_ass2_3_cmin0_cmax4);
  
  

  TCanvas * c1_trg4_8_ass2_3_cmin0_cmax4 = new TCanvas();
  corr_trg4_8_ass2_3_cmin0_cmax4->Draw("surf1");
  TCanvas * c2_trg4_8_ass2_3_cmin0_cmax4 = new TCanvas();
  projx_corr_trg4_8_ass2_3_cmin0_cmax4->Draw();
  TCanvas * c3_trg4_8_ass2_3_cmin0_cmax4 = new TCanvas();
  subtracted_corr_trg4_8_ass2_3_cmin0_cmax4->Draw("surf1");
  TCanvas * c4_trg4_8_ass2_3_cmin0_cmax4 = new TCanvas();
  result_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->SetRange(result_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->FindBin(-pi/2.),result_trg4_8_ass2_3_cmin0_cmax4->GetYaxis()->FindBin(pi/2.));
  result_trg4_8_ass2_3_cmin0_cmax4->Draw("surf1");
    c4_trg4_8_ass2_3_cmin0_cmax4->SaveAs("MCc4_trg4_8_ass2_3_cmin0_cmax4.png");
  // ====================================================
  
  
  
  
  TH2D * corr_trg4_8_ass2_3_cmin28_cmax32 = (TH2D*)_file0->Get("corr_trg4_8_ass2_3_cmin28_cmax32");
  
  int xmin_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(1);
  int xmax_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(1.6);
  // int xmin_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(2);
  // int xmax_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(4);
  cout << xmin_trg4_8_ass2_3_cmin28_cmax32 << " " << xmax_trg4_8_ass2_3_cmin28_cmax32 <<endl;
  TH1D * projx_corr_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->ProjectionY("projx_corr_trg4_8_ass2_3_cmin28_cmax32",xmin_trg4_8_ass2_3_cmin28_cmax32,xmax_trg4_8_ass2_3_cmin28_cmax32);
  double nbins_trg4_8_ass2_3_cmin28_cmax32 = xmax_trg4_8_ass2_3_cmin28_cmax32 - xmin_trg4_8_ass2_3_cmin28_cmax32 + 1;
  projx_corr_trg4_8_ass2_3_cmin28_cmax32->Scale(1/nbins_trg4_8_ass2_3_cmin28_cmax32);

  TH2D * subtracted_corr_trg4_8_ass2_3_cmin28_cmax32 = (TH2D*) corr_trg4_8_ass2_3_cmin28_cmax32->Clone("subtracted_corr_trg4_8_ass2_3_cmin28_cmax32");
  
  int xstart_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(-1.6);
  int xend_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetXaxis()->FindBin(1.6);

  int ystart_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->FindBin(-pi/2.);
  int yend_trg4_8_ass2_3_cmin28_cmax32 = corr_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->FindBin(3*pi/2.);
  
  for(int i = ystart_trg4_8_ass2_3_cmin28_cmax32 ; i < yend_trg4_8_ass2_3_cmin28_cmax32 ; ++i)
  {
    double ypos = corr_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->GetBinCenter(i);
    int thisbin = projx_corr_trg4_8_ass2_3_cmin28_cmax32->FindBin(ypos);
    double meanvalue = projx_corr_trg4_8_ass2_3_cmin28_cmax32->GetBinContent(thisbin);
    
    for(int j = xstart_trg4_8_ass2_3_cmin28_cmax32 ; j < xend_trg4_8_ass2_3_cmin28_cmax32 ; ++j)
    {
      subtracted_corr_trg4_8_ass2_3_cmin28_cmax32->SetBinContent(j,i,meanvalue);
    }
  }
  
  TH2D * result_trg4_8_ass2_3_cmin28_cmax32 = (TH2D*) corr_trg4_8_ass2_3_cmin28_cmax32->Clone("result_trg4_8_ass2_3_cmin28_cmax32");
  subtracted_corr_trg4_8_ass2_3_cmin28_cmax32->Scale(-1);
  result_trg4_8_ass2_3_cmin28_cmax32->Add(subtracted_corr_trg4_8_ass2_3_cmin28_cmax32);
  
  

  TCanvas * c1_trg4_8_ass2_3_cmin28_cmax32 = new TCanvas();
  corr_trg4_8_ass2_3_cmin28_cmax32->Draw("surf1");
  TCanvas * c2_trg4_8_ass2_3_cmin28_cmax32 = new TCanvas();
  projx_corr_trg4_8_ass2_3_cmin28_cmax32->Draw();
  TCanvas * c3_trg4_8_ass2_3_cmin28_cmax32 = new TCanvas();
  subtracted_corr_trg4_8_ass2_3_cmin28_cmax32->Draw("surf1");
  TCanvas * c4_trg4_8_ass2_3_cmin28_cmax32 = new TCanvas();
  result_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->SetRange(result_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->FindBin(-pi/2.),result_trg4_8_ass2_3_cmin28_cmax32->GetYaxis()->FindBin(pi/2.));
  result_trg4_8_ass2_3_cmin28_cmax32->Draw("surf1");
  
  c4_trg4_8_ass2_3_cmin28_cmax32->SaveAs("MCc4_trg4_8_ass2_3_cmin28_cmax32.png");
  // ====================================================
  // ====================================================
  
  
  
  
  
  
  
  
  
  
  
  // int 
}

