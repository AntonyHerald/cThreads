#include <stdio.h>
#include <pthread.h>

#define TOTALTHREADS 10


void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   pthread_t thread_id[TOTALTHREADS];
   int i, j;

   for(i=0; i < TOTALTHREADS; i++)
   {
      pthread_create( &thread_id[i], NULL, thread_function, NULL );
   }

   for(j=0; j < TOTALTHREADS; j++)
   {
      pthread_join( thread_id[j], NULL);
   }

   /* Now that all threads are complete I can print the final result.     */
   /* Without the join I could be printing a value before all the threads */
   /* have been completed.                                                */

   printf("Final counter value: %d\n", counter);

   return 0;
}

void *thread_function(void *dummyPtr)
{
   printf("%d - Thread number %ld\n",++counter, pthread_self());
   pthread_mutex_lock( &mutex1 );
   //counter++;
   pthread_mutex_unlock( &mutex1 );
}

