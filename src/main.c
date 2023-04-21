#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sldl.h"

int main() {

  // First thing we need to do is open the files relating to configuration.
  FILE* binsfilepath = fopen("bins.txt", "r");
  FILE* iwadfilepath = fopen("iwad.txt", "r");

  // Do some rudementary error handling - brush up on this in the future.
  if(binsfilepath == NULL) {
    printf("\nError! bins.txt does not exist.");
    return 1;
  }
  if(iwadfilepath == NULL) {
    printf("\nError! iwad.txt does not exist.");
    return 1;
  }

  // And then we call the variables that make up our binary and our IWAD.
  char binary[64];
  char iwad[64];
  char argone[16];

  // We first define our Binary.
  printf("\nPlease select your binary:");
  argumentparser(binsfilepath, binary);
  // Then we define our IWAD.
  printf("\nPlease select your IWAD:");
  argumentparser(iwadfilepath, iwad);
  // We run the Binary's path through our parser:
  binarypartitioner(binary, argone);
  // And we set up our args:
  char* args[4];
  args[0] = argone;
  args[1] = "-iwad";
  args[2] = iwad;
  args[3] = NULL;
  // Close our files down:
  fclose(binsfilepath);
  fclose(iwadfilepath);

  // Print out the nessicary information for diagnosis of what we're launching:
  printf("\n\nBinary:	%s",binary);
  printf("\nIwad:	%s",iwad);
  for(int i = 0; i < 4; i++)
    printf("\nargv[%d]:		%s",i,args[i]);

  // And launch:
  execvp(binary, args);
  return 0;
}
