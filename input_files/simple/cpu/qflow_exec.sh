#!/usr/bin/tcsh -f
#-------------------------------------------
# qflow exec script for project /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu
#-------------------------------------------

/usr/lib/qflow/scripts/synthesize.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
/usr/lib/qflow/scripts/placement.sh -d /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
# /usr/lib/qflow/scripts/vesta.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
# /usr/lib/qflow/scripts/router.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
# /usr/lib/qflow/scripts/placement.sh -f -d /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
# /usr/lib/qflow/scripts/router.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1 $status
# /usr/lib/qflow/scripts/cleanup.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
# /usr/lib/qflow/scripts/display.sh /home/naufal/Documents/auc/ravacancy/tdp_app/hello_world/input_files/simple/cpu cpu || exit 1
