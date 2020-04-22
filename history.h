//---------------------------------------------------------------------------
//history.h : contains struct Cmd
//			  history function prototypes
//
//Author: Anthony Baird 3/7/20
//---------------------------------------------------------------------------

#ifndef HISTORY
#define HISTORY

#define MAXHISTORY 10
#include "smash.h"
struct Cmd{//struct to hold commands
	char *cmd;
	int exitStatus;
};
void init_history(int); //Builds data structures for recording cmd history
void add_history(char *cmd, int exitStatus); //Adds an entry to history
void clear_history(void); //Frees all malloc'd memory in history
void print_history(void); //Prints history to stdout
int nextIndex(int); //Gets next index in circular history array
#endif
