now="submit_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now
cp -r HiForestAnalysis $now
cp runcorr.C corrana.C PA2013_PromptReco_Json_FullTrack12_v84_prod2_MIT.txt $now
cat runcorr.condor | sed "s@log_flag@$now@g" | sed "s@dir_flag@$PWD/$now@g" > $now/runcorr.condor
cat runcorr.sh | sed "s@dir_flag@$PWD/$now@g" > $now/runcorr.sh
chmod +x $now/runcorr.sh

rootn.exe -b <<EOF
.L $now/runcorr.C+
.q
EOF

# condor_submit $now/runcorr.condor

