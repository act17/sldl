#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sldl.h"

int main() {

  // Current/Alpha setup for arguments:
  char* args[4];
  args[0] = malloc(sizeof(char) * 64);
  args[1] = "-iwad";
  args[2] = malloc(sizeof(char) * 64);
  args[3] = NULL;

  // Getting the screen size, checking for errors, returning in case of size being too small.
  int Y,X;
  initscr();
  start_color();
  getmaxyx(stdscr,Y,X);
  noecho();
  if(Y < 36 || X < 92) {
    endwin();
    printf("\nError: Screen size too small.");
    printf("\nMinimum:	36-Y	92-X");
    printf("\nYours:	%d-Y	%d-X",Y,X);
    return 1;
  }

  // Setting Y/X to being the position of the windows.
  Y = (Y - 36) / 2;
  X = (X - 92) / 2;

  // Now we run the Main Menu Loop.
  mainmenu(Y,X,args);
  clear();
  refresh();
  endwin();

  // When done, args[] should have all arguments filled in.
  // We then need to process the binary name from the path.
  char* binarypath = malloc(64);
  strcpy(binarypath, args[0]);

  binarypartitioner(binarypath, args[0]);

  printf("\nPre-launch check:");
  printf("\n\nPath to binary:\n%s",binarypath);
  printf("\nList of args:");
  for(int i = 0; args[i] != NULL; i++)
    printf("\narg[%d]:	%s",i,args[i]);

  execvp(binarypath, args);

  // Freeing memory (duh)
  free(binarypath);
  free(args[0]);
  free(args[2]);
  return 0;
}
