SECTION = "devel"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

LIC_FILES_CHKSUM += " \
file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"

# Needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"
export LIBSSH2_SYS_USE_PKG_CONFIG = "1"

BBCLASSEXTEND = "native"
