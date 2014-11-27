#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <aio.h> 

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

int *prev;
int *curr;
int *next;


/*void fillArr(int sz){
 int i,j;
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)arr[i][j]=buff[(sz*i)+j];
 }
}
*/
void addScalar(int x,int y,int blkSz,int sc){
 int i,j;
 for(i=0;i<blkSz;i++){
  for(j=0;j<blkSz;j++){
   arr[i+x][j+y]=curr[i+j]+sc;
  }
 }
}


int main(int argc,char *argv[]){
 int blk,sz,c,sc,x,y;
 int blkSz;
 int f;
 int currB,prevB,nextB;
 struct aiocb cb;
 struct aiocb cbw;
 if(argc>2){
  sz=atoi(argv[1]);
  blk=atoi(argv[2]);
  blkSz=sz/blk;
  construct(sz);
  prev=malloc(blkSz *sizeof(int));
  curr=malloc(blkSz *sizeof(int));
  next=malloc(blkSz *sizeof(int));
  memset(&cb, 0, sizeof(struct aiocb));
  memset(&cbw, 0, sizeof(struct aiocb));
  cb.aio_fildes=0;
  cb.aio_buf=curr;
  cb.aio_offset=0;
  cb.aio_nbytes=blkSz;
  cbw.aio_fildes=1;
  cbw.aio_buf=prev;
  cbw.aio_offset=0;
  cbw.aio_nbytes=blkSz;
  aio_read(&cb);
  srand(time(NULL));
  sc=rand()%100;
  cb.aio_buf=next;  
  for(x=1;x<blkSz-2;x++){
   for(y=1;y<blkSz-2;y++){
    currB=(pow(x,2))+(pow(y,2));
    nextB=currB+blkSz;
    prevB=currB-blkSz;
    cb.aio_offset=nextB;
    aio_read(&cb);
    addScalar(x,y,blkSz,sc);
    cbw.aio_offset=prevB;
    aio_write(&cbw);
    aio_return(&cbw);
    memcpy(prev,curr,blkSz);
    aio_return(&cb);
    memcpy(curr,next,blkSz);
   }
  }
  
  outarr(sz);
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
