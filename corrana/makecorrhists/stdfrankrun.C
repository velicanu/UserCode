#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/stdfrank.C"
#include <fstream>

void stdruncorr(int condor_iter = 0, int doptweight = 0, const char * infname = 0, const char * outftag = 0, int mccommand = 0, double jetamin = 0.0 , double jetamax = 2.0)
{
  const int nptbins = 3;
  const int ncentbins = 4;
  const int najbins = 1;
  
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  // ifstream infile("/net/hisrv0001/home/dav2105/corrana/makecorrhists/franksorted.txt");
  ifstream infile(infname);

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
  double ptasslow[] =            {1,  2  ,4  ,5  ,3  ,3  ,1  ,2  ,3  };
  double ptasshigh[] =           {2,  4  ,8  ,8  ,4  ,4  ,2  ,3  ,4  };


  // int centmin[] = {0,4,12,20};
  // int centmax[] = {4,12,20,40};
  
  int centmin[] = {0,4,12,20,0};
  int centmax[] = {4,12,20,40,12};
  
  float ajmin[] = { 0.00, 0.13, 0.24, 0.35 };
  float ajmax[] = { 0.13, 0.24, 0.35, 1.00 };
  
  TFile * outf = new TFile(Form("%s_eff%d_mctag%d_%d.root",outftag,doptweight,mccommand,condor_iter),"recreate");
  TH2D * ljtsig = JetTrackSignal    (0, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin],doptweight,mccommand,jetamin,jetamax);
  TH2D * ljtbak = JetTrackBackground(0, leadingjetptlow[ptbin], leadingjetpthigh[ptbin] , subleadingjetptlow[ptbin] , subleadingjetpthigh[ptbin] , ptasslow[ptbin] , ptasshigh[ptbin], centmin[centbin], centmax[centbin],ajmin[ajbin],ajmax[ajbin],doptweight,mccommand,jetamin,jetamax);
  TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow[ptbin],(int)leadingjetpthigh[ptbin],(int)ptasslow[ptbin],(int)ptasshigh[ptbin],centmin[centbin],centmax[centbin],(int)(ajmin[ajbin]*100),(int)(ajmax[ajbin]*100)));
  ljtcorr->Divide(ljtbak);
  ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
  ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-4.0),ljtcorr->GetXaxis()->FindBin(4.0));
  ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
        
  outf->Write();
  outf->Close();
}

