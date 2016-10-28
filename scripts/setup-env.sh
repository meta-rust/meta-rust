#!/bin/bash -e

mkdir -p build

sudo mount -t tmpfs -o size=64G,mode=755,uid=${UID} tmpfs build

exit 0
