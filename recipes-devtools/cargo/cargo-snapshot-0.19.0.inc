CARGO_SNAPSHOT = "cargo-0.19.0-${RUST_BUILD_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot \
"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[cargo-snapshot.md5sum] = "e3cbae9515cb770454e661d8847f685d"
SRC_URI[cargo-snapshot.sha256sum] = "24d5e01b09ba0fb15c4b7ef4f527aca874ce2e0cebc3850fdc2535ac7e25b205"
