#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/alicecorrana.C"
#include <fstream>
 
void makeCFfromhists()
{

  // TFile * inf = new TFile("/net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/unmerged/jetcorrhists_13.root");
  TFile * inf = new TFile("/net/hidsk0001/d00/scratch/dgulhan/jet-track-minbias.root");
  
  double leadingjetptlow[] = {120,90,60,120,90,60,120,90,60};
  double leadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double subleadingjetptlow[] = {50,50,50,50,50,50,50,50,50};
  double subleadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double ptasslow[] = {1,1,1,2,2,2,3,3,3};
  double ptasshigh[] = {2,2,2,3,3,3,4,4,4};
  int centmin[] = {0,4,8,16,24};
  int centmax[] = {4,8,16,24,28};
  // TFile * outf = new TFile(Form("/net/hidsk0001/d00/scratch/dgulhan/newCFhists_jet-track-minbias.root"),"recreate");
  TFile * outf = new TFile(Form("newCFhists_jet-track-minbias.root"),"recreate");
  for(int i = 0 ; i < 9 ; ++i)
  {
    for(int cent = 0 ; cent < 5 ; ++cent)
    {
      TH2D * ljtsig = (TH2D*)inf->Get(Form("signal_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      TH2D * ljtbak = (TH2D*)inf->Get(Form("background_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      ljtcorr->Divide(ljtbak);
      ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
      ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-1.6),ljtcorr->GetXaxis()->FindBin(1.6));
      ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      
      TH2D * sljtsig = (TH2D*)inf->Get(Form("signal_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      TH2D * sljtbak = (TH2D*)inf->Get(Form("background_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      TH2D * sljtcorr = (TH2D*)sljtsig->Clone(Form("corr_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      sljtcorr->Divide(sljtbak);
      sljtcorr->Scale(sljtbak->GetBinContent(sljtbak->FindBin(0,0)));
      sljtcorr->GetXaxis()->SetRange(sljtcorr->GetXaxis()->FindBin(-1.6),sljtcorr->GetXaxis()->FindBin(1.6));
      sljtcorr->GetYaxis()->SetRange(sljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),sljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      
    }
  }
  outf->Write();
  outf->Close();
}