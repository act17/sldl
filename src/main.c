#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sldl.h"

int main() {

  // This is the storage for the path to the binary.
  char binarypath[256];
  // This is the storage for the IWAD used.
  char iwadpath[256];
  // This is the storage for the binary.
  char binaryname[256];

  // Now we handle I/O for the rudamentary launcher:
  printf("\nPlease enter the full path to your source port/binary of choice:\n");
  scanf("%s",binarypath);

  printf("\nPlease enter the full path to your IWAD of choice:\n");
  scanf("%s",iwadpath);

  // Then we define what the binary's name is.
  binarypartitioner(binarypath, binaryname);

  printf("\n");
  printf("Binary path:\n %s \n",binarypath);
  printf("Binary name:\n %s \n",binaryname);
  printf("IWAD path:\n %s \n",iwadpath);
  printf("\n");

  // Then we set up the args used to launch the actual binary:
  char* args[4];
  args[0] = binaryname;
  args[1] = "-iwad";
  args[2] = iwadpath;
  args[3] = NULL;

  // And finally... we launch.
  execvp(binarypath, args);

  return 0;
}
