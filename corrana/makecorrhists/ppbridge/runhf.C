#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/hfcorr.C"
#include <fstream>

void runcorr(int condor_iter, int trackqual)
{

  const int nptbins = 1;
  const int ncentbins = 1;
  const int najbins = 1;
  
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  // ifstream infile("sortedforests.txt");
  ifstream infile("doeproposalforests.txt");

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
  bool dostdhists = (condor_iter%(nptbins * ncentbins * najbins) == 0);
  int ptbin = condor_iter % nptbins;
  int centbin = (condor_iter / nptbins) % ncentbins;
  int ajbin = (condor_iter / (nptbins * ncentbins)) % najbins;
  int filenum = (condor_iter / (nptbins * ncentbins * najbins));
  cout << "ipt: " << ptbin << " icent: " << centbin << " iaj: " << ajbin << " filenum: " << filenum << " dostdhists: " << dostdhists << endl;
 

  int nmin = 190 , nmax = 1000, one = 1;
  //! for first iteration of forest production
  /*
  if(filenum==0) { nmin = 110 ; nmax = 1000; }
  if(filenum==1) { nmin = 90  ; nmax = 110 ; }
  if(filenum>1 ) { nmin = 0   ; nmax = 35  ; }
  if(filenum>9 ) { nmin = 35  ; nmax = 90  ; }
  */
  //! for second iteration of forest production
  // /*
  // if(filenum<24 ) { nmin = 90  ; nmax = 110 ; }
  // if(filenum<22 ) { nmin = 35  ; nmax = 90  ; }
  // if(filenum<12 ) { nmin = 110 ; nmax = 1000; }
  // if(filenum<10 ) { nmin = 0   ; nmax = 35  ; }
  // */
  //! for second iteration of forest production
  /*
  if(filenum<26 ) { nmin = 90  ; nmax = 110 ; }
  if(filenum<23 ) { nmin = 35  ; nmax = 90  ; }
  if(filenum<13)  { nmin = 110 ; nmax = 1000; }
  if(filenum<10)  { nmin = 0   ; nmax = 35  ; }
  */
  corrana(listoffiles[filenum].data(),trackqual);
  
  
  double pttriglow[] =  {1   ,1 ,2 ,3, 1};
  double pttrighigh[] = {3   ,2 ,3 ,4, 3};
  double ptasslow[] =   {0.25 ,1 ,2 ,3, 1};
  double ptasshigh[] =  {3   ,2 ,3 ,4, 3};
  
  
  int centmin[] = {1,0,4,8,12,16,20,24,28,32};
  int centmax[] = {1,41,8,12,16,20,24,28,32,36};
  TFile * outf = new TFile(Form("corrhists_trkhfplus_trkqaul%d_nmin%d_nmax%d_ptmin%d_ptmax%d_%d.root",trackqual,nmin,nmax,(int)pttriglow[ptbin]/one,(int)pttrighigh[ptbin]/one,filenum),"recreate");
  
  int i = 0;
  int cent = 0;

  cout<<"cent iteration "<<cent<<endl;
  TH2D * ttsig = HFTrackSignal(pttriglow[ptbin],pttrighigh[ptbin],ptasslow[ptbin],ptasshigh[ptbin],centmin[cent],centmax[cent],nmin,nmax);
  TH2D * ttbak = HFTrackBackground(pttriglow[ptbin],pttrighigh[ptbin],ptasslow[ptbin],ptasshigh[ptbin],centmin[cent],centmax[cent],nmin,nmax);

  // TH1I * hntottrig = new TH1I(Form("nttottrig_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow[ptbin],(int)pttrighigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent]),"",1,0.5,1.5);
  // int myntottrig = GetNTotTrig();
  // hntottrig->Fill(1,myntottrig);
  // cout<<"ntottrig: "<<myntottrig<<endl;

  TH2D * ttcorr = (TH2D*)ttsig->Clone(Form("corr_trg%d_%d_ass%d_%d_cmin%d_cmax%d",(int)pttriglow[ptbin],(int)pttrighigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[cent],centmax[cent]));
  ttcorr->Divide(ttbak);
  ttcorr->Scale(ttbak->GetBinContent(ttbak->FindBin(4,0)));
  ttcorr->Scale(1/0.0594998609); //! bin width
  ttcorr->GetXaxis()->SetRange(ttcorr->GetXaxis()->FindBin(1),ttcorr->GetXaxis()->FindBin(7));
  ttcorr->GetYaxis()->SetRange(ttcorr->GetYaxis()->FindBin(-3.1415926/2.0),ttcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
  
  outf->Write();
  outf->Close();
}