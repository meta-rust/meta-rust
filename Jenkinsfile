node {
    stage('Checkout') {
        checkout scm
    }
    stage('Yocto Fetch') {
        sh './scripts/fetch.sh master'
    }
    stage('Build') {
        sh './scripts/build.sh'
    }
}
