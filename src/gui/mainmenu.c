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
    WINDOW * mainmenuwin = newwin(36,92,Y,X);
    WINDOW * controlwin = newwin(4,90,Y + 31,X+1);
    wbkgd(stdscr,COLOR_PAIR(2));
    wbkgd(mainmenuwin,COLOR_PAIR(1));
    wbkgd(controlwin,COLOR_PAIR(1));
    wattron(mainmenuwin,COLOR_PAIR(1));
    wattron(controlwin,COLOR_PAIR(1));
    box(mainmenuwin,0,0);
    box(controlwin,0,0);
    keypad(mainmenuwin,true);

    // Printing info:
    wattron(mainmenuwin,A_BOLD);
    mvwprintw(mainmenuwin,1,1,"Binary path:");
    mvwprintw(mainmenuwin,2,1,"%s",binarypath);
    mvwprintw(mainmenuwin,4,1,"IWAD path:");
    mvwprintw(mainmenuwin,5,1,"%s",iwadpath);

    wattron(controlwin,A_BOLD);
    mvwprintw(controlwin,1,1,"B - Select Binary | G - Select IWAD | RETURN - Play Doom!");
    mvwprintw(controlwin,2,1,"I - Info Screen");

    // Refreshing screen:
    refresh();
    wrefresh(mainmenuwin);
    wrefresh(controlwin);
    wrefresh(stdscr);

    // Input-output:
    userchoice = wgetch(mainmenuwin);
    switch(userchoice) {
    case 'b':
      wclear(mainmenuwin);
      wclear(controlwin);
      wrefresh(mainmenuwin);
      wrefresh(controlwin);
      delwin(mainmenuwin);
      delwin(controlwin);
      argselect(Y,X,"bins.txt",binarypath);
      break;
    case 'g':
      wclear(mainmenuwin);
      wclear(controlwin);
      wrefresh(mainmenuwin);
      wrefresh(controlwin);
      delwin(mainmenuwin);
      delwin(controlwin);
      argselect(Y,X,"iwad.txt",iwadpath);
      break;
    case 'i':
      wclear(mainmenuwin);
      wclear(controlwin);
      wrefresh(mainmenuwin);
      wrefresh(controlwin);
      delwin(mainmenuwin);
      delwin(controlwin);
      infoscreen(Y, X);
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
