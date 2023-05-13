# sldl
A Curses-based Doom Launcher operating under the Suckless philosophy.

Current Version:

Beta 0.1.2 | 2023/05/13


# Description

  SLDL (SuckLess Doom Launcher) is a launcher for the 1993 hit *Doom*. The major aim of SLDL is to provide a very simple and very clean experience for users wishing to play Doom, and the variety of other games made in the Doom engine (and source ports), alongside the plentiful mods made for Doom and the different games made in the Doom engine.


# Compiling

  To compile SLDL, simply navigate to the directory in which the repository is in, and run the command ``make``. It will create a binary, ``sldl``, which is the program.


# Usage

  Currently, the usage of SLDL is as follows:

  1)  Compile SLDL.
  2)  Make two files in the directory that the binary ``sldl`` is within; ``bins.txt`` and ``iwad.txt``.
  3)  Enter the names and paths to the binaries in ``bins.txt``, and names and paths to the IWADs in ``iwad.txt``. Refer to below for examples.

  *File: bins.txt*
  ```
  Crispy Doom
  /home/user/games/doom/crispy-doom
  GZDoom
  /home/user/games/gzdoom/gzdoom
  ```

  *File: iwad.txt*
  ```
  Doom II: Hell on Earth
  /home/user/games/doom/doom2.wad
  ```

  4) Run ``sldl`` and follow onscreen instructions to play Doom.


# Changelog

  Version Beta 0.1.2 (2023/05/09)
  - Added new feature, the ability to quit SLDL. This is made in anticipation of a new feature that will fork the process for running the DOOM binary so that launching Doom does not subsequently terminate SLDL.
    - This is done by adding a new integer in ``main()`` - ``int quitcheck``. It is passed as a pointer into ``mainmenu()``, and upon striking the ``Q`` key, will be set to ``1``, immediately terminating the process of ``mainmenu()`` and informing ``main()`` to not launch the binary of DOOM.
    - ``sldl.h`` and ``mainmenu.c`` have been updated to account for this feature.
  - Added new feature to ``mainmenu()``, a way of preventing Segfaults by checking to see if the strings ``binarypath`` and ``iwadpath`` have been filled. If they are not filled, then SLDL will try to launch DOOM using empty strings, causing a Segfault. This new check happens after striking the ``RETURN`` key, seeing if the first character of each string is equal to ``'\0'``.
    - A new function may be added in the future that checks to see if they are valid files. This may be extended into ``argselect()`` as to inform the user if Binaries, IWADs, or PWADs are given a valid path.

  Version Beta 0.1.1 (2023/05/09)
  - Added new file, ``src/gui/infoscreen.c``. Has the function ``void infoscreen(int Y, int X)``.
    - It simply displays the current version, date of version release, info about the program, and info about the GNU License.
  - Altered ``mainmenu.c`` to increase visual flair, and to add functionality with ``infoscreen()``.
  - Altered ``argselect.c`` to increase visual flair and to remove windows called by the function.
  - Added headers in ``sldl.h`` for ``infoscreen()``.
  - Added new file to ``Makefile``.

  Version Beta 0.1.0 (2023/05/09)
  - Readded the use of files.
  - Updated ``main.c`` to now work with the new system for selecting arguments.
  - Updated ``mainmenu.c`` to now include the system of selecting arguments from files.
  - Added new file: ``src/gui/argselect.c``. Includes the function ``void argselect(int Y, int X, char* filename, char* arg)``.
    - ``argselect()`` takes the information from the file specified in ``filename``, and displays the potential options. Then, the user can select an option, and it will be written to ``arg``.
  - Added headers in ``sldl.h`` to account for ``argselect.c``.
  - Added new files into ``Makefile``.

  Version Alpha 0.0.4 (2023/04/30)
  - Added NCurses support.
  - Temporarily depricated the use of files for the sake of simplifying the development process.
  - Removed ``./src/tools/argumentparser.c``, removed the heading for ``void argumentparser(FILE* filestream, char* argument)`` in ``./src/sldl.h``.
  - Added directory ``./src/gui/``
    - Currently contains one file: ``./src/gui/mainmenu.c``. It includes the function ``void mainmenu(int Y, int X, char** args)``. Will be used in the future to access other functions that allow you to select binaries, IWADs, PWADs, and other command-line arguments before running.
  - Altered ``./src/main.c`` to now handle the "higher-up" management of args used to run the program alongside NCurses initialization.
  - Altered ``./Makefile`` to reflect changes to project structure.

  Version Alpha 0.0.3 (2023/04/20)
  - Added a new feature: the usage of files (See above) to enter in pre-defined locations for arguments, hopefully speeding up the process of launching Doom in the future.
  - Added new file, ``./src/tools/argumentparser.c``. It includes the function ``void argumentparser(FILE* filestream, char* argument)``.
    - The current operation of the function is taking all the available info from ``filestream`` and putting it into an array of strings called ``argumentstorage``.
    - Then, the user is prompted to enter the entry they choose. Currently, it is *far* from working. But, it does work! I have, by entering random combinations of 0, 1, 2, and 3, have been able to somehow achieve different combinations of source port and IWAD as "intended."
    - It should be noted that the current use of ``argumentparser()`` is not something I intend to keep permanent; it will likely be changed to merely take a number, take a filename, and return out a functional ``argv[]`` value to be used by the rest of the program.
  - Updated ``sldl.h`` and ``Makefile`` to reflect the addition of a new function.
  - Updated ``./README.md``'s "Usage" section to reflect the addition of a file system.
  - Updated ``main.c`` to now reflect the changes to how arguments are taken.

  Version Alpha 0.0.2 (2023/04/18)
  - Added new directory, ``./src/tools/``.
    - Added ``./src/tools/binarypartitioner.c``. Includes the function ``void binarypartitioner(char* binarypath, char* binaryname)``. It performs a now cleaned-up algorithm for determining what the arg given by the path to a specific binary is. (E.g. path ``/games/doom/engine`` can give ``./engine``.)
  - Added file ``./src/sldl.h``. Includes headers for ``binarypartitioner()``.
  - Altered ``./src/main.c`` to no longer partition the binary path. File is much smaller as a consequence.
  - Altered ``./Makefile`` to now include the newly added file.

  Version Alpha 0.0.1 (2023/04/17)
  - Added ``./Makefile``.
  - Added ``./src/``.
    - Added ``./src/main.c``. It includes the function ``int main()``. It currently handles I/O for the path to the IWAD, the path to the source port/binary of the user's choice, the handling of all arguments, and the launching of the program. Obviously, these will be partitioned in the future.