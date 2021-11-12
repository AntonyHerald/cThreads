/* A simple program to demonstrate using Posix thread
 * uses pthread_create to create number of threads
 *
 * build - gcc -pthread <filename.c>
 *
 * Note pthread is the library which is to be included while build
 *
 * Execution - [./a.out 10 (10 given at cmd argument to specify no. of threads to be created]
 */ 

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void printids(const char *s)
{
 pid_t processID;
 pthread_t threadID;
 processID = getpid();
 threadID  = pthread_self();
 printf("%s processID-%lu  threadID %lu-(0x%lx)\n", s, (unsigned long)processID, (unsigned long)threadID, (unsigned long)threadID);
}


void * threadFunc(void *arg)
{
   printids("threadFUNCTION:  ");
   return((void *)0);
}

int main(int argc, char **argv)
{

	if(argc < 2 ){
	  printf("Usage: %s <num> \n", argv[0]);
  	  exit(1);
	}

	/* attoll = convert a string to an integer */	
	long long limit = atoll(argv[1]);  //asci to long long
	int err, i;
	pthread_t tid[limit];
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);

	//When thread is created, thread function is invoked
	//    pthread_create(threadID, threadAttribute, threadfunc, funcParameter)
	for(i = 1; i<= limit;i++){
	  	err = pthread_create(&tid[i], &attr, threadFunc, &i);
        } 

	if(err != 0){
		printf("can’t create thread");
	}

	//calling the print IDs function here
	printids("main thread:    ");
	sleep(5);

exit(0);
}
