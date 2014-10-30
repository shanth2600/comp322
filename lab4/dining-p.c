#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

sem_t *chop[2];
sem_t * returnVal;


int seats;
int position;
int cycles=0;
char semStr1[4];
char semStr2[4];

void wt(sem_t *sem){
 while(sem>0){}
 sem=0;
}

void sig(sem_t *sem){
 sem++;
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
 sem_close(chop[0]);
 sem_unlink(semStr1);
 sem_close(chop[1]);
 sem_unlink(semStr2);
 exit(0);
}


int main(int argc, char *argv[]){
 int i;
 char cnum1,cnum2;
 if(argc>2){
  position=atoi(argv[2]);
  seats=atoi(argv[1]);
  char *tmp;
  if(position==1){
   sprintf(tmp,"%d",seats);
   cnum1=tmp[0];
  }else{
   sprintf(tmp,"%d",position-1);
   cnum1=tmp[0];
  }
  cnum2=argv[2][0];
  char tmp1[]={'/','c',cnum1,'\0'};
  strcpy(semStr1,tmp1);
  char tmp2[]={'/','c',cnum2,'\0'};
  strcpy(semStr2,tmp2);
  printf("%s %s\n",semStr1,semStr2);
  chop[0]=sem_open(semStr1, O_CREAT, 0666, 1);
  chop[1]=sem_open(semStr2, O_CREAT, 0666, 1);
  printf("PID:%d\n",getpid());
  signal(15,handler);
  do{
if(cycles==6)handler();
   wait(chop[0]);
   wait(chop[1]);
   eat();
   sig(chop[0]);
   sig(chop[1]);
   think();
   cycles++;
  }while(1);
 }else{
  printf("incorrect usage: Not enough parameters\n");
 }
 return 0;
}

