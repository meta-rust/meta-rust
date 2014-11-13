SRCREV = "15ba87f0314fda5e81603f37ae5f40e2022bcfc1"
require rust-git.inc

SRC_URI_append = "\
	file://0001-src-etc-snapshot-support-triples-lacking-a-vendor.patch \
"
