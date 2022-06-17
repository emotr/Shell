#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifndef MAX_BUFFER
#define MAX_BUFFER 200
#endif

char currentPath[MAX_BUFFER];  		/** Lagre hele filsti  */
char currentPathShort[MAX_BUFFER]; 	/** Lagre bare katalogen man er i  */

void trimString(char[]); 		/** Fjern ubrukt space i input string så man kan sammenligne stringer  */
void parseInput(char[]); 		/** Håndter input */
void getCurrentPath(); 			/** Lagrer den nåværende stien i currentPath  */
void printPath(); 				/** Printer den nåværende stien */
void trimPath();				/** Fjern alt bortsett fra nåværende katalog og lagre i currentPathShort  */
int changeDirectory(char[]);  	/** Endre katalog prosessen er i */

int main(int argc, char **argv[]){
	char command[50];
	char quit[] = "quit";
	int loopControl = 1;

	while (loopControl) {
		getCurrentPath();
		trimPath();
		printf("[%s] > ", currentPathShort);
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
	int index = -1, i = 0;
	while(str[i] != '\0'){
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			index = i;
		i++;
	}

	str[index + 1] = '\0'; // Legg til avsluttende karakter
}

void parseInput(char command[]){
	if (strcmp(command, "pwd") == 0)
		printPath();
	else 
		printf("%s\n", command);	
}

void getCurrentPath(){
	errno = 0;
	if (getcwd(currentPath, MAX_BUFFER) == NULL){
		if (errno == ERANGE)
			printf("[ERROR] pathname length exceeds the buffer size\n");
		else 
			perror("[ERROR] getcwd\n");
		exit(1);
	}	

	getcwd(currentPath, MAX_BUFFER);
}

void printPath(){
	printf("%s\n", currentPath);
}

void trimPath(){
	int flag = -1, i = 0;
	while (currentPath[i] != '\0'){
		if (currentPath[i] == '/'){
			flag = i;
		}

		i++;
	}

	if (flag == -1){
		return;
	}

	i = 0;
	while (currentPath[i] != '\0'){
		currentPathShort[i] = currentPath[flag + i + 1];	
		i++;
	}

	currentPathShort[i] = '\0'; // Legg til avsluttende karakter
}

int changeDirectory(char newDirectory[]){
	
	
	return 0;
}
