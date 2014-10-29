SRC_URI[md5sum] = "24f80304da2ef1c0362b7caf700390f9"
SRC_URI[sha256sum] = "883e66b24d90d9957c5c538469fcde6f0668e5fb6448beecfc60884060e769b7"

SRC_URI_append = "\
	file://0001-mk-rt-export-CC-does-not-seem-to-work-gcc-observed-u.patch \
"
require rust-release.inc
