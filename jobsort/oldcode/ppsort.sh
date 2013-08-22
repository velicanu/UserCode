if [[ -z "$1" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript>"
  exit 1
fi
if [[ -z "$2" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript>"
  exit 1
fi
if [[ -z "$3" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript>"
  exit 1
fi
if [[ -z "$4" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript>"
  exit 1
fi



input=$(($1+1))

source /osg/app/cmssoft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc434
cd /net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src
eval `scramv1 runtime -sh` 
cd -

# flist='${2}'
filename=`head -$input ${2} | tail -1`
echo dav2105 running on $filename

rootn.exe -b <<EOF
.L /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/${4}+
stdsort($1,"$2")
.q
EOF

echo "before mv"
mv sortedHiForest_* ${3}
echo "job done successfully"
