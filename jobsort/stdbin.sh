if [[ -z "$1" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi
if [[ -z "$2" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi
if [[ -z "$3" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi
if [[ -z "$4" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi

if [[ -z "$5" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi

if [[ -z "$6" ]]
then
  echo "Usage: ./condor.sh <fileNumber> <list_of_files.txt> <outfolder> <sortscript> <nmin> <nmax>"
  exit 1
fi

# example ./stdsort.sh 1 /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/promptskim-hihighpt-hltjet80-pt90-v3-forest-v2.txt /mnt/hadoop/cms/store/user/velicanu/unmerged_promptskim-hihighpt-hltjet80-pt90-v3-forest-v2 pbpbsort.C
# example ./stdsort.sh 0 mc100sortlist.txt /mnt/hadoop/cms/store/user/velicanu/testmcsort100 pbpbsort.C
# example ./stdsort.sh 0 mc100sortlist.txt /mnt/hadoop/cms/store/user/velicanu/testppbtrack12sort ppbmultbin.C
 


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
.L $PWD/${4}+
stdsort($1,"$PWD/$2",$5,$6)
.q
EOF

echo "sending to: ${3}/`ls sortedHiForest_*`"
mv sortedHiForest_* ${3}
echo "job done successfully"
