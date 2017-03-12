# Specifics for Rust 1.18.0

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
"
SRC_URI[rust.md5sum] = "c37c0cd9d500f6a9d1f2f44401351f88"
SRC_URI[rust.sha256sum] = "d2dc36e99b9e2269488b2bcddde43c234e6bde03edf70cba82a027ff49c36111"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"

# set this as our default
S = "${RUSTSRC}"
