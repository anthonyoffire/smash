//---------------------------------------------------------------------------
//history.h : contains struct Cmd
//			  history function prototypes
//
//Author: Anthony Baird 3/7/20
//---------------------------------------------------------------------------

#ifndef HISTORY
#define HISTORY

#include "smash.h"
#define MAXHISTORY 10

//Struct to hold commands
struct Cmd{
	char *cmd;
	int exitStatus;
};
void init_history(void); //Builds data structures for recording cmd history
void add_history(char *cmd, int exitStatus); //Adds an entry to history
void clear_history(void); //Frees all malloc'd memory in history
void print_history(int firstSequenceNumber); //Prints history to stdout

#endif
