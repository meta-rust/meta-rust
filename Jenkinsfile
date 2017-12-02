def targets = [ 'qemux86', 'qemux86-64', 'qemuarm', 'qemuarm64', 'qemumips' ]

def machine_builds = [:]

for (int i = 0; i < targets.size(); i++) {
    def machine = targets.get(i)

    machine_builds["$machine"] = {
        node {
            try {
                stage("checkout $machine") {
                    checkout scm
                }
                stage("setup-env $machine") {
                    sh "./scripts/setup-env.sh"
                }
                stage("fetch $machine") {
                    sh "GIT_LOCAL_REF_DIR=/srv/git-cache/ ./scripts/fetch.sh master"
                }
                stage("build $machine") {
                    sh "MACHINE=${machine} ./scripts/build.sh"
                }
            } catch (e) {
                echo "Caught: ${e}"
                throw e
            } finally {
                stage("push build cache $machine") {
                    sh "./scripts/publish-build-cache.sh master"
                }
                stage("cleanup $machine") {
                    sh "./scripts/cleanup-env.sh"
                    deleteDir()
                }
            }
        }
    }
}

parallel machine_builds
