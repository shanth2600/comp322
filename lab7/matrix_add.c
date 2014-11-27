#include <stdio.h>
#include <stdlib.h>
int **arr;

void outarr(int sz){
 printf("herererere\n");
 int i,j;
 for(i=0;i<sz;i++){
  for(j=0;j<sz;j++)printf("%d",arr[i][j]);
  printf("\n");
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


int main(int argc,char *argv[]){
 int sz,c;
 FILE *f;
 if(argc>1){
  sz=atoi(argv[1]);
  construct(sz);
  buff=malloc((sz*sz)*sizeof(int));
  f=fdopen(0,"r+");

  fwrite(buff,sizeof(int),sz*sz,f);
  fclose(f);
//  fillArr(sz);
//printf("herere123\n");

  //outarr(sz);
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
