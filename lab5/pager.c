#include <stdio.h>

int main(int argc,char *argv[]){
 int address;
 if(argc>1){
  address=atoi(argv[1]);
  printf("The adress %d contains:\n",address);
  printf("page number: %d\n",address/4096);
  printf("offset: %d\n",address%4096);
 }else{
  printf("Correct usage: pager [mem address]\n");
 }
 return 0;
}
