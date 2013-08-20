{
  // gROOT->ProcessLine(".L trackTree.C+");
  // trackTree t;
  
  
  // TH2D * sig = t.TrackTrackSignal(1,2,1,2);
  // TH2D * bak = t.TrackTrackBackground(1,2,1,2);
  // TH2D * corr = (TH2D*)sig->Clone("corr");
  // corr->Divide(bak);
  // corr->Scale(bak->GetBinContent(bak->FindBin(0,0)));
  // corr->GetXaxis()->SetRange(corr->GetXaxis()->FindBin(-4),corr->GetXaxis()->FindBin(4));
  // corr->GetYaxis()->SetRange(corr->GetYaxis()->FindBin(-3.1415926/2.0),corr->GetYaxis()->FindBin(3*3.1415926/2.0));
  // corr->Draw("surf1");
  
  // TH2D * jsig = t.JetTrackjsignal(40,1000,1,2);
  // TH2D * jbak = t.JetTrackBackground(40,1000,1,2);
  // TH2D * jcorr = (TH2D*)jsig->Clone("jcorr");
  // jsig->Draw("surf1");
  // jcorr->Divide(jbak);
  // jcorr->Scale(jbak->GetBinContent(jbak->FindBin(0,0)));
  // jcorr->GetXaxis()->SetRange(jcorr->GetXaxis()->FindBin(-4),jcorr->GetXaxis()->FindBin(4));
  // jcorr->GetYaxis()->SetRange(jcorr->GetYaxis()->FindBin(-3.1415926/2.0),jcorr->GetYaxis()->FindBin(3*3.1415926/2.0));
  // jcorr->Draw("surf1");
  
  gROOT->ProcessLine(".x corrana.C+");
  TH2D * sig = TrackTrackSignal(1,2,1,2);
  TH2D * bak = TrackTrackBackground(1,2,1,2);
  TH2D * corr = (TH2D*)sig->Clone("corr");
  corr->Divide(bak);
  corr->Scale(bak->GetBinContent(bak->FindBin(0,0)));
  corr->GetXaxis()->SetRange(corr->GetXaxis()->FindBin(-4),corr->GetXaxis()->FindBin(4));
  corr->GetYaxis()->SetRange(corr->GetYaxis()->FindBin(-3.1415926/2.0),corr->GetYaxis()->FindBin(3*3.1415926/2.0));
  corr->Draw("surf1");
  
}