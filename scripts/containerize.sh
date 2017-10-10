#!/bin/bash

# what container are we using to build this
CONTAINER="cardoe/yocto:pyro"

einfo() {
	echo "$*" >&2
}

die() {
    echo "$*" >&2
    exit 1
}

# Save the commands for future use
cmd=$@

# If no command was specified, just drop us into a shell if we're interactive
[ $# -eq 0 ] && tty -s && cmd="/bin/bash"

# user and group we are running as to ensure files created inside
# the container retain the same permissions
my_uid=$(id -u)
my_gid=$(id -g)

# Are we in an interactive terminal?
tty -s && termint=t

# Fetch the latest version of the container
einfo "*** Ensuring local container is up to date"
docker pull ${CONTAINER} > /dev/null || die "Failed to update docker container"

# Ensure we've got what we need for SSH_AUTH_SOCK
if [[ -n ${SSH_AUTH_SOCK} ]]; then
	SSH_AUTH_DIR=$(dirname $(readlink -f ${SSH_AUTH_SOCK}))
	SSH_AUTH_NAME=$(basename ${SSH_AUTH_SOCK})
fi

# Kick off Docker
einfo "*** Launching container ..."
exec docker run \
    --privileged \
    -e BUILD_UID=${my_uid} \
    -e BUILD_GID=${my_gid} \
    -e TEMPLATECONF=meta-rust/conf \
    -e MACHINE=${MACHINE:-qemux86-64} \
    ${SSH_AUTH_SOCK:+-e SSH_AUTH_SOCK="/tmp/ssh-agent/${SSH_AUTH_NAME}"} \
    -v ${HOME}/.ssh:/var/build/.ssh \
    -v "${PWD}":/var/build:rw \
    ${SSH_AUTH_SOCK:+-v "${SSH_AUTH_DIR}":/tmp/ssh-agent} \
    ${EXTRA_CONTAINER_ARGS} \
    -${termint}i --rm -- \
    ${CONTAINER} \
    ${cmd}
