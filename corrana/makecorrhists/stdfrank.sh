if [[ "$#" -lt 8 ]]
then
  echo "Usage: ./stdfrank.sh <fileNumber> <doeffweighting> <filelist> <outftag> <mccommand> <jetamin> <jetamax> <C-file>"
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

cp /net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/trkPara.tar .
cp /net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/trkcorr.tar .
tar -xf trkPara.tar
tar -xf trkcorr.tar

echo "dav2105"

# filename=`head -$sinput /net/hidsk0001/d00/scratch/dav2105/forest/jobsort/sortlist.txt | tail -$nfiles`
# echo running on $filename

rootn.exe -b <<EOF
.L /net/hisrv0001/home/dav2105/corrana/makecorrhists/$8+
stdruncorr($1,$2,"/net/hisrv0001/home/dav2105/corrana/makecorrhists/$3","$4",$5,$6,$7)
.q
EOF

# echo "before mv"
mv ${4}_eff${2}_* /net/hidsk0001/d00/scratch/dav2105/corrhists/HIData_Minbias_2760GeV/unmerged
# echo "after cp, before rm"
# rm sortedHiForest_*
rm -r trkPara
rm -r trkcorr
rm trkPara.tar
rm trkcorr.tar
echo "job done successfully"
