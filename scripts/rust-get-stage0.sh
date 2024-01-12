#!/bin/sh
#
# This script helps to update rust version by taking sha256sum from stage0.json
# (For updating recipes-devtool/rust/rust-snapshot-${RUST_VERSION}.inc)
#
# Stage0 url :
# https://raw.githubusercontent.com/rust-lang/rust/${RUST_VERSION}/src/stage0.json
#
# Dependency on "jq" shell tools for Json parsing.
##
# Usage :
#  ./rust-get-stage0.sh <Rust_version>
# ex: ./rust-get-stage0.sh 1.75.0

set -u
set -e

RUST_VERSION="${1:-1.75.0}"

OUT="$(mktemp --suffix=_stage0.json)"

printf -- "Get stage0.json for rust version %s\n" "${RUST_VERSION}"

# Get Stage0
curl -s -S --header "Accept: application/json" \
    "https://raw.githubusercontent.com/rust-lang/rust/${RUST_VERSION}/src/stage0.json" \
    -o "${OUT}"

STAGE0_RUST_VERSION=$(jq -r .compiler.version <"${OUT}")
printf -- "Compiler version for stage0 is : %s\n" "${STAGE0_RUST_VERSION}"


# x86_64-unknown-linux-gnu
printf -- "Hashes (sha256sum) for x86_64-unknow-linux-gnu.tar.xz snapshot\n"

printf -- "- rust-std-%s-x86_64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rust-std-${STAGE0_RUST_VERSION}-x86_64-unknown-linux-gnu.tar.xz"
printf -- "\n"

printf -- "- rustc-%s-x86_64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rustc-${STAGE0_RUST_VERSION}-x86_64-unknown-linux-gnu.tar.xz"
printf -- "\n"

printf -- "- cargo-%s-x86_64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "cargo-${STAGE0_RUST_VERSION}-x86_64-unknown-linux-gnu.tar.xz"
printf -- "\n"


# aarch64-unknown-linux-gnu
printf -- "Hashes (sha256sum) for aarch64-unknown-linux-gnu snapshot\n"

printf -- "- rust-std-%s-aarch64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rust-std-${STAGE0_RUST_VERSION}-aarch64-unknown-linux-gnu.tar.xz"
printf -- "\n"

printf -- "- rustc-%s-aarch64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rustc-${STAGE0_RUST_VERSION}-aarch64-unknown-linux-gnu.tar.xz"
printf -- "\n"

printf -- "- cargo-%s-aarch64-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "cargo-${STAGE0_RUST_VERSION}-aarch64-unknown-linux-gnu.tar.xz"
printf -- "\n"


# powerpc64le-unknown-linux-gnu
printf -- "Hashes (sha256sum) for powerpc64le snapshot\n"

printf -- "- rust-std-%s-powerpc64le-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rust-std-${STAGE0_RUST_VERSION}-powerpc64le-unknown-linux-gnu.tar.xz"
printf -- "\n"
printf -- "- rustc-%s-powerpc64le-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "rustc-${STAGE0_RUST_VERSION}-powerpc64le-unknown-linux-gnu.tar.xz"
printf -- "\n"
printf -- "- cargo-%s-powerpc64le-unknown-linux-gnu.tar.xz\n" "${STAGE0_RUST_VERSION}"
jq .checksums_sha256 <"${OUT}" | grep "cargo-${STAGE0_RUST_VERSION}-powerpc64le-unknown-linux-gnu.tar.xz"
printf -- "\n"


rm "${OUT}"
