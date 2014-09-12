#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <time.h>


void startFork(){
 struct tms cTms;
 int cpid;
 int stt;
 times(&cTms);
 cpid=fork();
 waitpid(cpid,&stt,WCONTINUED);
 printf("PID:%d",getpid());
 printf(", PPID:%d",getppid());
 if(cpid!=0){
  printf(", CPID:%d",cpid);
  printf(", RETVAL:%d\n",WEXITSTATUS(stt));
  times(&cTms);
  printf("USER:%d, SYS:%d, ",cTms.tms_utime,cTms.tms_utime);
  printf("CUSER:%d, CSYS:%d",cTms.tms_cutime,cTms.tms_cstime);
 }else{
  int i,j;
  for(i=0;i<100000000;i++)j=i;
  exit(0);
 }
 printf("\n");


}


int main(){
 printf("Start:%d\n",time(NULL));
 startFork();
 printf("Stop:%d\n",time(NULL));
 return 0;
}

