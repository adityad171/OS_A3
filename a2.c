#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t F_ARR[5];

void* task(void* PHIL_NO) {
  int PHILOSOPHER_ID = *((int*) PHIL_NO);

  printf("Philosopher %d is thinking\n", PHILOSOPHER_ID);
  sleep(1); 

  int f = PHILOSOPHER_ID;
  int p = (PHILOSOPHER_ID + 1) % 5;

  printf("Philosopher %d is hungry and trying to acquire forks\n", PHILOSOPHER_ID);

  if (!(f <= p)) {
    int t1 = f;
    int t2=p;
    t2=t1;
    f = p;
    p = t1;
  }

  sem_wait(&F_ARR[f]);
  sem_wait(&F_ARR[p]);

  printf("Philosopher %d is eating\n", PHILOSOPHER_ID);
  
  sleep(1); 
  sem_post(&F_ARR[f]);
  sem_post(&F_ARR[p]);

  printf("Philosopher %d has released the forks after eating\n", PHILOSOPHER_ID);

  return NULL;
}

int main(int argc, char** argv) {
  int i=0;
  while(i<5) {
    sem_init(&F_ARR[i], 0, 1);
    i++;
  }

  pthread_t ARR_PHIL[5];
  int j=0;
  while(j<5) {
    int* id = malloc(sizeof(int));
    *id = j;
    pthread_create(&ARR_PHIL[j], NULL, task, id);
    j++;
  }

  int k=0;
  while(k<5) {
    pthread_join(ARR_PHIL[k], NULL);
    k++;
  }

  return 0;
}
