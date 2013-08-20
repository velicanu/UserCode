#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TF2.h"
#include "TMath.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"

void histana_jettrack(){
// TFile *f1 = new TFile("/net/hidsk0001/d00/scratch/dgulhan/newCFhists_jet-track-minbias.root");//minbias
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/AJ-jetcorr.root");//Aj 
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/jet-leading-sub-equalpt.root");//equal pt
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/mymchists.root");//MC  
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/ppcorrhists.root");//pp
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/frank_base_merged.root");
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/frank_pf3_merged.root");
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/mccorrhists_base_merged.root");
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/mccorrhists_simjet_merged.root");
// TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/stdfrankv2.root");
TFile *f1 = new TFile("/d102/dgulhan/AnaDragos_input/stdmcv2.root.root");


//----------------set pt ass bins-------------------
int ptrange[2][3];
ptrange[0][0]=2; ptrange[1][0]=3;
ptrange[0][1]=3; ptrange[1][1]=5;
ptrange[0][2]=5; ptrange[1][2]=8;
// int ptrange[2][3];
// ptrange[0][0]=1; ptrange[1][0]=2;
// ptrange[0][1]=2; ptrange[1][1]=3;
// ptrange[0][2]=3; ptrange[1][2]=4;

//---------------set cent bins------------------
int cbin[2][4];
cbin[0][0]=0; cbin[1][0]=4;
cbin[0][1]=4; cbin[1][1]=12;
cbin[0][2]=12; cbin[1][2]=20;
cbin[0][3]=20; cbin[1][3]=40;
// int cbin[2][4];
// cbin[0][0]=0; cbin[1][0]=4;
// cbin[0][1]=4; cbin[1][1]=8;
// cbin[0][2]=8; cbin[1][2]=12;
// cbin[0][3]=12; cbin[1][3]=16;

TH2D * corr[2][3][4];
TH1D * proj[2][3][4];
TH2D * subtracted_corr[2][3][4];
TH2D * result[2][3][4];

//---------------subtract long range correlation--------------------------------------------------------------------------------------------------------------------
for (int i=0; i<3; i++){
   for (int j=0; j<4; j++){
      cout<<i<<" " <<j<<endl;
      corr[0][i][j]=(TH2D*)f1->Get(Form("corr_leadingjet100_120_ass%i_%i_cmin%i_cmax%i_ajmin0.35_ajmax1.00",ptrange[0][i],ptrange[1][i],cbin[0][j],cbin[1][j]));
      // corr[0][i][j]=(TH2D*)f1->Get(Form("corr_leadingjet90_300_ass%i_%i_cmin%i_cmax%i",ptrange[0][i],ptrange[1][i],cbin[0][j],cbin[1][j]));
      corr[1][i][j]=(TH2D*)f1->Get(Form("corr_subleadingjet100_120_ass%i_%i_cmin%i_cmax%i_ajmin0.35_ajmax1.00",ptrange[0][i],ptrange[1][i],cbin[0][j],cbin[1][j]));
      // corr[1][i][j]=(TH2D*)f1->Get(Form("corr_subleadingjet90_300_ass%i_%i_cmin%i_cmax%i",ptrange[0][i],ptrange[1][i],cbin[0][j],cbin[1][j]));
      cout<<"next canvas"<<endl;
      corr[0][i][j]->Draw("surf1");
      for (int k=0;k<2;k++){
        int xmin = corr[k][i][j]->GetXaxis()->FindBin(1);
        int xmax = corr[k][i][j]->GetXaxis()->FindBin(1.6);
        cout << xmin << " " << xmax <<endl;
        proj[k][i][j] = corr[k][i][j]->ProjectionY(Form("proj%i_%i_%i",k,i,j),xmin,xmax);
        double nbins = xmax - xmin + 1;
        proj[k][i][j]->Scale(1/nbins);
        // proj[1][i][j]->Draw();
        subtracted_corr[k][i][j] = (TH2D*) corr[k][i][j]->Clone(Form("subtracted_corr%i_%i_%i",k,i,j));
  
       int xstart = corr[k][i][j]->GetXaxis()->FindBin(-1.6);
       int xend = corr[k][i][j]->GetXaxis()->FindBin(1.6);
  
       int ystart = corr[k][i][j]->GetYaxis()->FindBin(-TMath::Pi()/2.);
       int yend = corr[k][i][j]->GetYaxis()->FindBin(3*TMath::Pi()/2.);

       for(int m = ystart ; m < yend ; ++m){ 
          double ypos = corr[k][i][j]->GetYaxis()->GetBinCenter(m);
          int thisbin = proj[k][i][j]->FindBin(ypos);
          double meanvalue = proj[k][i][j]->GetBinContent(thisbin);
  
          for(int n = xstart ;n < xend ; ++n){
            subtracted_corr[k][i][j]->SetBinContent(n,m,meanvalue);
          }
        }
      
        result[k][i][j] = (TH2D*) corr[k][i][j]->Clone(Form("result%i_%i_%i",k,i,j));
        subtracted_corr[k][i][j]->Scale(-1);
        result[k][i][j]->Add(subtracted_corr[k][i][j]);
        result[k][i][j]->GetYaxis()->SetRange(result[k][i][j]->GetYaxis()->FindBin(-TMath::Pi()/2.),result[k][i][j]->GetYaxis()->FindBin(TMath::Pi()/2.));
        result[k][i][j]->GetXaxis()->SetRange(result[k][i][j]->GetXaxis()->FindBin(-1.6),result[k][i][j]->GetXaxis()->FindBin(1.6));
      }
    }  
}

//##########################################################PLOTS###################################################################################################

//-----------------------centrality dependence plot for CF's (CF0=leading, CF1=subleading)--------------------------------------------------------------------------
// for (int k=0;k<2;k++){
   // for(int i=0;i<3;i++){
        // TCanvas *c1=new TCanvas("c1","",1200,1000);
        // c1->Divide(2,2);
        // c1->cd(1);
        // corr[k][i][0]->SetTitle("%0-10; #Delta#eta;#Delta#phi");
        // corr[k][i][0]->GetXaxis()->CenterTitle();
        // corr[k][i][0]->GetYaxis()->CenterTitle();
        // corr[k][i][0]->Draw("surf1");
        // c1->cd(2);
        // corr[k][i][1]->SetTitle("%10-30; #Delta#eta;#Delta#phi"); 
        // corr[k][i][1]->GetXaxis()->CenterTitle();
        // corr[k][i][1]->GetYaxis()->CenterTitle();
        // corr[k][i][1]->Draw("surf1");
        // c1->cd(3);
        // corr[k][i][2]->SetTitle("%30-50; #Delta#eta;#Delta#phi");
        // corr[k][i][2]->GetXaxis()->CenterTitle();
        // corr[k][i][2]->GetYaxis()->CenterTitle();
        // corr[k][i][2]->Draw("surf1");
        // c1->cd(4);
        // corr[k][i][3]->SetTitle("%50-100; #Delta#eta;#Delta#phi");
        // corr[k][i][3]->GetXaxis()->CenterTitle();
        // corr[k][i][3]->GetYaxis()->CenterTitle();
        // corr[k][i][3]->Draw("surf1");
        // c1->SaveAs(Form("7_19/CF%i_jet90_300_ass%i_%i_cent_depend.png",k,ptrange[0][i],ptrange[1][i]));
        // c1->Delete();
    // }
  // }

 //-----------------------centrality dependence plot for CF-LR's (CF-LR0=leading, CF-LR1=subleading)--------------------------------------------------------------------
 // for (int k=0;k<2;k++){
   // for(int i=0;i<3;i++){
        // TCanvas *c1=new TCanvas("c1","",1200,1000);
        // c1->Divide(2,2);
        // c1->cd(1);
        // result[k][i][0]->SetTitle("%0-10; #Delta#eta;#Delta#phi");
        // result[k][i][0]->GetXaxis()->CenterTitle();
        // result[k][i][0]->GetYaxis()->CenterTitle();
        // result[k][i][0]->Draw("surf1");
        // c1->cd(2);
        // result[k][i][1]->SetTitle("%10-30; #Delta#eta;#Delta#phi"); 
        // result[k][i][1]->GetXaxis()->CenterTitle();
        // result[k][i][1]->GetYaxis()->CenterTitle();
        // result[k][i][1]->Draw("surf1");
        // c1->cd(3);
        // result[k][i][2]->SetTitle("%30-50; #Delta#eta;#Delta#phi");
        // result[k][i][2]->GetXaxis()->CenterTitle();
        // result[k][i][2]->GetYaxis()->CenterTitle();
        // result[k][i][2]->Draw("surf1");
        // c1->cd(4);
        // result[k][i][3]->SetTitle("%50-100; #Delta#eta;#Delta#phi");
        // result[k][i][3]->GetXaxis()->CenterTitle();
        // result[k][i][3]->GetYaxis()->CenterTitle();
        // result[k][i][3]->Draw("surf1");
        // c1->SaveAs(Form("7_19/CF-LR%i_jet90_300_ass%i_%i_cent_depend.png",k,ptrange[0][i],ptrange[1][i]));
        // c1->Delete();
 
    // }
  // }

//-----------------------------pt dependence plots (CF)-----------------------------------------------------------------------------------------------------------------------
// for (int j=0; j<4; j++){
   // TCanvas *c1=new TCanvas("c1","",1600,1000);
   // c1->Divide(3,2);
   // c1->cd(1);
   // corr[0][0][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][0],ptrange[1][0]));
   // corr[0][0][j]->GetXaxis()->CenterTitle();
   // corr[0][0][j]->GetYaxis()->CenterTitle();
   // corr[0][0][j]->Draw("surf1");
   // c1->cd(2);
   // corr[0][1][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][1],ptrange[1][1]));
   // corr[0][1][j]->GetXaxis()->CenterTitle();
   // corr[0][1][j]->GetYaxis()->CenterTitle();
   // corr[0][1][j]->Draw("surf1");
   // c1->cd(3);
   // corr[0][2][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][2],ptrange[1][2]));
   // corr[0][2][j]->GetXaxis()->CenterTitle();
   // corr[0][2][j]->GetYaxis()->CenterTitle();
   // corr[0][2][j]->Draw("surf1");
   // c1->cd(4);
   // corr[1][0][j]->SetTitle(Form("Subeading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][0],ptrange[1][0]));
   // corr[1][0][j]->GetXaxis()->CenterTitle();
   // corr[1][0][j]->GetYaxis()->CenterTitle();
   // corr[1][0][j]->Draw("surf1");
   // c1->cd(5);
   // corr[1][1][j]->SetTitle(Form("Subleading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][1],ptrange[1][1]));
   // corr[1][1][j]->GetXaxis()->CenterTitle();
   // corr[1][1][j]->GetYaxis()->CenterTitle();
   // corr[1][1][j]->Draw("surf1");
   // c1->cd(6);
   // corr[1][2][j]->SetTitle(Form("Subleading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][2],ptrange[1][2]));
   // corr[1][2][j]->GetXaxis()->CenterTitle();
   // corr[1][2][j]->GetYaxis()->CenterTitle();
   // corr[1][2][j]->Draw("surf1");
   // c1->SaveAs(Form("7_19/CF_jet90_300_cent%i_%i_pt_depend.png",cbin[0][j],cbin[1][j]));
// }

//-----------------------------pt dependence plots (CF-LR)----------------------------------------------------------------------------------------------------------------------
// for (int j=0; j<4; j++){
   // TCanvas *c1=new TCanvas("c1","",1600,1000);
   // c1->Divide(3,2);
   // c1->cd(1);
   // result[0][0][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][0],ptrange[1][0]));
   // result[0][0][j]->GetXaxis()->CenterTitle();
   // result[0][0][j]->GetYaxis()->CenterTitle();
   // result[0][0][j]->Draw("surf1");
   // c1->cd(2);
   // result[0][1][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][1],ptrange[1][1]));
   // result[0][1][j]->GetXaxis()->CenterTitle();
   // result[0][1][j]->GetYaxis()->CenterTitle();
   // result[0][1][j]->Draw("surf1");
   // c1->cd(3);
   // result[0][2][j]->SetTitle(Form("Leading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][2],ptrange[1][2]));
   // result[0][2][j]->GetXaxis()->CenterTitle();
   // result[0][2][j]->GetYaxis()->CenterTitle();
   // result[0][2][j]->Draw("surf1");
   // c1->cd(4);
   // result[1][0][j]->SetTitle(Form("Subleading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][0],ptrange[1][0]));
   // result[1][0][j]->GetXaxis()->CenterTitle();
   // result[1][0][j]->GetYaxis()->CenterTitle();
   // result[1][0][j]->Draw("surf1");
   // c1->cd(5);
   // result[1][1][j]->SetTitle(Form("Subleading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][1],ptrange[1][1]));
   // result[1][1][j]->GetXaxis()->CenterTitle();
   // result[1][1][j]->GetYaxis()->CenterTitle();
   // result[1][1][j]->Draw("surf1");
   // c1->cd(6);
   // result[1][2][j]->SetTitle(Form("Subleading (%i<p_{T}^{ass}<%i);#Delta#eta;#Delta#phi",ptrange[0][2],ptrange[1][2]));
   // result[1][2][j]->GetXaxis()->CenterTitle();
   // result[1][2][j]->GetYaxis()->CenterTitle();
   // result[1][2][j]->Draw("surf1");
   // c1->SaveAs(Form("7_19/CF-LR_jet90_300_cent%i_%i_pt_depend.png",cbin[0][j],cbin[1][j]));
// }

//-------------------------single plots(CF and CF-LR) for all pt and cent bins-----------------------------------------------------------------------------------------------------
for (int k=0;k<2;k++){
  for (int i=0;i<3;i++){
    for (int j=0; j<4; j++){
      TCanvas *c1=new TCanvas();
      result[k][i][j]->SetTitle(Form("(%i<p_{T}^{ass}<%i)(%(%.0f-%.0f));#Delta#eta;#Delta#phi",ptrange[0][i],ptrange[1][i],2.5*(cbin[0][j]),2.5*(cbin[1][j])));
      result[k][i][j]->GetXaxis()->CenterTitle();
      result[k][i][j]->GetYaxis()->CenterTitle();
      result[k][i][j]->Draw("surf1");
      c1->SaveAs(Form("7_19/CF-LR%i_jet90_300_ass%i_%i_cent%i_%i_single.png",k,ptrange[0][i],ptrange[1][i],2.5*(cbin[0][j]),2.5*(cbin[1][j])));
      c1->Delete();
      // TCanvas *c2=new TCanvas();
      // corr[k][i][j]->SetTitle(Form("(%i<p_{T}^{ass}<%i)(%(%.0f-%.0f));#Delta#eta;#Delta#phi",ptrange[0][i],ptrange[1][i],2.5*(cbin[0][j]),2.5*(cbin[1][j])));
      // corr[k][i][j]->GetXaxis()->CenterTitle();
      // corr[k][i][j]->GetYaxis()->CenterTitle();
      // corr[k][i][j]->Draw("surf1");
      // c2->SaveAs(Form("7_19/CF%i_jet90_300_ass%i_%i_cent%i_%i_single.png",k,ptrange[0][i],ptrange[1][i],cbin[0][j],cbin[1][j]));
      // c2->Delete();
    }
  }
}
} 

