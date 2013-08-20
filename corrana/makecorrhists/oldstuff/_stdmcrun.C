#include "/net/hisrv0001/home/dav2105/corrana/makecorrhists/stdmc.C"
#include <fstream>

void stdruncorr(int filenum = 0, int doptweight = 0)
{


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

  
  cout<<"opening: "<<listoffiles[filenum].data()<<endl;
  stdcorrana(listoffiles[filenum].data());
  double leadingjetptlow[] =     {100,100,100,100,100,100,100,100,100};
  double leadingjetpthigh[] =    {300,300,300,300,300,300,300,300,300};
  double subleadingjetptlow[] =  {50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 };
  double subleadingjetpthigh[] = {300,300,300,300,300,300,300,300,300};
  double ptasslow[] =            {2  ,3  ,5  ,1  ,3  ,3  ,1  ,2  ,3  };
  double ptasshigh[] =           {3  ,5  ,8  ,2  ,4  ,4  ,2  ,3  ,4  };


  int centmin[] = {0,4,12,20};
  int centmax[] = {4,12,20,40};
  
  float ajmin[] = { 0.00, 0.13, 0.24, 0.35 };
  float ajmax[] = { 0.13, 0.24, 0.35, 1.00 };
 
  
  TFile * outf = new TFile(Form("sstdmc_ptw%d_%d.root",doptweight,filenum),"recreate");
  
  makestdhists();
  
  for(int i = 0 ; i < 4 ; ++i)
  {
  // break;
    cout<<"pt iteration "<<i<<endl;
    for(int cent = 0 ; cent < 4 ; ++cent)
    {
      cout<<"cent iteration "<<cent<<endl;
      for(int aj = 0 ; aj < 4 ; ++aj)
      {
        cout<<"aj iteration "<<aj<<endl;
        // makethisstdhists(leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent],ajmin[aj],ajmax[aj]);
        // break;
        
        TH2D * ljtsig = JetTrackSignal    (0, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent],ajmin[aj],ajmax[aj],doptweight);
        TH2D * ljtbak = JetTrackBackground(0, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent],ajmin[aj],ajmax[aj],doptweight);
        TH2D * ljtcorr = (TH2D*)ljtsig->Clone(Form("corr_leadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)ajmax[aj]*100));
        ljtcorr->Divide(ljtbak);
        ljtcorr->Scale(ljtbak->GetBinContent(ljtbak->FindBin(0,0)));
        ljtcorr->GetXaxis()->SetRange(ljtcorr->GetXaxis()->FindBin(-4.0),ljtcorr->GetXaxis()->FindBin(4.0));
        ljtcorr->GetYaxis()->SetRange(ljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),ljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
        
        TH2D * sljtsig = JetTrackSignal    (1, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent],ajmin[aj],ajmax[aj],doptweight);
        TH2D * sljtbak = JetTrackBackground(1, leadingjetptlow[i], leadingjetpthigh[i] , subleadingjetptlow[i] , subleadingjetpthigh[i] , ptasslow[i] , ptasshigh[i], centmin[cent], centmax[cent],ajmin[aj],ajmax[aj],doptweight);
        TH2D * sljtcorr = (TH2D*)sljtsig->Clone(Form("corr_subleadingjet%d_%d_ass%d_%d_cmin%d_cmax%d_ajmin%d_ajmax%d",(int)leadingjetptlow[i],(int)leadingjetpthigh[i],(int)ptasslow[i],(int)ptasshigh[i],centmin[cent],centmax[cent],(int)(ajmin[aj]*100),(int)ajmax[aj]*100));
        sljtcorr->Divide(sljtbak);
        sljtcorr->Scale(sljtbak->GetBinContent(sljtbak->FindBin(0,0)));
        sljtcorr->GetXaxis()->SetRange(sljtcorr->GetXaxis()->FindBin(-4.0),sljtcorr->GetXaxis()->FindBin(4.0));
        sljtcorr->GetYaxis()->SetRange(sljtcorr->GetYaxis()->FindBin(-3.1415926/2.0),sljtcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
        break;
      }
    break;
    }
  break;
  }
  
  outf->Write();
  outf->Close();
}

