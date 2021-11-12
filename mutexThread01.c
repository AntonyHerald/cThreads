#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//global value
#define numloops 50000000
int sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * countThread(void *arg)
{
	int *offset = (int*) arg ;
	int value = *offset;
	printf(" offset value %d \n", *offset);
	for(int i = 0; i < numloops ; i++){

//Start of critical section
	pthread_mutex_lock(&mutex);
		sum += value ;
	pthread_mutex_unlock(&mutex);
//End of critical section
	}
	pthread_exit(NULL);
}

int main() 
{
	//spwan all threads 
	pthread_t id1;
	int offset1 = 1;
	pthread_create(&id1,NULL,countThread,&offset1);

	pthread_t id2;
	int offset2 = -1;
	pthread_create(&id2,NULL,countThread,&offset2);

	//wait for all the threads to complete...
	pthread_join(id1, NULL);
	pthread_join(id1, NULL);

	pthread_mutex_destory(&mutex);

	printf("\nThe Sum value = %d\n\n",sum);
	return 0;
	
}
