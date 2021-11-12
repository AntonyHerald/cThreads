#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//global value
#define loop 5
long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * threadFunc(void *arg)
{
 	
	long *limit_ptr = (long*) arg;
	long limit = *limit_ptr;

	for(int i=1; i<=loop;i++){
//start of critical section
	pthread_mutex_lock(&mutex);
		sum += limit;
	printf(" %d - Inside critical section value %ld \n", i, sum);
	pthread_mutex_unlock(&mutex);
//end of critical section
	}
	printf("-----------------\n");
	pthread_exit(0);	
}

int main(int argc, char **argv)
{
	if(argc < 2 ){
	  printf("Usage: %s <num> \n", argv[0]);
  	  exit(1);
	}
	long limit = atoll(argv[1]);  //asci to long long
	int err, i;
	pthread_t tid[limit];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//When thread is created, thread function is invoked
	for(i = 1 ;i<= limit;i++){
	        //    pthread_create(threadID, threadAttribute, threadfunc, funcParameter)
		err = pthread_create(&tid[i], &attr, threadFunc, &i);
		if(err != 0){
			printf("can’t create thread");
		}
		//pthread_join(tid[i], NULL); 
	}

#if 1
	for(i = 1;i<=limit;i++){
		pthread_join(tid[i], NULL); 
	}
#endif
	pthread_mutex_destory(&mutex);
	printf("The Global Value of data added from all the Threads = %ld \n", sum);

exit(0);
}
