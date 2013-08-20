#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/oldstuff/corrana.C"
#include <fstream>

void runcorr(int filenum)
{


  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile("/net/hisrv0001/home/dav2105/corrana/makecorrhists/oldstuff/sortedforests.txt");

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


  corrana(listoffiles[filenum].data());
  
  double pttriglow[] = {1,4};
  double pttrighigh[] = {2,8};
  double ptasslow[] = {1,2};
  double ptasshigh[] = {2,3};
  int centmin[] = {0,4,8,12,16,20,24,28,32};
  int centmax[] = {40,8,12,16,20,24,28,32,36};
  TFile * outf = new TFile(Form("corrhists_%d.root",filenum),"recreate");
  
  // for(int i = 0 ; i < 9 ; ++i)
  // for(int i = 0 ; i < 2 ; ++i)
  for(int i = 0 ; i < 1 ; ++i)
  {
    cout<<"pt iteration "<<i<<endl;
    // for(int cent = 0 ; cent < 3 ; ++cent)
    // for(int cent = 0 ; cent < 9 ; ++cent)
    for(int cent = 0 ; cent < 1 ; ++cent)
    {
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
      ttcorr->GetXaxis()->SetRange(ttcorr->GetXaxis()->FindBin(-4.0),ttcorr->GetXaxis()->FindBin(4.0));
      ttcorr->GetYaxis()->SetRange(ttcorr->GetYaxis()->FindBin(-3.1415926/2.0),ttcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
      // ttcorr->Draw("surf1");
    }
  }
  
  outf->Write();
  outf->Close();
}