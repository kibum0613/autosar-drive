// CI for the AEB SWC: build -> static analysis -> unit test -> back-to-back test
pipeline {
  agent any

  options {
    timestamps()
    buildDiscarder(logRotator(numToKeepStr: '20'))
  }

  triggers {
    // poll GitHub every 5 minutes (no public webhook needed for a local Jenkins)
    pollSCM('H/5 * * * *')
  }

  stages {
    stage('Checkout') {
      steps {
        checkout scm
        sh 'git log -1 --oneline'
      }
    }

    stage('Build') {
      steps {
        sh 'gcc --version | head -1'
        sh 'make clean all'
      }
    }

    stage('Static Analysis') {
      steps {
        sh 'make static'
      }
    }

    stage('Unit Test (SWC via RTE)') {
      steps {
        sh 'make test-unit'
      }
    }

    stage('Back-to-Back Test (ERT vs AUTOSAR)') {
      steps {
        sh 'make test-b2b'
      }
    }
  }

  post {
    always {
      junit testResults: 'reports/junit-*.xml', allowEmptyResults: true
      archiveArtifacts artifacts: 'build/libaeb_swc.a, reports/**, model_gen/autosar/arxml/*.arxml',
                       allowEmptyArchive: true, fingerprint: true
    }
  }
}
