#include "/net/hisrv0001/home/davidlw/useful_macros/Histograms.C"

void HFvsL1ETT_pPb()
{
  TFile* f = new TFile("HFvsL1ETT_pPb_v2.root");
  TCanvas* c = (TCanvas*)f->Get("aa");
  TH2D* hl1ettotvshf = (TH2D*)c->FindObject("hl1ettotvshf");
 
  TCanvas* cc = new TCanvas("cc","cc",550,500);
  cc->SetLogz();
  hl1ettotvshf->Draw("colz");
  SaveCanvas(cc,"pPb/trigger","HFvsL1ETT");

  TH1D* hhf = (TH1D*)hl1ettotvshf->ProjectionY("hhf",-1,-1,"e");
  TH1D* hhf_20 = (TH1D*)hl1ettotvshf->ProjectionY("hhf_20",5,60,"e");
  TH1D* hhf_40 = (TH1D*)hl1ettotvshf->ProjectionY("hhf_40",9,60,"e");
  TH1D* hhf_60 = (TH1D*)hl1ettotvshf->ProjectionY("hhf_60",13,60,"e");

  hhf_20->SetMarkerColor(2);
  hhf_40->SetMarkerColor(3);
  hhf_60->SetMarkerColor(4);

  TCanvas* cc1 = new TCanvas("cc1","cc1",550,500);
  cc1->SetLogy();
  hhf->Draw("PE");
  hhf_20->Draw("PESAME");
  hhf_40->Draw("PESAME");
  hhf_60->Draw("PESAME");
  SaveCanvas(cc1,"pPb/trigger","HF_dist");

  TCanvas* cc2 = new TCanvas("cc2","cc2",550,500);
  TH1D* hhf_20_ratio = (TH1D*)hhf_20->Clone("hhf_20_ratio");
  TH1D* hhf_40_ratio = (TH1D*)hhf_40->Clone("hhf_40_ratio");
  TH1D* hhf_60_ratio = (TH1D*)hhf_60->Clone("hhf_60_ratio");
  hhf_20_ratio->Divide(hhf_20_ratio,hhf,1,1,"b");
  hhf_40_ratio->Divide(hhf_40_ratio,hhf,1,1,"b");
  hhf_60_ratio->Divide(hhf_60_ratio,hhf,1,1,"b");
  hhf_20_ratio->Draw("PE");
  hhf_40_ratio->Draw("PESAME");
  hhf_60_ratio->Draw("PESAME");
  SaveCanvas(cc2,"pPb/trigger","Eff_HF");
}

void ana_L1Jet() 
{
  TFile *_file0 = TFile::Open("/mnt/hadoop/cms/store/user/yenjie/HiForest2PPb/PAPhysics-pt04-test.root");
//  TFile *_file0 = TFile::Open("/mnt/hadoop/cms/store/user/yilmaz/HiForest2_pPb_v5/PAPhysics/pPb_hiForest2_33_1_FHY.root");
  _file0->cd("ppTrack");
  trackTree->AddFriend("hltanalysis/HltTree");
  trackTree->AddFriend("ak5CaloJetAnalyzer/t");
  trackTree->AddFriend("hiEvtAnalyzer/HiTree");
  
  TH1D * hl1ett = new TH1D("hl1ett",";L1ETT",150,0,150);
  TH1D * hntrk = new TH1D("hntrk",";nTrk",250,0,250);
  TH2D * hntrkl1ett = new TH2D("hntrkl1ett",";nTrk;L1ETT",250,0,250,50,0,50);
  TH1D * htrkpt = new TH1D("htrkpt",";Max$(trkPt*(abs(trkEta)<2.4&&highPurity))",50,0,50);
  TH1D * htrkpt_l1jet16 = new TH1D("htrkpt_l1jet16",";Max$(trkPt*(abs(trkEta)<2.4&&highPurity))",50,0,50);

  TH1D * htrkpte3 = new TH1D("htrkpte3",";max trkPt && nTrk > 165",300,0,300);
  TH1D * htrkpte4 = new TH1D("htrkpte4",";max trkPt && nTrk > 195",300,0,300);
  
  TH1D * hl1ettrate = new TH1D("hl1ettrate",";L1ETT cut;rate",150,0,150);
  TH1D * hntrkrate = new TH1D("hntrkrate",";nTrk cut;rate",250,0,250);
  TH1D * htrkptrate = new TH1D("htrkptrate",";Max trkPt cut;rate",50,0,50);
  TH1D * htrkpte3rate = new TH1D("htrkpte3rate",";Max trkPt cut;rate",300,0,300);
  TH1D * htrkpte4rate = new TH1D("htrkpte4rate",";Max trkPt cut;rate",300,0,300);

  TH2D * htrkptl1jetet = new TH2D("htrkptl1jetet",";All L1 Jet E_{T};Track p^{max}_{T}",100,0,100,100,0,100);
  TH1D * hl1cenjetet = new TH1D("hl1cenjetet",";E_{T}",100,0,50);
  TH1D * hl1taujetet = new TH1D("hl1taujetet",";E_{T}",100,0,50);
  TH1D * hl1cenjetet_l1jet16 = new TH1D("hl1cenjetet_l1jet16",";E_{T}",100,0,50);
  TH1D * hl1taujetet_l1jet16 = new TH1D("hl1taujetet_l1jet16",";E_{T}",100,0,50);
  TH1D * hjetpt_l1jet16 = new TH1D("hjetpt_l1jet16",";E_{T}",100,0,100);
  TH1D * hjetpt = new TH1D("hjetpt",";E_{T}",100,0,100);
  TH1D * hl1ettot = new TH1D("hl1ettot",";L1_ETT (GeV)",60,0,300);
  TH1D * hl1ettot_pu2 = new TH1D("hl1ettot_pu2",";L1_ETT (GeV)",60,0,300);
  TH1D * hl1ettot_pu3 = new TH1D("hl1ettot_pu3",";L1_ETT (GeV)",60,0,300);

  TH2D * hl1ettotvshf = new TH2D("hl1ettotvshf",";L1_ETT (GeV); HF sum (GeV)",60,0,300,100,0,1000);
  TH2D * hl1ettotvsntracks = new TH2D("hl1ettotvsntracks",";L1_ETT (GeV); N_{trk}^{offline}",60,0,300,100,0,1000);
  TH2D * hl1ntracksvshf = new TH2D("hl1ntracksvshf",";N_{trk}^{offline};HF sum (GeV)",250,0,250,100,0,1000);

  trackTree->Draw("Sum$(abs(trkCharge)*(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&abs(trkDz1/trkDzError1)<3.&&abs(trkDxy1/trkDxyError1)<3.&&trkPtError/trkPt<0.1)):L1EtTot>>hl1ettotvsntracks","HLT_PAZeroBiasPixel_SingleTrack_v1","GOFF");
  trackTree->Draw("Sum$(abs(trkCharge)*(trkPt>0.4&&abs(trkEta)<2.4&&highPurity&abs(trkDz1/trkDzError1)<3.&&abs(trkDxy1/trkDxyError1)<3.&&trkPtError/trkPt<0.1)):hiHF>>hl1ntracksvshf","HLT_PAZeroBiasPixel_SingleTrack_v1","GOFF");
  trackTree->Draw("(hiHFplus+hiHFminus):L1EtTot>>hl1ettotvshf","HLT_PAZeroBiasPixel_SingleTrack_v1","GOFF");

  TCanvas* aa = new TCanvas("aa","aa",900,350);
  aa->Divide(3,1);
  aa->cd(1);
  hl1ettotvsntracks->Draw("colz");
  aa->cd(2);
  hl1ntracksvshf->Draw("colz");
  aa->cd(3);
  hl1ettotvshf->Draw("colz");

return;
  TCanvas* a = new TCanvas("a","a",900,400);
  a->Divide(2,1);
  a->cd(1);
  a->GetPad(1)->SetLogy();
  trackTree->Draw("L1EtTot>>hl1ettot","HLT_PAZeroBiasPixel_SingleTrack_v1","hist");
  hl1ettot->Scale(1.0/hl1ettot->Integral());
  for(int i=0;i<300000;i++)
  {
    double evt1 = hl1ettot->GetRandom();
    double evt2 = hl1ettot->GetRandom();
    double evt3 = hl1ettot->GetRandom();
    hl1ettot_pu2->Fill(evt1+evt2);
    hl1ettot_pu3->Fill(evt1+evt2+evt3);
  }
  hl1ettot_pu2->SetLineColor(kRed);
  hl1ettot_pu3->SetLineColor(kBlue);
  hl1ettot_pu2->Scale(1.0/hl1ettot_pu2->Integral());
  hl1ettot_pu3->Scale(1.0/hl1ettot_pu3->Integral());
  hl1ettot_pu2->Draw("histsame");
  hl1ettot_pu3->Draw("histsame");

  TH1D* hl1ettot_all[20];
  TH1D* hl1ettot_all_accum[20];
  for(int i=0;i<20;i++)
  { 
    hl1ettot_all[i] = (TH1D*)hl1ettot->Clone(Form("hl1ettot_all_%d",i));
    hl1ettot_all[i]->Add(hl1ettot_pu2,TMath::Poisson(2,0.05+0.025*i)/TMath::Poisson(1,0.05+0.025*i));
    hl1ettot_all[i]->Add(hl1ettot_pu3,TMath::Poisson(3,0.05+0.025*i)/TMath::Poisson(1,0.05+0.025*i));
    hl1ettot_all_accum[i] = AccumulatedHist(hl1ettot_all[i]);
  }
  a->cd(2);
  a->GetPad(2)->SetLogy();
  TH1D* hl1ettot_accum = AccumulatedHist(hl1ettot);
  hl1ettot_accum->Draw("hist");
  hl1ettot_all_accum[0]->SetLineColor(2);
  hl1ettot_all_accum[0]->Draw("histsame");
  hl1ettot_all_accum[18]->SetLineColor(4);
  hl1ettot_all_accum[18]->Draw("histsame");

  double rate_total[20];
  double rate_l1ett20_nopu[20];
  double rate_l1ett20_pu[20];
  double rate_l1ett40_nopu[20];
  double rate_l1ett40_pu[20];
  double rate_l1ett60_nopu[20];
  double rate_l1ett60_pu[20];
  for(int i=0;i<20;i++)
  { 
    rate_total[i]=100.+190.*i;
    rate_l1ett20_nopu[i]=3.2*(10+19*i);
    rate_l1ett20_pu[i]=3.2*(10+19*i)*hl1ettot_all_accum[i]->GetBinContent(5)/hl1ettot_accum->GetBinContent(5);
    rate_l1ett40_nopu[i]=0.4*(10+19*i);
    rate_l1ett40_pu[i]=0.4*(10+19*i)*hl1ettot_all_accum[i]->GetBinContent(9)/hl1ettot_accum->GetBinContent(9);
    rate_l1ett60_nopu[i]=0.04*(10+19*i);
    rate_l1ett60_pu[i]=0.04*(10+19*i)*hl1ettot_all_accum[i]->GetBinContent(13)/hl1ettot_accum->GetBinContent(13);
  }
  TGraph* gr_rate_l1ett20_nopu = new TGraph(20,rate_total,rate_l1ett20_nopu);
  TGraph* gr_rate_l1ett20_pu = new TGraph(20,rate_total,rate_l1ett20_pu);
  TGraph* gr_rate_l1ett40_nopu = new TGraph(20,rate_total,rate_l1ett40_nopu);
  TGraph* gr_rate_l1ett40_pu = new TGraph(20,rate_total,rate_l1ett40_pu);
  TGraph* gr_rate_l1ett60_nopu = new TGraph(20,rate_total,rate_l1ett60_nopu);
  TGraph* gr_rate_l1ett60_pu = new TGraph(20,rate_total,rate_l1ett60_pu);
  gr_rate_l1ett20_nopu->SetLineWidth(3); 
  gr_rate_l1ett20_pu->SetLineWidth(3);
  gr_rate_l1ett40_nopu->SetLineWidth(3);
  gr_rate_l1ett40_pu->SetLineWidth(3);
  gr_rate_l1ett60_nopu->SetLineWidth(3);
  gr_rate_l1ett60_pu->SetLineWidth(3);
  gr_rate_l1ett20_nopu->SetLineStyle(9);
  gr_rate_l1ett40_nopu->SetLineStyle(9);
  gr_rate_l1ett60_nopu->SetLineStyle(9);
  gr_rate_l1ett40_pu->SetLineColor(2);
  gr_rate_l1ett40_nopu->SetLineColor(2);
  gr_rate_l1ett60_pu->SetLineColor(4);
  gr_rate_l1ett60_nopu->SetLineColor(4);

  TCanvas* c_rate = new TCanvas("c_rate","c_rate",600,550);
  c_rate->SetLogy();
  c_rate->SetLogx();
  TH2D* h_tmp = new TH2D("h_tmp",";Total interaction rate (kHz);L1_ETT rate (kHz)",1000,100,2000,1000,0.3,1000);
  h_tmp->Draw("");
  gr_rate_l1ett20_nopu->Draw("Lsame");
  gr_rate_l1ett20_pu->Draw("Lsame");
  gr_rate_l1ett40_nopu->Draw("Lsame");
  gr_rate_l1ett40_pu->Draw("Lsame");
  gr_rate_l1ett60_nopu->Draw("Lsame");
  gr_rate_l1ett60_pu->Draw("Lsame");
  SaveCanvas(c_rate,"pPb/trigger","L1ettRateVsLumi_pileup");
/*
  TH1D* hl1ettot_pu2_accum = AccumulatedHist(hl1ettot_pu2);
  TH1D* hl1ettot_pu3_accum = AccumulatedHist(hl1ettot_pu3);
  hl1ettot_pu2_accum->Draw("histsame");
  hl1ettot_pu3_accum->Draw("histsame");
*/
//  SaveCanvas(a,"pPb/trigger","L1jetet_centralandtau");
return;
/*
  TCanvas* aa = new TCanvas("aa","aa",800,400);
  aa->Divide(2,1);
  aa->cd(1);
  aa->GetPad(1)->SetLogy();
  trackTree->Draw("L1TauEt[0]>>hl1taujetet_l1jet16","abs(L1TauEta[0])<2.4 && L1_SingleJet16","hist");
  aa->cd(2);
  aa->GetPad(2)->SetLogy();
  trackTree->Draw("L1CenJetEt[0]>>hl1cenjetet_l1jet16","abs(L1CenJetEta[0])<2.4 && L1_SingleJet16","hist");
  SaveCanvas(aa,"pPb/trigger","L1jetet_centralandtau_l1jet16");
*/
/*
  TH1D* hl1jetettotal = (TH1D*)hl1taujetet->Clone("hl1taujetet");
  hl1jetettotal->Add(hl1cenjetet);
  TCanvas* b = new TCanvas("b","b",500,500);
  b->SetLogy();
  hl1jetettotal->Draw("hist");  
//  SaveCanvas(b,"pPb/trigger","L1jetet_all");
  TCanvas* bb = new TCanvas("bb","bb",500,500);
  bb->SetLogy();
  TH1D* hl1jetettotal_accum = AccumulatedHist(hl1jetettotal);
  hl1jetettotal_accum->Draw("PE");
*/
/*
  TH1D* hl1jetettotal_l1jet16 = (TH1D*)hl1taujetet_l1jet16->Clone("hl1taujetet_l1jet16");
  hl1jetettotal_l1jet16->Add(hl1cenjetet_l1jet16);
  TCanvas* bb = new TCanvas("bb","bb",500,500);
  bb->SetLogy();
  hl1jetettotal_l1jet16->Draw("hist");
  SaveCanvas(bb,"pPb/trigger","L1jetet_all_l1jet16");

  TH1D* hl1jet16_eff = (TH1D*)hl1jetettotal_l1jet16->Clone("hl1jet16_eff");
  hl1jet16_eff->Divide(hl1jetettotal);
  TCanvas* cc = new TCanvas("cc","cc",500,500);
  hl1jet16_eff->Draw("hist");

  TCanvas* cjet = new TCanvas("cjet","cjet",500,500);
  trackTree->Draw("rawpt[0]>>hjetpt_l1jet16","abs(jteta[0])<2.0 && L1_SingleJet16","GOFF");
  trackTree->Draw("rawpt[0]>>hjetpt","abs(jteta[0])<2.0","GOFF");
  TH1D* hjeteff_l1jet16 = (TH1D*)hjetpt_l1jet16->Clone("hjeteff_l1jet16");
  hjeteff_l1jet16->Divide(hjetpt);
  hjeteff_l1jet16->Draw("PE");
  SaveCanvas(cjet,"pPb/trigger","JetEff_L1Jet16");
*/
/*
  TCanvas * c1 = new TCanvas();
  c1->SetLogy(1);
  trackTree->Draw("L1EtTot>>hl1ett");
  TCanvas * c2 = new TCanvas();
  c2->SetLogy(1);
  trackTree->Draw("Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity)>>hntrk");
  TCanvas * c22 = new TCanvas();
  trackTree->Draw("L1EtTot:Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity)>>hntrkl1ett","","colz");
*/

  TCanvas * c3 = new TCanvas("c3","",800,400);
  c3->Divide(2,1);
  c3->cd(1);
  c3->GetPad(1)->SetLogy();
  trackTree->Draw("Max$(trkPt*(abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&trkPtError/trkPt<0.1))>>htrkpt","","colz");
  c3->cd(2);
  c3->GetPad(2)->SetLogy();
  TH1D* htrkpt_accum = AccumulatedHist(htrkpt);
  htrkpt_accum->Draw("PE");

  TCanvas * c333 = new TCanvas("c333","",800,400);
  c333->Divide(2,1);
  c333->cd(1);
  c333->GetPad(1)->SetLogy();
  trackTree->Draw("Max$(trkPt*(abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&trkPtError/trkPt<0.1))>>htrkpt_l1jet16","L1_SingleJet16","colz");
  c333->cd(2);
  c333->GetPad(2)->SetLogy();
  TH1D* htrkpt_l1jet16_accum = AccumulatedHist(htrkpt_l1jet16);
  htrkpt_l1jet16_accum->Draw("PE");

  TH1D* htrkpt_l1jet16_eff = (TH1D*)htrkpt_l1jet16->Clone("htrkpt_l1jet16_eff");
  htrkpt_l1jet16_eff->Divide(htrkpt);
  TCanvas * c3a = new TCanvas("c3a","",500,500);
  htrkpt_l1jet16_eff->Draw("PE");
/*
  TCanvas * c33 = new TCanvas();
  c33->SetLogz(1);
  trackTree->Draw("Max$(trkPt*(abs(trkEta)<2.4&&highPurity&&abs(trkDz1/trkDzError1)<3&&abs(trkDxy1/trkDxyError1)<3&&trkPtError/trkPt<0.1)):max(L1TauEt[0]*(abs(L1TauEta[0])<3.0),L1CenJetEt[0]*(abs(L1CenJetEta[0])<3.0))>>htrkptl1jetet","","colz");
  TLine * l = new TLine(0,0,100,100);
  l->Draw("Lsame");
  SaveCanvas(c33,"pPb/trigger","JetETvsTrackPt");
*/
  // TCanvas * c33 = new TCanvas();
  // c33->SetLogy(1);
  // trackTree->Draw("Max$(trkPt*(abs(trkEta)<2.4&&highPurity)*(Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity)>165))>>htrkpte3");
  // TCanvas * c34 = new TCanvas();
  // c34->SetLogy(1);
  // trackTree->Draw("Max$(trkPt*(abs(trkEta)<2.4&&highPurity)*(Sum$(trkPt>0.4&&abs(trkEta)<2.4&&highPurity)>195))>>htrkpte4");
  
  return;
  for(int i = 0 ; i < 150 ; ++i)
  {
    hl1ettrate->Fill(i,hl1ett->Integral(i,150)/hl1ett->Integral());
  }
  for(int i = 0 ; i < 250 ; ++i)
  {
    hntrkrate->Fill(i,hntrk->Integral(i,250)/hntrk->Integral());
  }
  for(int i = 0 ; i < 300 ; ++i)
  {
    htrkptrate->Fill(i,htrkpt->Integral(i,300)/htrkpt->Integral());
  }
  // for(int i = 0 ; i < 300 ; ++i)
  // {
    // htrkpte3rate->Fill(i,htrkpte3->Integral(i,300)/htrkpte3->Integral());
  // }
  // for(int i = 0 ; i < 300 ; ++i)
  // {
    // htrkpte4rate->Fill(i,htrkpte4->Integral(i,300)/htrkpte4->Integral());
  // }
  
  
  TCanvas * c4 = new TCanvas();
  c4->SetLogy(1);
  hl1ettrate->Draw("hist");
  TCanvas * c5 = new TCanvas();
  c5->SetLogy(1);
  hntrkrate->Draw("hist");
  TCanvas * c6 = new TCanvas();
  c6->SetLogy(1);
  htrkptrate->Draw("hist");
 return; 
  c1->SaveAs("L1EtTot.png");
  c2->SaveAs("nTrk.png");
  c3->SaveAs("maxtrkPt.png");
  // c33->SaveAs("maxtrkPt-nTrke-3.png");
  // c34->SaveAs("maxtrkPte-nTrke-4.png");
  
  c4->SaveAs("L1EtTot-rate.png");
  c5->SaveAs("nTrk-rate.png");
  c6->SaveAs("maxtrkPt-rate.png");
  
}
