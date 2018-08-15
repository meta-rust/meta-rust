#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 RUST_VERSION"
  exit 1
fi

RUST_VERSION=$1
RUST_STD_PREFIX="rust-std-${RUST_VERSION}-"
RUST_DIST_URL="https://dev-static.rust-lang.org/dist/"
OUTPUT_FILE="rust-snapshot-target-${RUST_VERSION}.inc"
TMP_FILE="${OUTPUT_FILE}.tmp"

TRIPLETS=$(curl -s "${RUST_DIST_URL}" | grep "${RUST_STD_PREFIX}" | grep href | grep unknown-linux | grep tar.gz.sha256 | sed -e "s#.*href=\\\"/dist/${RUST_STD_PREFIX}\(.*\).tar.gz.sha256\\\".*#\1#g")

if [ -z "${TRIPLETS}" ]; then
    echo "No file is found for version \"${RUST_VERSION}\"!"
    exit 1
fi

echo "# This file is generated automatically by scripts/gen-rust-snapshot-target-inc.sh" > "${TMP_FILE}"
echo "" >> "${TMP_FILE}"

for TRIPLET in ${TRIPLETS}; do
    RUST_STD_FILE="${RUST_STD_PREFIX}${TRIPLET}.tar.gz"

    curl "${RUST_DIST_URL}${RUST_STD_FILE}" -O
    curl "${RUST_DIST_URL}${RUST_STD_FILE}.sha256" -O
    sha256sum -c "${RUST_STD_FILE}.sha256" || exit 1

    MD5SUM=$(md5sum "${RUST_STD_FILE}" | awk '{ print $1 }')
    SHA256SUM=$(cat "${RUST_STD_FILE}.sha256" | awk '{ print $1 }')
    echo "SRC_URI[rust-std-snapshot-target-${TRIPLET}.md5sum] = \"${MD5SUM}\"" | tee -a "${TMP_FILE}"
    echo "SRC_URI[rust-std-snapshot-target-${TRIPLET}.sha256sum] = \"${SHA256SUM}\"" | tee -a "${TMP_FILE}"

    rm "${RUST_STD_FILE}"
    rm "${RUST_STD_FILE}.sha256"
done

mv "${TMP_FILE}" "${OUTPUT_FILE}"
