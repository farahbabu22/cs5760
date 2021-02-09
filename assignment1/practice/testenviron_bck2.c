#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;


// function to return the name part of the environment variable (name=value pair)
char *environSubString(char *namevalue, int n){
	char *new = malloc(sizeof(char)*n+1);
	strncpy(new, namevalue, n);
	new[n] = '\0';
	return new;
}

// to update the environment value using putenv method
void updateEnvironmentVariable(char *namevalue){
    putenv(namevalue);
}

// to clear all environment variables and set the one that is required passed as argument -i option from the command line
void clearAllEnvironmentVariables(char *namevalue){
    clearenv();
    updateEnvironmentVariable(namevalue);
}

// To print all the env values in the same way as env utility
// This method makes use of getenv method as per the requirement of the assignment
void printAllEnvironmentVariables(){
   int i =0; 
   for (i=0; environ[i] != NULL; i++){
      /* The first part of the printf statement prints name of the environment variable the second one prints the value of the environment variable
 * 	 As a requirement from the question I have used the getenv method with the env variable name to print the value held
 * 	 */
      printf("%s:%s\n", environSubString(environ[i], (strlen(environ[i]) - strlen(strchr(environ[i], '=')))), getenv(environSubString(environ[i], (strlen(environ[i])- strlen(strchr(environ[i], '='))))));
   }
}

//executes the system command 
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
  //printf("MY VAR :%s", getMyEnv("PASSCODE2"));

  getchar();
  updateEnvironmentVariable("TZ=est5est");
  printAllEnvironmentVariables();
  executeSystem("date");
  return 0;
}
