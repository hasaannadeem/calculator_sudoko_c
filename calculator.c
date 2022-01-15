#include <pthread.h>
#include <stdio.h>
 #include <stdlib.h>

 #define NUM_THREADS

void *sum(void *threadid)
{
int a,b;

int *r=(int*)threadid;

int sum=r[0]+r[1];
printf("answer is %d = ",sum);

 }
void *mul(void *threadid)
{
int a,b;

int *r=(int*)threadid;

int mull=r[0]*r[1];
printf("answer is %d = ",mull);

 }

void *divide(void *threadid){
int a,b;

int *r=(int*)threadid;

int divide=r[0]/r[1];

printf("answer is %d = ",divide);

 }

 int main (int argc , char *argv[])
{
 pthread_t threads;
 int rc[2];
 int i;
 rc[0]=atoi(argv[1]);
 rc[1]=atoi(argv[2]);
 char *msg=argv[3];

if(msg[0] == 's'){

  i = pthread_create(&threads, NULL ,sum,( void *)rc);
}

if(msg[0] == 'm'){
 
  i = pthread_create(&threads, NULL ,mul,( void *)rc);
}

if(msg[0] == 'd'){
    
  i = pthread_create(&threads, NULL ,divide,( void *)rc);
}

if (i)
{
printf("ERROR; return code from pthread_create() is \n");
 exit(-1);
}

pthread_exit(0);
}
