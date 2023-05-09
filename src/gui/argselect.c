#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

// This function allows the user to select an argument.
void argselect(int Y, int X, char* filename, char* arg) {

  // Window init:
  init_pair(3,COLOR_WHITE,COLOR_BLACK);
  WINDOW * argwin = newwin(36, 92, Y, X);
  WINDOW * listwin = newwin(18, 90, Y + 1, X + 1);
  wbkgd(argwin,COLOR_PAIR(1));
  wattron(argwin,COLOR_PAIR(1));
  wbkgd(listwin,COLOR_PAIR(3));
  wattron(listwin,COLOR_PAIR(3));
  box(argwin,0,0);
  box(listwin,0,0);
  keypad(argwin,true);

  // File-related information gathering:
  char arguments[16][64];
  char* buffer = malloc(64);
  FILE* file = fopen(filename,"r");
  int linecount = 0;

  while(feof(file) != true) {
    fgets(buffer,64,file);
    strcpy(arguments[linecount], buffer);
    linecount++;
  }

  fclose(file);

  // Printing information at bottom:
  wattron(argwin,A_BOLD);
  mvwprintw(argwin, 33, 1, "CONTROLS:");
  mvwprintw(argwin, 34, 1, "UP/DOWN/RETURN - SELECT ENTRY");

  // Refreshing:
  refresh();
  wrefresh(argwin);
  wrefresh(listwin);
  wrefresh(stdscr);

  // Input-output:
  int choice = 0;
  int highlight = 0;
  wattron(listwin,A_BOLD);
  while(choice != 10) {
    for(int i = 0; i < linecount - 1; i = i + 2) {
      if(i == highlight)
        wattron(listwin,A_REVERSE);
      mvwprintw(listwin,1 + (i / 2), 2, "%s",arguments[i]);
      wattroff(listwin,A_REVERSE);
    }

    wrefresh(listwin);
    wrefresh(stdscr);

    choice = wgetch(argwin);
    switch (choice) {
    case KEY_UP:
      if(highlight == 0)
        break;
      highlight = highlight - 2;
      break;
    case KEY_DOWN:
      if(highlight == linecount - 1)
        break;
      highlight = highlight + 2;
      break;
    default:
      break;
    }
  }

  // Then we need to run through the argument and ensure it's fixed:
  strcpy(arg,arguments[highlight + 1]);
  for(int i = 0; arg[i] != '\0'; i++) {
    if(arg[i] == '\n')
      arg[i] = '\0';
  }

  return;
}
