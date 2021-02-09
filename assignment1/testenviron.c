#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;

void printsomething(const char *c){
    int len = strlen(c);
    char *env_var;
    env_var = malloc(sizeof(char) * len + 1);
    strcpy(env_var, c);

    //printf("test char :%s : %s : %s ---> %i\n",c, getenv("OLDPWD"), c, len);
    printf("Variable %s:%s\n", env_var, getenv(env_var));
}

void updateEnvironmentVariable(char *namevalue){
    putenv(namevalue);
}

void clearAllEnvironmentVariables(char *namevalue){
    clearenv();
    updateEnvironmentVariable(namevalue);
}

void printAllEnvironmentVariables(){
   int i =0; 
   for (i=0; environ[i] != NULL; i++){
      printf("%s\n", environ[i]);
   }
}

void executeSystem(char *command){
	system(command);
}
int main() {

  printAllEnvironmentVariables();

  getchar();
  updateEnvironmentVariable("PASSCODE1=BABU");
  
  
  printAllEnvironmentVariables();

  getchar();
  updateEnvironmentVariable("PASSCODE1=FARAH");

  printAllEnvironmentVariables();
 
  getchar();
  printf("********\n");
  clearAllEnvironmentVariables("PASSCODE2=TEST");
  printAllEnvironmentVariables();

  getchar();
  updateEnvironmentVariable("TZ=est5est");
  executeSystem("date");
  return 0;
}
