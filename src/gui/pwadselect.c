#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void pwadselect(int Y, int X, char** pwads, char* pwadname)
{
  char* buffer = malloc(sizeof(char) * 64);
  int choice = 0;
  int highlight = 0;

  while(choice != 'q') {
    WINDOW * mainwin = newwin(36,92,Y,X);
    WINDOW * listwin = newwin(8,90,Y+1,X+1);
    WINDOW * controlwin = newwin(4,90,Y+31,X+1);
    wbkgd(mainwin,COLOR_PAIR(1));
    wbkgd(listwin,COLOR_PAIR(3));
    wbkgd(controlwin,COLOR_PAIR(1));
    wattron(mainwin,COLOR_PAIR(1));
    wattron(listwin,COLOR_PAIR(3));
    wattron(controlwin,COLOR_PAIR(1));
    box(mainwin,0,0);
    box(listwin,0,0);
    box(controlwin,0,0);
    keypad(mainwin,true);
    wattron(controlwin,A_BOLD);
    mvwprintw(controlwin,1,1,"Up/Down - Select PWAD | Return - Enter PWAD");
    mvwprintw(controlwin,2,1,"D - Delete PWAD | C - Clear PWADs | Q - Exit");
    wrefresh(mainwin);
    wrefresh(controlwin);

    for(int i = 0; i < 6; i++) {
      if(i == highlight)
        wattron(listwin,A_REVERSE);
      mvwprintw(listwin,i+1,3,"                                                        ");
      mvwprintw(listwin,i+1,1,"%d: %s",i,pwads[i * 2 + 1]);
      wattroff(listwin,A_REVERSE);
    }
    wrefresh(listwin);
    wrefresh(stdscr);

    choice = wgetch(mainwin);
    switch(choice) {
    case KEY_UP:
      if(highlight == 0)
        break;
      highlight--;
      break;
    case KEY_DOWN:
      if(highlight == 5)
        break;
      highlight++;
      break;
    case 'd':
      strcpy(pwads[highlight * 2 + 1],"\0");
      break;
    case 'c':
      for(int i = 0; i < 6; i++)
        strcpy(pwads[i * 2 + 1],"\0");
      break;
    case 10:
      argselect(Y,X,pwadname,buffer);
      strcpy(pwads[highlight * 2 + 1],buffer);
      break;
    case 'q':
      break;
    default:
      break;
    }
  }

  char* pwadbuffer[6];
  for(int i = 0; i < 6; i++) {
    pwadbuffer[i] = malloc(sizeof(char) * 64);
    strcpy(pwadbuffer[i],pwads[i * 2 + 1]);
  }

  argumentcollapser(pwadbuffer,6);

  for(int i = 0; i < 6; i++) {
    strcpy(pwads[i * 2 + 1],pwadbuffer[i]);
    free(pwadbuffer[i]);
  }

  free(buffer);
  return;
}
