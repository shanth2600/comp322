#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int bs=32;
char *dta=NULL;

char zcntPrty(char *str){
 int i;
 int ones=0;
 for(i=0;i<8;i++){
  if(str[i]=='1')ones++;
 }
// printf("%s",str);
 printf("%d ",ones);
 if(ones%2>0){
  return 'o';
 }else return 'e';

}

char cntPrty(char *str){
 int i;
 int len;
 int ones;
 ones=0;
 len=8;
 //str[0]="0";
 for(i=0;i<len;i++){
  if(str[i]!='0')ones++;
 }
 return (ones%2>0?'o':'e');
}

int strToBin(char *str){
 int i;
 int len;
 int rv=0;
 len=8;
 str[0]='0';
 str=strrev(str);
 for(i=0;i<len;i++){
  printf("%c",str[i]);
  if(str[i]=='1')rv+=pow(2,i);
 }
 printf("\n");
 str=strrev(str);
 return rv;
}

void anlz(){
 int i,j,val;
 char byt[9];
 char byt2[9];
 printf("Original  ASCII  DECIMAL Parity  T.Error\n");
 printf("--------  ------ ------- ------  -------\n");
 for(i=0;i<bs;i=i+8){
  for(j=0;j<8;j++){
   byt[j]=dta[i+j];
  }
  strncpy(byt2,byt,9);
  val=strToBin(byt2);
  printf("%s       ",byt);
  printf("%c  ",(char)val);
  printf("%d\t",val);
  printf(" %s    \n",cntPrty(byt)=='o'?"Odd":"Even");
 }
}

void readFile(int fd){
 int n;
 int i,sz;
 char buf[bs];
 read(fd,buf,bs);
 for(i=0;i<bs;i++){
  if(buf[i]==0)break;
 }
// sz=32;
 dta=(char *)malloc(bs * sizeof(char));
 for(i=0;i<bs;i++){
  dta[i]=buf[i];
 }

 anlz();

}



int main(int argc, char *argv[]){
 int fd=0;
 if(argc>1&&strcmp(argv[1],"-")!=0){
  fd=open(argv[1],O_RDONLY);
 }
 readFile(fd);
}

