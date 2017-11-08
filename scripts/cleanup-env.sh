#!/bin/bash -x

sudo fuser -m `pwd`/build

# Only attempt to unmount if the directory is already mounted
if mountpoint -q `pwd`/build; then
    sudo umount `pwd`/build
fi

sudo fuser -m `pwd`/build

ps -ef

exit 0
