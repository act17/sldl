#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void mainmenu(int Y, int X, char** args) {

  // Initializing screen:
  init_pair(1,COLOR_BLACK,COLOR_WHITE);
  init_pair(2,COLOR_CYAN,COLOR_CYAN);
  WINDOW * mainmenuwin = newwin(36,92,Y,X);
  wbkgd(stdscr,COLOR_PAIR(2));
  wbkgd(mainmenuwin,COLOR_PAIR(1));
  wattron(mainmenuwin,COLOR_PAIR(1));
  box(mainmenuwin,0,0);
  refresh();
  wrefresh(stdscr);
  wrefresh(mainmenuwin);

  // I/O:
  echo();
  char binarypath[64];
  char iwadpath[64];

  wattron(mainmenuwin,A_BOLD);
  mvwprintw(mainmenuwin,2,1,"ENTER THE PATH TO THE BINARY:");
  mvwprintw(mainmenuwin,5,1,"ENTER THE PATH TO THE IWAD:");
  wrefresh(mainmenuwin);
  wattron(mainmenuwin,A_REVERSE);
  wattroff(mainmenuwin,A_BOLD);
  mvwscanw(mainmenuwin,3,1,"%s",binarypath);
  mvwscanw(mainmenuwin,6,1,"%s",iwadpath);
  wattroff(mainmenuwin,A_REVERSE);
  noecho();

  // Copying info from what's inputted to the storage.
  strcpy(args[0], binarypath);
  strcpy(args[2], iwadpath);

  return;
}
