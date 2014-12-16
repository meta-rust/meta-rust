## Introduction

This openembedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 - MACHINE="beaglebone" (TARGET_SYS=arm-poky-linux-gnueabi)
 - Building rust-native, rust-cross, rust-hello-world, cargo-native
 - Running/using all of these (including rust-hello-world)
 - cargo-native (use a local package for -native)

## What doesn't:

 - Probably some of the untested things

## What's untested:

 - rust (built for target)
 - Other TARGETs
 - cargo

## Common issues when packaging things using cargo

 You may run into errors similar to:

```
| src/lib.rs:12:1: 12:35 error: can't find crate for `ffi`
| src/lib.rs:12 extern crate "openssl-sys" as ffi;
|               ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

 Where a "-sys" crate (or other crate) is not found. These are typically caused
by a crate's Cargo.toml including triplet-specific dependencies and then using
the crate based on a feature (most often, `#[cfg(unix)]`). Until cargo and it's
ecosystem get their act together, you'll need to supply patches to the
misbehaving packages. See `recipies/cargo/cargo_*.bb` for an example of how to
do this.

## TODO

 - Include downloaded stage0 snapshot in `SRC_URI`
 - -crosssdk and -buildsdk packages
 - -runtime? (install target libraries on target)
 - Add SRC_URI components so that cargo doesn't use the network
 - Convince cargo (via env vars or patching) not to use '$HOME/.cargo' for storing downloaded source code
 - Upstream local rustc patches for libdir and bindir support

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

