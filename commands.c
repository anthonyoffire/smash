//----------------------------------------------------------------------------
//commands.c : executeCommand function
//
//Author: Anthony Baird 3/7/20
//----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "smash.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "history.h"
#include <sys/wait.h>

//-------------------------------------------------------
//executeCommand : takes string of command and arguments, 
//				   tries to run argument, returns exit
//				   status
//-------------------------------------------------------
extern int elementsAdded;
int executeCommand(char *str){
	
	//Copy str to avoid manipulating the original copy
	char str2[MAXLINE];
	strncpy(str2, str, MAXLINE);

	char* token; //holds each space-separated token
	token = strtok(str2, " ");
	int i = 0;
	char* args[MAXLINE/2];//max # tokens 'str' can contain = MAXLINE/2 - 1
	
	//If there are no tokens, return normally
	if(token == NULL){
		return 0;
	}

	//Get all tokens and place them in *args[]
	while(token != NULL){
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}

	//Place NULL after last element
	args[i] = NULL;
	
	//Check whether args[0] matches any internal commands
	//exit
	if(strcmp(args[0],"exit") == 0){
		clear_history();//Free malloc'd memory
		exit(0);//Exit normally
	}
	//history
	if(strcmp(args[0], "history") == 0){
		//run print_history(initial command # to list)
		print_history();
	}
	//cd
	else if(strcmp(args[0],"cd") == 0){
		if(i>1){//cd command: if i==1, command has no arguments; do nothing
			if(chdir(args[1]) == 0){
				//Chdir successful, return printCwd
				return printCwd();
			}else{
				//Chdir failed, print error, cwd, return 1
				perror(args[1]);
				printCwd();
				return 1;//Exit status 1
			}
		}
	
	}else{
		//Internal command not found, search for external command
		return executeExternalCommand(args);
	}
	return 0;
}
//printCwd: tries to print current working dir
//			returns 0 on success, 1 on failure
int printCwd(){
	
	//Holder for file path
	char dir[FILENAME_MAX];
	
	//If cwd can be retrieved, print and return normally
	if(getcwd(dir, sizeof(dir)) != NULL){
		printf("%s\n", dir);
		return 0;
	}else{
		//getcwd error
		perror("getcwd() error!");
		return 1;
	}
}
//------------------------------------------------------------
//executeExternalCommand: fork and run external command,
//			  return exit status
//------------------------------------------------------------
int executeExternalCommand(char *args[]){
	
	//Fork
	int pid = fork();
	if(pid == 0){
		//Child, release malloc'd memory then run execvp
		clear_history();
		execvp(args[0], args);
		//External program not found
		perror(args[0]);
		exit(127);
	}else if(pid > 0){
		//Parent, wait for child and get exit status
		int status;
		wait(&status);
		return WEXITSTATUS(status);
	}else{
		//Error forking
		perror("Fork failed!");
		return 1;
	}
}
