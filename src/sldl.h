#ifndef __SLDL_H
#define __SLDL_H

int fileinit();
int filevalidcheck(char* path);
void binarypartitioner(char* binarypath, char* binaryname);
void argumentsaver(char* binarypath, char* iwadpath, char** pwads, char** parameters, char* basedir);
void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters, char* basedir);
void argumentcollapser(char** args, int size);

void mainmenu(int Y, int X, char** args, int* quitcheck, char* basedir);
void argselect(int Y, int X, char* filename, char* arg);
void pwadselect(int Y, int X, char** pwads,char* pwadname);
void paraselect(int Y, int X, char** parameters);
void infoscreen(int Y, int X);
void homedirsetup(char* dir);

#define VERSION_ID "Release 1.3.0"
#define VERSION_DATE "2023/09/09"

#endif
