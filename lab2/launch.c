#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

char **newargv=NULL;

void forkMe(char *prog){
 int stt;
 int cpid=fork();
 if(cpid==0){
  char *newenviron[] = { NULL };
  execve(newargv[0],&newargv[0],newenviron);
  printf("here\n");
 }else{
  fprintf(stderr,"CPID:%d\n",cpid);
  int rv=waitpid(cpid,&stt,WCONTINUED);
  fprintf(stderr,"returns %d\n",stt);
  
 }
}



int main(int argc, char *argv[]){
 char *prog;
 int i;
 if(argc>1){
  newargv=malloc(argc * sizeof(char*));
  for(i=1;i<argc;i++){
   newargv[i-1]=argv[i];
  }
  newargv[i]=NULL;
  forkMe(argv[1]);
 }
 return 0;
}
