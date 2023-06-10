#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function ensures that all non-"\0" entries in args are next to eachother
// E.g. args[0] = "A" args[1] = "\0" args[2] = "B" -> args[1] = "B" args[2] = "\0"
void argumentcollapser(char** args, int size)
{

  char* buffer = malloc(sizeof(char) * 64);
  char* argstorage[size];
  int currentarg = 0;

  for(int i = 0; i < size; i++) {
    argstorage[i] = malloc(sizeof(char) * 64);
    if(args[i][0] != '\0') {
      strcpy(argstorage[currentarg],args[i]);
      currentarg++;
    }
  }

  for(int i = currentarg; i < size; i++)
    strcpy(argstorage[i],"\0");

  for(int i = 0; i < size; i++) {
    strcpy(args[i],argstorage[i]);
    free(argstorage[i]);
  }
  free(buffer);
  return;
}

// This function takes arguments specified in prev.txt, and writes to the passed char*s
// the contents of prev.txt.
void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters)
{
  FILE* file = fopen("prev.txt", "r");

  if(!file)
    return;

  char* buffer = malloc(sizeof(char) * 64);
  char* blank = '\0';

  if(fgets(buffer, 64, file) ==  NULL)
    strcpy(binarypath,blank);
  for(int i = 0; buffer[i] != '\0'; i++) {
    if(buffer[i] == '\n')
      buffer[i] = '\0';
  }
  strcpy(binarypath,buffer);

  if(fgets(buffer, 64, file) ==  NULL)
    strcpy(iwadpath,blank);
  for(int i = 0; buffer[i] != '\0'; i++) {
    if(buffer[i] == '\n')
      buffer[i] = '\0';
  }
  strcpy(iwadpath,buffer);

  for(int i = 0; i < 12; i++) {
    if(fgets(buffer, 64, file) ==  NULL)
      strcpy(pwads[i],blank);
    for(int i = 0; buffer[i] != '\0'; i++) {
      if(buffer[i] == '\n')
        buffer[i] = '\0';
    }
    strcpy(pwads[i],buffer);
  }

  for(int i = 0; i < 12; i++) {
    if(fgets(buffer, 64, file) ==  NULL)
      strcpy(parameters[i],blank);
    for(int i = 0; buffer[i] != '\0'; i++) {
      if(buffer[i] == '\n')
        buffer[i] = '\0';
    }
    strcpy(parameters[i],buffer);
  }

  free(buffer);
  fclose(file);
  return;
}

// This function takes the passed char*s and writes them to prev.txt.
void argumentsaver(char* binarypath, char* iwadpath, char** pwads, char** parameters)
{
  FILE* file = fopen("prev.txt", "w+");
  char* buffer = "\n";

  fwrite(binarypath,1,strlen(binarypath),file);
  fwrite(buffer,1,1,file);
  fwrite(iwadpath,1,strlen(iwadpath),file);
  fwrite(buffer,1,1,file);

  for(int i = 0; i < 12; i++) {
    fwrite(pwads[i],1,strlen(pwads[i]),file);
    fwrite(buffer,1,1,file);
  }
  for(int i = 0; i < 12; i++) {
    fwrite(parameters[i],1,strlen(parameters[i]),file);
    fwrite(buffer,1,1,file);
  }

  fclose(file);
  return;
}

// This function takes binarypath and returns the actual name of the binary.
// E.g. "/home/bins/bin" becomes "bin".
void binarypartitioner(char* binarypath, char* binaryname)
{
  int binarynamelength = 0;
  for(int i = strlen(binarypath); binarypath[i] != '/'; i--)
    binarynamelength++;

  binaryname[0] = '.';
  for(int i = 0; i < binarynamelength + 2; i++)
    binaryname[i + 1] = binarypath[strlen(binarypath) - binarynamelength + i];

  return;
}

// This function checks to see if the files used by SLDL are valid.
int fileinit()
{
  int returnvalue = 0;
  char defaultname[13] = "Display Name";
  char defaultpath[13] = "/path/to/file";
  defaultname[12] = '\n';


  FILE* bins = fopen("bins.txt","r");
  if(!bins) {
    FILE* bins = fopen("bins.txt","w+");
    printf("\nError!\n");
    printf("bins.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,bins);
    fwrite(defaultpath,1,13,bins);
    fclose(bins);
    returnvalue++;
  } else
    fclose(bins);

  FILE* iwad = fopen("iwad.txt","r");
  if(!iwad) {
    FILE* iwad = fopen("iwad.txt","w+");
    printf("\nError!\n");
    printf("iwad.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,iwad);
    fwrite(defaultpath,1,13,iwad);
    fclose(iwad);
    returnvalue++;
  } else
    fclose(iwad);

  FILE* pwad = fopen("pwad.txt","r");
  if(!pwad) {
    FILE* pwad = fopen("pwad.txt","w+");
    printf("\nError!\n");
    printf("pwad.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,pwad);
    fwrite(defaultpath,1,13,pwad);
    fclose(pwad);
    returnvalue++;
  } else
    fclose(pwad);

  return returnvalue;
}

// This function simply returns 1 if the path is invalid.
int filevalidcheck(char* path)
{
  FILE* file = fopen(path,"r");

  if(!file)
    return 1;

  fclose(file);
  return 0;
}
