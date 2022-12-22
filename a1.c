#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fks[5];

void *PHIL(void *arg) {
  int PHIL_NO = *((int *)arg)+1;

  int l = PHIL_NO;
  int r = (PHIL_NO + 1) % 5;

  while (1) {
    printf("Philosopher %d is thinking\n", PHIL_NO);
    sleep(1);
    if (fks[l] == 1) {}
    fks[l] = 1;
    printf("Philosopher %d picked up left fork\n", PHIL_NO);
    if (fks[r] == 1) {}
    fks[r] = 1;
    printf("Philosopher %d picked up right fork and starts eating\n", PHIL_NO);
    sleep(1);
    fks[l] = 0;
    fks[r] = 0;
  }
  return NULL;
}

int main(void) {
  int i=0;
  while(i<5) {
    fks[i] = 0;
    i++;
  }

  pthread_t PHIL_ARR[5];
  int PHIL_NO_ARR[5];

  int j=0;
  while(j<5) {
    PHIL_NO_ARR[j] = j;
    pthread_create(&PHIL_ARR[j], NULL, PHIL, &PHIL_NO_ARR[j]);
    j++;
  }

  int k=0;
  while(k<5) {
    pthread_join(PHIL_ARR[k], NULL);
    k++;
  }

  return 0;
}