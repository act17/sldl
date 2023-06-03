#include <ncurses.h>
#include "../sldl.h"

void infoscreen(int Y, int X)
{

  char* logo[7];
  logo[0] = " \\ ^   ^ / ";
  logo[1] = "\\ \\     / /";
  logo[2] = "|   < >   |";
  logo[3] = "| \\\\    //|";
  logo[4] = "|  \\\\||// |";
  logo[5] = "|  ///\\\\\\ |";
  logo[6] = "\\_________/";

  WINDOW * infowin = newwin(36, 92, Y, X);
  wbkgd(infowin,COLOR_PAIR(1));
  wattron(infowin,COLOR_PAIR(1));
  box(infowin,0,0);

  wattron(infowin,A_BOLD);
  mvwprintw(infowin,1,1,"SLDL - SuckLess Doom Launcher");
  mvwprintw(infowin,2,1,"%s  -  %s",VERSION_ID,VERSION_DATE);
  wattroff(infowin,A_BOLD);

  mvwprintw(infowin,3,1,"SLDL, or the SuckLess Doom Launcher, is a TUI launcher for the 1993 hit Doom. It also is");
  mvwprintw(infowin,4,1,"compatable with any game made within the Doom engine. It uses plaintext files within the");
  mvwprintw(infowin,5,1,"directory that the SLDL binary is within to identify potential source ports, IWADs,");
  mvwprintw(infowin,6,1,"and PWADs that can be launched. SLDL can also be used to append further Command-Line");
  mvwprintw(infowin,7,1,"Arguments.");

  mvwprintw(infowin,8,1,"For help, please refer to README.md.");

  mvwprintw(infowin,9,1,"SLDL is free software, covered by the GNU General Public License. There is NO warranty;");
  mvwprintw(infowin,10,1,"not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. You are welcome to");
  mvwprintw(infowin,11,1,"change and distribute copies under certain conditions. See the source for more");
  mvwprintw(infowin,12,1,"information.");

  wattron(infowin,A_REVERSE);
  mvwprintw(infowin,14,1,"STRIKE ANY KEY TO RETURN TO THE PREVIOUS SCREEN.");

  wattron(infowin,COLOR_PAIR(4));
  wattron(infowin,A_BOLD);
  wattron(infowin,A_REVERSE);
  for(int i = 0; i < 7; i++)
    mvwprintw(infowin,17 + i, 1, "%s",logo[i]);

  wrefresh(infowin);
  wrefresh(stdscr);
  getch();


  return;
}
