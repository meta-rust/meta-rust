def targets = [ 'qemux86', 'qemux86-64', 'qemuarm', 'qemuarm64' ]

def machine_builds = [:]

for (int i = 0; i < targets.size(); i++) {
    def machine = targets.get(i)

    machine_builds["$machine"] = {
        node {
            try {
                stage('Checkout') {
                    checkout scm
                }
                stage('Setup Environment') {
                    sh "./scripts/setup-env.sh"
                }
                stage('Yocto Fetch') {
                    sh "GIT_LOCAL_REF_DIR=/srv/git-cache/ ./scripts/fetch.sh master"
                }
                stage('Build') {
                    sh "MACHINE=${machine} ./scripts/build.sh"
                }
            } catch (e) {
                echo "Caught: ${e}"
                throw e
            } finally {
                stage('Cleanup Environment') {
                    sh "./scripts/cleanup-env.sh"
                    deleteDir()
                }
            }
        }
    }
}

parallel machine_builds
