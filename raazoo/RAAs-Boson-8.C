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
   hRAATmp->SetMaximum(2.5);
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
   

   box = new TBox(172.4,87.2321,189.6,112.7679);

   ci = TColor::GetColor("#33ccff");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);
   box->Draw();


   box = new TBox(20,0.7614161,25,1.655778);

   box = new TBox(91.19-2.5,1.008,91.19+2.5,1.392);

   ci = TColor::GetColor("#ff8888");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#ff8888");
   box->SetLineColor(ci);
   box->Draw();

   box = new TBox(80.38-2.5,0.9,80.38+2.5,1.1);

   ci = TColor::GetColor("#FF88FF");
   box->SetFillColor(ci);
   box->SetFillStyle(1001);

   ci = TColor::GetColor("#ff00FF");
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
   entry=leg->AddEntry("hEtSIEIECorrected","0-10%, #int L dt = 7 #mub^{-1}","");
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
   entry->SetLineWidth(1);
   entry->SetLineColor(0);
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
   leg->Draw();
//   leg2->Draw();
   newShift_shiftedPhotoh->Draw("same e x0");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
