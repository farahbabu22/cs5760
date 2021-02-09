#include<stdio.h>

extern char **environ;

int main() {

  char *s = *environ;
  int i = 1;


  while(s){
    printf("%s\n", s);
    s = *(environ+i);
    i++;
  }

  return 0;
}
