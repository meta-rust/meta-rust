#!/bin/bash -e

if [[ $# -lt 1 ]]; then
    echo "No Yocto branch specified, defaulting to master"
    echo "To change this pass a Yocto branch name as an argument to this script"
fi
branch=${1-master}

rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress build/downloads yocto-cache@build-cache.asterius.io:/srv/yocto-cache/

rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress build/sstate-cache yocto-cache@build-cache.asterius.io:/srv/yocto-cache/${branch}/

exit 0
