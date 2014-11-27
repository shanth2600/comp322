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
  blkSz=((sz/blk)*sizeof(int));
  construct(sz);
  prev=malloc(blkSz);
  curr=malloc(blkSz);
  next=malloc(blkSz);
// Remember to take this out
buff=malloc((sz*sz) * sizeof(int));
read(0,buff,(sz*sz));
  memset(&cb, 0, sizeof(struct aiocb));
  memset(&cbw, 0, sizeof(struct aiocb));
  cb.aio_fildes=0;
  cb.aio_buf=curr;
  cb.aio_offset=0;
  cb.aio_nbytes=blkSz*4;
  cbw.aio_fildes=1;
  cbw.aio_buf=prev;
  cbw.aio_offset=0;
  cbw.aio_nbytes=blkSz*4;
  aio_read(&cb);
  srand(time(NULL));
  sc=rand()%100;
  aio_return(&cb);
  while(aio_error(&cb)==115){}
  currB=0;
  for(x=0;x<sqrBlk;x++){
   for(y=0;y<sqrBlk;y++){
    if(x==0&&y==0)y=1;
    currB+=blkSz;
    nextB=currB+blkSz;
    prevB=currB-blkSz;
    memcpy(prev,curr,blkSz*4);
//int i;
//for(i=0;i<blkSz;i++)fprintf(stderr,"%d\n",prev[i]);
//return 0;
//    fprintf(stderr,"prev:%d\ncurr: %d\nnext:%d\n",prevB,currB,nextB);
    cb.aio_offset=currB;
    aio_read(&cb);
    //addScalar(x,y,blkSz,sc);
    while(aio_error(&cb)==115){}
    aio_return(&cb);
    cbw.aio_offset=prevB;
    aio_write(&cbw);
//printf("%s\n",strerror(aio_error(&cbw)));
//    memcpy(prev,curr,blkSz);
    while(aio_error(&cbw)==115){}
    aio_return(&cbw);
   }
  }
fprintf(stderr,"prev:%d\ncurr: %d\nnext:%d\n",prevB,currB,nextB);
  cbw.aio_offset=currB;
  aio_write(&cbw);
  while(aio_error(&cbw)==115){}
  aio_return(&cb);
  //outarr(sz);
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
