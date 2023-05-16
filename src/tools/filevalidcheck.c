#include <ncurses.h>
#include <stdlib.h>

// This function simply returns 1 if the path is invalid.
int filevalidcheck(char* path)
{

  FILE* file = fopen(path,"r");

  if(!file)
    return 1;

  fclose(file);
  return 0;
}
