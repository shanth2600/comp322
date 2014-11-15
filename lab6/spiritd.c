#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/times.h>
#include <signal.h>
#include <sys/resource.h>
#include <string.h>

FILE *lf;
char *cpt;
int m[]={0,0};
char *arg[]={"Mole1","Mole2"};

void newMole(){
 srand(time(NULL));
 int r=0;
 while(r==0){
  r = rand()%3;
 }
 m[r-1]=fork();
 if(m[r-1]==0){
  char str[100];
  strcpy(str,cpt);
  strcat(str,"/mole\0");
  char *zargs[]={NULL,arg[r-1],NULL};
  char *envp[]={NULL};
  int rv;
  zargs[0]=str;
  execv(str,zargs);
 }
}

void hndlr(int signo){
 if(signo==SIGTERM){
  if(m[0]!=0)kill(m[0],SIGTERM);
  if(m[1]!=0)kill(m[1],SIGTERM);
  exit(0);
 }else if(signo==SIGUSR1){
  if(m[0]!=0){
   kill(m[0],SIGTERM);
   m[0]=0;
  }
  newMole();
 }else if(signo==SIGUSR2){
  if(m[1]!=0){
   kill(m[1],SIGTERM);
   m[1]=0;
  }
  newMole();
 }
}



int main(int argc,char *argv[]){
 int i;
 int devNull;
 int cpid;
 int sid;
 int max;
 const char *pt="/";
 struct rlimit lm;
 cpid=fork();
 if(cpid!=0)exit(0);
 printf("PID: %d\n",getpid());
 umask(0);
 sid=setsid();
 cpt=getenv("PWD");
 chdir(pt);
 getrlimit(RLIMIT_NOFILE,&lm);
 max=lm.rlim_max;
 for(i=0;i<max-1;i++){
  close(i);
 }
 devNull=open("/dev/null",O_RDONLY);
 dup2(devNull,0);
 dup2(devNull,1);
 dup2(devNull,3);
 signal(SIGTERM,hndlr);
 signal(SIGUSR1,hndlr);
 signal(SIGUSR2,hndlr);
 do{
  // WAIT
 }while(1);
 return 0;
}
