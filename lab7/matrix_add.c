#include <stdio.h>
#include <stdlib.h>


int **arr;

void outarr(int sz){
 int i,j;
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)printf("%d\n",arr[i][j]);
 }
}

void construct(int sz){
 int i,j;
 arr=(int **)malloc(sz*sizeof(int *));
 for(i=0;i<sz;i++)arr[i]=(int *)malloc(sz*sizeof(int));
/*
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)arr[i][j]=0;
 }
 outarr(sz);
*/
}

int *buff;


void fillArr(int sz){
 int i,j;
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)arr[i][j]=buff[(sz*i)+j];
 }
}

void addScalar(int x,int y,int sz,int blk,int sc){
 int i,j;
 for(i=0;i<(sz/blk)+x;i++){
  for(j=0;j<(sz/blk)+y;j++){
   arr[i][j]+=sc;
  }
 }
}


int main(int argc,char *argv[]){
 int blk,sz,c,sc,x,y;
 int blkSz;
 FILE *f;
 if(argc>2){
  sz=atoi(argv[1]);
  blk=atoi(argv[2]);
  blkSz=sz/blk;
  construct(sz);
  buff=malloc((sz*sz)*sizeof(int));
  f=fdopen(0,"r");
  if(f!=NULL){
   fread(buff,sizeof(int),sz*sz,f);
   fclose(f);
   fillArr(sz);
   srand(time(NULL));
   sc=rand()%100;
   for(x=0;x<blkSz;x++){
    for(y=0;y<blkSz;y++){
     addScalar(x,y,sz,blk,sc);
    }
   }
   addScalar(sz,blk,sc);
   outarr(sz);
  }else{
   printf("Hererere\n");
  }
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
