#include <stdio.h>
#include <stdlib.h>
int **arr;

void outarr(int sz){
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
// for(i=0;i<sz;i++){
//  for(j=0;j<sz;j++)arr[i][j]=0;
// }
// outarr(sz);
}



int main(int argc,char *argv[]){
 int c,i=0;
 char *x;
 if(argc>1){
  construct(atoi(argv[1]));
  char buff[4];
  while((c=fgetc(stdin))!= EOF){
   buff[i]=(char)(((int)'0')+c);
   printf("%c",buff[i]);
   i++;
   if(i==3){
    sprintf(x,"%s",atoi(buff));
    i=0;
   }
printf("%s\n",x);
break;
  }
 }else{
  printf("Not enough parameters dumb dumb!\n");
 }
 return 0;
}
