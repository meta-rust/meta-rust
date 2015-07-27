DESCRIPTION = "An implementation of regular expressions for Rust"
DEPENDS = "\
	aho-corasick-rs \
	memchr-rs \
	regex-syntax-rs \
"

require regex.inc

S = "${WORKDIR}/git"
