#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters)
{
  FILE* file = fopen("prev.txt", "r");

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
