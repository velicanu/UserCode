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


# if [[ -z "$2" ]]
# then
# nfiles=1
# else
# nfiles=$2
# fi

# input=$(($1+110))
input=$(($1))
# sinput=$(($input*$nfiles))


source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc434
cd /net/hisrv0001/home/dav2105/run/5_2_5_patch1/src
eval `scramv1 runtime -sh` 
cd -

echo "dav2105"

# filename=`head -$sinput /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt | tail -$nfiles`
# echo running on $filename

# cp /net/hisrv0001/home/dav2105/corrana/makecorrhists/ppbridge/sortedforests.txt .
cp dir_flag/PA2013_PromptReco_Json_FullTrack12_v84_prod2_MIT.txt .

rootn.exe -b <<EOF
.L dir_flag/runcorr.C+
runcorr($input,$2)
.q
EOF

# echo "before mv"
mv pbpb_corrhists_2fixedscale_trkqaul* /net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/unmerged
# echo "after cp, before rm"
# rm sortedHiForest_*
echo "job done successfully"
