#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void paraselect(int Y, int X, char** parameters)
{
  char* buffer = malloc(sizeof(char) * 64);
  int choice = 0;
  int highlight = 0;

  WINDOW * mainwin = newwin(36,92,Y,X);
  WINDOW * listwin = newwin(14,90,Y+1,X+1);
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
  mvwprintw(controlwin,1,1,"Up/Down - Select Parameter | Return - Enter Parameter");
  mvwprintw(controlwin,2,1,"D - Delete Parameter | C - Clear Parameters | Q - Exit");
  wrefresh(mainwin);
  wrefresh(controlwin);

  while(choice != 'q') {
    for(int i = 0; i < 12; i++) {
      if(i == highlight)
        wattron(listwin,A_REVERSE);
      mvwprintw(listwin,i+1,1,"%d: %s                                              ",i,parameters[i]);
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
      if(highlight == 12)
        break;
      highlight++;
      break;
    case 'd':
      strcpy(parameters[highlight],"\0");
      break;
    case 'c':
      for(int i = 0; i < 12; i++)
        strcpy(parameters[i],"\0");
      break;
    case 10:
      echo();
      mvwscanw(listwin,highlight+1,4,"%s",buffer);
      strcpy(parameters[highlight],buffer);
      noecho();
      break;
    case 'q':
      break;
    default:
      break;
    }
  }


  argumentcollapser(parameters,12);

  free(buffer);
  return;
}
