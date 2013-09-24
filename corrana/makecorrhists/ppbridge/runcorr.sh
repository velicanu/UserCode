if [[ -z "$1" ]]
then
  echo "Usage: ./condor.sh <condor_iteration> <trackqualityflag> <file-list> <tag>"
  exit 1
fi

if [[ -z "$2" ]]
then
  echo "Usage: ./condor.sh <condor_iteration> <trackqualityflag> <file-list> <tag>"
  exit 1
fi

if [[ -z "$3" ]]
then
  echo "Usage: ./condor.sh <condor_iteration> <trackqualityflag> <file-list> <tag>"
  exit 1
fi

if [[ -z "$4" ]]
then
  echo "Usage: ./condor.sh <condor_iteration> <trackqualityflag> <file-list> <tag>"
  exit 1
fi

echo | awk -v i=$1 -v trkq=$2 -v flist=$3 -v tag=$4 '{print "./runcorr.exe "i" "trkq" "flist" "tag" "}' | bash
echo | awk -v tag=$4 '{print "mv "tag"*.root /net/hidsk0001/d00/scratch/dav2105/corrhists/HIRun2013/unmerged"}' | bash

echo "job done successfully"
