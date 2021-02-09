#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	const char* s = getenv("PATH");
	printf("The current environment variables are: %s\n", s); 
	return 0;
}
