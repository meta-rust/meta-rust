SRCREV_cargo = "8cc600a33436a3c75372b252ddecb1f90961d61b"
require cargo.inc

SRC_URI_append = " \
	git://github.com/jmesmon/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
"
#git://github.com/jmesmon/libz-sys.git;protocol=https;name=libz-sys;destsuffix=libz-sys
SRCREV_git2-rs  = "fa270b5eed7e9e94aa7d8bc18fa923d8e6b32ba6"
#SRCREV_libz-sys = "
OECARGO_PATH = "${WORKDIR}/git2-rs"
