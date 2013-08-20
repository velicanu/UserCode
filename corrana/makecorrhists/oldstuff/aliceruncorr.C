#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/alicecorrana.C"
#include <fstream>
#include <iostream>

void aliceruncorr(int filenum = 4)
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


  alicecorrana(listoffiles[filenum].data());
  
  double pttriglow[] = {2,3,3,4,4};
  double pttrighigh[] = {3,4,4,8,8};
  double ptasslow[] = {1,1,2,1,2};
  double ptasshigh[] = {2,2,3,2,3};
  int centmin[] = {0,4,8,16,24};
  int centmax[] = {4,8,16,24,28};
  TFile * outf = new TFile(Form("acorrhists_%d.root",filenum),"recreate");
  
  // for(int i = 0 ; i < 9 ; ++i)
  // for(int i = 0 ; i < 1 ; ++i)
  for(int cent = 4 ; cent < 5 ; ++cent)
  {
    for(int i = 4 ; i < 5 ; ++i)
    {
      cout<<"pt iteration "<<i<<endl;
      // for(int cent = 0 ; cent < 3 ; ++cent)
      // for(int cent = 0 ; cent < 1 ; ++cent)
      cout<<"cent iteration "<<cent<<endl;
      TH2D * ttsig = TrackTrackSignal(pttriglow[i],pttrighigh[i],ptasslow[i],ptasshigh[i],centmin[cent],centmax[cent]);
      TH2D * ttbak = TrackTrackBackground(pttriglow[i],pttrighigh[i],ptasslow[i],ptasshigh[i],centmin[cent],centmax[cent]);
      // TCanvas * c1 = new TCanvas();
      // ttsig->Draw("surf1");
      // TCanvas * c2 = new TCanvas();
      // ttbak->Draw("surf1");
      // TCanvas * c3 = new TCanvas();
      TH2D * ttcorr = (TH2D*)ttsig->Clone(Form("corr_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow[i],(int)pttrighigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent]));
      ttcorr->Divide(ttbak);
      ttcorr->Scale(ttbak->GetBinContent(ttbak->FindBin(0,0)));
      ttcorr->GetXaxis()->SetRange(ttcorr->GetXaxis()->FindBin(-1.6),ttcorr->GetXaxis()->FindBin(1.6));
      ttcorr->GetYaxis()->SetRange(ttcorr->GetYaxis()->FindBin(-3.1415926/2.0),ttcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      // ttcorr->Draw("surf1");
    }
    // TH1D * hnTrk = GetNtrk(centmin[cent],centmax[cent]);
  }
  
  outf->Write();
  outf->Close();
}