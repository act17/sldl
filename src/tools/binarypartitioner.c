#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function takes binarypath and returns the actual name of
// the binary.
void binarypartitioner(char* binarypath, char* binaryname) {

  // We find the length of the binary's name with the last usage of '/'.
  int binarynamelength = 0;
  for(int i = strlen(binarypath); binarypath[i] != '/'; i--)
    binarynamelength++;

  // Then we write to the binaryname string with the proper info.
  binaryname[0] = '.';
  for(int i = 0; i < binarynamelength + 2; i++)
    binaryname[i + 1] = binarypath[strlen(binarypath) - binarynamelength + i];

  return;
}
