## Introduction

This openembedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 - MACHINE="beaglebone" (TARGET_SYS=arm-poky-linux-gnueabi)
 - Building rust-native, rust-cross, rust-hello-world

## What doesn't:

 - building cargo-native (I managed to break it)

## What's untested:

 - cargo, rust (built for target)
 - running anything

## TODO

 - Use rust-native when building rust & rust-cross
 - Include downloaded stage0 snapshot in `SRC_URI`

## Dependencies

On the host:
	unknown

On the target:
	unknown

## Maintainer(s) & Patch policy

Open a Pull Request

## Copyright

MIT/Apache-2.0 - Same as rust

