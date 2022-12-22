#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int left(int PERSON){
	return PERSON;
}

void bl_p1(int PERSON){
		printf("Philosopher %d has put down bowl 1",PERSON);
		printf("\n");
}

int rt(int PERSON){
	return (PERSON+1)%5;
}

#define num 10
void bl_p0(int PERSON){
		printf("Philosopher %d has put down bowl 0\n",PERSON);
}

void fk_g(int PERSON){

	printf("Philosopher %d has picked up fork %d\n",PERSON,rt(PERSON));
	printf("Philosopher %d has picked up fork %d\n",PERSON,left(PERSON));
	
}

void bl_g0(int PERSON){
	printf("Philosopher %d has picked up bowl 0\n",PERSON);
}

void fk_p(int PERSON){
	printf("Philosopher %d has put down fork %d\n",PERSON,left(PERSON));
	printf("Philosopher %d has put down fork %d\n",PERSON,rt(PERSON));
}

void bl_g1(int PERSON){
	printf("Philosopher %d has picked up bowl 1\n",PERSON);
}


void check(int PERSON){
	if(PERSON<=5){
		fk_g(PERSON);
		bl_g1(PERSON);
		sleep(1);
		bl_p1(PERSON);
		fk_p(PERSON);
	}
	else{

        fk_g(PERSON-num);
		bl_g0(PERSON-num);
		sleep(1);
		bl_p0(PERSON-num);
		fk_p(PERSON-num);
	}
}

void CONSUME(int PERSON){
	check(PERSON);
}

void* phil_sim(void* i){
	int PHILOSOPHER_NUMBER = *(int*)i;
	CONSUME(PHILOSOPHER_NUMBER);
}

int main(){
    int NUMBER1 = 0;
    int NUMBER2 = (num-7);
	
	pthread_t PHIL_ARR[5];
	printf("PROGRAM HAS STARTED\n");

    for(int k=0;k<5;k++){
    	int NUMBER3 = NUMBER2+num;
		pthread_create(&PHIL_ARR[NUMBER1],NULL,phil_sim,(void *)&NUMBER1);
		pthread_create(&PHIL_ARR[NUMBER2],NULL,phil_sim,(void *)&NUMBER3);

		pthread_join(PHIL_ARR[NUMBER1],NULL);
		pthread_join(PHIL_ARR[NUMBER2],NULL);

		NUMBER1++;
		NUMBER2+=1;
        NUMBER1=NUMBER1%5;
		NUMBER2=NUMBER2%5;
	}

	printf("DINNER FINISHED BY ALL W/O DEADLOCK");
    printf("\n");
}