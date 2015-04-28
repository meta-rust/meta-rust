SRC_URI = "\
	gitsm://github.com/rust-lang/rust.git;protocol=https \
"

SRC_URI[md5sum] = "6447489e0009519c845b8e350c220636"
SRC_URI[sha256sum] = "b62eed6bdb3cb356c90d587e9d9ee7fb5aedad917ff872c04e67e20b4c8f1c91"

S = "${WORKDIR}/git"
PV .= "+git${SRCPV}"
require rust.inc

