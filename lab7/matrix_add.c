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

int *buff;

int main(int argc,char *argv[]){
 int blk,sz,c,sc,x,y;
 int blkSz;
 int f,sqrBlk;
 int currB,prevB,nextB;
 struct aiocb cb;
 struct aiocb cbw;
 if(argc>2){
  sz=atoi(argv[1]);
  blk=atoi(argv[2]);
  sqrBlk=sqrt(blk);
  blkSz=((sz*sz)/blk);
  construct(sz);
  prev=malloc(blkSz * sizeof(int));
  curr=malloc(blkSz * sizeof(int));
  next=malloc(blkSz * sizeof(int));
// Remember to take this out
int i;
buff=malloc((sz*sz) * sizeof(int));
i=read(0,buff,64);
for(i=0;i<sz*sz;i++)fprintf(stderr,"%d\n",buff[i]);
fprintf(stderr,"---------------------\n");
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
  while(aio_error(&cb)==115){}
  aio_return(&cb);
  currB=0;
  cb.aio_buf=curr;
  for(x=0;x<sqrBlk;x++){
   for(y=0;y<sqrBlk;y++){
    if(x==0&&y==0)y=1;
    currB+=blkSz*sizeof(int);
    nextB=currB+(blkSz * sizeof(int));
    prevB=currB-(blkSz * sizeof(int));
    cbw.aio_offset=prevB;
    aio_write(&cbw);
    while(aio_error(&cbw)==115){}
    aio_return(&cbw);
    cb.aio_offset=currB;
    aio_read(&cb);
    //addScalar(x,y,blkSz,sc);
    while(aio_error(&cb)==115){}
    aio_return(&cb);
 memcpy(prev,curr,blkSz*sizeof(int));
   }
  }
  cbw.aio_offset=currB;
  aio_write(&cbw);
  for(i=0;i<blkSz;i++)fprintf(stderr,"%d\n",curr[i]);
  while(aio_error(&cbw)==115){}
  aio_return(&cb);
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
