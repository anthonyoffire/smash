//---------------------------------------------------------------
//smash.c : loops for user input, calls executeCommand
//
//Author: Anthony Baird 3/7/20
//---------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "smash.h"
#include "history.h"
#include <signal.h>

int main(int argc, char **argv){
	
	//Disable SIGINT
	signal(SIGINT, SIG_IGN);
	//Disable buffering in stdout stream
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	//Define variables
	char bfr[MAXLINE];
	int exitStatus;

	//Output inital prompt
	fputs("$ ", stderr);

	//Loop for input
	while(fgets(bfr, MAXLINE, stdin) != NULL){
		bfr[strlen(bfr) - 1] = '\0';
		if(strcmp(bfr, "") != 0){
			exitStatus = executeCommand(bfr);
			add_history(bfr, exitStatus);
		}
		fputs("$ ", stderr);
	}
	
	//Free malloc'd memory
	clear_history();
	
	return 0;
}
