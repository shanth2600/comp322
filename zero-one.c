#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int bs=64;
char *dta=NULL;

void printOut(char *buf){

}

void readFile(int fd){
 int n;
 int i,sz;
 char buf[bs];
 read(fd,buf,bs);
 for(i=0;i<bs;i++){
  if(buf[i]==0)break;
 }
 sz=i+1;
 dta=(char *)malloc(sz * sizeof(char));
 for(i=0;i<sz;i++){
  dta[i]=buf[i];
 }
 printf("%d\n",sz);

}

int main(int argc, char *argv[]){
 int fd=0;
 if(argc>1&&strcmp(argv[1],"-")!=0){
  fd=open(argv[1],O_RDONLY);
 }
 readFile(fd);
}

