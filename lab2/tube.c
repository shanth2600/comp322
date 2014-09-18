#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char* argv[]){
 int pipefd[2];
 pipe(pipefd);
 int cpid1=fork();
 if(cpid1==0){
//CHILD 1
  dup2(pipefd[0],0);
  close(pipefd[1]);
  char* newArgv[]={argv[1],"." ,NULL};
  char* env[]={NULL};
  execve(newArgv[0],&newArgv[0],env);
 }else{
  int cpid2=fork();
  if(cpid2==0){
// CHILD 2
//   dup2(pipefd[0],0);
//   close(pipefd[1]);
   char* newArgv[2];
   newArgv[0]=argv[2];
   char* env[]={NULL};
   printf("FUCK %s\n",*newArgv[0]);
   execve(newArgv[0],&newArgv[0],env);
  }else{
// Parent
   fprintf(stderr,"CPID1:%d\n",cpid1);
   fprintf(stderr,"CPID2:%d\n",cpid2);
   close(pipefd[0]);
  }
 }
 return 0;
}
