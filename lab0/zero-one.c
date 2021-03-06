#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int maxSize=256;
int totalBytesRead;
char *dta=NULL;
char *asci[32]={"  NUL","  SOH","  STX","  ETX","  EOT","  ENQ","  ACK","  BEL","  BS","  HT","  LF","  VT","  FF","  CR","  SO","  SI","  DLE","  DC1","  DC2","  DC3","  DC4","  NAK","  SYN","  ETB","  CAN","  EM","  SUB","  ESC","  FS","  GS","  RS","  US","SPACE"};

char *strrev(char *str)
{
 char *p1, *p2;
 if (! str || ! *str)return str;
 for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
  *p1 ^= *p2;
  *p2 ^= *p1;
  *p1 ^= *p2;
 }
 return str;
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
 len=7;
 str[0]='0';
 str=strrev(str);
 for(i=0;i<len;i++){
  if(str[i]=='1')rv+=pow(2,i);
 }
 return rv;
}

void anlz(){
 int i,j,val;
 char byt[9];
 char byt2[9];
 char prty;
 printf("Original  ASCII  DECIMAL Parity P.Error\n");
 printf("--------  ------ ------- ------ -------\n");
 int fullBytes=totalBytesRead/8;
 int remainderBytes=8-totalBytesRead%8;
 for(i=0;i<fullBytes;i++){
  for(j=0;j<8;j++){
   byt[j]=dta[(i*8)+j];
  }
  byt[8]='\0';
  strncpy(byt2,byt,9);
  val=strToBin(byt2);
  prty=cntPrty(byt);
  printf("%s   ",byt);
  if(val<33){
   printf("%s    ",asci[val]);
  }else{
   printf("    %c    ",(char)val);
  }
  printf("%d\t",val);
  printf("  %s  ",prty=='o'?"Odd ":"Even");
  printf("%s    \n",prty=='o'?"Error":"Fine"); 
 }
// Horrendous hack to pad bits on incomplete byte
  for(j=0;j<8-remainderBytes;j++)byt[j]='0';
  for(j=remainderBytes;j<8;j++)byt[j]=dta[fullBytes+j];
  byt[8]='\0';
  strncpy(byt2,byt,9);
  val=strToBin(byt2);
  prty=cntPrty(byt);
  printf("%s   ",byt);
  if(val<33){
   printf("%s    ",asci[val]);
  }else{
   printf("    %c   ",(char)val);
  }
  printf("%d \t",val);
  printf("  %s  ",prty=='o'?"Odd ":"Even");
  printf("%s    \n",prty=='o'?"Error":"Fine");


}

void readFile(int fd){
 int i,n,sz;
 int bs=256;
 char buf[bs];
 n=1;
 while(n!=0){
  n=read(fd,buf,bs);
  totalBytesRead+=n;
 }

 dta=malloc((totalBytesRead)*sizeof(char));

 for(i=0;i<totalBytesRead;i++){

  dta[i]=buf[i];
 }
 dta[totalBytesRead]='\0';
 anlz();


}



int main(int argc, char *argv[]){
 int fd=0;
 if(argc>1&&strcmp(argv[1],"-")!=0){
  fd=open(argv[1],O_RDONLY);
 }
 readFile(fd);
}

