#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifndef MAX_BUFFER
#define MAX_BUFFER 200
#endif

void trimString(char[]);
void parseInput(char[]);
int getCurrentPath();

int main(int argc, char **argv[]){
	char command[50];
	char quit[] = "quit";
	int loopControl = 1;

	while (loopControl) {
		printf("> ");
		fgets(command, sizeof(command), stdin); // les string
		trimString(command);
		

		if (strcmp(command, quit) == 0){
			printf("Program exiting\n");
			loopControl = 0;
			break;
		}

		parseInput(command);
	} 
	
	return 0;
}

/** Fjern ubrukt space i input string så man kan sammenligne stringer  */
void trimString(char str[]){
	int index, i;
	index = -1;
	i = 0;
	while(str[i] != '\0'){
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			index = i;
		i++;
	}

	str[index + 1] = '\0';
}

void parseInput(char command[]){
	getCurrentPath();
}

int getCurrentPath(){
	char path[MAX_BUFFER];
	errno = 0;
	if (getcwd(path, MAX_BUFFER) == NULL){
		if (errno == ERANGE)
			printf("[ERROR] pathname length exceeds the buffer size");
		else 
			perror("getcwd");
		return 1;
	}	

	getcwd(path, MAX_BUFFER);
	printf("%s\n", path);

	return 0;
}
