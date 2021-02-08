#include <stdio.h>
#include <stdlib.h> 

int main(){
	char c = '3';
	printf("PATH: %s\n", getenv(&c));
	return 0;
}
