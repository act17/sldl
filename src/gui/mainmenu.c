#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void mainmenu(int Y, int X, char** args) {

  // Initializing variables:
  char* binarypath = malloc(64);
  char* iwadpath = malloc(64);

  // Loop that controls when mainmenu() is to stop,
  // allows for recreation of appearance.
  int userchoice = 0;
  while(userchoice != 10) {

    // Initializing screen:
    noecho();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_CYAN,COLOR_CYAN);
    WINDOW * mainmenuwin = newwin(36,92,Y,X);
    wbkgd(stdscr,COLOR_PAIR(2));
    wbkgd(mainmenuwin,COLOR_PAIR(1));
    wattron(mainmenuwin,COLOR_PAIR(1));
    box(mainmenuwin,0,0);
    keypad(mainmenuwin,true);

    // Printing info:
    wattron(mainmenuwin,A_BOLD);
    mvwprintw(mainmenuwin,1,1,"Binary path:");
    mvwprintw(mainmenuwin,2,1,"%s",binarypath);
    mvwprintw(mainmenuwin,4,1,"IWAD path:");
    mvwprintw(mainmenuwin,5,1,"%s",iwadpath);

    wattron(mainmenuwin,A_REVERSE);
    mvwprintw(mainmenuwin,33,1,"CONTROLS:");
    mvwprintw(mainmenuwin,34,1,"B - Select Binary | I - Select IWAD | RETURN - Play Doom!");
    wattroff(mainmenuwin,A_BOLD);
    wattroff(mainmenuwin,A_REVERSE);

    // Refreshing screen:
    refresh();
    wrefresh(mainmenuwin);
    wrefresh(stdscr);

    // Input-output:
    userchoice = wgetch(mainmenuwin);
    switch(userchoice) {
    case 'b':
      wclear(mainmenuwin);
      wrefresh(mainmenuwin);
      delwin(mainmenuwin);
      argselect(Y,X,"bins.txt",binarypath);
      break;
    case 'i':
      wclear(mainmenuwin);
      wrefresh(mainmenuwin);
      delwin(mainmenuwin);
      argselect(Y,X,"iwad.txt",iwadpath);
      break;
    case 10:
      break;
    default:
      break;
    }

  }

  // Exporting and freeing memory:
  strcpy(args[0],binarypath);
  strcpy(args[2],iwadpath);
  free(binarypath);
  free(iwadpath);

  return;
}
