inherit rust

SRC_URI = "git://github.com/jmesmon/rust-hello-world.git;protocol=https"
SRCREV="e0fa23f1a3cb1eb1407165bd2fc36d2f6e6ad728"
LIC_FILES_CHKSUM="file://COPYRIGHT;md5=e6b2207ac3740d2d01141c49208c2147"

SUMMARY = "Hello World by Cargo for Rust"
HOMEPAGE = "https://github.com/jmesmon/rust-hello-world"
LICENSE = "MIT | Apache-2.0"

# FIXME: we really depend on cargo-native, but avoid it for now as building it
# is more painful than it should be
DEPENDS = "cargo-native"

S = "${WORKDIR}/git"
B = "${S}"

do_compile () {
	oe_cargo_build
}

do_install () {
	install -d "${D}${bindir}"
	for tgt in "${B}/target/${HOST_SYS}/release/"*; do
		if [ -f "$tgt" ] && [ -x "$tgt" ]; then
			install -m755 "$tgt" "${D}${bindir}"
		fi
	done
}
