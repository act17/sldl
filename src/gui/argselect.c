#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

// This function allows the user to select an argument.
void argselect(int Y, int X, char* filename, char* arg)
{

  // Window init:
  init_pair(3,COLOR_WHITE,COLOR_BLACK);
  WINDOW * argwin = newwin(36, 92, Y, X);
  WINDOW * listwin = newwin(31, 90, Y + 1, X + 1);
  WINDOW * controlwin = newwin(3, 90, Y + 32, X + 1);
  wbkgd(argwin,COLOR_PAIR(1));
  wattron(argwin,COLOR_PAIR(1));
  wbkgd(listwin,COLOR_PAIR(3));
  wattron(listwin,COLOR_PAIR(3));
  wbkgd(controlwin,COLOR_PAIR(1));
  wattron(controlwin,COLOR_PAIR(1));
  box(argwin,0,0);
  box(listwin,0,0);
  box(controlwin,0,0);
  keypad(argwin,true);

  // File-related information gathering:
  char arguments[28][64];
  char* buffer = malloc(sizeof(char) * 64);
  FILE* file = fopen(filename,"r");
  int linecount = 0;

  // We gather all entries from file, and then correct them.
  while(feof(file) != true) {
    fgets(buffer,64,file);
    strcpy(arguments[linecount], buffer);
    linecount++;
  }
  fclose(file);

  // Printing information at bottom:
  wattron(controlwin,A_BOLD);
  mvwprintw(controlwin, 1, 1, "Up/Down/Return - Select Entry | Q - Return to Previous Screen");

  // Refreshing:
  refresh();
  wrefresh(argwin);
  wrefresh(listwin);
  wrefresh(controlwin);
  wrefresh(stdscr);

  // Input-output operators:
  int choice = 0;
  int highlight = 0;
  int quitcheck = 0;
  wattron(listwin,A_BOLD);

  // This upper-loop will only be broken when the selected argument is valid.
  while(1) {
    // This loop controls input-output related printing.
    while(quitcheck != 1) {
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
      case 'q':
        quitcheck = 1;
        break;
      case 10:
        quitcheck = 1;
      default:
        break;
      }
    }

    // We first check to see if 'q' was given.
    if(choice == 'q')
      break;

    // Otherwise, we see if the argument is valid after correcting it:
    strcpy(arg,arguments[highlight + 1]);
    for(int i = 0; arg[i] != '\0'; i++) {
      if(arg[i] == '\n')
        arg[i] = '\0';
    }
    if(filevalidcheck(arg) == 0)
      break;

    // In the case of invalidity, we set input variables to zero and print a warning message.
    quitcheck = 0;
    choice = 0;
    wattron(argwin,COLOR_PAIR(4));
    wattron(argwin,A_BOLD);
    mvwprintw(argwin,29,1,"ERROR! Selected argument is not valid!");
    wrefresh(argwin);
    arg[0] = '\0';
  }

  // Then we delete the windows, free memory, and return:
  wclear(argwin);
  wclear(listwin);
  wclear(controlwin);
  wrefresh(argwin);
  wrefresh(listwin);
  wrefresh(controlwin);
  delwin(argwin);
  delwin(listwin);
  delwin(controlwin);
  free(buffer);

  return;
}
