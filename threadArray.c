/* Classic example of pthread_join
 * Basically pthread_join will wait till all the threads are complete
 * then finally exit from the main thread
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//This is a sequential use of pthread and join called

//global value
long sum = 0;
void * threadFunc(void *arg)
{
 	
	long *limit_ptr = (long*) arg;
	long limit = *limit_ptr;

	//for(long i = 0; i < limit; i++)
	//	sum += i;
	 
	sum = sum + *limit_ptr;
	printf(" Inside TheadFunction %ld == %ld \n", *limit_ptr, sum );
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

		//pthread_join will wait for each of the thread[i] to complete and then create phread[i+1]
		pthread_join(tid[i], NULL); //Note: this is sequential thread1 execute, wait till it finish 
		//Then thread2 starts, execute & finish
	}

	printf("The Global Value of data added from all the Threads = %ld \n", sum);
	sleep(5);

	exit(0);
}
