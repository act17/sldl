#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../sldl.h"

void mainmenu(int Y, int X, char** args, int* quitcheck)
{
  char* binarypath = malloc(sizeof(char) * 64);
  char* iwadpath = malloc(sizeof(char) * 64);
  char* filepara = "-file";
  char* pwads[12];
  char* parameters[12];
  int pwadcount = 3;
  int userchoice = 0;
  int goodcheck = -1;

  for(int i = 0; i < 12; i++) {
    pwads[i] = malloc(sizeof(char) * 64);
    pwads[i][0] = '\0';
    parameters[i] = malloc(sizeof(char) * 64);
    parameters[i][0] = '\0';
  }
  for(int i = 0; i < 12; i = i + 2)
    strcpy(pwads[i],filepara);

  FILE * file = fopen("prev.txt","r");
  if(file) {
    argumentreader(binarypath, iwadpath, pwads, parameters);
    fclose(file);
  }

  // Loop that controls when mainmenu() is to stop,
  // allows for recreation of appearance.
  while(1) {
    noecho();
    WINDOW * mainmenuwin = newwin(36,92,Y,X);
    WINDOW * binswin = newwin(3,90,Y+1,X+1);
    WINDOW * iwadwin = newwin(3,90,Y+4,X+1);
    WINDOW * pwadwin = newwin(9,90,Y+7,X+1);
    WINDOW * parawin = newwin(15,90,Y+16,X+1);
    WINDOW * controlwin = newwin(4,90,Y + 31,X+1);
    wbkgd(stdscr,COLOR_PAIR(2));
    wbkgd(mainmenuwin,COLOR_PAIR(1));
    wbkgd(binswin,COLOR_PAIR(1));
    wbkgd(iwadwin,COLOR_PAIR(1));
    wbkgd(pwadwin,COLOR_PAIR(1));
    wbkgd(parawin,COLOR_PAIR(1));
    wbkgd(controlwin,COLOR_PAIR(1));
    wattron(mainmenuwin,COLOR_PAIR(1));
    wattron(binswin,COLOR_PAIR(1));
    wattron(iwadwin,COLOR_PAIR(1));
    wattron(pwadwin,COLOR_PAIR(1));
    wattron(parawin,COLOR_PAIR(1));
    wattron(controlwin,COLOR_PAIR(1));
    box(mainmenuwin,0,0);
    box(binswin,0,0);
    box(iwadwin,0,0);
    box(pwadwin,0,0);
    box(parawin,0,0);
    box(controlwin,0,0);
    keypad(mainmenuwin,true);

    wattron(binswin,A_BOLD);
    wattron(iwadwin,A_BOLD);
    wattron(pwadwin,A_BOLD);
    wattron(parawin,A_BOLD);
    wattron(controlwin,A_BOLD);
    if(goodcheck == 0) {
      wattron(binswin,COLOR_PAIR(4));
      wattron(iwadwin,COLOR_PAIR(4));
    }
    mvwprintw(binswin,1,1,"Binary path:");
    mvwprintw(iwadwin,1,1,"IWAD path:");
    wattron(binswin,COLOR_PAIR(1));
    wattron(iwadwin,COLOR_PAIR(1));
    mvwprintw(pwadwin,1,1,"PWAD paths:");
    mvwprintw(parawin,1,1,"Extra Parameters:");
    wattroff(binswin,A_BOLD);
    wattroff(iwadwin,A_BOLD);
    wattroff(pwadwin,A_BOLD);
    wattroff(parawin,A_BOLD);

    mvwprintw(binswin,1,14,"%s",binarypath);
    mvwprintw(iwadwin,1,14,"%s",iwadpath);
    for(int i = 0; i < 6; i++)
      mvwprintw(pwadwin,i + 2,1,"%d: %s",i,pwads[i * 2 + 1]);
    for(int i = 0; i < 12; i++)
      mvwprintw(parawin,i + 2,1,"%d: %s",i,parameters[i]);
    mvwprintw(controlwin,1,1,"B - Select Binary | I - Select IWAD | P - Select PWADs | A - Enter Parameters");
    mvwprintw(controlwin,2,1,"RETURN - Play Doom! | SPACE - Info Screen | Q - Quit SLDL");

    refresh();
    wrefresh(mainmenuwin);
    wrefresh(binswin);
    wrefresh(iwadwin);
    wrefresh(pwadwin);
    wrefresh(parawin);
    wrefresh(controlwin);
    wrefresh(stdscr);

    userchoice = wgetch(mainmenuwin);
    switch(userchoice) {
    case 'b':
      argselect(Y,X,"bins.txt",binarypath);
      break;
    case 'i':
      argselect(Y,X,"iwad.txt",iwadpath);
      break;
    case 'p':
      pwadselect(Y,X,pwads);
      break;
    case 'a':
      paraselect(Y,X,parameters);
      break;
    case 32:
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

    // In the case that the user selects 'q' to quit, we exit the loop immediately.
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

  // This routine writes all arguments into the proper char**.
  if(userchoice == 10) {
    strcpy(args[0],binarypath);
    strcpy(args[2],iwadpath);

    for(int i = 0; pwads[i][0] != '\0'; i++) {
      if(pwads[i + 1][0] == '\0')
        break;
      strcpy(args[i + 3],pwads[i]);
      pwadcount++;
    }

    for(int i = 0 ; parameters[i][0] != '\0'; i++)
      strcpy(args[pwadcount + i],parameters[i]);

    argumentsaver(binarypath,iwadpath,pwads,parameters);
  }

  free(binarypath);
  free(iwadpath);
  for(int i = 0; i < 12; i++) {
    free(pwads[i]);
    free(parameters[i]);
  }

  return;
}
