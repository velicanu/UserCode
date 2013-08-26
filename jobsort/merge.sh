find $1|grep root|awk '\
BEGIN{i=0;c=0;print "mkdir -p mergedTmp/0"}{i++}{if (i>100) \
{print "hadd mergedTmp/"c".root mergedTmp/"c"/*.root";c++; i=0;print "mkdir -p mergedTmp/"c}}\
{print "ln -s "$1,"mergedTmp/"c"/"}{sub(".*/","",$1)}{print "./check.sh mergedTmp/"c"/"$1"|bash"}END{print "hadd mergedFile.root mergedTmp/*.root";}\
'
