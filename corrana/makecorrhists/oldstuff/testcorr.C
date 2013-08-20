#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/alicecorrana.C"
#include <fstream>

void testcorr(int filenum = 0)
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

  cout<<"opening: "<<listoffiles[filenum].data()<<endl;
  alicecorrana(listoffiles[filenum].data());
  
  double pttriglow[] = {2,4};
  double pttrighigh[] = {3,8};
  double ptasslow[] = {1,2};
  double ptasshigh[] = {2,3};
  int centmin[] = {0,4,8,12,16,20,24,28,32};
  int centmax[] = {4,8,12,16,20,24,28,32,36};
  TFile * outf = new TFile(Form("corrhists_%d.root",filenum),"recreate");
  
  for(int i = 0 ; i < 1 ; ++i)
  {
    cout<<"pt iteration "<<i<<endl;
    // for(int cent = 0 ; cent < 3 ; ++cent)
    // for(int cent = 0 ; cent < 9 ; ++cent)
    for(int cent = 0 ; cent < 1 ; ++cent)
    {
      cout<<"cent iteration "<<cent<<endl;
      // TH2D * ljtsig = JetTrackSignal(pttriglow[i],pttrighigh[i],ptasslow[i],ptasshigh[i],centmin[cent],centmax[cent]);
      TH2D * ljtsig = JetTrackSignal(0, 90, 300 , 50 , 300 , 1 , 2, 4, 8);
      TH2D * ljtbak = JetTrackBackground(0, 90, 300 , 50 , 300 , 1 , 2, 4, 8);
      // TH2D * ljtbak = TrackTrackBackground(pttriglow[i],pttrighigh[i],ptasslow[i],ptasshigh[i],centmin[cent],centmax[cent]);
      TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow[i],(int)pttrighigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      ljtcorr->Divide(ljtbak);
      ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
      ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-1.6),ljtcorr->GetXaxis()->FindBin(1.6));
      ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      
      TH2D * sljtsig = JetTrackSignal(1, 90, 300 , 50 , 300 , 1 , 2, 4, 8);
      TH2D * sljtbak = JetTrackBackground(1, 90, 300 , 50 , 300 , 1 , 2, 4, 8);
      // TH2D * sljtbak = TrackTrackBackground(pttriglow[i],pttrighigh[i],ptasslow[i],ptasshigh[i],centmin[cent],centmax[cent]);
      TH2D * sljtcorr = (TH2D*)sljtsig->Clone(Form("corr_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow[i],(int)pttrighigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      sljtcorr->Divide(sljtbak);
      sljtcorr->Scale(sljtbak->GetBinContent(sljtbak->FindBin(0,0)));
      sljtcorr->GetXaxis()->SetRange(sljtcorr->GetXaxis()->FindBin(-1.6),sljtcorr->GetXaxis()->FindBin(1.6));
      sljtcorr->GetYaxis()->SetRange(sljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),sljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      
      
    }
  }
  outf->Write();
  outf->Close();
}