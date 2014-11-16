## Introduction

This openembedded layer provides the rust compiler, tools for building packages
(cargo), and a few example projects.

## What works:

 Building:
	 rust-native, cargo-native,
	 rust-cross (tested with qemux86)

## What doesn't:

 - building rust-hello-world

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

