//--------------------------------------------------------------
//history.c : contains functionality for history command
//
//Author: Anthony Baird 3/9/20
//--------------------------------------------------------------
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

static int elementsAdded = 0;//Total elements added while running
static int writeIndex = 0;//Write index for circular array
static int readIndex = 0;//Read index for circular array
static struct Cmd *history[MAXHISTORY];

//--------------------------------------------------------------
//init_history: allocates memory for Cmd structure at
//				history[index], initializes exit status
//--------------------------------------------------------------
void init_history(int index){
		//allocate mem for structs
		history[index] = malloc(sizeof(struct Cmd));
		//Initialize exit status
		history[index]->exitStatus = -1;
}

//--------------------------------------------------------------
//add_history: adds a command to the circular history array.
//			   if full, frees next spot and then replaces it
//--------------------------------------------------------------
void add_history(char *c, int exit){

	//If list is full, free old cmd
	if(elementsAdded >= MAXHISTORY){
		free(history[writeIndex]->cmd);
		readIndex = nextIndex(readIndex);
	}else{
		//If list is not full, initialize history[writeIndex]
		init_history(writeIndex);
	}
	//add new cmd to history[writeIndex]
	history[writeIndex]->cmd = strndup(c, strlen(c));
	history[writeIndex]->exitStatus = exit;
	
	//increment elementsAdded and writeIndex
	elementsAdded++;
	writeIndex = nextIndex(writeIndex);
}

//--------------------------------------------------------------
//clear_history: frees all malloc'd memory in history
//--------------------------------------------------------------
void clear_history(void){
	for(int i=0; i < MAXHISTORY; i++){
		if(history[i] != NULL){
			free(history[i]->cmd);
			free(history[i]);
		}
	}
}

//--------------------------------------------------------------
//print_history: prints the items in history to stdout
//--------------------------------------------------------------
void print_history(void){
	
	//Compute first commandNumber for printing
	int commandNumber = elementsAdded < MAXHISTORY ? 
								1 : elementsAdded - 9;
	//Save initial read index
	int idx = readIndex;

	//for length of history array unless you hit an empty element
	for(int i = 0; i < MAXHISTORY &&
			history[idx] != NULL; i++){
		printf("%d [%d] %s\n",
				commandNumber++, //increment number after print
				history[idx]->exitStatus,
				history[idx]->cmd);
		idx = nextIndex(idx);
	}
}
//---------------------------------------------------------------
//nextIndex: returns next index in circular history array
//---------------------------------------------------------------
int nextIndex(int i){
	return (i+1) % MAXHISTORY;
}

