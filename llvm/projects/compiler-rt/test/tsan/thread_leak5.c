// RUN: %clang_tsan -O1 %s -o %t && %deflake %run %t | FileCheck %s
#include <pthread.h>
#include <unistd.h>

void *Thread(void *x) {
  return 0;
}

int main() {
  volatile int N = 5;  // prevent loop unrolling
  for (int i = 0; i < N; i++) {
    pthread_t t;
    pthread_create(&t, 0, Thread, 0);
  }
  sleep(1);
  return 0;
}

// CHECK: WARNING: ThreadSanitizer: thread leak
// CHECK:   And 4 more similar thread leaks
