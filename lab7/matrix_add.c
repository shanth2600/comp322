#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
#include <aio.h> 
#include <time.h>

int **arr;

void outarr(int sz){
 int i,j;
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)fprintf(stderr,"%d\n",arr[i][j]);
 }
}
void construct(int sz){
 int i,j;
 arr=(int **)malloc(sz*sizeof(int *));
 for(i=0;i<sz;i++)arr[i]=(int *)malloc(sz*sizeof(int));
}

int *prev;
int *curr;
int *next;



void addScalar(int x,int y,int blkSz,int sc){
 int i,j;
 x=x*sqrt(blkSz);
 y=y*sqrt(blkSz);
 for(i=0;i<blkSz/2;i++){
  for(j=0;j<blkSz/2;j++){
   arr[x+i][y+j]=prev[i+j]+sc;
  }
 }
}

int *buff;

int main(int argc,char *argv[]){
 int blk,sz,c,sc,x,y;
 int blkSz;
 int f,sqrBlk;
 int currB,prevB,nextB;
 int start=0;
 int end=0;
 struct aiocb cb;
 struct aiocb cbw;
 struct timeval tv;
 struct timeval tv2;
 if(argc>2){
  sz=atoi(argv[1]);
  blk=atoi(argv[2]);
  sqrBlk=sqrt(blk);
  blkSz=((sz*sz)/blk);
  construct(sz);
  prev=malloc(blkSz * sizeof(int));
  curr=malloc(blkSz * sizeof(int));
  next=malloc(blkSz * sizeof(int));
  memset(&cb, 0, sizeof(struct aiocb));
  memset(&cbw, 0, sizeof(struct aiocb));
  cb.aio_fildes=0;
  cb.aio_buf=prev;
  cb.aio_offset=0;
  cb.aio_nbytes=blkSz*sizeof(int);
  cbw.aio_fildes=1;
  cbw.aio_buf=curr;
  cbw.aio_offset=0;
  cbw.aio_nbytes=blkSz*sizeof(int);
  srand(time(NULL));
  sc=rand()%100;
  aio_read(&cb);
  memset(&tv, 0, sizeof(struct timeval));
  memset(&tv2, 0, sizeof(struct timeval));
  gettimeofday(&tv,NULL);
  start=tv.tv_usec;


/*
buff=malloc(sz*sz*sizeof(int));
read(0,buff,sz*sz*sizeof(int));
int i;
for(i=0;i<sz*sz;i++)fprintf(stderr,"%d\n",buff[i]);
fprintf(stderr,"---------------------------------\n");
*/
  while(aio_error(&cb)==115){}
  aio_return(&cb);
  currB=0;
  cb.aio_buf=curr;
  for(x=0;x<sqrBlk;x++){
   for(y=0;y<sqrBlk;y++){
if(y==0&&x==0)y=1;
    currB+=blkSz*sizeof(int);
    nextB=currB+(blkSz * sizeof(int));
    prevB=currB-(blkSz * sizeof(int));
    addScalar(x,(y==1?0:y),blkSz,sc);
    cbw.aio_offset=prevB;
    aio_write(&cbw);
    while(aio_error(&cbw)==115){}
    aio_return(&cbw);
    cb.aio_offset=currB;
    aio_read(&cb);
    while(aio_error(&cb)==115){}
    aio_return(&cb);
    memcpy(prev,curr,blkSz*sizeof(int));
   }
  }
  cbw.aio_offset=currB;
  aio_write(&cbw);
  while(aio_error(&cbw)==115){}
  aio_return(&cb);
  gettimeofday(&tv2,NULL);
  end=tv2.tv_usec;

  fprintf(stderr,"Time :%d\n",(end-start));
//  fprintf("Time: %d\n",end);
//  outarr(sz);
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
