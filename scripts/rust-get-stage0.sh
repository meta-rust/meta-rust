#!/bin/sh
#
# This script helps to update rust version by taking sha256sum from stage0.json
# (For updating recipes-devtool/rust/rust-snapshot-${RUST_VERSION}.inc)
#
# Before version 1.80, stage0 was a json file
# parsing was done using jq.
# Starting from 1.80.x stage0 is a plain text file with key=value.
#
# RUST_VERSION < 1.80.0 : Stage0 url :
# https://raw.githubusercontent.com/rust-lang/rust/${RUST_VERSION}/src/stage0.json
#
# RUST_VERSION >= 1.80.0 : Stage0 url :
# https://raw.githubusercontent.com/rust-lang/rust/${RUST_VERSION}/src/stage0
#
# Dependency on "jq" shell tools for Json parsing before RUST_VERSION 1.80.0
##
# Usage :
#  ./rust-get-stage0.sh <Rust_version>
# ex: ./rust-get-stage0.sh 1.75.0

set -u
set -e

RUST_VERSION="${1:-1.83.0}"


SUPPORTED_ARCH=" \
    x86_64-unknown-linux-gnu \
    aarch64-unknown-linux-gnu \
    powerpc64le-unknown-linux-gnu\
"


##
# rust-lang ressource
##
RUSTC_CHECKSUM_URI="https://static.rust-lang.org/dist/rustc-${RUST_VERSION}-src.tar.xz.sha256"
STAGE0_URI="https://raw.githubusercontent.com/rust-lang/rust/${RUST_VERSION}/src/stage0"

RUSTSTD_PREFIX="rust-std"
RUSTC_PREFIX="rustc"
CARGO_PREFIX="cargo"
TARBALL_FORMAT="tar.xz"
###

get_checksum_for_snapshot_json () {
    [ $# -lt 2 ] && return 10
    _snapshot_version="${1}"
    _arch="${2}"

    _arch_only="$(echo "${_arch}" |cut -d'-' -f1)"

    printf -- "Get sha256 for arch %s (snapshot version %s)\n" "${_arch}" "${_snapshot_version}"

    # rust-std
    printf -- "- Update recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${RUSTSTD_PREFIX}" "${_arch_only}"
    jq .checksums_sha256 <"${OUT}" | grep "$(printf -- "%s-%s-%s.%s" "${RUSTSTD_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" |sed -n -r -e 's/\s+".*": "([a-f0-9]{1,64})",$/\1/p'
    printf -- "\n"

    # rustc
    printf -- "- recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${RUSTC_PREFIX}" "${_arch_only}"
    jq .checksums_sha256 <"${OUT}" | grep "$(printf -- "%s-%s-%s.%s" "${RUSTC_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" |sed -n -r -e 's/\s+".*": "([a-f0-9]{1,64})",$/\1/p'
    printf -- "\n"

    # cargo
    printf -- "- recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${CARGO_PREFIX}" "${_arch_only}"
    jq .checksums_sha256 <"${OUT}" | grep "$(printf -- "%s-%s-%s.%s" "${CARGO_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" |sed -n -r -e 's/\s+".*": "([a-f0-9]{1,64})",$/\1/p'
    printf -- "\n"
}

get_checksum_for_snapshot () {
    [ $# -lt 2 ] && return 10
    _snapshot_version="${1}"
    _arch="${2}"
    _arch_only="$(echo "${_arch}" | cut -d'-' -f1 -)"

    printf -- "Get sha256 for arch %s (snapshot version %s)\n" "${_arch}" "${_snapshot_version}"

    # rust-std
    printf -- "- Update recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${RUSTSTD_PREFIX}" "${_arch_only}"
    grep "$(printf -- "%s-%s-%s.%s" "${RUSTSTD_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" "${OUT}" |cut -d'=' -f2
    printf -- "\n"

    # rustc
    printf -- "- recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${RUSTC_PREFIX}" "${_arch_only}"
    grep "$(printf -- "%s-%s-%s.%s" "${RUSTC_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" "${OUT}" |cut -d'=' -f2
    printf -- "\n"

    # cargo
    printf -- "- recipes-devtool/rust-snapshot-%s.inc:\n\tSRC_URI[%s-snapshot-%s.sha256sum] = " \
        "${RUST_VERSION}" \
        "${CARGO_PREFIX}" "${_arch_only}"
    grep "$(printf -- "%s-%s-%s.%s" "${CARGO_PREFIX}" "${_snapshot_version}" "${_arch}" "${TARBALL_FORMAT}")" "${OUT}" |cut -d'=' -f2
    printf -- "\n"
}

##
# WARNING
##
# To avoid getting rustc archive and compute sha256sum on it
# we get directly the sha256sum file
get_rustcsrc_sha256 () {
    # Note: sha256sum length is 32bytes but can produce less than 64 hex character
    curl "${RUSTC_CHECKSUM_URI}" 2>/dev/null | sed -n -r -e 's/([a-f0-9]{1,64}).*$/\1/p'
}

# Get Stage0
#   - ${1}: Output file path
#   - [$2 : Get JSON (before rust 1.80.0)]
get_stage0 () {
    [ "$#" -lt 1 ] && return 10

    # Note: No local in posix shell, use _
    _out="${1}"
    _json="${2:-undef}"

    if [ "${_json}" = "undef" ]
    then
        # Get stage0
        curl -s -S \
	    "${STAGE0_URI}" \
	    -o "${_out}"
    else
        # Get stage0.json
        curl -s -S --header "Accept: application/json" \
	    "${STAGE0_URI}.json" \
	    -o "${_out}"
    fi
}



if [ "$(echo "${RUST_VERSION}"|cut -d'.' -f2 )" -ge 80 ]
then # Plain text Stage0
    OUT="$(mktemp --suffix=_stage0)"

    get_stage0 "${OUT}"

    STAGE0_RUST_VERSION=$(grep "compiler_version=" "${OUT}" | cut -d'=' -f2)
    printf -- "Compiler version for stage0 is : %s\n" "${STAGE0_RUST_VERSION}"

    # Get snapshot sha256sum
    for arch in ${SUPPORTED_ARCH}
    do
        get_checksum_for_snapshot "${STAGE0_RUST_VERSION}" "${arch}"
    done

else # Json Stage0
    OUT="$(mktemp --suffix=_stage0.json)"

    ## Stage0 Json
    printf -- "Get stage0.json for rust version %s\n" "${RUST_VERSION}"

    get_stage0 "${OUT}" "json"
    STAGE0_RUST_VERSION=$(jq -r .compiler.version <"${OUT}")
    printf -- "Compiler version for stage0 is : %s\n" "${STAGE0_RUST_VERSION}"

    # Get snapshot sha256sum
    for arch in ${SUPPORTED_ARCH}
    do
        get_checksum_for_snapshot_json "${STAGE0_RUST_VERSION}" "${arch}"
    done
fi

# Rustc Source
printf -- "Create 'recipes-devtool/rust-source-%s.inc' with \`SRC_URI[rust.sha256sum] = %s\`\n" \
    "${RUST_VERSION}" "$(get_rustcsrc_sha256)"

# TODO: Check LLVM_RELEASE update
printf -- "Check LLVM_RELEASE version for rust %s and update 'recipes-devtool/%s'\n" \
    "${RUST_VERSION}" "rust-llvm_${RUST_VERSION}.bb"

rm "${OUT}"
