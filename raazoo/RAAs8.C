{
//=========Macro generated from canvas: c/
//=========  (Thu Jul 28 16:05:45 2011) by ROOT version5.22/00a
   TCanvas *c = new TCanvas("c", "",340,130,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c->Range(-22.59494,-0.4125,110.3165,2.3375);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(0);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.17);
   c->SetRightMargin(0.04);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameLineColor(0);
   c->SetFrameBorderMode(0);
   c->SetFrameLineColor(0);
   c->SetFrameBorderMode(0);
   
   TH1 *hRAATmp = new TH1D("hRAATmp","",1000,0,105);
   hRAATmp->SetMinimum(0);
   hRAATmp->SetMaximum(2.2);
   hRAATmp->SetFillColor(1);
   hRAATmp->SetFillStyle(0);
   hRAATmp->SetLineStyle(0);
   hRAATmp->SetMarkerStyle(20);
   hRAATmp->SetMarkerSize(1.25);
   hRAATmp->GetXaxis()->SetTitle("m_{(T)} [GeV]");
   hRAATmp->GetXaxis()->CenterTitle(true);
   hRAATmp->GetXaxis()->SetLabelFont(42);
   hRAATmp->GetXaxis()->SetLabelOffset(0.01);
   hRAATmp->GetXaxis()->SetLabelSize(0.045);
   hRAATmp->GetXaxis()->SetTitleSize(0.055);
   hRAATmp->GetXaxis()->SetTitleFont(42);
   hRAATmp->GetYaxis()->SetTitle("R_{AA}");
   hRAATmp->GetYaxis()->CenterTitle(true);
   hRAATmp->GetYaxis()->SetNdivisions(905);
   hRAATmp->GetYaxis()->SetLabelFont(42);
   hRAATmp->GetYaxis()->SetLabelOffset(0.01);
   hRAATmp->GetYaxis()->SetLabelSize(0.045);
   hRAATmp->GetYaxis()->SetTitleSize(0.055);
   hRAATmp->GetYaxis()->SetTitleOffset(1.25);
   hRAATmp->GetYaxis()->SetTitleFont(42);
   hRAATmp->GetZaxis()->SetLabelFont(42);
   hRAATmp->GetZaxis()->SetLabelSize(0.045);
   hRAATmp->GetZaxis()->SetTitleFont(42);
   hRAATmp->Draw("");
   Double_t xAxis2[6] = {20, 25, 30, 40, 50, 80}; 
   
   TH1 *shiftedPhotoh = new TH1F("shiftedPhotoh","",5, xAxis2);
   shiftedPhotoh->SetBinContent(1,1.208597);
   shiftedPhotoh->SetBinContent(2,0.8527842);
   shiftedPhotoh->SetBinContent(3,1.269127);
   shiftedPhotoh->SetBinContent(4,1.163531);
   shiftedPhotoh->SetBinContent(5,1.095464);
   shiftedPhotoh->SetBinError(1,1e-05);
   shiftedPhotoh->SetBinError(2,1e-05);
   shiftedPhotoh->SetBinError(3,1e-05);
   shiftedPhotoh->SetBinError(4,1e-05);
   shiftedPhotoh->SetBinError(5,1e-05);
   shiftedPhotoh->SetMinimum(0.1);
   shiftedPhotoh->SetMaximum(1000);
   shiftedPhotoh->SetEntries(129.6303);
   shiftedPhotoh->SetLineStyle(0);
   shiftedPhotoh->SetMarkerStyle(20);
   shiftedPhotoh->SetMarkerSize(0);
   shiftedPhotoh->GetXaxis()->SetTitle("Photon E_{T} (GeV)");
   shiftedPhotoh->GetXaxis()->SetLabelFont(42);
   shiftedPhotoh->GetXaxis()->SetLabelOffset(0.01);
   shiftedPhotoh->GetXaxis()->SetLabelSize(0.045);
   shiftedPhotoh->GetXaxis()->SetTitleSize(0.055);
   shiftedPhotoh->GetXaxis()->SetTitleFont(42);
   shiftedPhotoh->GetYaxis()->SetTitle("dN/dE_{T}/ <T_{AA}> (pb)");
   shiftedPhotoh->GetYaxis()->SetLabelFont(42);
   shiftedPhotoh->GetYaxis()->SetLabelOffset(0.01);
   shiftedPhotoh->GetYaxis()->SetLabelSize(0.045);
   shiftedPhotoh->GetYaxis()->SetTitleSize(0.055);
   shiftedPhotoh->GetYaxis()->SetTitleOffset(1.3);
   shiftedPhotoh->GetYaxis()->SetTitleFont(42);
   shiftedPhotoh->GetZaxis()->SetLabelFont(42);
   shiftedPhotoh->GetZaxis()->SetLabelSize(0.045);
   shiftedPhotoh->GetZaxis()->SetTitleFont(42);
   shiftedPhotoh->Draw("same e x0");
   Double_t xAxis3[12] = {20, 22.1635, 22.3635, 27.2003, 27.4003, 34.2544, 34.4544, 44.34841, 44.54841, 61.6196, 61.8196, 200}; 
   
   Double_t xAxis5[12] = {20, 22.1635, 22.3635, 27.2003, 27.4003, 34.2544, 34.4544, 44.34841, 44.54841, 61.6196, 61.8196, 200}; 
   
   TH1 *newShift_shiftedPhotoh = new TH1D("newShift_shiftedPhotoh","",11, xAxis5);
   newShift_shiftedPhotoh->SetBinContent(2,1.031736);
   newShift_shiftedPhotoh->SetBinContent(4,0.8391617);
   newShift_shiftedPhotoh->SetBinContent(6,1.36557);
   newShift_shiftedPhotoh->SetBinContent(8,0.9768955);
   newShift_shiftedPhotoh->SetBinContent(10,0.9949167);
   newShift_shiftedPhotoh->SetBinError(2,0.116257);
   newShift_shiftedPhotoh->SetBinError(4,0.1384846);
   newShift_shiftedPhotoh->SetBinError(6,0.2225921);
   newShift_shiftedPhotoh->SetBinError(8,0.24422);
   newShift_shiftedPhotoh->SetBinError(10,0.3077061);
   newShift_shiftedPhotoh->SetEntries(5);
   newShift_shiftedPhotoh->SetFillColor(1);
   newShift_shiftedPhotoh->SetFillStyle(0);
   newShift_shiftedPhotoh->SetLineStyle(0);
   newShift_shiftedPhotoh->SetMarkerStyle(20);
   newShift_shiftedPhotoh->SetMarkerSize(1.2);
   newShift_shiftedPhotoh->GetXaxis()->SetLabelFont(42);
   newShift_shiftedPhotoh->GetXaxis()->SetLabelOffset(0.01);
   newShift_shiftedPhotoh->GetXaxis()->SetLabelSize(0.045);
   newShift_shiftedPhotoh->GetXaxis()->SetTitleSize(0.055);
   newShift_shiftedPhotoh->GetXaxis()->SetTitleFont(42);
   newShift_shiftedPhotoh->GetYaxis()->SetLabelFont(42);
   newShift_shiftedPhotoh->GetYaxis()->SetLabelOffset(0.01);
   newShift_shiftedPhotoh->GetYaxis()->SetLabelSize(0.045);
   newShift_shiftedPhotoh->GetYaxis()->SetTitleSize(0.055);
   newShift_shiftedPhotoh->GetYaxis()->SetTitleOffset(1.3);
   newShift_shiftedPhotoh->GetYaxis()->SetTitleFont(42);
   newShift_shiftedPhotoh->GetZaxis()->SetLabelFont(42);
   newShift_shiftedPhotoh->GetZaxis()->SetLabelSize(0.045);
   newShift_shiftedPhotoh->GetZaxis()->SetTitleFont(42);
   
   TH1 *hRAATmp = new TH1D("hRAATmp","",1000,0,105);
   hRAATmp->SetMinimum(0);
   hRAATmp->SetMaximum(2.2);
   hRAATmp->SetDirectory(0);
   hRAATmp->SetFillColor(1);
   hRAATmp->SetFillStyle(0);
   hRAATmp->SetLineStyle(0);
   hRAATmp->SetMarkerStyle(20);
   hRAATmp->SetMarkerSize(1.25);
   hRAATmp->GetXaxis()->SetTitle("m_{T} (m) (GeV)");
   hRAATmp->GetXaxis()->CenterTitle(true);
   hRAATmp->GetXaxis()->SetLabelFont(42);
   hRAATmp->GetXaxis()->SetLabelOffset(0.01);
   hRAATmp->GetXaxis()->SetLabelSize(0.045);
   hRAATmp->GetXaxis()->SetTitleSize(0.055);
   hRAATmp->GetXaxis()->SetTitleFont(42);
   hRAATmp->GetYaxis()->SetTitle("R_{AA}");
   hRAATmp->GetYaxis()->CenterTitle(true);
   hRAATmp->GetYaxis()->SetNdivisions(905);
   hRAATmp->GetYaxis()->SetLabelFont(42);
   hRAATmp->GetYaxis()->SetLabelOffset(0.01);
   hRAATmp->GetYaxis()->SetLabelSize(0.045);
   hRAATmp->GetYaxis()->SetTitleSize(0.055);
   hRAATmp->GetYaxis()->SetTitleOffset(1.25);
   hRAATmp->GetYaxis()->SetTitleFont(42);
   hRAATmp->GetZaxis()->SetLabelFont(42);
   hRAATmp->GetZaxis()->SetLabelSize(0.045);
   hRAATmp->GetZaxis()->SetTitleFont(42);
   
   hRAATmp->Draw("sameaxis");
      TBox *box = new TBox(20,0.680768,25,1.382703);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ffff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(25,0.5666873,30,1.111636);

   ci = TColor::GetColor("#ffff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(30,0.956104,40,1.775036);

   ci = TColor::GetColor("#ffff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(40,0.7114027,50,1.242388);

   ci = TColor::GetColor("#ffff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(50,0.7324548,80,1.257379);

   ci = TColor::GetColor("#ffff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   box->SetLineColor(ci);
   box->Draw();
   newShift_shiftedPhotoh->Draw("same e x0");
   
   TGraph *graph = new TGraph(6);
   graph->SetName("Graph_from_hAARef__");
   graph->SetTitle("");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetPoint(0,20,0.992943);
   graph->SetPoint(1,27.5,1.002046);
   graph->SetPoint(2,35,1.008718);
   graph->SetPoint(3,45,1.004626);
   graph->SetPoint(4,65,0.9899735);
   graph->SetPoint(5,90,0.9899735);
   

   //TBox *box = new TBox(0,-108.3677,0.1,-91.63227);
   TBox *box = new TBox(0,0,0.1,0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#33ccff");
   
   /*
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.1,-108.3256,0.2,-91.67441);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.2,-108.2834,0.3,-91.71656);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.3,-108.2483,0.4,-91.75166);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.4,-108.2132,0.5,-91.78676);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,-108.1847,0.6,-91.81533);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.6,-108.1561,0.7,-91.8439);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.7,-108.1336,0.8,-91.86642);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.8,-108.1111,0.9,-91.88894);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.9,-108.0941,1,-91.90588);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.337,1.1,0.390);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.1,0.347,1.2,0.402);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.2,0.365,1.4,0.423);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.4,0.381,1.6,0.441);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.6,0.393,1.8,0.455);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.8,0.396,2,0.458);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2,0.395,2.2,0.458);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.2,0.388,2.4,0.449);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.4,0.344,3.2,0.399);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(3.2,0.252,4,0.292);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(4,0.183,4.8,0.212);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(4.8,0.146,5.6,0.170);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(5.6,0.135,6.4,0.157);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(6.4,0.137,7.2,0.159);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(7.2,0.151,9.6,0.175);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(9.6,0.179,12,0.208);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(12,0.215,14.4,0.251);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(14.4,0.262,19.2,0.308);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(19.2,0.352,24,0.418);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(24,0.350,28.8,0.418);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(28.8,0.385,35.2,0.463);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(35.2,0.456,41.6,0.559);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(41.6,0.501,48,0.645);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(48,0.479,60.8,0.604);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(60.8,0.557,73.6,0.709);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(73.6,0.494,86.4,0.632);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(86.4,0.471,103.6,0.602);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(103.6,85.002,120.8,114.998);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(120.8,85.00199,138,114.998);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(138,85.00199,155.2,114.998);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(155.2,85.00199,172.4,114.998);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(172.4,85.00199,189.6,114.998);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#33ccff");
   box->SetLineColor(ci);
   box->Draw();
   */

   // manually drawn syste RAA (Andre)
     ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.1,0,0.2,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.2,0,0.3,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.3,0,0.4,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.4,0,0.5,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.5,0,0.6,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.6,0,0.7,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.7,0,0.8,0);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.8,0.3041186,0.9,0.3520075);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(0.9,0.372831,1,0.4315449);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1,0.3366688,1.1,0.3896924);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1.1,0.3469489,1.2,0.4015963);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1.2,0.3650894,1.4,0.4226017);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1.4,0.3813269,1.6,0.4414085);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1.6,0.39263,1.8,0.4545041);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(1.8,0.396135,2,0.4585742);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(2,0.3955877,2.2,0.4579532);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(2.2,0.3881311,2.4,0.449335);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(2.4,0.3447951,3.2,0.399196);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(3.2,0.2524608,4,0.2923386);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(4,0.183719,4.8,0.2127714);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(4.8,0.1471801,5.6,0.170491);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(5.6,0.1364971,6.4,0.1581499);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(6.4,0.1379895,7.2,0.1599329);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(7.2,0.1517881,9.6,0.1760443);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(9.6,0.1798491,12,0.2091189);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(12,0.2150772,14.4,0.2507151);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(14.4,0.2623466,19.2,0.3080135);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(19.2,0.3525234,24,0.4178584);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(24,0.3522601,28.8,0.4204636);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(28.8,0.3865864,35.2,0.4652023);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(35.2,0.4581389,41.6,0.5617028);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(41.6,0.5626625,48,0.7028893);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(48,0.4800837,60.8,0.6049381);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(60.8,0.5557046,73.6,0.7083543);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(73.6,0.497255,86.4,0.634719);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(86.4,0.4703899,103.6,0.6013932);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();
   box = new TBox(103.6,87.65689,120.8,112.3431);



   box = new TBox(20,0.7614161,25,1.655778);

   box = new TBox(91.19-2.5,1.008,91.19+2.5,1.392);

   ci = TColor::GetColor("#ff8888");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#ff8888");
   box->SetLineColor(ci);
   box->Draw();

   box = new TBox(80.38-2.5,0.9,80.38+2.5,1.1);

   ci = TColor::GetColor("#ff88ff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#ff88ff");
   box->SetLineColor(ci);
   box->Draw();


    box = new TBox(sqrt(6.5*6.5+3.1*3.1),0.35,sqrt(30*30+3.1*3.1),0.39);

   ci = TColor::GetColor("#ee7711");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#ff8888");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.3,0.9568966,10,1.043103);
   box->SetFillColor(kGray+1);
   box->SetFillStyle(1001);
   box->Draw();




   TLine *line = new TLine(0,1,105,1);
   line->SetLineStyle(7);
   line->Draw();
   Double_t xAxis1[43] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 138, 155.2, 172.4, 189.6}; 
   
   // HIN-10-005 (Andre)
   TH1D *hData_merge = new TH1D("hData_merge","eta vs pt vs jet y projection",42, xAxis1);
   hData_merge->SetBinContent(9,0.3280631);
   hData_merge->SetBinContent(10,0.402188);
   hData_merge->SetBinContent(11,0.3631806);
   hData_merge->SetBinContent(12,0.3742726);
   hData_merge->SetBinContent(13,0.3938456);
   hData_merge->SetBinContent(14,0.4113677);
   hData_merge->SetBinContent(15,0.423567);
   hData_merge->SetBinContent(16,0.4273546);
   hData_merge->SetBinContent(17,0.4267705);
   hData_merge->SetBinContent(18,0.4187331);
   hData_merge->SetBinContent(19,0.3719955);
   hData_merge->SetBinContent(20,0.2723997);
   hData_merge->SetBinContent(21,0.1982452);
   hData_merge->SetBinContent(22,0.1588355);
   hData_merge->SetBinContent(23,0.1473235);
   hData_merge->SetBinContent(24,0.1489612);
   hData_merge->SetBinContent(25,0.1639162);
   hData_merge->SetBinContent(26,0.194484);
   hData_merge->SetBinContent(27,0.2328962);
   hData_merge->SetBinContent(28,0.28518);
   hData_merge->SetBinContent(29,0.3851909);
   hData_merge->SetBinContent(30,0.3863618);
   hData_merge->SetBinContent(31,0.4258944);
   hData_merge->SetBinContent(32,0.5099209);
   hData_merge->SetBinContent(33,0.6327759);
   hData_merge->SetBinContent(34,0.5425109);
   hData_merge->SetBinContent(35,0.6320295);
   hData_merge->SetBinContent(36,0.565987);
   hData_merge->SetBinContent(37,0.5358915);
   hData_merge->SetBinContent(38,100);
   hData_merge->SetBinContent(39,100);
   hData_merge->SetBinContent(40,100);
   hData_merge->SetBinContent(41,100);
   hData_merge->SetBinContent(42,100);
   hData_merge->SetBinError(9,0.001048723);
   hData_merge->SetBinError(10,0.000253575);
   hData_merge->SetBinError(11,0.0002158273);
   hData_merge->SetBinError(12,0.0002426081);
   hData_merge->SetBinError(13,0.0002096065);
   hData_merge->SetBinError(14,0.0002656964);
   hData_merge->SetBinError(15,0.0003311976);
   hData_merge->SetBinError(16,0.0004018826);
   hData_merge->SetBinError(17,0.0004825326);
   hData_merge->SetBinError(18,0.0005652245);
   hData_merge->SetBinError(19,0.0003802225);
   hData_merge->SetBinError(20,0.0005022124);
   hData_merge->SetBinError(21,0.0006179205);
   hData_merge->SetBinError(22,0.0007761261);
   hData_merge->SetBinError(23,0.001066454);
   hData_merge->SetBinError(24,0.001504792);
   hData_merge->SetBinError(25,0.001527926);
   hData_merge->SetBinError(26,0.003262212);
   hData_merge->SetBinError(27,0.006363009);
   hData_merge->SetBinError(28,0.009152627);
   hData_merge->SetBinError(29,0.02043902);
   hData_merge->SetBinError(30,0.01001524);
   hData_merge->SetBinError(31,0.03987539);
   hData_merge->SetBinError(32,0.05214663);
   hData_merge->SetBinError(33,0.08881304);
   hData_merge->SetBinError(34,0.02220791);
   hData_merge->SetBinError(35,0.04290412);
   hData_merge->SetBinError(36,0.04641189);
   hData_merge->SetBinError(37,0.0664665);
   hData_merge->SetBinError(38,0.120674);
   hData_merge->SetBinError(40,0.2821545);
   hData_merge->SetBinError(41,0.1917044);
   hData_merge->SetEntries(1948.8);
   hData_merge->SetStats(0);
   hData_merge->SetFillStyle(0);
   hData_merge->SetFillStyle(0);
   hData_merge->SetMarkerStyle(24);
   hData_merge->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hData_merge->GetXaxis()->SetLabelFont(42);
   hData_merge->GetXaxis()->SetLabelOffset(0.01);
   hData_merge->GetXaxis()->SetTitleSize(0.045);
   hData_merge->GetXaxis()->SetTitleOffset(1.2);
   hData_merge->GetXaxis()->SetTitleFont(42);
   hData_merge->GetYaxis()->SetLabelFont(42);
   hData_merge->GetYaxis()->SetLabelOffset(0.01);
   hData_merge->GetYaxis()->SetTitleSize(0.045);
   hData_merge->GetYaxis()->SetTitleOffset(1.8);
   hData_merge->GetYaxis()->SetTitleFont(42);
   hData_merge->GetZaxis()->SetLabelFont(42);
   hData_merge->GetZaxis()->SetTitleFont(42);
   hData_merge->Draw("same e x0");


   /*
   TH1 *raaHadMerged = new TH1D("raaHadMerged","eta vs pt vs jet y projection",42, xAxis1);
   raaHadMerged->SetBinContent(1,-100);
   raaHadMerged->SetBinContent(2,-100);
   raaHadMerged->SetBinContent(3,-100);
   raaHadMerged->SetBinContent(4,-100);
   raaHadMerged->SetBinContent(5,-100);
   raaHadMerged->SetBinContent(6,-100);
   raaHadMerged->SetBinContent(7,-100);
   raaHadMerged->SetBinContent(8,-100);
   raaHadMerged->SetBinContent(9,-100);
   raaHadMerged->SetBinContent(10,-100);
   raaHadMerged->SetBinContent(11,0.363);
   raaHadMerged->SetBinContent(12,0.374);
   raaHadMerged->SetBinContent(13,0.394);
   raaHadMerged->SetBinContent(14,0.411);
   raaHadMerged->SetBinContent(15,0.424);
   raaHadMerged->SetBinContent(16,0.427);
   raaHadMerged->SetBinContent(17,0.427);
   raaHadMerged->SetBinContent(18,0.418);
   raaHadMerged->SetBinContent(19,0.372);
   raaHadMerged->SetBinContent(20,0.272);
   raaHadMerged->SetBinContent(21,0.198);
   raaHadMerged->SetBinContent(22,0.158);
   raaHadMerged->SetBinContent(23,0.146);
   raaHadMerged->SetBinContent(24,0.148);
   raaHadMerged->SetBinContent(25,0.163);
   raaHadMerged->SetBinContent(26,0.194);
   raaHadMerged->SetBinContent(27,0.233);
   raaHadMerged->SetBinContent(28,0.285);
   raaHadMerged->SetBinContent(29,0.385);
   raaHadMerged->SetBinContent(30,0.384);
   raaHadMerged->SetBinContent(31,0.424);
   raaHadMerged->SetBinContent(32,0.508);
   raaHadMerged->SetBinContent(33,0.573);
   raaHadMerged->SetBinContent(34,0.542);
   raaHadMerged->SetBinContent(35,0.633);
   raaHadMerged->SetBinContent(36,0.563);
   raaHadMerged->SetBinContent(37,0.537);
   raaHadMerged->SetBinContent(38,100);
   raaHadMerged->SetBinContent(39,100);
   raaHadMerged->SetBinContent(40,100);
   raaHadMerged->SetBinContent(41,100);
   raaHadMerged->SetBinContent(42,100);
   raaHadMerged->SetBinError(9,0.0000);
   raaHadMerged->SetBinError(10,0.000);
   raaHadMerged->SetBinError(11,0.0002);
   raaHadMerged->SetBinError(12,0.0002);
   raaHadMerged->SetBinError(13,0.0002);
   raaHadMerged->SetBinError(14,0.0003);
   raaHadMerged->SetBinError(15,0.0003);
   raaHadMerged->SetBinError(16,0.0004);
   raaHadMerged->SetBinError(17,0.0005);
   raaHadMerged->SetBinError(18,0.0006);
   raaHadMerged->SetBinError(19,0.0004);
   raaHadMerged->SetBinError(20,0.0005);
   raaHadMerged->SetBinError(21,0.0006);
   raaHadMerged->SetBinError(22,0.0008);
   raaHadMerged->SetBinError(23,0.0011);
   raaHadMerged->SetBinError(24,0.0015);
   raaHadMerged->SetBinError(25,0.0016);
   raaHadMerged->SetBinError(26,0.0033);
   raaHadMerged->SetBinError(27,0.0064);
   raaHadMerged->SetBinError(28,0.0092);
   raaHadMerged->SetBinError(29,0.0206);
   raaHadMerged->SetBinError(30,0.0298);
   raaHadMerged->SetBinError(31,0.0396);
   raaHadMerged->SetBinError(32,0.0518);
   raaHadMerged->SetBinError(33,0.0946);
   raaHadMerged->SetBinError(34,0.0225);
   raaHadMerged->SetBinError(35,0.0438);
   raaHadMerged->SetBinError(36,0.0472);
   raaHadMerged->SetBinError(37,0.0666);
   raaHadMerged->SetBinError(38,1.740722e-14);
   raaHadMerged->SetBinError(39,5.581975e-15);
   raaHadMerged->SetEntries(136);
   raaHadMerged->SetFillStyle(0);
   raaHadMerged->SetMarkerStyle(24);
   raaHadMerged->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   raaHadMerged->GetXaxis()->SetLabelFont(42);
   raaHadMerged->GetXaxis()->SetLabelOffset(0.01);
   raaHadMerged->GetXaxis()->SetTitleSize(0.045);
   raaHadMerged->GetXaxis()->SetTitleOffset(1.2);
   raaHadMerged->GetXaxis()->SetTitleFont(42);
   raaHadMerged->GetYaxis()->SetLabelFont(42);
   raaHadMerged->GetYaxis()->SetLabelOffset(0.01);
   raaHadMerged->GetYaxis()->SetTitleSize(0.045);
   raaHadMerged->GetYaxis()->SetTitleOffset(1.8);
   raaHadMerged->GetYaxis()->SetTitleFont(42);
   raaHadMerged->GetZaxis()->SetLabelFont(42);
   raaHadMerged->GetZaxis()->SetTitleFont(42);
   raaHadMerged->Draw("same e x0");
   */
   
   
   TH1 *raaZ = new TH1D("raaZ","",1,91.19,91.19);
   raaZ->SetBinContent(1,1.2);
   raaZ->SetBinError(1,0.29);
   raaZ->SetEntries(1);
   raaZ->SetFillColor(1);
   raaZ->SetFillStyle(0);
   raaZ->SetLineStyle(0);
   raaZ->SetMarkerStyle(21);
   raaZ->SetMarkerSize(1.2);
   raaZ->GetXaxis()->SetLabelFont(42);
   raaZ->GetXaxis()->SetLabelOffset(0.01);
   raaZ->GetXaxis()->SetLabelSize(0.045);
   raaZ->GetXaxis()->SetTitleSize(0.055);
   raaZ->GetXaxis()->SetTitleFont(42);
   raaZ->GetYaxis()->SetLabelFont(42);
   raaZ->GetYaxis()->SetLabelOffset(0.01);
   raaZ->GetYaxis()->SetLabelSize(0.045);
   raaZ->GetYaxis()->SetTitleSize(0.055);
   raaZ->GetYaxis()->SetTitleOffset(1.3);
   raaZ->GetYaxis()->SetTitleFont(42);
   raaZ->GetZaxis()->SetLabelFont(42);
   raaZ->GetZaxis()->SetLabelSize(0.045);
   raaZ->GetZaxis()->SetTitleFont(42);
   raaZ->Draw("same e x0");

   TH1 *raaW = new TH1D("raaW","",1000,80.38,80.38);
   raaW->SetBinContent(1,1.0);
   raaW->SetBinError(1,0.084);
   raaW->SetEntries(1);
   raaW->SetFillColor(1);
   raaW->SetFillStyle(0);
   raaW->SetLineStyle(0);
   raaW->SetMarkerStyle(29);
   raaW->SetMarkerSize(2);
   raaW->GetXaxis()->SetLabelFont(42);
   raaW->GetXaxis()->SetLabelOffset(0.01);
   raaW->GetXaxis()->SetLabelSize(0.045);
   raaW->GetXaxis()->SetTitleSize(0.055);
   raaW->GetXaxis()->SetTitleFont(42);
   raaW->GetYaxis()->SetLabelFont(42);
   raaW->GetYaxis()->SetLabelOffset(0.01);
   raaW->GetYaxis()->SetLabelSize(0.045);
   raaW->GetYaxis()->SetTitleSize(0.055);
   raaW->GetYaxis()->SetTitleOffset(1.3);
   raaW->GetYaxis()->SetTitleFont(42);
   raaW->GetZaxis()->SetLabelFont(42);
   raaW->GetZaxis()->SetLabelSize(0.045);
   raaW->GetZaxis()->SetTitleFont(42);
   raaW->Draw("same e x0");


   TH1 *raabJetViaJpsi = new TH1D("raabJetViaJpsi","",1000,6.5,30);
   raabJetViaJpsi->SetBinContent(raabJetViaJpsi->FindBin(sqrt(10*10+3.1*3.1)),0.37);
   raabJetViaJpsi->SetBinError(raabJetViaJpsi->FindBin(sqrt(10*10+3.1*3.1)),0.08);
   raabJetViaJpsi->SetEntries(1);
   raabJetViaJpsi->SetFillColor(1);
   raabJetViaJpsi->SetFillStyle(0);
   raabJetViaJpsi->SetLineStyle(0);
   raabJetViaJpsi->SetMarkerStyle(25);
   raabJetViaJpsi->SetMarkerSize(1.2);
   raabJetViaJpsi->SetMarkerColor(1);
   raabJetViaJpsi->GetXaxis()->SetLabelFont(42);
   raabJetViaJpsi->GetXaxis()->SetLabelOffset(0.01);
   raabJetViaJpsi->GetXaxis()->SetLabelSize(0.045);
   raabJetViaJpsi->GetXaxis()->SetTitleSize(0.055);
   raabJetViaJpsi->GetXaxis()->SetTitleFont(42);
   raabJetViaJpsi->GetYaxis()->SetLabelFont(42);
   raabJetViaJpsi->GetYaxis()->SetLabelOffset(0.01);
   raabJetViaJpsi->GetYaxis()->SetLabelSize(0.045);
   raabJetViaJpsi->GetYaxis()->SetTitleSize(0.055);
   raabJetViaJpsi->GetYaxis()->SetTitleOffset(1.3);
   raabJetViaJpsi->GetYaxis()->SetTitleFont(42);
   raabJetViaJpsi->GetZaxis()->SetLabelFont(42);
   raabJetViaJpsi->GetZaxis()->SetLabelSize(0.045);
   raabJetViaJpsi->GetZaxis()->SetTitleFont(42);
   raabJetViaJpsi->Draw("same e x0");


   TLegend *leg = new TLegend(0.04,0.79,0.7,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hEtSIEIECorrected","CMS","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hEtSIEIECorrected","PbPb #sqrt{s_{NN}} = 2.76 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hEtSIEIECorrected","","");
   entry=leg->AddEntry("hEtSIEIECorrected","0-10%, #int L dt = 7-150 #mub^{-1}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TLatex *   tex = new TLatex(0.76,0.23,"0-10%");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(20);
//   tex->Draw();
   
   leg = new TLegend(0.52,0.68,0.93,0.93,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("raaHadL","T_{AA} uncertainty","f");
   entry->SetFillColor(kGray+1);
   entry->SetFillStyle(1001);
   entry->SetLineColor(0);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("raaHadL","Z^{0}                              |y|<2.0","lpf");

   ci = TColor::GetColor("#ff8888");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("raaHadL","W  p_{T}^{#mu} > 25 GeV/c^{^{ }}     |#eta^{#mu}|<2.1","lpf");

   ci = TColor::GetColor("#ff88ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(2);
   entry=leg->AddEntry("raaPhoL","Isolated photon       |#eta|<1.44","lpf");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
/*
   TLegend *leg2 = new TLegend(0.48,0.16,0.92,0.30,NULL,"brNDC");
   leg2->SetBorderSize(0);
   leg2->SetTextFont(62);
   leg2->SetLineColor(1);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(19);
   leg2->SetFillStyle(0);
*/
   entry=leg->AddEntry("raaHadL","Charged particles^{^{ }}   |#eta|<1.0","lpf");

   ci = TColor::GetColor("#33ccff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("raaHadL","b-quarks (0-20%)^{ }    |#eta|<2.4","lpf");
   ci = TColor::GetColor("#ee7711");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("raabJetViaJpsi", "(via secondary J/#psi) ","");
   leg->Draw();
//   leg2->Draw();
   newShift_shiftedPhotoh->Draw("same e x0");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
