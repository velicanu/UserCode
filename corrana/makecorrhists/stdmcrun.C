#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/stdmc.C"
#include <fstream>

void stdruncorr(int condor_iter = 0, int doptweight = 0)
{
  const int nptbins = 4;
  const int ncentbins = 1;
  const int najbins = 4;
  
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile("/net/hisrv0001/home/dav2105/corrana/makecorrhists/mcsorted.txt");

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
  
  // exit(0);
  
  cout<<"opening: "<<listoffiles[filenum].data()<<endl;
  stdcorrana(listoffiles[filenum].data());
  double leadingjetptlow[] =     {100,100,100,100,100,100,100,100,100};
  double leadingjetpthigh[] =    {300,300,300,300,300,300,300,300,300};
  double subleadingjetptlow[] =  {50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 };
  double subleadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double ptasslow[] =            {1,  2  ,3  ,5  ,3  ,3  ,1  ,2  ,3  };
  double ptasshigh[] =           {2,  3  ,5  ,8  ,4  ,4  ,2  ,3  ,4  };


  // int centmin[] = {0,4,12,20};
  // int centmax[] = {4,12,20,40};
  
  int centmin[] = {0,4,12,20};
  int centmax[] = {12,12,20,40};
  
  float ajmin[] = { 0.00, 0.13, 0.24, 0.35 };
  float ajmax[] = { 0.13, 0.24, 0.35, 1.00 };
 
  
  TFile * outf = new TFile(Form("sssstdmc_ptw%d_%d.root",doptweight,condor_iter),"recreate");
  
  // if(dostdhists) makestdhists();
  
  // for(int i = 0 ; i < nptbins ; ++i)
  // {
    // cout<<"pt iteration "<<i<<endl;
    // for(int cent = 0 ; cent < dostdhists ; ++cent)
    // {
      // cout<<"cent iteration "<<cent<<endl;
      // for(int aj = 0 ; aj < najbins ; ++aj)
      // {
        // cout<<"aj iteration "<<aj<<endl;
        
        TH2D * ljtsig = JetTrackSignal    (0, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin]);
        TH2D * ljtbak = JetTrackBackground(0, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin]);
        TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[centbin],centmax[centbin],(int)(ajmin[ajbin]*100),(int)(ajmax[ajbin]*100)));
        ljtcorr->Divide(ljtbak);
        ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
        ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-4.0),ljtcorr->GetXaxis()->FindBin(4.0));
        ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
        
        TH2D * sljtsig = JetTrackSignal    (1, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin]);
        TH2D * sljtbak = JetTrackBackground(1, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin]);
        TH2D * sljtcorr = (TH2D*)sljtsig->Clone(Form("corr_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[centbin],centmax[centbin],(int)(ajmin[ajbin]*100),(int)(ajmax[ajbin]*100)));
        sljtcorr->Divide(sljtbak);
        sljtcorr->Scale(sljtbak->GetBinContent(sljtbak->FindBin(0,0)));
        sljtcorr->GetXaxis()->SetRange(sljtcorr->GetXaxis()->FindBin(-4.0),sljtcorr->GetXaxis()->FindBin(4.0));
        sljtcorr->GetYaxis()->SetRange(sljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),sljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
        // break;
      // }
      // break;
    // }
    // break;
  // }
  outf->Write();
  outf->Close();
}

