#include <stdio.h>
#include <stdlib.h>

int *buff=NULL;

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

void fillBuff(int sz){
 int i;
 int min=-100;
 int max=100;
 srand(time(NULL));
// for(i=0;i<sz;i++)buff[i]=i;
 for(i=0;i<sz;i++)buff[i]=(rand() % (max+1-min))+min;

}

FILE *f;
int main(int argc,char *argv[]){
 int sz;
 if(argc>1){
   sz=atoi(argv[1]);
   buff=malloc((sz*sz)*sizeof(int));
   fillBuff(sz*sz);
   f=fdopen(1,"w");
   fwrite(buff,sizeof(int),sz*sz,f);
   fclose(f);
  }else{
  printf("Not enough paramters, dumb dumb\n");
 }
 return 0;
}
