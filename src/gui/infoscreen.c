#include <ncurses.h>

#define VERSION_ID "Beta 0.3.0"
#define VERSION_DATE "2023/05/22"

void infoscreen(int Y, int X)
{

  WINDOW * infowin = newwin(36, 92, Y, X);
  wbkgd(infowin,COLOR_PAIR(1));
  wattron(infowin,COLOR_PAIR(1));
  box(infowin,0,0);

  wattron(infowin,A_BOLD);
  mvwprintw(infowin,1,1,"SLDL - SuckLess Doom Launcher");
  mvwprintw(infowin,2,1,"%s  -  %s",VERSION_ID,VERSION_DATE);
  wattroff(infowin,A_BOLD);

  mvwprintw(infowin,5,1,"SLDL, or the SuckLess Doom Launcher, is a TUI launcher for the 1993 hit Doom. It also is");
  mvwprintw(infowin,6,1,"compatable with any game made within the Doom engine. It uses plaintext files within the");
  mvwprintw(infowin,7,1,"directory that the SLDL binary is within to identify potential source ports, IWADs,");
  mvwprintw(infowin,8,1,"and PWADs that can be launched. SLDL can also be used to append further Command-Line");
  mvwprintw(infowin,9,1,"Arguments.");

  mvwprintw(infowin,11,1,"For help, please refer to README.md.");

  mvwprintw(infowin,13,1,"SLDL is free software, covered by the GNU General Public License. There is NO warranty;");
  mvwprintw(infowin,14,1,"not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. You are welcome to");
  mvwprintw(infowin,15,1,"change and distribute copies under certain conditions. See the source for more");
  mvwprintw(infowin,16,1,"information.");

  wattron(infowin,A_REVERSE);
  mvwprintw(infowin,18,1,"STRIKE ANY KEY TO RETURN TO THE PREVIOUS SCREEN.");

  wrefresh(infowin);
  wrefresh(stdscr);
  getch();

  return;
}
