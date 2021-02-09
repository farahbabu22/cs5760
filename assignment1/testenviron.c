#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;

char *substring(char *string, int position, int length)
{
   char *p;
   int c;
 
   p = malloc(length+1);
   
   if (p == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position-1);      
      string++;  
   }
 
   *(p+c) = '\0';
 
   return p;
}

char *environSubString(char *namevalue, int n){
	char *new = malloc(sizeof(char)*n+1);
	strncpy(new, namevalue, n);
	new[n] = '\0';
	return new;
}

void printsomething(const char *c){
    int len = strlen(c);
    char *env_var;
    env_var = malloc(sizeof(char) * len + 1);
    strcpy(env_var, c);

    //printf("test char :%s : %s : %s ---> %i\n",c, getenv("OLDPWD"), c, len);
    printf("Variable %s:%s\n", env_var, getenv(env_var));
}

char *getMyEnv(const char *name){
     int i = 0;
     char *p;
     while(environ[i]){
       if(!strncmp(environ[i], name, strlen(name))){
            //return(environ[i] + strlen(name) + 1);
            //printf("equals appear at %s", strchr(environ[i], '='));
            printf("strlen(environ): %zu strlen(name): %zu, strlen 2: %zu, length to = %zu \n", strlen(environ[i]), strlen(name), strlen(strchr(environ[i], '=')), (strlen(environ[i]) - strlen(strchr(environ[i], '='))));
            //p = substring(environ[i], 0, strlen(name) - strlen(strchr(environ[i], '=')));
            //printf("The name %s", p);
            //free(p);
            //printf("Name of the variable: %s\n", environSubString(environ[i], strlen(name)));
            printf("Name of the variable: %s\n", environSubString(environ[i], (strlen(environ[i]) - strlen(strchr(environ[i], '=')))));
	    printf("Get Env : %s\n", getenv(environSubString(environ[i], (strlen(environ[i]) - strlen(strchr(environ[i], '='))))));
	    return(environ[i]);
       }
       i++;
     }
     return NULL;
}


//char printEnvironmentVariable(const char *name){
//
//}

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
  clearAllEnvironmentVariables("PASSCODE2=TEST=TEST2");
  printAllEnvironmentVariables();
  printf("MY VAR :%s", getMyEnv("PASSCODE2"));

  getchar();
  updateEnvironmentVariable("TZ=est5est");
  executeSystem("date");
  return 0;
}
