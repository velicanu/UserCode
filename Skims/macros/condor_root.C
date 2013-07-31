void condor_root(const std::string& infile, const std::string& outfile)
{
  gSystem->Load( "libFWCoreFWLite" );
  gSystem->Load("libDataFormatsFWLite");
  AutoLibraryLoader::enable();

  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libDataFormatsPatCandidates.so");

  gSystem->Load("/net/hisrv0001/home/dav2105/run/CMSSW_3_5_8_patch3/src/UserCode/velicanu/Skims/macros/trkAnaExample_C");
  trkAnaExample(infile,outfile);
}
