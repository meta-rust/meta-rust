#!/bin/bash -e

# Only attempt to unmount if the directory is already mounted
if mountpoint -q `pwd`/build; then
    sudo umount build
fi

exit 0
