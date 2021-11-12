/* This program demonstrate condition variable between 2 threads
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT_DONE  10
#define COUNT_HALT1  3
#define COUNT_HALT2  6

/*pthread_mutex initialization*/
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

/* func prototype declaration*/
void *funcCounter1();
void *funcCounter2();
int  count = 0;


int main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &funcCounter1, NULL);
   pthread_create( &thread2, NULL, &funcCounter2, NULL);
   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   exit(0);

   return 0;
}

void *funcCounter1()
{
   for(;;)
   {
      pthread_mutex_lock( &condition_mutex );
      while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
      {
         pthread_cond_wait( &condition_cond, &condition_mutex );
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      count++;
      printf("Counter value funcCounter1: %d\n",count);
      pthread_mutex_unlock( &count_mutex );

      if(count >= COUNT_DONE) return(NULL);
    }
}

void *funcCounter2()
{
    for(;;)
    {
       pthread_mutex_lock( &condition_mutex );
       if( count < COUNT_HALT1 || count > COUNT_HALT2 )
       {
          pthread_cond_signal( &condition_cond );
       }
       pthread_mutex_unlock( &condition_mutex );

       pthread_mutex_lock( &count_mutex );
       count++;
       printf("Counter value funcCounter2: %d\n",count);
       pthread_mutex_unlock( &count_mutex );

       if(count >= COUNT_DONE) return(NULL);
    }
}

