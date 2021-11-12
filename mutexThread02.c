/* The program examples the mutex lock and unlock 
 * where Thread1 and Thread2 trying to access counter variable
 * this is to demonstrate the race condition
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *mutexfunc();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute mutexfunc */

   if( (rc1=pthread_create( &thread1, NULL, &mutexfunc, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (rc2=pthread_create( &thread2, NULL, &mutexfunc, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   exit(0);

   return 0;
}

void *mutexfunc()
{
   pthread_mutex_lock( &mutex1 );
   counter++;
   printf("Counter value: %d\n",counter);
   pthread_mutex_unlock( &mutex1 );
}

