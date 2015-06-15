# 1.1.0
require rust-release.inc
require rust.inc
SRC_URI[rust.md5sum] = "5f2f923f8d1c77a55721d1f0813a158a"
SRC_URI[rust.sha256sum] = "cb09f443b37ec1b81fe73c04eb413f9f656859cf7d00bc5088008cbc2a63fa8a"

## snapshot info taken from rust/src/snapshots.txt
## TODO: find a way to add aditional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2015-04-27"
RS_SRCHASH = "857ef6e"
# linux-x86_64
RS_HASH = "94089740e48167c5975c92c139ae9c286764012f"
RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-linux-x86_64-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "e0d49475a787aaa9481ec0b1a28d1f7a"
SRC_URI[rust-snapshot.sha256sum] = "e7858a90c2c6c35299ebe2cb6425f3f84d0ba171dcbce20ff68295a1ff75c7e5"

# "patch-prefix"
PP = "rust-${PV}"
SRC_URI_append = "\
	file://${PP}/0001-platform.mk-avoid-choking-on-i586.patch \
	file://${PP}/0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://${PP}/0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://${PP}/0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://${PP}/0005-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://${PP}/0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
	file://${PP}/0007-mk-install-use-disable-rewrite-paths.patch \
	file://${PP}/0008-install-disable-ldconfig.patch \
	file://${PP}/0009-src-rt-arch-i386-morestack.S-call-rust_stack_exhaust.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
