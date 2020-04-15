//--------------------------------------------------------------
//history.c : contains functionality for history command
//
//Author: Anthony Baird 3/9/20
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
int elementsAdded = 0;
static struct Cmd *history[MAXHISTORY];
//--------------------------------------------------------------
//init_history: allocates memory for and initializes elements
//				of history array
//--------------------------------------------------------------
void init_history(void){
	for(int i=0; i<MAXHISTORY; i++){
		//allocate mem for structs
		history[i] = malloc(sizeof(struct Cmd));
		//allocate mem for char* inside structs
		history[i]->cmd = malloc(MAXLINE);
		//Initialize exit status
		history[i]->exitStatus = -1;
		//Initialize all of cmd to '\0'
		memset(history[i]->cmd, '\0', MAXLINE);
	}
}
//--------------------------------------------------------------
//add_history: adds a command to the history array
//			   if full, removes first, moves elements,
//			   and adds new entry at the end
//			   does not add command to history if it is identical
//			   to the previous command
//--------------------------------------------------------------
void add_history(char *c, int exit){

	//Calculate index of last element in history
	int lastIndex = elementsAdded < MAXHISTORY ? elementsAdded - 1 : MAXHISTORY - 1;
	

	//If list is full
	if(lastIndex == MAXHISTORY - 1){
			
		//save pointer to first cmd's mem loc
		char* tmp = history[0]->cmd;
			
		//move elements and pointers from history[1-last] to
		//history[0-second to last]
		for(int i=0; i<MAXHISTORY-1; i++){
			history[i]->cmd = history[i+1]->cmd;
			history[i]->exitStatus = history[i+1]->exitStatus;
		}
		//assign original malloc'd mem from history[0] to
		//history[MAXHISTORY-1]
		history[lastIndex]->cmd = tmp;
		
		//re-initialize h[last]->cmd to '\0'
		memset(history[lastIndex]->cmd, '\0', MAXLINE);
	}
	//if lastIndex is not in the last spot, increment it
	if(lastIndex < 9){
		lastIndex++;			
	}
	//add new cmd to h[lastIndex]
	if(strcmp(c, "") != 0)
	strncpy(history[lastIndex]->cmd, c, strlen(c));
	history[lastIndex]->exitStatus = exit;
	//increment elementsAdded
	elementsAdded++;
}

//--------------------------------------------------------------
//clear_history: frees all malloc'd memory in history
//--------------------------------------------------------------
void clear_history(void){
	for(int i=0; i < MAXHISTORY; i++){
		free(history[i]->cmd);
		free(history[i]);
	}
}
//--------------------------------------------------------------
//print_history: prints the items in history to stdout
//--------------------------------------------------------------
void print_history(int firstSequenceNumber){
	//for length of history array unless you hit an empty element
	for(int i = 0; i < MAXHISTORY &&
			history[i]->exitStatus != -1; i++){
		printf("%d [%d] %s\n",
				firstSequenceNumber++, //increment number after print
				history[i]->exitStatus,
				history[i]->cmd);
	}
}
