#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "math.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"
#endif

void trkAnaExample(std::string infile, std::string outfile){

  TString inname(infile);
  TString outname(outfile);
  
  //TFile mapfile("/net/hisrv0001/home/dav2105/run/CMSSW_3_5_8_patch3/src/UserCode/velicanu/Skims/macros/map.root");
  //TH1D* map = (TH1D*)mapfile.Get("map");
  
  /*
  TChain * tr = new TChain("rootpleProducer/AnalysisTree","");
  tr->Add(inputstring.Data());

  TFile file(outputstring.Data(),"ReCreate");
  */
  // is gen track needed
  const bool isGEN = false;
  
  // event cuts
  //const unsigned int maxEvents = 10000;
  // vertex cuts 
  const double nVtxTrackCut = 3.0;
  // track cuts
  const char srcTrack[50] = "selectTracks";
  //const char srcTrack[50] = "generalTracks";
  //const char srcTrack[50] = "refitTracks";
  const string qualityString = "highPurity";
  const double normD0Cut = 3.0;
  const double normDZCut = 3.0;
  const double ptErrCut = 0.1;
  const unsigned nHitsCut = 1; // at least this many hits on track
  // kinematic cuts
  const double etaCut = 2.4;
  const double ptCut = 0.1;
  
  //
  //char *hltNames[nTrigs] = {"HLT_MinBiasBSC","HLT_L1Jet6U","HLT_Jet15U","HLT_Jet30U","HLT_Jet50U"};
  const int nTrigs = 1;
  bool hasTrigger = {false};
  char *hltNames[nTrigs] = {"HLT_PixelTracks_Multiplicity70"};


  //----- input files -----
  vector<string> fileNames;
  //string fileDir = "/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/MinimumBias/MB-C10-May6thReRecov1-MINBIASTRKANASKIM-v1/1ada6822635250882a3443f7c3641f57";       // data skim
  string fileDir = "";       // data skim
  cout << "directory: '" << fileDir << "'" << endl;
     cout << "  adding file: " << inname.Data() << endl;
     //fileNames.push_back("dcache:" + fileDir + "/" + inname.Data());
     fileNames.push_back(inname.Data());
  fwlite::ChainEvent event(fileNames);
  
  //----- output files -----
  //TFile file(outputstring.Data(),"ReCreate");
  //TFile outFile("PPMult.root","ReCreate");

  
  //----- define output hists/trees in directories of output file -----
  TFile *outFile = new TFile(outname.Data(),"recreate");
  //TNtuple *ntuple = new TNtuple("ntuple","PPMult","mult");
  TH1D::SetDefaultSumw2();

  TH1D *hVtxSize    = new TH1D("hVtxSize","number of reconstructed pixel vertices",10,-0.5,9.5);
  TH1D *hVtxTrks    = new TH1D("hVtxTrks","number of tracks used to fit pixel vertex",50,-0.5,49.5);
  TH1D *hVtxZ       = new TH1D("hVtxZ","z position of best reconstructed pixel vertex", 80,-20,20);

  // track hists
  TH1D *hTrkDxyBeam = new TH1D("hTrkDxyBeam","track dxy from beamspot; dxy [cm]", 80, -2.0, 2.0);
  TH1D *hTrkDzVtx   = new TH1D("hTrkDzVtx","track dz from vertex; dz [cm]", 80, -2.0, 2.0);
  TH1D *hTrkNhits   = new TH1D("hTrkNhits", "number of valid hits on track", 30,-0.5,29.5);
  TH1D *hTrkPt      = new TH1D("hTrkPt","track p_{T}; p_{T} [GeV/c]", 100, 0.0, 50.0);
  TH1D *hTrkEta     = new TH1D("hTrkEta","track #eta; #eta", 60, -3.0, 3.0);
  TH1D *hTrkPhi     = new TH1D("hTrkPhi","track #phi; #phi [radians]", 56, -3.5, 3.5);
  TH1D *hNTrks      = new TH1D("hNTrks","Event Multiplicity;N", 200, 0, 200);
  TH1D *hNTrigTrks      = new TH1D("hNTrigTrks","Event Multiplicity fired by trigger;N", 200, 0, 200);
  TH1D *hNTrksTrigOn      = new TH1D("hNTrksTrigOn","Event Multiplicity when trigger is on;N", 200, 0, 200);
  //TH1D *hHLTPaths   = new TH1D("hHLTPaths","HLT Paths",3,0,3);

  // gen track hists
  TH1D *hGenTrkPt=0;      
  if(isGEN) hGenTrkPt = new TH1D("hGenTrkPt","track p_{T}; p_{T} [GeV/c]", 100, 0.0, 50.0);

  //----- loop over events -----
  unsigned int iEvent=0;
  for(event.toBegin(); !event.atEnd(); ++event, ++iEvent){

	//cout<<"map("<<event.id().run()<<")="<<map->GetBinContent(event.id().run())<<endl;
    //if( iEvent == maxEvents ) break;
    if( iEvent % 1000 == 0 ) cout << "Processing " << iEvent<< "th event: "
				  << "run " << event.id().run() 
				  << ", lumi " << event.luminosityBlock() 
				  << ", evt " << event.id().event() << endl;

    // select on requirement of valid vertex
    fwlite::Handle<std::vector<reco::Vertex> > vertices;
    //vertices.getByLabel(event, "pixel3Vertices");        //agglomerative pixel vertex
    vertices.getByLabel(event, "offlinePrimaryVertices");  //full-track primary vertex
    hVtxSize->Fill(vertices->size());
    if(!vertices->size()) continue;
    if(vertices->size()!=1) continue;
    size_t maxtracks=0; double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9, bestNchi2=999.9;
    int numFake=0, numVtxTrk=0;
    for(unsigned it=0; it<vertices->size(); ++it) {
      const reco::Vertex & vtx = (*vertices)[it];
      if(vtx.isFake()) numFake++;
      numVtxTrk = vtx.tracksSize();
      if(vtx.tracksSize() > maxtracks
	 || (vtx.tracksSize() == maxtracks && vtx.normalizedChi2() < bestNchi2) ) {
	maxtracks = vtx.tracksSize();
	bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
	bestNchi2 = vtx.normalizedChi2();
      }	
    }
    if(numVtxTrk<nVtxTrackCut) continue;
    if(numFake>=1) continue;
    hVtxTrks->Fill(maxtracks);
    hVtxZ->Fill(bestvz);

	// get hlt bits	
    fwlite::Handle<edm::TriggerResults> triggerResults;
    triggerResults.getByLabel(event, "TriggerResults","", "HLT");
	const edm::TriggerNames triggerNames = event.triggerNames(*triggerResults);
    bool accept[nTrigs];
    for(int i=0; i<nTrigs; i++) {
	  if(triggerNames.triggerIndex(hltNames[i])!=triggerNames.size()) hasTrigger = true;
	  if(hasTrigger)
		accept[i] = triggerResults->accept(triggerNames.triggerIndex(hltNames[i]));
      //if(accept[i]) hHLTPaths->Fill(hltNames[i],1);
    }
	
	
	// get beamspot
    fwlite::Handle<reco::BeamSpot> beamspot;
    beamspot.getByLabel(event, "offlineBeamSpot");

    //----- loop over tracks -----
    fwlite::Handle<std::vector<reco::Track> > tracks;
    tracks.getByLabel(event, srcTrack);

    unsigned nfinalTracks = 0;
    //int multiplicity = 0;
    for(unsigned it=0; it<tracks->size(); ++it){
      
      const reco::Track & trk = (*tracks)[it];
      
      // select high purity tracks
      //if(!trk.quality(reco::TrackBase::qualityByName(qualityString))) continue;

      // select tracks based on transverse proximity to beamspot
      double dxybeam = trk.dxy(beamspot->position());
      hTrkDxyBeam->Fill(dxybeam);
      //if(fabs(dxybeam/trk.d0Error()) > normD0Cut) continue;

      // select tracks based on z-proximity to best vertex 
      math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
      double dzvtx = trk.dz(bestvtx);
      hTrkDzVtx->Fill(dzvtx);
      //if(fabs(dzvtx/trk.dzError()) > normDZCut) continue;

      // select tracks based on relative pt error
      double pterr = trk.ptError()/trk.pt();
      //if(pterr > ptErrCut) continue;

      // select tracks based on number of valid rechits
      unsigned nhits = trk.numberOfValidHits();
      hTrkNhits->Fill(nhits);
      //if(nhits < nHitsCut) continue;

      // select tracks based on kinematic cuts
      if(abs(trk.eta())>etaCut || trk.pt()<ptCut) continue;

      nfinalTracks++;

      // fill selected track histograms
      hTrkPt->Fill(trk.pt());
      hTrkEta->Fill(trk.eta());
      hTrkPhi->Fill(trk.phi());
      
      
      
      
      
    }
    //ntuple->Fill((int)nfinalTracks);
    //hNTrks->Fill(nfinalTracks,map->GetBinContent(event.id().run())); 
    hNTrks->Fill(nfinalTracks); 
	if(hasTrigger)
	{
		hNTrksTrigOn->Fill(nfinalTracks);
		if(accept[0]) hNTrigTrks->Fill(nfinalTracks); 
	}

    	
    
    
    //---- loop over MC gen level track ---- 
    if(!isGEN) continue;

    fwlite::Handle<std::vector<reco::GenParticle> > genTracks;
    genTracks.getByLabel(event, "genParticles");
    
    for(unsigned ip=0; ip<genTracks->size(); ++ip){
       const reco::GenParticle & p = (*genTracks)[ip];
       if(p.status() != 1) continue;
       if(p.collisionId() != 0) continue;
       if(p.charge() == 0) continue;
       if(fabs(p.eta())>etaCut) continue;
       // fill selected GEN track histograms
       hGenTrkPt->Fill(p.pt());
    }
    
  }
  
  cout << "Number of events processed : " << iEvent << endl;
  cout << "Number passing all event selection cuts: " << hVtxZ->GetEntries() << endl;
/*
  TCanvas* c = new TCanvas("c","",800,800);
  c->Divide(2,2);
  c->cd(1);
  c->GetPad(1)->SetLogy();
  hNTrks->Draw("PE");
  c->cd(2);
  c->GetPad(2)->SetLogy();
  hTrkPt->Draw("PE");
  c->cd(3);
  hTrkEta->Draw("PE");
  c->cd(4);
  hTrkPhi->Draw("PE");

  TCanvas* c1 = new TCanvas("c1","",900,300);
  c1->Divide(3,1);
  c1->cd(1);
  c1->GetPad(1)->SetLogy();
  hVtxSize->Draw("PE");  
  c1->cd(2);
  hVtxTrks->Draw("PE");
  c1->cd(3);
  hVtxZ->Draw("PE");  
  
  */
  if(hNTrigTrks->GetEntries()==0) delete hNTrigTrks;
  // write to output file
  //ntuple->Write();
  outFile->Write();
  outFile->Close();
/*
  outFile->ls();
*/
}

