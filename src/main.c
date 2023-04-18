#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  // This is the storage for the path to the binary.
  char binarypath[256];
  // This is the storage for the IWAD used.
  char iwadpath[256];

  // Now we handle I/O for the rudamentary launcher:
  printf("\nPlease enter the full path to your source port/binary of choice:\n");
  scanf("%s",binarypath);

  printf("\nPlease enter the full path to your IWAD of choice:\n");
  scanf("%s",iwadpath);

  /*
    MY DISGUSTING ATTEMPT AT MAKING AN ALGORITHM THAT DETERMINES THE NAME
    OF A BINARY, GIVEN FROM A PATH.
  */

  /* 0 */
  // We store the length of binarypath as an integer.
  // We begin at one to offset the extra integer.
  int binarypathlength = 0;
  for(int i = 1; binarypath[i] != '\0'; i++)
    binarypathlength++;

  /* 1 */
  // Then we determine the length of our binary's name.
  int binarynamelength = 0;
  for(int i = binarypathlength; binarypath[i] != '/'; i--)
    binarynamelength++;

  /* 2 */
  // Then we write to a string to create the proper argument to launch the binary.
  char binaryname[binarynamelength + 2];
  binaryname[0] = '.';
  for(int i = 0; i < binarynamelength + 2; i++)
    binaryname[i + 1] = binarypath[binarypathlength - binarynamelength + i];

  printf("\n");
  printf("Binary path:\n %s \n",binarypath);
  printf("Binary name:\n %s \n",binaryname);
  printf("IWAD path:\n %s \n",iwadpath);

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
