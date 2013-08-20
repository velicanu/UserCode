// #include "/net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/hiForest_charge.h"
#include "/net/hisrv0001/home/dav2105/hiforest/hiForest.h"


void trkqualdistros()
{
  // gROOT->ProcessLine(".L /net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/hiForest_charge.h+");
  HiForest * c = new HiForest("/mnt/hadoop/cms/store/user/yenjie/HiForest2PPb/PAPhysics-pt04-test.root","",cPPb);
  
  cout<<"before pi"<<endl;
  float pi = 3.1415926;
  cout<<"after pi"<<endl;
  // TH2D * hetaphi_qual;
  // TH1D * hdz_qual;
  // TH1D * hdxy_qual;
  // TH1D * hdz_dzerr_qual;
  // TH1D * hdxy_dxyerr_qual;
  // TH1D * hpterr_pt_qual;
  // TH1D * hnhits_qual;
  // TH1D * hchi2ndof_qual;
  // TH1D * hmult_qual;

  // int nmin = 0 , nmax = 1000;
  
  // cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  // hdz_qual = new TH1D("hdz_qual",Form(";dz quality_sel"),1000,-100,100);
  // hdz_dzerr_qual = new TH1D("hdz_dzerr_qual",Form(";dz/dzerr quality_sel"),1000,-50,50);
  // hdxy_qual = new TH1D("hdxy_qual",Form(";dxy quality_sel"),1000,-50,50);
  // hdxy_dxyerr_qual = new TH1D("hdxy_dxyerr_qual",Form(";dxy/dxyerr quality_sel"),1000,-50,50);
  // hpterr_pt_qual = new TH1D("hpterr_pt_qual",Form(";pterror/pt quality_sel"),1000,0,1);
  // hnhits_qual = new TH1D("hnhits_qual",Form(";nhits quality_sel"),80,0,80);
  // hchi2ndof_qual = new TH1D("hchi2ndof_qual",Form(";chi2/ndof quality_sel"),1000,0,10);
  // hetaphi_qual = new TH2D("hetaphi_qual",Form(";#eta quality_sel;#phi"),50,-2.5,2.5,62,-pi,pi);
  // hmult_qual = new TH1D("hmult_qual",Form(";N quality_sel"),500,0,500);
 

  
  TH1D * hdz_coll_highPurity;
  TH1D * hdxy_coll_highPurity;
  TH1D * hdz_dzerr_coll_highPurity;
  TH1D * hdxy_dxyerr_coll_highPurity;
  TH1D * hpterr_pt_coll_highPurity;
  TH1D * hnhits_coll_highPurity;
  TH1D * hchi2ndof_coll_highPurity;
  TH2D * hetaphi_coll_highPurity;
  TH1D * hmult_coll_highPurity;

  cout<<"after coll pointers"<<endl;
  
  // cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  hdz_coll_highPurity = new TH1D("hdz_coll_highPurity",Form(";dz coll highPurity"),1000,-100,100);
  hdz_dzerr_coll_highPurity = new TH1D("hdz_dzerr_coll_highPurity",Form(";dz/dzerr coll highPurity"),1000,-50,50);
  hdxy_coll_highPurity = new TH1D("hdxy_coll_highPurity",Form(";dxy coll highPurity"),1000,-50,50);
  hdxy_dxyerr_coll_highPurity = new TH1D("hdxy_dxyerr_coll_highPurity",Form(";dxy/dxyerr coll highPurity"),1000,-50,50);
  hpterr_pt_coll_highPurity = new TH1D("hpterr_pt_coll_highPurity",Form(";pterror/pt coll highPurity"),1000,0,1);
  hnhits_coll_highPurity = new TH1D("hnhits_coll_highPurity",Form(";nhits coll highPurity"),80,0,80);
  hchi2ndof_coll_highPurity = new TH1D("hchi2ndof_coll_highPurity",Form(";chi2/ndof coll highPurity"),1000,0,10);
  hetaphi_coll_highPurity = new TH2D("hetaphi_coll_highPurity",Form(";#eta coll highPurity;#phi"),50,-2.5,2.5,62,-pi,pi);
  hmult_coll_highPurity = new TH1D("hmult_coll_highPurity",Form(";N coll highPurity"),500,0,500);
 

  cout<<"before nocoll pointers"<<endl;
  
  TH1D * hdz_nocoll_highPurity;
  TH1D * hdxy_nocoll_highPurity;
  TH1D * hdz_dzerr_nocoll_highPurity;
  TH1D * hdxy_dxyerr_nocoll_highPurity;
  TH1D * hpterr_pt_nocoll_highPurity;
  TH1D * hnhits_nocoll_highPurity;
  TH1D * hchi2ndof_nocoll_highPurity;
  TH2D * hetaphi_nocoll_highPurity;
  TH1D * hmult_nocoll_highPurity;
  
  cout<<"after nocoll pointers"<<endl;
  // cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  hdz_nocoll_highPurity = new TH1D("hdz_nocoll_highPurity",Form(";dz !coll highPurity"),1000,-100,100);
  hdz_dzerr_nocoll_highPurity = new TH1D("hdz_dzerr_nocoll_highPurity",Form(";dz/dzerr !coll highPurity"),1000,-50,50);
  hdxy_nocoll_highPurity = new TH1D("hdxy_nocoll_highPurity",Form(";dxy !coll highPurity"),1000,-50,50);
  hdxy_dxyerr_nocoll_highPurity = new TH1D("hdxy_dxyerr_nocoll_highPurity",Form(";dxy/dxyerr !coll highPurity"),1000,-50,50);
  hpterr_pt_nocoll_highPurity = new TH1D("hpterr_pt_nocoll_highPurity",Form(";pterror/pt !coll highPurity"),1000,0,1);
  hnhits_nocoll_highPurity = new TH1D("hnhits_nocoll_highPurity",Form(";nhits !coll highPurity"),80,0,80);
  hchi2ndof_nocoll_highPurity = new TH1D("hchi2ndof_nocoll_highPurity",Form(";chi2/ndof !coll highPurity"),1000,0,10);
  hetaphi_nocoll_highPurity = new TH2D("hetaphi_nocoll_highPurity",Form(";#eta !coll highPurity;#phi"),50,-2.5,2.5,62,-pi,pi);
  hmult_nocoll_highPurity = new TH1D("hmult_nocoll_highPurity",Form(";N !coll highPurity"),500,0,500);
  
  cout<<"before hdz_coll_highPurity"<<endl;
  c->tree->Draw("trkDz1>>hdz_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDz1>>hdz_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdz_dzerr_coll_highPurity"<<endl;
  c->tree->Draw("trkDz1/trkDzError1>>hdz_dzerr_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDz1/trkDzError1>>hdz_dzerr_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdxy_coll_highPurity"<<endl;
  c->tree->Draw("trkDxy1>>hdxy_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDxy1>>hdxy_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdxy_dxyerr_coll_highPurity"<<endl;
  c->tree->Draw("trkDxy1/trkDxyError1>>hdxy_dxyerr_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDxy1/trkDxyError1>>hdxy_dxyerr_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hpterr_pt_coll_highPurity"<<endl;
  c->tree->Draw("trkPtError/trkPt>>hpterr_pt_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkPtError/trkPt>>hpterr_pt_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hnhits_coll_highPurity"<<endl;
  c->tree->Draw("trkNHit>>hnhits_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkNHit>>hnhits_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hchi2ndof_coll_highPurity"<<endl;
  c->tree->Draw("trkChi2/trkNdof>>hchi2ndof_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkChi2/trkNdof>>hchi2ndof_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hetaphi_coll_highPurity"<<endl;
  c->tree->Draw("trkEta:trkPhi>>hetaphi_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkEta:trkPhi>>hetaphi_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hmult_coll_highPurity"<<endl;
  c->tree->Draw("Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&abs(trkDxy1/trkDxyError1)<3&&trkPtError/trkPt<0.1)>>hmult_coll_highPurity","highPurity&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&abs(trkDxy1/trkDxyError1)<3&&trkPtError/trkPt<0.1)>>hmult_nocoll_highPurity","highPurity&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  
  TH1D * hdz_coll_nohighPurity;
  TH1D * hdxy_coll_nohighPurity;
  TH1D * hdz_dzerr_coll_nohighPurity;
  TH1D * hdxy_dxyerr_coll_nohighPurity;
  TH1D * hpterr_pt_coll_nohighPurity;
  TH1D * hnhits_coll_nohighPurity;
  TH1D * hchi2ndof_coll_nohighPurity;
  TH2D * hetaphi_coll_nohighPurity;
  TH1D * hmult_coll_nohighPurity;

  cout<<"after coll pointers"<<endl;
  
  // cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  hdz_coll_nohighPurity = new TH1D("hdz_coll_nohighPurity",Form(";dz coll !highPurity"),1000,-100,100);
  hdz_dzerr_coll_nohighPurity = new TH1D("hdz_dzerr_coll_nohighPurity",Form(";dz/dzerr coll !highPurity"),1000,-50,50);
  hdxy_coll_nohighPurity = new TH1D("hdxy_coll_nohighPurity",Form(";dxy coll !highPurity"),1000,-50,50);
  hdxy_dxyerr_coll_nohighPurity = new TH1D("hdxy_dxyerr_coll_nohighPurity",Form(";dxy/dxyerr coll !highPurity"),1000,-50,50);
  hpterr_pt_coll_nohighPurity = new TH1D("hpterr_pt_coll_nohighPurity",Form(";pterror/pt coll !highPurity"),1000,0,1);
  hnhits_coll_nohighPurity = new TH1D("hnhits_coll_nohighPurity",Form(";nhits coll !highPurity"),80,0,80);
  hchi2ndof_coll_nohighPurity = new TH1D("hchi2ndof_coll_nohighPurity",Form(";chi2/ndof coll !highPurity"),1000,0,10);
  hetaphi_coll_nohighPurity = new TH2D("hetaphi_coll_nohighPurity",Form(";#eta coll !highPurity;#phi"),50,-2.5,2.5,62,-pi,pi);
  hmult_coll_nohighPurity = new TH1D("hmult_coll_nohighPurity",Form(";N coll !highPurity"),500,0,500);
 

  cout<<"before nocoll pointers"<<endl;
  
  TH1D * hdz_nocoll_nohighPurity;
  TH1D * hdxy_nocoll_nohighPurity;
  TH1D * hdz_dzerr_nocoll_nohighPurity;
  TH1D * hdxy_dxyerr_nocoll_nohighPurity;
  TH1D * hpterr_pt_nocoll_nohighPurity;
  TH1D * hnhits_nocoll_nohighPurity;
  TH1D * hchi2ndof_nocoll_nohighPurity;
  TH2D * hetaphi_nocoll_nohighPurity;
  TH1D * hmult_nocoll_nohighPurity;
  
  cout<<"after nocoll pointers"<<endl;
  // cout<<"nmin: "<<nmin<<"   nmax: "<<nmax<<endl;
  hdz_nocoll_nohighPurity = new TH1D("hdz_nocoll_nohighPurity",Form(";dz !coll !highPurity"),1000,-100,100);
  hdz_dzerr_nocoll_nohighPurity = new TH1D("hdz_dzerr_nocoll_nohighPurity",Form(";dz/dzerr !coll !highPurity"),1000,-50,50);
  hdxy_nocoll_nohighPurity = new TH1D("hdxy_nocoll_nohighPurity",Form(";dxy !coll !highPurity"),1000,-50,50);
  hdxy_dxyerr_nocoll_nohighPurity = new TH1D("hdxy_dxyerr_nocoll_nohighPurity",Form(";dxy/dxyerr !coll !highPurity"),1000,-50,50);
  hpterr_pt_nocoll_nohighPurity = new TH1D("hpterr_pt_nocoll_nohighPurity",Form(";pterror/pt !coll !highPurity"),1000,0,1);
  hnhits_nocoll_nohighPurity = new TH1D("hnhits_nocoll_nohighPurity",Form(";nhits !coll !highPurity"),80,0,80);
  hchi2ndof_nocoll_nohighPurity = new TH1D("hchi2ndof_nocoll_nohighPurity",Form(";chi2/ndof !coll !highPurity"),1000,0,10);
  hetaphi_nocoll_nohighPurity = new TH2D("hetaphi_nocoll_nohighPurity",Form(";#eta !coll !highPurity;#phi"),50,-2.5,2.5,62,-pi,pi);
  hmult_nocoll_nohighPurity = new TH1D("hmult_nocoll_nohighPurity",Form(";N !coll !highPurity"),500,0,500);
  
  cout<<"before hdz_coll_nohighPurity"<<endl;
  c->tree->Draw("trkDz1>>hdz_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDz1>>hdz_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdz_dzerr_coll_nohighPurity"<<endl;
  c->tree->Draw("trkDz1/trkDzError1>>hdz_dzerr_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDz1/trkDzError1>>hdz_dzerr_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdxy_coll_nohighPurity"<<endl;
  c->tree->Draw("trkDxy1>>hdxy_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDxy1>>hdxy_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hdxy_dxyerr_coll_nohighPurity"<<endl;
  c->tree->Draw("trkDxy1/trkDxyError1>>hdxy_dxyerr_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkDxy1/trkDxyError1>>hdxy_dxyerr_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hpterr_pt_coll_nohighPurity"<<endl;
  c->tree->Draw("trkPtError/trkPt>>hpterr_pt_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkPtError/trkPt>>hpterr_pt_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hnhits_coll_nohighPurity"<<endl;
  c->tree->Draw("trkNHit>>hnhits_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkNHit>>hnhits_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hchi2ndof_coll_nohighPurity"<<endl;
  c->tree->Draw("trkChi2/trkNdof>>hchi2ndof_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkChi2/trkNdof>>hchi2ndof_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hetaphi_coll_nohighPurity"<<endl;
  c->tree->Draw("trkEta:trkPhi>>hetaphi_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("trkEta:trkPhi>>hetaphi_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  cout<<"before hmult_coll_nohighPurity"<<endl;
  c->tree->Draw("Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&abs(trkDxy1/trkDxyError1)<3&&trkPtError/trkPt<0.1)>>hmult_coll_nohighPurity","(!highPurity)&&phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter","goff");
  c->tree->Draw("Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&abs(trkDxy1/trkDxyError1)<3&&trkPtError/trkPt<0.1)>>hmult_nocoll_nohighPurity","(!highPurity)&&!(phfPosFilter1&&phfNegFilter1&&phltPixelClusterShapeFilter)","goff");
  
  
  
  
  
  
  // TFile * ffail = new TFile("track_quality_distros.root","recreate");
  TFile * ffail = new TFile("track_quality_distros_full.root","update");
  
  hdz_coll_highPurity->Write();
  hdxy_coll_highPurity->Write();
  hdz_dzerr_coll_highPurity->Write();
  hdxy_dxyerr_coll_highPurity->Write();
  hpterr_pt_coll_highPurity->Write();
  hnhits_coll_highPurity->Write();
  hchi2ndof_coll_highPurity->Write();
  hetaphi_coll_highPurity->Write();
  hmult_coll_highPurity->Write();

  hdz_nocoll_highPurity->Write();
  hdxy_nocoll_highPurity->Write();
  hdz_dzerr_nocoll_highPurity->Write();
  hdxy_dxyerr_nocoll_highPurity->Write();
  hpterr_pt_nocoll_highPurity->Write();
  hnhits_nocoll_highPurity->Write();
  hchi2ndof_nocoll_highPurity->Write();
  hetaphi_nocoll_highPurity->Write();
  hmult_nocoll_highPurity->Write();

  hdz_coll_nohighPurity->Write();
  hdxy_coll_nohighPurity->Write();
  hdz_dzerr_coll_nohighPurity->Write();
  hdxy_dxyerr_coll_nohighPurity->Write();
  hpterr_pt_coll_nohighPurity->Write();
  hnhits_coll_nohighPurity->Write();
  hchi2ndof_coll_nohighPurity->Write();
  hetaphi_coll_nohighPurity->Write();
  hmult_coll_nohighPurity->Write();

  hdz_nocoll_nohighPurity->Write();
  hdxy_nocoll_nohighPurity->Write();
  hdz_dzerr_nocoll_nohighPurity->Write();
  hdxy_dxyerr_nocoll_nohighPurity->Write();
  hpterr_pt_nocoll_nohighPurity->Write();
  hnhits_nocoll_nohighPurity->Write();
  hchi2ndof_nocoll_nohighPurity->Write();
  hetaphi_nocoll_nohighPurity->Write();
  hmult_nocoll_nohighPurity->Write();

  
   
  // hetaphi_coll->Write();
  // hdz_coll->Write();
  // hdxy_coll->Write();
  // hdz_dzerr_coll->Write();
  // hdxy_dxyerr_coll->Write();
  // hpterr_pt_coll->Write();
  // hnhits_coll->Write();
  // hchi2ndof_coll->Write();
  // hmult_coll->Write();
  
  // hetaphi_nocoll->Write();
  // hdz_nocoll->Write();
  // hdxy_nocoll->Write();
  // hdz_dzerr_nocoll->Write();
  // hdxy_dxyerr_nocoll->Write();
  // hpterr_pt_nocoll->Write();
  // hnhits_nocoll->Write();
  // hchi2ndof_nocoll->Write();
  // hmult_nocoll->Write();
  
  ffail->Write();
  ffail->Close();
}