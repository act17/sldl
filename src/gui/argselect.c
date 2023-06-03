#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

// This function allows the user to select an argument.
void argselect(int Y, int X, char* filename, char* arg)
{
  FILE* file = fopen(filename,"r");
  char* arguments[256];
  for(int i = 0; i < 256; i++)
    arguments[i] = malloc(sizeof(char) * 64);
  char* buffer = malloc(sizeof(char) * 64);
  char* blank = "\0";
  int linecount = 0;
  int choice = 0;
  int page = 0;
  int highlight = 0;
  int quitcheck = 0;
  int selectedarg = 0;
  int verticalshift = 1;

  WINDOW * argwin = newwin(36, 92, Y, X);
  WINDOW * listwin = newwin(30, 90, Y + 1, X + 1);
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

  while(feof(file) != true) {
    // This is the only line of the whole darn program that gives a warning.
    fgets(buffer,64,file);
    strcpy(arguments[linecount], buffer);
    linecount++;
  }
  fclose(file);

  wattron(controlwin,A_BOLD);
  mvwprintw(controlwin, 1, 1, "Up/Down/Return - Select Entry | Q - Return to Previous Screen");
  refresh();
  wrefresh(argwin);
  wrefresh(listwin);
  wrefresh(controlwin);
  wrefresh(stdscr);
  wattron(listwin,A_BOLD);

  // This upper-loop will only be broken when the selected argument is valid.
  while(1) {
    while(quitcheck != 1) {
      verticalshift = 1;
      for(int print = 56 * page; print <= 56 * (page + 1) - 2; print = print + 2) {
        if(print == linecount - 1)
          break;
        if((verticalshift - 1) * 2 == highlight)
          wattron(listwin,A_REVERSE);
        mvwprintw(listwin,verticalshift,1,"%s",arguments[print]);
        wattroff(listwin,A_REVERSE);
        verticalshift++;
      }

      wrefresh(listwin);
      wrefresh(stdscr);

      choice = wgetch(argwin);
      switch(choice) {

      case KEY_UP:
        if(selectedarg == 0)
          break;
        if(highlight == 56 * (page - 1) && page > 0) {
          page--;
          highlight = 56;
          for(int i = 1; i < 29; i++)
            mvwprintw(listwin,i,1,"                        ");
        }
        highlight = highlight - 2;
        selectedarg = selectedarg - 2;
        break;

      case KEY_DOWN:
        if(selectedarg == linecount - 3)
          break;
        if(highlight == 56 * (page + 1) - 2) {
          page++;
          highlight = -2;
          for(int i = 1; i < 29; i++)
            mvwprintw(listwin,i,1,"                        ");
        }
        highlight = highlight + 2;
        selectedarg = selectedarg + 2;
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

    if(choice == 'q') {
      strcpy(arg,blank);
      break;
    }

    // This routine corrects the read argument.
    strcpy(arg,arguments[selectedarg + 1]);
    for(int i = 0; arg[i] != '\0'; i++) {
      if(arg[i] == '\n')
        arg[i] = '\0';
    }

    if(filevalidcheck(arg) == 0)
      break;

    quitcheck = 0;
    choice = 0;
    wattron(argwin,COLOR_PAIR(4));
    wattron(argwin,A_BOLD);
    mvwprintw(argwin,31,1,"ERROR! Selected argument is not valid!");
    wrefresh(argwin);
    arg[0] = '\0';
  }

  for(int i = 0; i < 256; i++)
    free(arguments[i]);
  free(buffer);
  return;
}
