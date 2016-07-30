## Introduction

This OpenEmbedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 - MACHINE="beaglebone" (TARGET_SYS=arm-poky-linux-gnueabi)
 - Building rust-native, rust-cross, rust-hello-world, cargo-native
 - Running/using all of these (including rust-hello-world)

## What doesn't:

 - Probably some of the untested things

## What's untested:

 - rust (built for target)
 - Other TARGETs

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

 - -crosssdk and -buildsdk packages
 - Upstream local rustc patches for libdir and bindir support
 - add bitbake fetch support for crates.io
 - add required cargo package registry clones in SRC_URI to prevent the need
   for network when building.

## Pitfalls

 - TARGET_SYS _must_ be different from BUILD_SYS. This is due to the way configuration options are tracked for different targets.

## Dependencies

On the host:
	unknown

On the target:
	unknown

## Maintainer(s) & Patch policy

Open a Pull Request.

The master branch supports the latest master of poky. When poky creates releases, we will create a branch with the same name as the poky release. This release branch should always work with that poky release. Note that these release branches will typically be less tested than the master branch.

## Copyright

MIT OR Apache-2.0 - Same as rust

