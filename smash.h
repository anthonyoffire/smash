//-------------------------------------------------------
//smash.h : function prototypes for commands.c
//
//Author: Anthony Baird 3/7/20
//-------------------------------------------------------

#ifndef SMASH
#define SMASH
#define MAXLINE 4096
int executeExternalCommand(char*[]);
int executeCommand(char*);
int printCwd(void);
#endif
