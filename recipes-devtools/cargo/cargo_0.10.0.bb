require cargo-snapshot.inc
require cargo.inc

SRC_URI += " \
	https://github.com/rust-lang/cargo/archive/${PV}.tar.gz;name=cargo \
	file://cargo_index \
	file://0001-disable-cargo-snapshot-fetch.patch \
	file://0001-Add-option-for-version-in-library-file-name.patch \
	file://0002-package_id-don-t-hash-source_id.patch \
	file://0003-Allow-prebuilt-dependencies.patch \
	git://github.com/rust-lang/rust-installer.git;protocol=https;name=rust-installer;destsuffix=${BP}/src/rust-installer \
"
SRC_URI[cargo.md5sum] = "98ab2a422634d447152380898a974b08"
SRC_URI[cargo.sha256sum] = "1e73c038681fe308195427b71322a6350c65d3b8cbea199e45c7b672b4754e0e"

SRCREV_rust-installer = "c37d3747da75c280237dc2d6b925078e69555499"

S = "${WORKDIR}/${BP}"

LIC_FILES_CHKSUM ="\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
	file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"

## curl-rust
SRC_URI += "\
       git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
       file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.patch;patchdir=../curl-rust \
       file://curl-rust/0002-remove-per-triple-deps-on-openssl-sys.patch;patchdir=../curl-rust \
"

# 0.2.14  / -sys 0.1.29
SRCREV_curl-rust = "76172b3ebf958fcf0b10d400f19ee02486a80ee7"

SRCREV_FORMAT .= "_curl-rust"
EXTRA_OECARGO_PATHS += "${WORKDIR}/curl-rust"

## ssh2-rs
SRC_URI += "\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-libssh2-sys-avoid-explicitly-linking-in-openssl.patch;patchdir=../ssh2-rs \
"

# 0.2.11 / -sys 0.1.37
SRCREV_ssh2-rs = "ced77751cb780d0725a3411bd588c5a26ea79953"

SRCREV_FORMAT .= "_ssh2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/ssh2-rs"

## git2-rs
SRC_URI += "\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-libgit2-sys-avoid-blessed-triples.patch;patchdir=../git2-rs \
"

# 0.3.3 / -sys 0.3.8
SRCREV_git2-rs = "19b6873c1fad7dc93c9c2dac4cba339dacf16efa"

SRCREV_FORMAT .= "_git2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/git2-rs"

CREATE_LOCAL_CARGO_INDEX = "0"
do_cargo_local_registry () {
	pushd ${LOCAL_CARGO_INDEX_DIR}
	echo '{
	"dl": "file://${WORKDIR}/rustdeps",
	"api": "invalid"
}' > config.json
	git init
	git add .
	git commit -a -m "Local DL dir"
	popd

	# Create links to the "download" path where cargo wants to find crates
	for f in ${WORKDIR}/rustdeps/*/*/*.crate; do
		ln -sf $(basename $f) $(dirname $f)/download
	done
}
do_unpack[postfuncs] += "do_cargo_local_registry"

# Dependencies auto-generated using scripts/local-index

# regex 0.1.58
SRC_URI += "https://crates.io/api/v1/crates/regex/0.1.58/download;name=regex-0.1.58;downloadfilename=regex-0.1.58.crate;subdir=rustdeps/regex/0.1.58"
SRC_URI[regex-0.1.58.md5sum] = "b5ff67114a9b9e691b429be13ddbdaee"
SRC_URI[regex-0.1.58.sha256sum] = "3dd7659f81431206880b8e6eafae79bf060e646de2737125cc08c30f6ad1aebe"

# aho-corasick 0.5.1
SRC_URI += "https://crates.io/api/v1/crates/aho-corasick/0.5.1/download;name=aho-corasick-0.5.1;downloadfilename=aho-corasick-0.5.1.crate;subdir=rustdeps/aho-corasick/0.5.1"
SRC_URI[aho-corasick-0.5.1.md5sum] = "5450f901b5e7975251e1f3956734623f"
SRC_URI[aho-corasick-0.5.1.sha256sum] = "67077478f0a03952bed2e6786338d400d40c25e9836e08ad50af96607317fd03"

# fs2 0.2.3
SRC_URI += "https://crates.io/api/v1/crates/fs2/0.2.3/download;name=fs2-0.2.3;downloadfilename=fs2-0.2.3.crate;subdir=rustdeps/fs2/0.2.3"
SRC_URI[fs2-0.2.3.md5sum] = "ac00c7aafb4b34383cf4187a1f8729e0"
SRC_URI[fs2-0.2.3.sha256sum] = "a24f693fd93d04099962297dcdba0578b490d79ef26e0105204179520698bf91"

# crossbeam 0.2.8
SRC_URI += "https://crates.io/api/v1/crates/crossbeam/0.2.8/download;name=crossbeam-0.2.8;downloadfilename=crossbeam-0.2.8.crate;subdir=rustdeps/crossbeam/0.2.8"
SRC_URI[crossbeam-0.2.8.md5sum] = "0372195b9ea431a1bfd811ce9c1b590c"
SRC_URI[crossbeam-0.2.8.sha256sum] = "348228ce9f93d20ffc30c18e575f82fa41b9c8bf064806c65d41eba4771595a0"

# openssl-sys 0.7.8
SRC_URI += "https://crates.io/api/v1/crates/openssl-sys/0.7.8/download;name=openssl-sys-0.7.8;downloadfilename=openssl-sys-0.7.8.crate;subdir=rustdeps/openssl-sys/0.7.8"
SRC_URI[openssl-sys-0.7.8.md5sum] = "348f09038bded658b3b9fac085c89ee4"
SRC_URI[openssl-sys-0.7.8.sha256sum] = "065e99c2dca7abfe305bd8254d221952b46d47ea9a1c85b6d674c38f083765e6"

# winapi-build 0.1.1
SRC_URI += "https://crates.io/api/v1/crates/winapi-build/0.1.1/download;name=winapi-build-0.1.1;downloadfilename=winapi-build-0.1.1.crate;subdir=rustdeps/winapi-build/0.1.1"
SRC_URI[winapi-build-0.1.1.md5sum] = "c900e7dbce808ff8ced375077b17a163"
SRC_URI[winapi-build-0.1.1.sha256sum] = "2d315eee3b34aca4797b2da6b13ed88266e6d612562a0c46390af8299fc699bc"

# semver 0.2.3
SRC_URI += "https://crates.io/api/v1/crates/semver/0.2.3/download;name=semver-0.2.3;downloadfilename=semver-0.2.3.crate;subdir=rustdeps/semver/0.2.3"
SRC_URI[semver-0.2.3.md5sum] = "037152747ebc4f7551849e3c42bb0d05"
SRC_URI[semver-0.2.3.sha256sum] = "2d5b7638a1f03815d94e88cb3b3c08e87f0db4d683ef499d1836aaf70a45623f"

# memchr 0.1.10
SRC_URI += "https://crates.io/api/v1/crates/memchr/0.1.10/download;name=memchr-0.1.10;downloadfilename=memchr-0.1.10.crate;subdir=rustdeps/memchr/0.1.10"
SRC_URI[memchr-0.1.10.md5sum] = "d8f5033d0182a51e9ffa89869b8e2d14"
SRC_URI[memchr-0.1.10.sha256sum] = "c98adb597263e245c6ffe48dc50d338b51acb8cc53e8e7b3e9c21f53c0a411cb"

# regex-syntax 0.3.0
SRC_URI += "https://crates.io/api/v1/crates/regex-syntax/0.3.0/download;name=regex-syntax-0.3.0;downloadfilename=regex-syntax-0.3.0.crate;subdir=rustdeps/regex-syntax/0.3.0"
SRC_URI[regex-syntax-0.3.0.md5sum] = "9d27079c6ff2fe0d9da488b0e05197e9"
SRC_URI[regex-syntax-0.3.0.sha256sum] = "91f025592c64aca084b1eb1f556fcac9c016da96a66dbebd5f9a7bda6f92b540"

# libc 0.2.8
SRC_URI += "https://crates.io/api/v1/crates/libc/0.2.8/download;name=libc-0.2.8;downloadfilename=libc-0.2.8.crate;subdir=rustdeps/libc/0.2.8"
SRC_URI[libc-0.2.8.md5sum] = "74f1af9a2596c069bd7b5c1eab6445e7"
SRC_URI[libc-0.2.8.sha256sum] = "52f45f4d4d75de96cf7f8b0e37b6a8e2f96619749b80bd79aa9f5a3100d63208"

# hamcrest 0.1.0
SRC_URI += "https://crates.io/api/v1/crates/hamcrest/0.1.0/download;name=hamcrest-0.1.0;downloadfilename=hamcrest-0.1.0.crate;subdir=rustdeps/hamcrest/0.1.0"
SRC_URI[hamcrest-0.1.0.md5sum] = "03b0666861c40cb18f05e28661968833"
SRC_URI[hamcrest-0.1.0.sha256sum] = "27c180b409b988760a018e5cb5f0812bd67e87f40236e41d3b9375d3046e04ab"

# tar 0.4.4
SRC_URI += "https://crates.io/api/v1/crates/tar/0.4.4/download;name=tar-0.4.4;downloadfilename=tar-0.4.4.crate;subdir=rustdeps/tar/0.4.4"
SRC_URI[tar-0.4.4.md5sum] = "680011a51bd6b097f5a0c046effe705d"
SRC_URI[tar-0.4.4.sha256sum] = "c82692d9a0e663b8c8f942eab088901d80cb7365f360967562f237148d1792d3"

# url 0.2.38
SRC_URI += "https://crates.io/api/v1/crates/url/0.2.38/download;name=url-0.2.38;downloadfilename=url-0.2.38.crate;subdir=rustdeps/url/0.2.38"
SRC_URI[url-0.2.38.md5sum] = "572e2aba28b55c17bd722a2cb046e8a5"
SRC_URI[url-0.2.38.sha256sum] = "cbaa8377a162d88e7d15db0cf110c8523453edcbc5bc66d2b6fffccffa34a068"

# winapi 0.2.6
SRC_URI += "https://crates.io/api/v1/crates/winapi/0.2.6/download;name=winapi-0.2.6;downloadfilename=winapi-0.2.6.crate;subdir=rustdeps/winapi/0.2.6"
SRC_URI[winapi-0.2.6.md5sum] = "f2a03cd177d095193bbd5d442311b963"
SRC_URI[winapi-0.2.6.sha256sum] = "4dfaaa8fbdaa618fa6914b59b2769d690dd7521920a18d84b42d254678dd5fd4"

# bufstream 0.1.1
SRC_URI += "https://crates.io/api/v1/crates/bufstream/0.1.1/download;name=bufstream-0.1.1;downloadfilename=bufstream-0.1.1.crate;subdir=rustdeps/bufstream/0.1.1"
SRC_URI[bufstream-0.1.1.md5sum] = "6df894963ea494da7edb3bff48eec3a7"
SRC_URI[bufstream-0.1.1.sha256sum] = "7e493de6a8aed51697088e36dc5245ea3edd34e6872e32c732e5f996ed5b23b2"

# num_cpus 0.2.11
SRC_URI += "https://crates.io/api/v1/crates/num_cpus/0.2.11/download;name=num_cpus-0.2.11;downloadfilename=num_cpus-0.2.11.crate;subdir=rustdeps/num_cpus/0.2.11"
SRC_URI[num_cpus-0.2.11.md5sum] = "21be8f32c97bd7a2eb974ce3d7310731"
SRC_URI[num_cpus-0.2.11.sha256sum] = "51fedae97a05f7353612fe017ab705a37e6db8f4d67c5c6fe739a9e70d6eed09"

# num 0.1.31
SRC_URI += "https://crates.io/api/v1/crates/num/0.1.31/download;name=num-0.1.31;downloadfilename=num-0.1.31.crate;subdir=rustdeps/num/0.1.31"
SRC_URI[num-0.1.31.md5sum] = "1ce79be4db6b467e9ae78935c0c43601"
SRC_URI[num-0.1.31.sha256sum] = "be45b3e341522564415a07118d7cf44896d0919e7a1bb21d59ad82af48256324"

# glob 0.2.11
SRC_URI += "https://crates.io/api/v1/crates/glob/0.2.11/download;name=glob-0.2.11;downloadfilename=glob-0.2.11.crate;subdir=rustdeps/glob/0.2.11"
SRC_URI[glob-0.2.11.md5sum] = "f8ece52bd2dc2019f8ccc8401d259ecf"
SRC_URI[glob-0.2.11.sha256sum] = "8be18de09a56b60ed0edf84bc9df007e30040691af7acd1c41874faac5895bfb"

# curl 0.2.18
SRC_URI += "https://crates.io/api/v1/crates/curl/0.2.18/download;name=curl-0.2.18;downloadfilename=curl-0.2.18.crate;subdir=rustdeps/curl/0.2.18"
SRC_URI[curl-0.2.18.md5sum] = "18badeae4a13d6d85b1894e6a9fc0dfb"
SRC_URI[curl-0.2.18.sha256sum] = "2a48b72c66a1b8fc6767fe4f3cda7d6b9bdfab8f3f168344b830eddbbe8e2da0"

# strsim 0.3.0
SRC_URI += "https://crates.io/api/v1/crates/strsim/0.3.0/download;name=strsim-0.3.0;downloadfilename=strsim-0.3.0.crate;subdir=rustdeps/strsim/0.3.0"
SRC_URI[strsim-0.3.0.md5sum] = "47846ace61d09ab9eff9c053c532e8cc"
SRC_URI[strsim-0.3.0.sha256sum] = "e4d73a2c36a4d095ed1a6df5cbeac159863173447f7a82b3f4757426844ab825"

# unicode-normalization 0.1.2
SRC_URI += "https://crates.io/api/v1/crates/unicode-normalization/0.1.2/download;name=unicode-normalization-0.1.2;downloadfilename=unicode-normalization-0.1.2.crate;subdir=rustdeps/unicode-normalization/0.1.2"
SRC_URI[unicode-normalization-0.1.2.md5sum] = "45370fb077eb80579aa57c95c1b72c7c"
SRC_URI[unicode-normalization-0.1.2.sha256sum] = "26643a2f83bac55f1976fb716c10234485f9202dcd65cfbdf9da49867b271172"

# docopt 0.6.78
SRC_URI += "https://crates.io/api/v1/crates/docopt/0.6.78/download;name=docopt-0.6.78;downloadfilename=docopt-0.6.78.crate;subdir=rustdeps/docopt/0.6.78"
SRC_URI[docopt-0.6.78.md5sum] = "fa7ba7b35506d5bc544f3ea839db8249"
SRC_URI[docopt-0.6.78.sha256sum] = "55792ca5bb933e55a3e17888838883f854b029945310c9a0ea4f65ebda366155"

# flate2 0.2.13
SRC_URI += "https://crates.io/api/v1/crates/flate2/0.2.13/download;name=flate2-0.2.13;downloadfilename=flate2-0.2.13.crate;subdir=rustdeps/flate2/0.2.13"
SRC_URI[flate2-0.2.13.md5sum] = "013f3949189f9d05c3e1913165834b8c"
SRC_URI[flate2-0.2.13.sha256sum] = "f9e6fc69e0509336ff58a2e5ab91c7a9629cb78bad26e67d8c4489f5a648addb"

# gcc 0.3.26
SRC_URI += "https://crates.io/api/v1/crates/gcc/0.3.26/download;name=gcc-0.3.26;downloadfilename=gcc-0.3.26.crate;subdir=rustdeps/gcc/0.3.26"
SRC_URI[gcc-0.3.26.md5sum] = "c741260539130899d42d41ca857ad13b"
SRC_URI[gcc-0.3.26.sha256sum] = "3337bf4deec8dd33c331a62b59708f5b438779b8089b1888d56976ac2c325d3e"

# git2-curl 0.4.0
SRC_URI += "https://crates.io/api/v1/crates/git2-curl/0.4.0/download;name=git2-curl-0.4.0;downloadfilename=git2-curl-0.4.0.crate;subdir=rustdeps/git2-curl/0.4.0"
SRC_URI[git2-curl-0.4.0.md5sum] = "c1b9d87bbe34281aad4e8f6479bf669c"
SRC_URI[git2-curl-0.4.0.sha256sum] = "c13dafba61b79dc9fa45b40b0478a5196cab2b571a355128667fae951bb2d0cc"

# unicode-bidi 0.2.3
SRC_URI += "https://crates.io/api/v1/crates/unicode-bidi/0.2.3/download;name=unicode-bidi-0.2.3;downloadfilename=unicode-bidi-0.2.3.crate;subdir=rustdeps/unicode-bidi/0.2.3"
SRC_URI[unicode-bidi-0.2.3.md5sum] = "591fd7d34ad196a561fd284ce9715823"
SRC_URI[unicode-bidi-0.2.3.sha256sum] = "c1f7ceb96afdfeedee42bade65a0d585a6a0106f681b6749c8ff4daa8df30b3f"

# libssh2-sys 0.1.37
SRC_URI += "https://crates.io/api/v1/crates/libssh2-sys/0.1.37/download;name=libssh2-sys-0.1.37;downloadfilename=libssh2-sys-0.1.37.crate;subdir=rustdeps/libssh2-sys/0.1.37"
SRC_URI[libssh2-sys-0.1.37.md5sum] = "e1adb2fe15a547273ee89763e5f5d9f6"
SRC_URI[libssh2-sys-0.1.37.sha256sum] = "c45fba84ee1fa05b830cb471741ef30d41eb1c3b97160b8ad8d955af824de880"

# rand 0.3.14
SRC_URI += "https://crates.io/api/v1/crates/rand/0.3.14/download;name=rand-0.3.14;downloadfilename=rand-0.3.14.crate;subdir=rustdeps/rand/0.3.14"
SRC_URI[rand-0.3.14.md5sum] = "21b9a9164097d32101bed6b760b5e271"
SRC_URI[rand-0.3.14.sha256sum] = "2791d88c6defac799c3f20d74f094ca33b9332612d9aef9078519c82e4fe04a5"

# utf8-ranges 0.1.3
SRC_URI += "https://crates.io/api/v1/crates/utf8-ranges/0.1.3/download;name=utf8-ranges-0.1.3;downloadfilename=utf8-ranges-0.1.3.crate;subdir=rustdeps/utf8-ranges/0.1.3"
SRC_URI[utf8-ranges-0.1.3.md5sum] = "075bda329483078c4a57eb6988c6a31a"
SRC_URI[utf8-ranges-0.1.3.sha256sum] = "a1ca13c08c41c9c3e04224ed9ff80461d97e121589ff27c753a16cb10830ae0f"

# rustc-serialize 0.3.18
SRC_URI += "https://crates.io/api/v1/crates/rustc-serialize/0.3.18/download;name=rustc-serialize-0.3.18;downloadfilename=rustc-serialize-0.3.18.crate;subdir=rustdeps/rustc-serialize/0.3.18"
SRC_URI[rustc-serialize-0.3.18.md5sum] = "321396fa04f7302da1e30241f36af241"
SRC_URI[rustc-serialize-0.3.18.sha256sum] = "9cf81518cd579f8a9c58c0a71328bdb9be15c754181261da82583092dc8a7ff0"

# pnacl-build-helper 1.4.10
SRC_URI += "https://crates.io/api/v1/crates/pnacl-build-helper/1.4.10/download;name=pnacl-build-helper-1.4.10;downloadfilename=pnacl-build-helper-1.4.10.crate;subdir=rustdeps/pnacl-build-helper/1.4.10"
SRC_URI[pnacl-build-helper-1.4.10.md5sum] = "fe3ed81ac12fb4d0f7b9c6039a3541da"
SRC_URI[pnacl-build-helper-1.4.10.sha256sum] = "61c9231d31aea845007443d62fcbb58bb6949ab9c18081ee1e09920e0cf1118b"

# url 0.5.7
SRC_URI += "https://crates.io/api/v1/crates/url/0.5.7/download;name=url-0.5.7;downloadfilename=url-0.5.7.crate;subdir=rustdeps/url/0.5.7"
SRC_URI[url-0.5.7.md5sum] = "36c3ef06e64ac3216b502e463660d8c5"
SRC_URI[url-0.5.7.sha256sum] = "0cfad3f2f6c8bdeca794aba1a40f5b4b38ce4994844f5feb7466a0addbf5a36d"

# nom 1.2.2
SRC_URI += "https://crates.io/api/v1/crates/nom/1.2.2/download;name=nom-1.2.2;downloadfilename=nom-1.2.2.crate;subdir=rustdeps/nom/1.2.2"
SRC_URI[nom-1.2.2.md5sum] = "aa7fccb41b046c7c03f8510e69c05d37"
SRC_URI[nom-1.2.2.sha256sum] = "6caab12c5f97aa316cb249725aa32115118e1522b445e26c257dd77cad5ffd4e"

# git2 0.4.2
SRC_URI += "https://crates.io/api/v1/crates/git2/0.4.2/download;name=git2-0.4.2;downloadfilename=git2-0.4.2.crate;subdir=rustdeps/git2/0.4.2"
SRC_URI[git2-0.4.2.md5sum] = "d16ec260b79902281b11d414ad8b2c01"
SRC_URI[git2-0.4.2.sha256sum] = "1c663e06498eaced90ccd830ac23332b5b521b9a9ee82d095520b3394b5e9098"

# filetime 0.1.10
SRC_URI += "https://crates.io/api/v1/crates/filetime/0.1.10/download;name=filetime-0.1.10;downloadfilename=filetime-0.1.10.crate;subdir=rustdeps/filetime/0.1.10"
SRC_URI[filetime-0.1.10.md5sum] = "d5a18f1638809a9e3f53213727a6a78c"
SRC_URI[filetime-0.1.10.sha256sum] = "5363ab8e4139b8568a6237db5248646e5a8a2f89bd5ccb02092182b11fd3e922"

# user32-sys 0.1.2
SRC_URI += "https://crates.io/api/v1/crates/user32-sys/0.1.2/download;name=user32-sys-0.1.2;downloadfilename=user32-sys-0.1.2.crate;subdir=rustdeps/user32-sys/0.1.2"
SRC_URI[user32-sys-0.1.2.md5sum] = "d3b088b0b6a5d921dcb6d8f29b1bc09d"
SRC_URI[user32-sys-0.1.2.sha256sum] = "6717129de5ac253f5642fc78a51d0c7de6f9f53d617fc94e9bae7f6e71cf5504"

# uuid 0.1.18
SRC_URI += "https://crates.io/api/v1/crates/uuid/0.1.18/download;name=uuid-0.1.18;downloadfilename=uuid-0.1.18.crate;subdir=rustdeps/uuid/0.1.18"
SRC_URI[uuid-0.1.18.md5sum] = "56a9701ab1aa3374c8b6aa18cf9f6dfd"
SRC_URI[uuid-0.1.18.sha256sum] = "78c590b5bd79ed10aad8fb75f078a59d8db445af6c743e55c4a53227fc01c13f"

# libressl-pnacl-sys 2.1.6
SRC_URI += "https://crates.io/api/v1/crates/libressl-pnacl-sys/2.1.6/download;name=libressl-pnacl-sys-2.1.6;downloadfilename=libressl-pnacl-sys-2.1.6.crate;subdir=rustdeps/libressl-pnacl-sys/2.1.6"
SRC_URI[libressl-pnacl-sys-2.1.6.md5sum] = "71e498382e8e77f77b9325b4fb98c290"
SRC_URI[libressl-pnacl-sys-2.1.6.sha256sum] = "cbc058951ab6a3ef35ca16462d7642c4867e6403520811f28537a4e2f2db3e71"

# time 0.1.34
SRC_URI += "https://crates.io/api/v1/crates/time/0.1.34/download;name=time-0.1.34;downloadfilename=time-0.1.34.crate;subdir=rustdeps/time/0.1.34"
SRC_URI[time-0.1.34.md5sum] = "07d9398bfe2a8bbfdc7a500a00ba7fd2"
SRC_URI[time-0.1.34.sha256sum] = "8c4aeaa1c95974f5763c3a5ac0db95a19793589bcea5d22e161b5587e3aad029"

# miniz-sys 0.1.7
SRC_URI += "https://crates.io/api/v1/crates/miniz-sys/0.1.7/download;name=miniz-sys-0.1.7;downloadfilename=miniz-sys-0.1.7.crate;subdir=rustdeps/miniz-sys/0.1.7"
SRC_URI[miniz-sys-0.1.7.md5sum] = "deed7fc2e84ccd8f1734054b944240c9"
SRC_URI[miniz-sys-0.1.7.sha256sum] = "9d1f4d337a01c32e1f2122510fed46393d53ca35a7f429cb0450abaedfa3ed54"

# kernel32-sys 0.2.1
SRC_URI += "https://crates.io/api/v1/crates/kernel32-sys/0.2.1/download;name=kernel32-sys-0.2.1;downloadfilename=kernel32-sys-0.2.1.crate;subdir=rustdeps/kernel32-sys/0.2.1"
SRC_URI[kernel32-sys-0.2.1.md5sum] = "5ce985dca1b049f9cf218dee6be202bc"
SRC_URI[kernel32-sys-0.2.1.sha256sum] = "b5b5e7edf375e6d26243bde172f1d5ed1446f4a766fc9b7006e1fd27258243f1"

# curl-sys 0.1.34
SRC_URI += "https://crates.io/api/v1/crates/curl-sys/0.1.34/download;name=curl-sys-0.1.34;downloadfilename=curl-sys-0.1.34.crate;subdir=rustdeps/curl-sys/0.1.34"
SRC_URI[curl-sys-0.1.34.md5sum] = "0545b6890a1d85b6c81b9baac79021ab"
SRC_URI[curl-sys-0.1.34.sha256sum] = "93196668f75a947d849e1f2db9277223884ece3af169cbff3d36ceeeaf7736b0"

# cmake 0.1.16
SRC_URI += "https://crates.io/api/v1/crates/cmake/0.1.16/download;name=cmake-0.1.16;downloadfilename=cmake-0.1.16.crate;subdir=rustdeps/cmake/0.1.16"
SRC_URI[cmake-0.1.16.md5sum] = "02acdc1c2ff0ed57ba714efbe23072ba"
SRC_URI[cmake-0.1.16.sha256sum] = "eb61a8d3b65f8e0af52ac579923ec48bdd5ca4e335c0fde4071e5860eb650532"

# env_logger 0.3.2
SRC_URI += "https://crates.io/api/v1/crates/env_logger/0.3.2/download;name=env_logger-0.3.2;downloadfilename=env_logger-0.3.2.crate;subdir=rustdeps/env_logger/0.3.2"
SRC_URI[env_logger-0.3.2.md5sum] = "ad2c627cef4fbc89edc4561ebbaa66ea"
SRC_URI[env_logger-0.3.2.sha256sum] = "b6bbe7c0b619c81b9a1fd122ab3c7ef19a7b27cdba3c8486314b6f275ca211a4"

# gdi32-sys 0.1.1
SRC_URI += "https://crates.io/api/v1/crates/gdi32-sys/0.1.1/download;name=gdi32-sys-0.1.1;downloadfilename=gdi32-sys-0.1.1.crate;subdir=rustdeps/gdi32-sys/0.1.1"
SRC_URI[gdi32-sys-0.1.1.md5sum] = "385917ddc452d2d1a594647c11c031c8"
SRC_URI[gdi32-sys-0.1.1.sha256sum] = "65256ec4dc2592e6f05bfc1ca3b956a4e0698aa90b1dff1f5687d55a5a3fd59a"

# libgit2-sys 0.4.2
SRC_URI += "https://crates.io/api/v1/crates/libgit2-sys/0.4.2/download;name=libgit2-sys-0.4.2;downloadfilename=libgit2-sys-0.4.2.crate;subdir=rustdeps/libgit2-sys/0.4.2"
SRC_URI[libgit2-sys-0.4.2.md5sum] = "cabfb2c7b46496567109a469ad810e61"
SRC_URI[libgit2-sys-0.4.2.sha256sum] = "71064054e4a63d5558793ec3a96c5e352eb39817b1f99afaaaa9f22a691cb538"

# toml 0.1.28
SRC_URI += "https://crates.io/api/v1/crates/toml/0.1.28/download;name=toml-0.1.28;downloadfilename=toml-0.1.28.crate;subdir=rustdeps/toml/0.1.28"
SRC_URI[toml-0.1.28.md5sum] = "6979385c1926de02b7abfd654f7331ce"
SRC_URI[toml-0.1.28.sha256sum] = "fcd27a04ca509aff336ba5eb2abc58d456f52c4ff64d9724d88acb85ead560b6"

# log 0.3.5
SRC_URI += "https://crates.io/api/v1/crates/log/0.3.5/download;name=log-0.3.5;downloadfilename=log-0.3.5.crate;subdir=rustdeps/log/0.3.5"
SRC_URI[log-0.3.5.md5sum] = "32285c84c5ef66735a93f4ed555b09df"
SRC_URI[log-0.3.5.sha256sum] = "038b5d13189a14e5b6ac384fdb7c691a45ef0885f6d2dddbf422e6c3506b8234"

# libz-sys 1.0.2
SRC_URI += "https://crates.io/api/v1/crates/libz-sys/1.0.2/download;name=libz-sys-1.0.2;downloadfilename=libz-sys-1.0.2.crate;subdir=rustdeps/libz-sys/1.0.2"
SRC_URI[libz-sys-1.0.2.md5sum] = "09346a9b7982f40fe691f1e50443310f"
SRC_URI[libz-sys-1.0.2.sha256sum] = "aa6b53f9806f503569bbf3c29b6f0e3fdc86e7eff36f0c9e55381fb400f8b4fd"

# pkg-config 0.3.8
SRC_URI += "https://crates.io/api/v1/crates/pkg-config/0.3.8/download;name=pkg-config-0.3.8;downloadfilename=pkg-config-0.3.8.crate;subdir=rustdeps/pkg-config/0.3.8"
SRC_URI[pkg-config-0.3.8.md5sum] = "19597f86c60fea3552b10c4fb6c29b20"
SRC_URI[pkg-config-0.3.8.sha256sum] = "8cee804ecc7eaf201a4a207241472cc870e825206f6c031e3ee2a72fa425f2fa"

# tempdir 0.3.4
SRC_URI += "https://crates.io/api/v1/crates/tempdir/0.3.4/download;name=tempdir-0.3.4;downloadfilename=tempdir-0.3.4.crate;subdir=rustdeps/tempdir/0.3.4"
SRC_URI[tempdir-0.3.4.md5sum] = "48b61b850bc6a16b7c4891a4a5c5e851"
SRC_URI[tempdir-0.3.4.sha256sum] = "0b62933a3f96cd559700662c34f8bab881d9e3540289fb4f368419c7f13a5aa9"

# matches 0.1.2
SRC_URI += "https://crates.io/api/v1/crates/matches/0.1.2/download;name=matches-0.1.2;downloadfilename=matches-0.1.2.crate;subdir=rustdeps/matches/0.1.2"
SRC_URI[matches-0.1.2.md5sum] = "bf2f0a1c90e9f0d5c5598741f6f3de82"
SRC_URI[matches-0.1.2.sha256sum] = "15305656809ce5a4805b1ff2946892810992197ce1270ff79baded852187942e"

# bitflags 0.1.1
SRC_URI += "https://crates.io/api/v1/crates/bitflags/0.1.1/download;name=bitflags-0.1.1;downloadfilename=bitflags-0.1.1.crate;subdir=rustdeps/bitflags/0.1.1"
SRC_URI[bitflags-0.1.1.md5sum] = "320450094f2db257ead028e9db89a490"
SRC_URI[bitflags-0.1.1.sha256sum] = "2a6577517ecd0ee0934f48a7295a89aaef3e6dfafeac404f94c0b3448518ddfe"

# term 0.4.4
SRC_URI += "https://crates.io/api/v1/crates/term/0.4.4/download;name=term-0.4.4;downloadfilename=term-0.4.4.crate;subdir=rustdeps/term/0.4.4"
SRC_URI[term-0.4.4.md5sum] = "15bc859be982b62fb9696731100e1d50"
SRC_URI[term-0.4.4.sha256sum] = "3deff8a2b3b6607d6d7cc32ac25c0b33709453ca9cceac006caac51e963cf94a"

# advapi32-sys 0.1.2
SRC_URI += "https://crates.io/api/v1/crates/advapi32-sys/0.1.2/download;name=advapi32-sys-0.1.2;downloadfilename=advapi32-sys-0.1.2.crate;subdir=rustdeps/advapi32-sys/0.1.2"
SRC_URI[advapi32-sys-0.1.2.md5sum] = "01413787f8a1a5d596af159e400fbb12"
SRC_URI[advapi32-sys-0.1.2.sha256sum] = "307c92332867e586720c0222ee9d890bbe8431711efed8a1b06bc5b40fc66bd7"
