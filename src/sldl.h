#ifndef __SLDL_H
#define __SLDL_H

int fileinit();
int filevalidcheck(char* path);
void binarypartitioner(char* binarypath, char* binaryname);
void argumentsaver(char* binarypath, char* iwadpath, char** pwads, char** parameters);
void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters);

void mainmenu(int Y, int X, char** args, int* quitcheck);
void argselect(int Y, int X, char* filename, char* arg);
void pwadselect(int Y, int X, char** pwads);
void paraselect(int Y, int X, char** parameters);
void infoscreen(int Y, int X);

#define VERSION_ID "Release 1.0.0"
#define VERSION_DATE "2023/06/02"

#endif
