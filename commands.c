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
//-------------------------------------------------------
//executeCommand : takes string of command and arguments, 
//				   tries to run argument, returns exit
//				   status
//-------------------------------------------------------
extern int elementsAdded;
int executeCommand(char *str){
	char str2[MAXLINE];
	strncpy(str2, str, MAXLINE);
	char* token; //holds each space-separated token
	token = strtok(str2, " ");
	int i = 0;
	char* args[2047];//max # tokens 'str' can contain = 2047
	while(token != NULL){//get tokens
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	
	if(strcmp(args[0],"exit") == 0){//handle exit command
		clear_history();//Free malloc'd memory
		exit(0);//Exit normally
	}
	if(strcmp(args[0], "history") == 0){//handle history command
		print_history(elementsAdded < MAXHISTORY ?//determine the command #
					  1 : elementsAdded - 9);
	}
	else if(strcmp(args[0],"cd") == 0){
		if(i>1){//cd command: if i==1 do nothing
			char dir[FILENAME_MAX];
			if(chdir(args[1]) == 0){
				
				//char dir[FILENAME_MAX];
				if(getcwd(dir, sizeof(dir)) != NULL){
					printf("%s\n", dir);//print new dir
				}else{
					perror("getcwd() error!");
					return 1;//Exit status 1
				}
			}else{//chdir not successful
				perror(args[1]);
				if(getcwd(dir, sizeof(dir)) != NULL)
					printf("%s\n", dir);
				else
					perror("getcwd() error!");
				return 1;//Exit status 1
			}
		}
	}else{	//Command not found
		for(int j = 0; j<i; j++){
			printf("[%d] %s\n", j, args[j]);
		}
		return 127;//Exit status 127
	}
	return 0;
}
