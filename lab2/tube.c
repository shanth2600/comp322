#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char* argv[]){
 int pipefd[2];
 pipe(pipefd);
 int cpid1=fork();
 if(cpid1==0){
//CHILD 1
  dup2(pipefd[1],1);
  close(pipefd[0]);
  char* newArgv[]={argv[1],NULL};
  char* env[]={NULL};
 printf("Jere\n");
  execve(newArgv[0],&newArgv[0],env);
  exit(0);
 }else{
  int cpid2=fork();
  if(cpid2==0){
// CHILD 2
   dup2(pipefd[0],0);
   close(pipefd[1]);
   char* newArgv[3]={argv[2],argv[3],NULL};
   char* env[]={NULL};
   execve(newArgv[0],&newArgv[0],env);
   exit(0);
  }else{
// Parent
   fprintf(stderr,"CPID1:%d\n",cpid1);
   fprintf(stderr,"CPID2:%d\n",cpid2);
   int stt1;
   int stt2;
   close(pipefd[0]);
   close(pipefd[1]);
   waitpid(cpid2,&stt2,WCONTINUED);
   waitpid(cpid1,&stt1,WCONTINUED);
   fprintf(stderr,"Child 1 returns:%d\n",stt1);
   fprintf(stderr,"Child 2 returns:%d\n",stt2);
  }
 }
 return 0;
}
