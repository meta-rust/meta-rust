# check src/llvm-project/llvm/CMakeLists.txt for llvm version in use
#
LLVM_RELEASE = "11.0.1"
require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-llvm.inc

SRC_URI += "file://0001-nfc-Fix-missing-include.patch;striplevel=2" 