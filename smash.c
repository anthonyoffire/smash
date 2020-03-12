//---------------------------------------------------------------
//smash.c : loops for user input, calls executeCommand
//
//Author: Anthony Baird 3/7/20
//---------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "smash.h"
#include "history.h"

int main(int argc, char **argv){
	char bfr[MAXLINE];
	int exitStatus;
	init_history();//Initialize history
	fputs("$ ", stderr);
	while(fgets(bfr, MAXLINE, stdin) != NULL){
		bfr[strlen(bfr) - 1] = '\0';
		if(strcmp(bfr, "") != 0){
			exitStatus = executeCommand(bfr);
			add_history(bfr, exitStatus);
		}
		fputs("$ ", stderr);
	}
	clear_history();//Free malloc'd memory
	return 0;
}
