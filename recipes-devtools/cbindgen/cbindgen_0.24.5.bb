SUMMARY = "A tool for generating C bindings to Rust code."
HOMEPAGE = "https://github.com/eqrion/cbindgen"
LICENSE = "MPL-2.0"


SRC_URI += "crate://crates.io/cbindgen/${PV}"
S = "${WORKDIR}/cbindgen-${PV}"

SRC_URI += " \
    crate://crates.io/atty/0.2.14 \
    crate://crates.io/autocfg/1.1.0 \
    crate://crates.io/bitflags/1.3.2 \
    crate://crates.io/cfg-if/1.0.0 \
    crate://crates.io/clap/3.2.25 \
    crate://crates.io/clap_lex/0.2.4 \
    crate://crates.io/fastrand/1.9.0 \
    crate://crates.io/hashbrown/0.12.3 \
    crate://crates.io/heck/0.4.1 \
    crate://crates.io/hermit-abi/0.1.19 \
    crate://crates.io/indexmap/1.9.3 \
    crate://crates.io/instant/0.1.12 \
    crate://crates.io/itoa/1.0.6 \
    crate://crates.io/lazy_static/1.4.0 \
    crate://crates.io/libc/0.2.144 \
    crate://crates.io/lock_api/0.4.9 \
    crate://crates.io/log/0.4.17 \
    crate://crates.io/os_str_bytes/6.5.0 \
    crate://crates.io/parking_lot/0.11.2 \
    crate://crates.io/parking_lot_core/0.8.6 \
    crate://crates.io/proc-macro2/1.0.58 \
    crate://crates.io/quote/1.0.27 \
    crate://crates.io/redox_syscall/0.2.16 \
    crate://crates.io/remove_dir_all/0.5.3 \
    crate://crates.io/ryu/1.0.13 \
    crate://crates.io/scopeguard/1.1.0 \
    crate://crates.io/serde/1.0.163 \
    crate://crates.io/serde_derive/1.0.163 \
    crate://crates.io/serde_json/1.0.96 \
    crate://crates.io/serial_test/0.5.1 \
    crate://crates.io/serial_test_derive/0.5.1 \
    crate://crates.io/smallvec/1.10.0 \
    crate://crates.io/strsim/0.10.0 \
    crate://crates.io/syn/1.0.109 \
    crate://crates.io/syn/2.0.16 \
    crate://crates.io/tempfile/3.3.0 \
    crate://crates.io/termcolor/1.2.0 \
    crate://crates.io/textwrap/0.16.0 \
    crate://crates.io/toml/0.5.11 \
    crate://crates.io/unicode-ident/1.0.8 \
    crate://crates.io/winapi-i686-pc-windows-gnu/0.4.0 \
    crate://crates.io/winapi-util/0.1.5 \
    crate://crates.io/winapi-x86_64-pc-windows-gnu/0.4.0 \
    crate://crates.io/winapi/0.3.9 \
"

LIC_FILES_CHKSUM = " \
    file://LICENSE;md5=9741c346eef56131163e13b9db1241b3 \
"

inherit cargo
BBCLASSEXTEND = "native"
