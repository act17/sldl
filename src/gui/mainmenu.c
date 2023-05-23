#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void mainmenu(int Y, int X, char** args, int* quitcheck)
{

  // Initializing variables:
  char* binarypath = malloc(sizeof(char) * 64);
  char* iwadpath = malloc(sizeof(char) * 64);
  char* parameter = malloc(sizeof(char) * 256);
  int extraargcount = 3;

  // Loop that controls when mainmenu() is to stop,
  // allows for recreation of appearance.
  int userchoice = 0;
  int goodcheck = -1;
  while(1) {

    // Initializing screen:
    noecho();
    WINDOW * mainmenuwin = newwin(36,92,Y,X);
    WINDOW * binswin = newwin(3,90,Y+1,X+1);
    WINDOW * iwadwin = newwin(3,90,Y+4,X+1);
    WINDOW * parawin = newwin(13,90,Y+7,X+1);
    WINDOW * controlwin = newwin(4,90,Y + 31,X+1);
    wbkgd(stdscr,COLOR_PAIR(2));
    wbkgd(mainmenuwin,COLOR_PAIR(1));
    wbkgd(binswin,COLOR_PAIR(1));
    wbkgd(iwadwin,COLOR_PAIR(1));
    wbkgd(parawin,COLOR_PAIR(1));
    wbkgd(controlwin,COLOR_PAIR(1));

    wattron(mainmenuwin,COLOR_PAIR(1));
    wattron(binswin,COLOR_PAIR(1));
    wattron(iwadwin,COLOR_PAIR(1));
    wattron(parawin,COLOR_PAIR(1));
    wattron(controlwin,COLOR_PAIR(1));

    box(mainmenuwin,0,0);
    box(binswin,0,0);
    box(iwadwin,0,0);
    box(parawin,0,0);
    box(controlwin,0,0);
    keypad(mainmenuwin,true);

    // Printing info:
    wattron(binswin,A_BOLD);
    wattron(iwadwin,A_BOLD);
    wattron(parawin,A_BOLD);
    wattron(controlwin,A_BOLD);
    mvwprintw(binswin,1,1,"Binary path:");
    mvwprintw(iwadwin,1,1,"IWAD path:");
    mvwprintw(parawin,1,1,"Extra Parameters:");
    wattroff(binswin,A_BOLD);
    wattroff(iwadwin,A_BOLD);
    wattroff(parawin,A_BOLD);
    mvwprintw(binswin,1,14,"%s",binarypath);
    mvwprintw(iwadwin,1,14,"%s",iwadpath);
    for(int i = 0; i < 10; i++)
      mvwprintw(parawin,i + 2,1,"%d: %s",i,args[i + 3]);
    mvwprintw(controlwin,1,1,"B - Select Binary | G - Select IWAD | P - Enter Parameters");
    mvwprintw(controlwin,2,1,"RETURN - Play Doom! | I - Info Screen | Q - Quit SLDL");

    // Printing error info in case of unfilled arguments.
    if(goodcheck == 0) {
      wattron(mainmenuwin,COLOR_PAIR(4));
      wattron(mainmenuwin,A_BOLD);
      mvwprintw(mainmenuwin,30,1,"ERROR: BINARY/IWAD IS NOT FILLED!");
      wattron(mainmenuwin,COLOR_PAIR(1));
      wattroff(mainmenuwin,A_BOLD);
    }

    // Refreshing screen:
    refresh();
    wrefresh(mainmenuwin);
    wrefresh(binswin);
    wrefresh(iwadwin);
    wrefresh(parawin);
    wrefresh(controlwin);
    wrefresh(stdscr);

    // Input-output:
    userchoice = wgetch(mainmenuwin);
    switch(userchoice) {
    case 'b':
      argselect(Y,X,"bins.txt",binarypath);
      break;
    case 'g':
      argselect(Y,X,"iwad.txt",iwadpath);
      break;
    case 'p':
      echo();
      mvwscanw(parawin,extraargcount - 1,4,"%s",parameter);
      strcpy(args[extraargcount],parameter);
      extraargcount++;
      noecho();
      break;
    case 'i':
      infoscreen(Y, X);
      break;
    case 'q':
      *quitcheck = 1;
      break;
    case 10:
      break;
    default:
      break;
    }

    // In the case that the user selects 'Q' to quit, we exit the loop immediately.
    if(userchoice == 'q')
      break;

    // However, in the case that the user selects RETURN, then we have to do a check
    // to see if Binary and IWAD arguments are filled.
    if(userchoice == 10) {
      if(binarypath[0] == '\0' || iwadpath[0] == '\0')
        goodcheck = 0;
      else
        goodcheck = 1;
    }

    if(goodcheck == 1)
      break;
  }

  // Exporting main arguments:
  if(userchoice != 'q') {
    strcpy(args[0],binarypath);
    strcpy(args[2],iwadpath);
  }

  // Freeing memory:
  free(binarypath);
  free(iwadpath);
  free(parameter);

  return;
}
