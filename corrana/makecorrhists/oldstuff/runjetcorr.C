#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/alicecorrana.C"
#include <fstream>

void runjetcorr(int filenum = 0)
{


  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile("/net/hisrv0001/home/dav2105/corrana/makecorrhists/sortedforests.txt");

  if (!infile.is_open()) {
    cout << "Error opening file. Exiting." << endl;
    return;
  } else {
    while (!infile.eof()) {
      infile >> buffer;
      listoffiles.push_back(buffer);
      nlines++;
    }
  }

  // int filenum = 13;
  
  cout<<"opening: "<<listoffiles[filenum].data()<<endl;
  // alicecorrana("/mnt/hadoop/cms/store/user/velicanu/mergedv1_sortedforest/mergesortv1_2.root");
  alicecorrana(listoffiles[filenum].data());
  
  double leadingjetptlow[] = {120,90,60,120,90,60,120,90,60};
  double leadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double subleadingjetptlow[] = {50,50,50,50,50,50,50,50,50};
  double subleadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double ptasslow[] = {1,1,1,2,2,2,3,3,3};
  double ptasshigh[] = {2,2,2,3,3,3,4,4,4};
  int centmin[] = {0,4,8,16,24};
  int centmax[] = {4,8,16,24,28};
  TFile * outf = new TFile(Form("jetcorrhists_%d.root",filenum),"recreate");
  
  for(int i = 0 ; i < 9 ; ++i)
  {
    cout<<"pt iteration "<<i<<endl;
    // for(int cent = 0 ; cent < 3 ; ++cent)
    // for(int cent = 0 ; cent < 9 ; ++cent)
    for(int cent = 0 ; cent < 5 ; ++cent)
    {
      cout<<"cent iteration "<<cent<<endl;
      TH2D * ljtsig = JetTrackSignal(0, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent]);
      TH2D * ljtbak = JetTrackBackground(0, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent]);
      TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      ljtcorr->Divide(ljtbak);
      ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
      ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-1.6),ljtcorr->GetXaxis()->FindBin(1.6));
      ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      
      TH2D * sljtsig = JetTrackSignal(1, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent]);
      TH2D * sljtbak = JetTrackBackground(1, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent]);
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