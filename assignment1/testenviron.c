#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;

int main() {

  char *s = *environ;
  int i = 1;

  const char eq[2] = "=";
  char *token;
  char *val;
  char *variable;
 

  while(s){
    //printf("%s\n", s);
    token = strtok(s, eq);
    val = malloc(strlen(token)+1);
    strcpy(val, token);
    //char *c = getenv(val);
    //char *c = getenv("SSH_CLIENT");
    //variable = getenv(x*token);
    printf("%s:%s:%s\n", token, getenv("PATH"), val);
    s = *(environ+i);
    i++;
  }

  return 0;
}
