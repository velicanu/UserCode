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

# input=$(($1+1))
# sinput=$(($input*$nfiles))


source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc434
cd /net/hisrv0001/home/astrelni/CMSSW_4_4_4/src
eval `scramv1 runtime -sh` 
cd -

echo "astrelni"

# filename=`head -$sinput /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt | tail -$nfiles`
# echo running on $filename

cp /net/hisrv0001/home/astrelni/ridge/phi_cross_checks/sortedforests.txt .

rootn.exe -b <<EOF
.L /net/hisrv0001/home/astrelni/ridge/phi_cross_checks/runcorr.C+
runcorr($1,$2)
.q
EOF

# echo "before mv"
mv corrhists_tutorial_* /net/hisrv0001/home/astrelni/ridge/phi_cross_checks/unmerged/phibin7/
# echo "after cp, before rm"
# rm sortedHiForest_*
echo "job done successfully"
