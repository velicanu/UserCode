if [[ -z "$1" ]]
then
  echo "Usage: ./psort.sh <input-list> <flag>"
  exit 1
fi
if [[ -z "$2" ]]
then
  echo "Usage: ./psort.sh <input-list> <flag>"
  exit 1
fi

now="$2_$(date +"%Y_%m_%d__%H_%M_%S")"
len=`wc -l $1 | awk '{print $1}'`
njobs=$((len*2))

mkdir $now
cp $1 $now
cp runcorr.sh $now
cat runcorr.condor | sed "s@log_flag@$now@g" | sed "s@dir_flag@$PWD/$now@g" |  sed "s@arg1@$1@g" | sed "s@arg2@$2@g" | sed "s@njobs@$njobs@g" > $now/runcorr.condor

NAME="runcorr.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "${NAME/%.C/}.exe"
cp runcorr.exe $now
echo
cat $now/runcorr.condor
echo 
echo condor_submit $now/runcorr.condor
echo
# condor_submit $now/runcorr.condor

