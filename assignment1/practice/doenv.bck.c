#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>

/*
 * author : farab babu
 * userid : babu
 * course : cs5760
 *
 */

extern char **environ;
extern int errno;

// function to return the name part of the environment variable (name=value pair)
char *environSubString(char *namevalue, int n){
	char *new = malloc(sizeof(char)*n+1);
	strncpy(new, namevalue, n);
	new[n] = '\0';
	return new;
}

// to update the environment value using putenv method
void updateEnvironmentVariable(char *namevalue){
    putenv(namevalue); //System library function to update the name value pair
}

// to clear all environment variables and set the one that is required passed as argument -i option from the command line
void clearAllEnvironmentVariables(char *namevalue){
    clearenv();                           //to clear all the exisiting environment variables
    if(namevalue != NULL){
	updateEnvironmentVariable(namevalue);
    }
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
//returns the status which is zero if execution is OK, else 
int executeSystem(char *command){
	int status = system(command);
	return status;
}


//To check if the argument is a name value pair makes use of the string library function strchr
int isNameValuePair(char *argv){
	
	if(strchr(argv, '=') != NULL){
		return 1;
	}
	return 0;
}

//To check if its the end of the command terminated by a semicolon
int isEndOfCommand(char *argv){
	if(strchr(argv, ';') != NULL){
		return 0;
	}
	return 1;
}


extern int optind;

int main(int argc, char **argv){
	int option;
        int index;
	char *next;
	int status;
	int optionsflag = 0;
	int cmdflag = 0;

	if(argc == 1){
		printAllEnvironmentVariables();
		return 0;
	} 

	while((option = getopt(argc, argv, "ih")) != -1){
	optionsflag = 1;
		switch (option){
			case 'i':
					index = optind;
					
					clearAllEnvironmentVariables(NULL);
					while(index < argc){
						next = strdup(argv[index]);
						
						if(next[0] != -1){
							
							if(isNameValuePair(argv[index]) == 1){
							   updateEnvironmentVariable(argv[index]);
							}else{
							
							  char *cmd;
						          int j = 0;
							  while(index < argc){
								
								if(j==0){
								  cmd = argv[index];
								  j++;
								}else{
								  cmd = strcat(cmd, argv[index]);
								}
								if(isEndOfCommand(argv[index])==0){
									break;
								}
								cmd = strcat(cmd, " ");
								index++;
							  } 
							  
							   status = executeSystem(cmd);
							   cmdflag = 1; // to dispaly the list of environments after the command has been executed.
							   
							   if(status!=0){
								char str[160];
								index--;
								errno = 22;
								sprintf(str, "%s had an error during executing command %s", argv[0], argv[index]);
								perror(str);
								exit(EXIT_FAILURE);
							   }
							}
							index++;
						}else 
							break;				
					}
					if(cmdflag == 0)
					 printAllEnvironmentVariables();
				
					break;
			case 'h':
					printf("the program is similar to the env utility available in unix\nsupports two arguments \n\t-h : help \n\t-i: to modify name=value pairs, otherwise the pairs modify or add to the current environment\n");
					break;
			default:
					perror("Unsupported arguments please run the command -h to find out how to use it");
					break;
		}
	}

	if(optionsflag == 0){
		cmdflag = 0;

		int i = 1;
		while(i < argc){
			index = i;
		        if(isNameValuePair(argv[i]) == 1){
				updateEnvironmentVariable(argv[index]);
			}else{
			  	char *cmd;
				int j = 0;
				while(i < argc){
				  if (j ==0){
					cmd = argv[i];
					j++;
				  }else{
					cmd = strcat(cmd, argv[i]);
				  }
				  if(isEndOfCommand(argv[i])==0){
					break;
				  }
				  cmd = strcat(cmd, " ");
				  i++;
				}
				status = executeSystem(cmd);
				cmdflag = 1;

				if(status!=0){
					char str[160];
					i--;
					errno = 22;
					sprintf(str, "%s had an error during execution of command %s", argv[0], argv[i]);
					perror(str);
					exit(EXIT_FAILURE);
				}
			}
			i++;
		}
		if(cmdflag == 0)
			printAllEnvironmentVariables();
	}
}
