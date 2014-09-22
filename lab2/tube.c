#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int findComma(char *args[],int count){
 int pos=-1;
 int i;
 for(i=0;i<count;i++){
  if(*args[i]==',')pos=i;
 }
 return pos;
}
void manArray(char *src[],char *dst[],int beg,int end){
 int i;
 int j=0;
 for(i=beg;i<end;i++){
  dst[j]=src[i];
  j++;
 }
 dst[j]=NULL;
}

int main(int argc,char* argv[]){
 int pipefd[2];
 int commaPos;
 pipe(pipefd);
 commaPos=findComma(argv,argc);
 int cpid1=fork();
 if(cpid1==0){
//CHILD 1
  dup2(pipefd[1],1);
  close(pipefd[0]);
  char *newArgv[argc-commaPos+1];
  manArray(argv,newArgv,1,commaPos);
  char* env[]={NULL};
  execve(newArgv[0],&newArgv[0],env);
  exit(0);
 }else{
  int cpid2=fork();
  if(cpid2==0){
// CHILD 2
   dup2(pipefd[0],0);
   close(pipefd[1]);
   char* newArgv[3];
   manArray(argv,newArgv,commaPos+1,argc);
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
