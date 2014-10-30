#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

sem_t *chopstick[2];
sem_t * returnVal;


int seats;
int position;
int cycles=0;

void wait(){

}

void sig(){

}

void eat(){
 printf("Philosopher %d is eating\n",position);
 sleep(rand()%3);
}

void think(){
 printf("Philosopher %d is thinking\n",position);
 sleep(rand()%3);
}

void handler(){
 printf("Philosopher #%d completed %d cycles\n",position,cycles);
 exit(0);
}

int main(int argc, char *argv[]){
 int i;
 if(argc>2){
  position=atoi(argv[2]);
  seats=atoi(argv[1]);
  char *semStr1[4];
  char *semStr2[4];
  semStr1={'/','c',argv[2],'\0'};
  semStr2={'/','c',argv[2],'\0'};
  if(position==1){
   semStr1={'/','c',argv[2],'\0'};
   returnVal = sem_open("/chop1", O_CREAT|O_EXCL, 0666, 1);
  }
  printf()
//  returnVal = sem_open("/chop1", O_CREAT|O_EXCL, 0666, 1);
  
  signal(15,handler);
  printf("PID:%d\n",getpid());
  do{
   wait();
   eat();
   sig();
   think();
   cycles++;
  }while(1);
 }else{
  printf("incorrect usage: Not enough parameters\n");
 }
 return 0;

}

