#include <stdio.h>
#include <string.h>

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
