#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int termCount=0;
int ex=0;
int sigCount=0;

int sig_name2number(char *s) {
 int signumber = -1;
 if (!strcmp(s, "HUP"))     { signumber = SIGHUP; }
 if (!strcmp(s, "INT"))     { signumber = SIGINT; }
 if (!strcmp(s, "QUIT"))    { signumber = SIGQUIT; }
 if (!strcmp(s, "ILL"))     { signumber = SIGILL; }
 if (!strcmp(s, "TRAP"))    { signumber = SIGTRAP; }
 if (!strcmp(s, "ABRT"))    { signumber = SIGABRT; }
 if (!strcmp(s, "IOT"))     { signumber = SIGIOT; }
 if (!strcmp(s, "BUS"))     { signumber = SIGBUS; }
 if (!strcmp(s, "FPE"))     { signumber = SIGFPE; }
 if (!strcmp(s, "KILL"))    { signumber = SIGKILL; }
 if (!strcmp(s, "USR1"))   { signumber = SIGUSR1 ; }
 if (!strcmp(s, "SEGV"))   { signumber = SIGSEGV ; }
 if (!strcmp(s, "USR2"))   { signumber = SIGUSR2 ; }
 if (!strcmp(s, "PIPE"))   { signumber = SIGPIPE ; }
 if (!strcmp(s, "ALRM"))   { signumber = SIGALRM ; }
 if (!strcmp(s, "TERM"))   { signumber = SIGTERM ; }
 if (!strcmp(s, "STKFLT")) { signumber = SIGSTKFLT ; }
 if (!strcmp(s, "CHLD"))   { signumber = SIGCHLD ; }
 if (!strcmp(s, "CONT"))   { signumber = SIGCONT ; }
 if (!strcmp(s, "STOP"))   { signumber = SIGSTOP ; }
 if (!strcmp(s, "TSTP"))   { signumber = SIGTSTP ; }
 if (!strcmp(s, "TTIN"))   { signumber = SIGTTIN ; }
 if (!strcmp(s, "TTOU"))   { signumber = SIGTTOU ; }
 if (!strcmp(s, "URG"))    { signumber = SIGURG ; }
 if (!strcmp(s, "XCPU"))   { signumber = SIGXCPU ; }
 if (!strcmp(s, "XFSZ"))   { signumber = SIGXFSZ ; }
 if (!strcmp(s, "VTALRM")) { signumber = SIGVTALRM ; }
 if (!strcmp(s, "PROF"))   { signumber = SIGPROF ; }
 if (!strcmp(s, "WINCH"))  { signumber = SIGWINCH ; }
 return signumber;
}


void hndlr(int sig){
 printf("%s Caught at %d\n",strsignal(sig),time(NULL));
 signal(sig,hndlr);
 sigCount++;
 if(sig==SIGTERM){
  termCount++;
  if(termCount==3)ex=1;
 }
}

int main(int argc, char* argv[]){
 int i;
 if(argc>1){
  fprintf(stderr,"%s PID:%d\n",argv[0],getpid());
  for(i=1;i<argc;i++){
   signal(sig_name2number(argv[i]),hndlr);
  }
  while(ex!=1)pause();
  printf("%s: Total signals count = %d\n",argv[0],sigCount);
 }else{
  printf("Not enough args\n");
 }
}
