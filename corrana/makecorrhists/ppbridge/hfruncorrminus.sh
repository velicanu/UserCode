if [[ -z "$1" ]]
then
  echo "Usage: ./condor.sh <condor_iteration>"
  exit 1
fi

if [[ -z "$2" ]]
then
  echo "Usage: ./condor.sh <condor_iteration> <trackqualityflag>"
  exit 1
fi


# input=$(($1+110))
input=$(($1))
# sinput=$(($input*$nfiles))


source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc434
cd /net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src
eval `scramv1 runtime -sh` 
cd -

echo "dav2105"

# filename=`head -$sinput /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt | tail -$nfiles`
# echo running on $filename

# cp /net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/doeproposalforests.txt .
cp /net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/HIRun2013-PromptReco-v1-HLT_PAPixelTracks_Multiplicity190_v1-forest-v2.txt .

rootn.exe -b <<EOF
.L /net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/runhfminus.C+
runcorr($input,$2)
.q
EOF

# echo "before mv"
# mv corrhists_trkhfminus_trkqaul* /net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/unmerged
mv corrhists_trkhfminus_trkqaul* /net/hidsk0001/d00/scratch/dav2105/corrhists/HIRun2013/unmerged
# echo "after cp, before rm"
# rm sortedHiForest_*
echo "job done successfully"
