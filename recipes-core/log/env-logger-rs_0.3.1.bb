DESCRIPTION = "An logging implementation for `log` which is configured via an environment variable"
DEPENDS = "regex-rs log-rs"

require log.inc

LIB_SRC = "${S}/env/src/lib.rs"
