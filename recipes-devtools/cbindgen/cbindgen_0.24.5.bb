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

SRC_URI[cbindgen-0.24.5.sha256sum] = "4b922faaf31122819ec80c4047cc684c6979a087366c069611e33649bf98e18d"
SRC_URI[atty-0.2.14.sha256sum] = "d9b39be18770d11421cdb1b9947a45dd3f37e93092cbf377614828a319d5fee8"
SRC_URI[autocfg-1.1.0.sha256sum] = "d468802bab17cbc0cc575e9b053f41e72aa36bfa6b7f55e3529ffa43161b97fa"
SRC_URI[bitflags-1.3.2.sha256sum] = "bef38d45163c2f1dde094a7dfd33ccf595c92905c8f8f4fdc18d06fb1037718a"
SRC_URI[cfg-if-1.0.0.sha256sum] = "baf1de4339761588bc0619e3cbc0120ee582ebb74b53b4efbf79117bd2da40fd"
SRC_URI[clap-3.2.25.sha256sum] = "4ea181bf566f71cb9a5d17a59e1871af638180a18fb0035c92ae62b705207123"
SRC_URI[clap_lex-0.2.4.sha256sum] = "2850f2f5a82cbf437dd5af4d49848fbdfc27c157c3d010345776f952765261c5"
SRC_URI[fastrand-1.9.0.sha256sum] = "e51093e27b0797c359783294ca4f0a911c270184cb10f85783b118614a1501be"
SRC_URI[hashbrown-0.12.3.sha256sum] = "8a9ee70c43aaf417c914396645a0fa852624801b24ebb7ae78fe8272889ac888"
SRC_URI[heck-0.4.1.sha256sum] = "95505c38b4572b2d910cecb0281560f54b440a19336cbbcb27bf6ce6adc6f5a8"
SRC_URI[hermit-abi-0.1.19.sha256sum] = "62b467343b94ba476dcb2500d242dadbb39557df889310ac77c5d99100aaac33"
SRC_URI[indexmap-1.9.3.sha256sum] = "bd070e393353796e801d209ad339e89596eb4c8d430d18ede6a1cced8fafbd99"
SRC_URI[instant-0.1.12.sha256sum] = "7a5bbe824c507c5da5956355e86a746d82e0e1464f65d862cc5e71da70e94b2c"
SRC_URI[itoa-1.0.6.sha256sum] = "453ad9f582a441959e5f0d088b02ce04cfe8d51a8eaf077f12ac6d3e94164ca6"
SRC_URI[lazy_static-1.4.0.sha256sum] = "e2abad23fbc42b3700f2f279844dc832adb2b2eb069b2df918f455c4e18cc646"
SRC_URI[libc-0.2.144.sha256sum] = "2b00cc1c228a6782d0f076e7b232802e0c5689d41bb5df366f2a6b6621cfdfe1"
SRC_URI[lock_api-0.4.9.sha256sum] = "435011366fe56583b16cf956f9df0095b405b82d76425bc8981c0e22e60ec4df"
SRC_URI[log-0.4.17.sha256sum] = "abb12e687cfb44aa40f41fc3978ef76448f9b6038cad6aef4259d3c095a2382e"
SRC_URI[os_str_bytes-6.5.0.sha256sum] = "ceedf44fb00f2d1984b0bc98102627ce622e083e49a5bacdb3e514fa4238e267"
SRC_URI[parking_lot-0.11.2.sha256sum] = "7d17b78036a60663b797adeaee46f5c9dfebb86948d1255007a1d6be0271ff99"
SRC_URI[parking_lot_core-0.8.6.sha256sum] = "60a2cfe6f0ad2bfc16aefa463b497d5c7a5ecd44a23efa72aa342d90177356dc"
SRC_URI[proc-macro2-1.0.58.sha256sum] = "fa1fb82fc0c281dd9671101b66b771ebbe1eaf967b96ac8740dcba4b70005ca8"
SRC_URI[quote-1.0.27.sha256sum] = "8f4f29d145265ec1c483c7c654450edde0bfe043d3938d6972630663356d9500"
SRC_URI[redox_syscall-0.2.16.sha256sum] = "fb5a58c1855b4b6819d59012155603f0b22ad30cad752600aadfcb695265519a"
SRC_URI[remove_dir_all-0.5.3.sha256sum] = "3acd125665422973a33ac9d3dd2df85edad0f4ae9b00dafb1a05e43a9f5ef8e7"
SRC_URI[ryu-1.0.13.sha256sum] = "f91339c0467de62360649f8d3e185ca8de4224ff281f66000de5eb2a77a79041"
SRC_URI[scopeguard-1.1.0.sha256sum] = "d29ab0c6d3fc0ee92fe66e2d99f700eab17a8d57d1c1d3b748380fb20baa78cd"
SRC_URI[serde-1.0.163.sha256sum] = "2113ab51b87a539ae008b5c6c02dc020ffa39afd2d83cffcb3f4eb2722cebec2"
SRC_URI[serde_derive-1.0.163.sha256sum] = "8c805777e3930c8883389c602315a24224bcc738b63905ef87cd1420353ea93e"
SRC_URI[serde_json-1.0.96.sha256sum] = "057d394a50403bcac12672b2b18fb387ab6d289d957dab67dd201875391e52f1"
SRC_URI[serial_test-0.5.1.sha256sum] = "e0bccbcf40c8938196944a3da0e133e031a33f4d6b72db3bda3cc556e361905d"
SRC_URI[serial_test_derive-0.5.1.sha256sum] = "b2acd6defeddb41eb60bb468f8825d0cfd0c2a76bc03bfd235b6a1dc4f6a1ad5"
SRC_URI[smallvec-1.10.0.sha256sum] = "a507befe795404456341dfab10cef66ead4c041f62b8b11bbb92bffe5d0953e0"
SRC_URI[strsim-0.10.0.sha256sum] = "73473c0e59e6d5812c5dfe2a064a6444949f089e20eec9a2e5506596494e4623"
SRC_URI[syn-1.0.109.sha256sum] = "72b64191b275b66ffe2469e8af2c1cfe3bafa67b529ead792a6d0160888b4237"
SRC_URI[syn-2.0.16.sha256sum] = "a6f671d4b5ffdb8eadec19c0ae67fe2639df8684bd7bc4b83d986b8db549cf01"
SRC_URI[tempfile-3.3.0.sha256sum] = "5cdb1ef4eaeeaddc8fbd371e5017057064af0911902ef36b39801f67cc6d79e4"
SRC_URI[termcolor-1.2.0.sha256sum] = "be55cf8942feac5c765c2c993422806843c9a9a45d4d5c407ad6dd2ea95eb9b6"
SRC_URI[textwrap-0.16.0.sha256sum] = "222a222a5bfe1bba4a77b45ec488a741b3cb8872e5e499451fd7d0129c9c7c3d"
SRC_URI[toml-0.5.11.sha256sum] = "f4f7f0dd8d50a853a531c426359045b1998f04219d88799810762cd4ad314234"
SRC_URI[unicode-ident-1.0.8.sha256sum] = "e5464a87b239f13a63a501f2701565754bae92d243d4bb7eb12f6d57d2269bf4"
SRC_URI[winapi-i686-pc-windows-gnu-0.4.0.sha256sum] = "ac3b87c63620426dd9b991e5ce0329eff545bccbbb34f3be09ff6fb6ab51b7b6"
SRC_URI[winapi-util-0.1.5.sha256sum] = "70ec6ce85bb158151cae5e5c87f95a8e97d2c0c4b001223f33a334e3ce5de178"
SRC_URI[winapi-x86_64-pc-windows-gnu-0.4.0.sha256sum] = "712e227841d057c1ee1cd2fb22fa7e5a5461ae8e48fa2ca79ec42cfc1931183f"
SRC_URI[winapi-0.3.9.sha256sum] = "5c839a674fcd7a98952e593242ea400abe93992746761e38641405d28b00f419"

LIC_FILES_CHKSUM = " \
    file://LICENSE;md5=9741c346eef56131163e13b9db1241b3 \
"

inherit cargo
BBCLASSEXTEND = "native"
