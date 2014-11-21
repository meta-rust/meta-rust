## Introduction

This openembedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 - MACHINE="beaglebone" (TARGET_SYS=arm-poky-linux-gnueabi)
 - Building rust-native, rust-cross, rust-hello-world

## What doesn't:

 - building cargo-native (Using a local cargo install from somewhere else works just fine).

## What's untested:

 - cargo, rust (built for target)
 - running anything
 - Other TARGETs

## TODO

 - Include downloaded stage0 snapshot in `SRC_URI`
 - -crosssdk and -buildsdk packages
 - -runtime? (install target libraries on target)
 - Add SRC_URI components so that cargo doesn't use the network
 - Convince cargo not to use '$HOME/.cargo' for storing downloaded source code

## Pitfalls

 - TARGET_SYS _must_ be different from BUILD_SYS. This is due to the way configuration options are tracked for different targets.

## Dependencies

On the host:
	unknown

On the target:
	unknown

## Maintainer(s) & Patch policy

Open a Pull Request

## Copyright

MIT/Apache-2.0 - Same as rust

