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

	//If list is full, free old cmd, clear old exit status
	if(elementsAdded >= MAXHISTORY){
		free(history[writeIndex]->cmd);
		history[writeIndex]->exitStatus = -1;
	}else{
		//If list is not full, initialize history[writeIndex]
		init_history(writeIndex);
	}
	//add new cmd to history[writeIndex]
	history[writeIndex]->cmd = strndup(c, strlen(c));
	history[writeIndex]->exitStatus = exit;
	
	//increment elementsAdded and writeIndex
	elementsAdded++;
	inc_writeIndex();
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
	int initReadIdx = readIndex;

	//for length of history array unless you hit an empty element
	for(int i = 0; i < MAXHISTORY &&
			history[readIndex] != NULL; i++){
		printf("%d [%d] %s\n",
				commandNumber++, //increment number after print
				history[readIndex]->exitStatus,
				history[readIndex]->cmd);
		inc_readIndex();
	}
	//Reset readIndex to original value
	readIndex = initReadIdx;
}
//---------------------------------------------------------------
//inc_writeIndex: increments the write index for circular history 
//				  array.
//---------------------------------------------------------------
void inc_writeIndex(void){
	if(writeIndex == MAXHISTORY - 1)
		writeIndex = 0;
	else
		writeIndex++;
}

//---------------------------------------------------------------
//inc_readIndex: increments the read index for circular history
//               array
//---------------------------------------------------------------
void inc_readIndex(void){
	if(readIndex == MAXHISTORY - 1)
		readIndex = 0;
	else
		readIndex++;
}
