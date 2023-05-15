#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void mainmenu(int Y, int X, char** args, int* quitcheck)
{

  // Initializing variables:
  char* binarypath = malloc(sizeof(char) * 64);
  char* iwadpath = malloc(sizeof(char) * 64);

  // Loop that controls when mainmenu() is to stop,
  // allows for recreation of appearance.
  int userchoice = 0;
  int goodcheck = -1;
  while(1)
    {

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
      mvwprintw(controlwin,2,1,"I - Info Screen | Q - Quit SLDL");

      // Printing error info in case of unfilled arguments.
      if(goodcheck == 0)
        {
          wattron(mainmenuwin,COLOR_PAIR(4));
          wattron(mainmenuwin,A_BOLD);
          mvwprintw(mainmenuwin,30,1,"ERROR: BINARY/IWAD IS NOT FILLED!");
          wattron(mainmenuwin,COLOR_PAIR(1));
          wattroff(mainmenuwin,A_BOLD);
        }

      // Refreshing screen:
      refresh();
      wrefresh(mainmenuwin);
      wrefresh(controlwin);
      wrefresh(stdscr);

      // Input-output:
      userchoice = wgetch(mainmenuwin);
      switch(userchoice)
        {
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
      if(userchoice == 10)
        {
          if(binarypath[0] == '\0' || iwadpath[0] == '\0')
            goodcheck = 0;
          else
            goodcheck = 1;
        }

      if(goodcheck == 1)
        break;
    }

  // Exporting (Only occurs when 'q' is not specified):
  if(userchoice != 'q')
    {
      strcpy(args[0],binarypath);
      strcpy(args[2],iwadpath);
    }

  // Freeing memory:
  free(binarypath);
  free(iwadpath);

  return;
}
