SRCREV = "1e4e55aebc1a71b6674c00b8604efa6b1e2e52cd"
require rust-git.inc

SRC_URI_append = "\
	file://0001-src-etc-snapshot-support-triples-lacking-a-vendor.patch \
	file://0001-get-snapshot-debug.patch \
	file://0001-platform.mk-avoid-choking-on-i586.patch \
"
