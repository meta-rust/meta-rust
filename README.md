## Introduction

This OpenEmbedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 - Building rust-native, rust-cross, rust-hello-world, cargo-native
 - Building Rust based projects with Cargo for the TARGET

## What doesn't:

 - Using anything but x86_64 as the build environment
 - Probably some of the untested things

## What's untested:

 - rust (built for target)

## Building a rust package

When building a rust package in bitbake, it's usually easiest to build with
cargo using cargo.bbclass.  If the package already has a Cargo.toml file (most
rust packages do), then it's especially easy.  Otherwise you should probably
get the code building in cargo first.

Once your package builds in cargo, you can use
[cargo-bitbake](https://github.com/cardoe/cargo-bitbake) to generate a bitbake
recipe for it.  This allows bitbake to fetch all the necessary dependent
crates, as well as a pegged version of the crates.io index, to ensure maximum
reproducibility.

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

All new patches against rust, rust-llvm, and cargo must have referenced
upstream issues or PRs opened or an explanation why the patch cannot be
upstreamed. This cooresponds to the OpenEmbedded policy for other meta layers.

## Copyright

MIT OR Apache-2.0 - Same as rust

