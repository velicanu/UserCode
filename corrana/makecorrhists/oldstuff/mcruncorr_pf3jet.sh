if [[ -z "$1" ]]
then
  echo "Usage: ./condor.sh <fileNumber>"
  exit 1
fi


# if [[ -z "$2" ]]
# then
# nfiles=1
# else
# nfiles=$2
# fi

# input=$(($1+1))
# sinput=$(($input*$nfiles))


source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc434
cd /net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src
eval `scramv1 runtime -sh` 
cd -

echo "dav2105"

# filename=`head -$sinput /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt | tail -$nfiles`
# echo running on $filename

rootn.exe -b <<EOF
.L /net/hisrv0001/home/dav2105/corrana/makecorrhists/mcruncorr_pf3jet.C+
mcruncorr($1)
.q
EOF

# echo "before mv"
mv mccorrhists_pf3_* /net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/unmerged
# echo "after cp, before rm"
# rm sortedHiForest_*
echo "job done successfully"
