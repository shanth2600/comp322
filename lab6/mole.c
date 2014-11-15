#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


FILE *lf;
void hndlr(int signo){
 exit(0);
}
int main(int argc,char *argv[]){
 char *pt;
 pt=getenv("HOME");
 chdir(pt);
 lf=fopen("./lab6.log","a");
 fprintf(lf,"Pop %s\n",argv[1]);
 signal(SIGTERM,hndlr);
 fclose(lf);
 do{
// wait
 }while(1);
 return 0;
}
