if [ $# != 1 ]; then
    echo "Usage: ./condor.sh <fileNumber>"
    exit 1
fi
input=$(($1+1))

echo "./condor.sh $1"
#inputfile=`head -$input /net/hisrv0001/home/dav2105/run/listMC.txt | tail -1`
#outputfile=/net/hisrv0001/home/dav2105/run/outfiles/PPMultMC$input.root
inputfile=`head -$input /net/hisrv0001/home/dav2105/run/CMSSW_3_5_8_patch3/src/UserCode/velicanu/Skims/macros/rootfilenames.txt | tail -1`
outputfile=/net/hisrv0001/home/dav2105/scratch/dav2105/outfiles/PPMult$input.root
echo $inputfile
echo $outputfile
root -b -q /net/hisrv0001/home/dav2105/run/CMSSW_3_5_8_patch3/src/UserCode/velicanu/Skims/macros/condor_root.C\(\"$inputfile\"\,\"$outputfile\"\) rootlogon.C
