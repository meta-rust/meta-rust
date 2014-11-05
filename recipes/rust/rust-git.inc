SRC_URI = "\
	gitsm://github.com/rust-lang/rust.git;protocol=https \
"
S = "${WORKDIR}/git"
PV .= "+git${SRCPV}"
require rust.inc

