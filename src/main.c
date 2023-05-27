#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sldl.h"

int main()
{
  int pid;
  int status;

  char* iwadpara = "-iwad";
  char* blank = "\0";

  if(fileinit() == 1)
    return 1;

  // This loop repeats until 'q' is pressed within mainmenu();
  int quitcheck = 0;
  while(1) {

    char* args[28];
    char* binarypath = malloc(sizeof(char) * 64);
    for(int i = 0; i < 28; i++) {
      args[i] = malloc(sizeof(char) * 64);
      strcpy(args[i],blank);
    }
    strcpy(args[1],iwadpara);

    // This routine prepares Curses.
    int Y,X;
    initscr();
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_CYAN,COLOR_CYAN);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_WHITE);
    getmaxyx(stdscr,Y,X);
    noecho();
    if(Y < 36 || X < 92) {
      endwin();
      printf("\nError: Screen size too small.");
      printf("\nMinimum:	36-Y	92-X");
      printf("\nYours:	%d-Y	%d-X",Y,X);
      return 1;
    }
    noecho();

    // Setting Y/X to being the position of the windows.
    Y = (Y - 36) / 2;
    X = (X - 92) / 2;

    mainmenu(Y,X,args,&quitcheck);

    // After this point, it's expected that we exit Curses mode and reenter CLI. The following routine
    // essentially "exits" Curses.
    erase();
    refresh();
    echo();
    endwin();

    // We break the loop early and don't run Doom if the user decides to quit SLDL in mainmenu();.
    if(quitcheck == 1){
      free(binarypath);
      for(int i = 0; i < 27; i++)
        free(args[i]);
      return 0;
    }

    // When done, args[] should have all arguments filled in.
    // We then need to process the binary name from the path.
    strcpy(binarypath, args[0]);
    binarypartitioner(binarypath, args[0]);

    for(int i = 0; i < 28; i++) {
      if(args[i][0] == '\0') {
        args[i] = NULL;
        break;
      }
    }

    pid = fork();
    if(pid == 0) {
      printf("\nPre-launch check:");
      printf("\n\nPath to binary:\n%s",binarypath);
      printf("\nList of args:");
      for(int i = 0; i < 28; i++)
        printf("\narg[%d]:	%s",i,args[i]);
      printf("\n");
      execvp(binarypath, args);
    }

    waitpid(pid, &status, 0);

    free(binarypath);
    for(int i = 0; i < 27; i++)
      free(args[i]);
  }

  return 0;
}
