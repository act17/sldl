#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters)
{
  FILE* file = fopen("prev.txt", "r");

  char* buffer = malloc(sizeof(char) * 64);

  fgets(buffer, 64, file);
  for(int i = 0; buffer[i] != '\0'; i++) {
    if(buffer[i] == '\n')
      buffer[i] = '\0';
  }
  strcpy(binarypath,buffer);

  fgets(buffer, 64, file);
  for(int i = 0; buffer[i] != '\0'; i++) {
    if(buffer[i] == '\n')
      buffer[i] = '\0';
  }
  strcpy(iwadpath,buffer);

  for(int i = 0; i < 12; i++) {
    fgets(buffer, 64, file);
    for(int i = 0; buffer[i] != '\0'; i++) {
      if(buffer[i] == '\n')
        buffer[i] = '\0';
    }
    strcpy(pwads[i],buffer);
  }

  for(int i = 0; i < 12; i++) {
    fgets(buffer, 64, file);
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
