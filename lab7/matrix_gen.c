#include <stdio.h>
#include <stdlib.h>
void theBluePill(int sz){
 int n=-100;
 int m=100;
 int i,j;
 srand(time(NULL));
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)printf("%4d",m + rand()/(RAND_MAX/(n-m+1)+1));
  printf("\n");
 }
}

int main(int argc,char *argv[]){
 int sz;
 if(argc>1){
   theBluePill(atoi(argv[1]));
  }else{
  printf("Not enough paramters, dumb dumb\n");
 }
 return 0;
}
