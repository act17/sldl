# sldl
A Curses-based Doom Launcher operating under the Suckless philosophy.

Current Version:

Release 1.3.0 | 2023/09/09



# Description

  SLDL (SuckLess Doom Launcher) is a launcher for the 1993 hit *Doom*. The major aim of SLDL is to provide a very simple and very clean experience for users wishing to play Doom, and the variety of other games made in the Doom engine (and source ports), alongside the plentiful mods made for Doom and the different games made in the Doom engine.


# Compiling

  To compile SLDL, simply navigate to the directory in which the repository is in, and run the command ``make``. It will create a binary, ``sldl``, which is the program.

  You will need the packages for NCurses - both running and development.


# Usage

  Currently, the usage of SLDL is as follows:

  - Step 0. Compile SLDL (Or run a premade binary.)
  - Step 1. Run SLDL.
  - Step 2. Edit the files used to extrapolate binaries, located within ``~/.config/sldl/``.

  *File: ~/.config/sldl/bins.txt*
  ```
  Crispy Doom
  /home/user/games/doom/crispy-doom
  GZDoom
  /home/user/games/gzdoom/gzdoom
  ```

  *File: ~/.config/sldl/iwad.txt*
  ```
  Doom II: Hell on Earth
  /home/user/games/doom/doom2.wad
  ```

  - Step 3. Run ``sldl`` and follow onscreen instructions to play Doom.


# Changelog

  Release 1.3.0 (2023/09/09)
  - Added new feature: one home to the configuration files.
    - Config files are stored in ``~/.config/sldl``.
    - Added a new function: ``void homedirsetup(char* dir)``. It will take the home directory, concate it with ``/.config/sldl``, and then create that directory if not yet created. It writes this full directory to ``char* dir``, which is used as a reference to where different information files are stored.
  - Altered ``sldl.h`` to reflect the changes with this new system. Changes are also seen in ``main.c``, ``mainmenu.c``, ``argselect.c``, and ``pwadselect.c``.
  - Added a safety check in ``paraselect.c`` to prevent buffer overflows.

  Release 1.2.0 (2023/07/16)
  - Modified ``paraselect()``.
    - Fixed issues with string handling. Null and duplicate entry prevention measures have been implemented to ensure whitespaces in particular don't completely kaibosh the parameter selection process.
    - Added new features - shifting parameters.
      - Pressing 'w' will shift a parameter up. Pressing 's' will shift a parameter down.
      
  Release 1.1.0 (2023/06/10)
  - Added new feature: argument collapsing.
    - Before this version, if you entered information in the 0th PWAD slot, the 1st PWAD slot, and the 4th PWAD slot, only the 0th and 1st would be loaded. Now, PWADs and parameters are collapsed.
    - This is done by the way of a new function in ``tools.c``: ``void argumentcollapser(char** args, int size)``. It's included at the end of ``pwadselect()`` and ``paraselect()``. Headers in ``sldl.h`` have been added.
  - Altered ``mainmenu()``. Removed ``char* filepara``, as I realized it was unnessicary. Also switched up how ``char* pwads[12]`` are initialized: ``pwads[0]`` is set to ``-file``, and every subsequent second entry (2,4,6...) is set to ``-merge``. This is to permit the actual loading of other files.
  - ``main()``, ``pwadselect()``, and ``paraselect()`` have all had unnessicary ``char*``s used to set certain entries in ``char**``s to certain values (E.g. ``-iwad`` in ``main()``, or the usage of ``char* blank`` wholesale). They now simply copy the raw string as opposed to what essentially amounts to a glorified pointer.
  - Fixed bug in ``paraselect()`` where a missing ``break`` caused accidental deletion of parameters.

  Release 1.0.1 (2023/06/04)
  - Collapsed all files in ``./src/tools/`` into a single new file; ``./src/tools.c``. Comments have been added above each function to briefly describe their purpose.
  - Re-configured the algorithm in ``argselect()`` for writing information from the specified file to the ``char**`` ``arguments``. Now uses a new ``char*``, ``safeguard``, to check if we've reached the end of the file. The ``while()`` loop, which now ensures that no more than 256 arguments are provided to prevent an overflow with the use of ``linecount``, breaks. This prevents a bug, and gets rid of an annoying warning.
  - ``./Makefile`` has been altered to account for the new file, the removal of several files, and the apparent elimination of all potential warnings.

  Release 1.0.0 (2023/06/02)
  - Fixed bug when transitioning from ``argselect()`` to its calling function (``mainmenu()`` or ``pwadselect()``).
    - If 'q' is specified, it now assures that ``arg`` is set to ``\0``.
  - Added semi-feature wherein if the IWAD or Binary isn't filled, their respective text will be printed in red to alert the user.
  - Altered ``Makefile``:
    - Target ``debug`` has been added. It compiles the program with ``-Werror`` and ``-g``. The regular ``sldl`` target compiles with ``-O2``. Target ``dclean`` has been also added.
    - Formatting has been fiddled around with again.
  - In ``argreader()``, there was a few lines that gave me a warning. There's now a system that prevents ``argreader()`` from writing ``NULL`` to arguments. There's also a line in ``argselect()`` that gives the same warning. I can't find a "fix" that doesn't completely break the darn thing.
  - All files have been re-formatted with ``astyle``.
  - Version/Date of Release have been moved to ``./src/sldl.h``. A cute little ASCII Cacodemon I made has been added to ``infoscreen()``.

  Version Beta 0.7.0 (2023/06/01)
  - Added new feature: Pages!
    - ``argselect()``'s system for printing potential arguments. Not only has the buffer for potential arguments been increased from 64 to 256, but also there's a myroid of new variables. ``int page`` is used to determine the page that the user is on, which results in any argument past the 54th line to be properly printed on a new page. ``int verticalshift`` is now used in the place of ``(i / 2)`` in the calls of ``mvwprintw()`` in the ``for()`` loop. A whole bunch of other hackery has been implemented to make the system work, but it works - thank God.
  - ``main.c``'s use of ``fileinit()``, and ``fileinit()`` itself has changed. All three vital ``.txt`` files are created in one go as opposed to one at a time.

  Version Beta 0.6.0 (2023/05/29)
  - Added new feature - saved arguments!
    - This is done by way of two new functions, one that saves arguments - ``void argumentsaver(char* binarypath, char* iwadpath, char** pwads, char** parameters)`` - and one that reads these arguments - ``void argumentreader(char* binarypath, char* iwadpath, char** pwads, char** parameters)``.
    - Arguments aren't saved from ``main()``'s ``args``, rather, they're saved from ``mainmenu()``'s pre-arguments. It's done this way beause all of this is handled in ``mainmenu()``. Upon telling ``mainmenu()`` to run Doom by striking RETURN, ``argumentsaver()`` is ran after the arguments are written to ``args``. Upon running ``mainmenu()``, however, a file called ``prev.txt`` is read, and if it exists, ``argumentreader()`` is ran.
    - ``argumentsaver()`` operates by writing ``binarypath`` to ``prev.txt``, then a newline, then writing ``iwadpath`` to ``prev.txt`` followed by a newline. This is repeated for ``pwads`` and ``parameters``.
    - ``argumentreader()`` operates by reading each line of ``prev.txt``, then altering the last character of each line to be ``\0``, and then writing it to ``binarypath``, ``iwadpath``, and all 12 elements of ``pwads`` then ``parameters``.
    - ``argumentsaver()`` is in a new file, ``./src/tools/argumentsaver.c``. ``argumentreader()`` is also in a new file, ``./src/tools/argumentreader()``.
    - ``Makefile`` and ``sldl.h`` have been updated to add the new files and headers for the new arguments respectively.
  - Changed the keybindings in ``mainmenu()``. ``i`` now selects IWADs, ``p`` now selects PWADs, ``a`` selects parameters, and ``SPACE`` views the information screen.

  Version Beta 0.5.1 (2023/05/27)
  - Fixed major bug in ``main()`` where ``char* args[]`` would have corrupted strings. This issue was fixed by means of putting the calling of the ``char**``, memory allocation of the ``char**``, memory freeing of the ``char**`` and a new method to "reset" the values of each entry within the ``char**``, all within the ``while (1)`` loop only exited upon the user selecting to exit.

  Version Beta 0.5.0 (2023/05/26)
  - Added new feature - having SLDL automatically reopen after launching Doom.
    - ``main()`` now uses ``fork()`` and ``waitpid()`` to have SLDL automatically reopen after launching Doom. Further alterations have been made to ``main()``, including when ``binarypath`` and ``args[]`` have memory allocated to them, and when the routine to exit NCurses occurs.
  - ``mainmenu()``'s massive amount of ``wclear()`` and ``wrefresh()`` routines have been removed.
  - The amount of elements in ``char* args[]`` has been reduced from 32 to 27, as to reflect all possible arguments.
  - The amount of available parameters has been increased from the unintentional 10 to the originally-inteded 12. Changes are reflected in both ``mainmenu()`` and ``paraselect()``.
  - ``paraselect()``'s "Delete" function now works.
  - Code has been "cleaned up"; redundant comments have been removed and an attempt to standardize spacing has been introduced.

  Version Beta 0.4.0 (2023/05/25)
  - Added new feature - PWADs!
  - Altered how potential arguments are called in ``main()`` and ``mainmenu()``. Instead of before, where new parameters were simply written to ``args[]`` with ``args[0]`` and ``args[2]`` being reserved for whatever was written to ``binarypath`` and ``iwadpath`` respectively, there's now two new ``char**``s; ``char* parameters[12]`` and ``char* pwads[12]``.
    - These two ``char**``s can be edited by way of two new functions: ``void pwadselect(int Y, int X, char** pwads)`` and ``void paraselect(int Y, int X, char** parameters)`` in the files ``./src/gui/pwadselect.c`` and ``./src/gui/paraselect.c`` respectively.
    - These two functions offer the ability for users to enter up to 6 PWADs and up to 12 parameters. It also permits users to delete parameters and PWADs wholesale.
    - In the case of ``pwadselect()``, it uses the already existing ``argselect()`` to choose a PWAD from ``pwad.txt``.
  - Altered ``fileinit()`` to now detect if ``pwad.txt`` is a valid file.
  - Altered ``sldl.h`` to include headers for the two new functions added.
  - Altered ``Makefile`` to include ``paraselect.c`` and ``pwadselect.c``.

  Version Beta 0.3.0 (2023/05/22)
  - Added new feature - extra parameters.
    - ``mainmenu()`` handles this feature. There's 10 extra parameters that a user can fill.
    - ``main()``'s handling of ``args[]`` has now changed. Instead of each entry of ``args[]`` above ``2`` (Which is where the binary and IWAD are found) being set to ``NULL``, they are now ``malloc()``'d and set to ``'\0'`` by default. ``main()`` now finds where the first unfilled argument is, and sets that entry to ``NULL``.
  - Fixed a bug in ``main()`` where the pre-launch check would not print out the final valid argument.

  Version Beta 0.2.2 (2023/05/16)
  - Altered ``mainmenu()`` considerably to now be more visually appealing.
  - Removed seemingly unneeded calls of ``werase()`` and similar functions in ``mainmenu()``.
  - Altered ``argselect()`` to now have controls consistent with the rest of the program.

  Version Beta 0.2.1 (2023/05/16)
  - Added new file, ``./src/tools/filevalidcheck.c``. It includes the function ``int filevalidcheck(char* path)``.
    - It's essentially a macro that performs the simple job of returning ``1`` if the file given in ``path`` is invalid, and ``0`` if it is.
    - It's used in ``argcheck()`` as a means to prevent invalid entries from being selected. In the case an entry is invalid, it will not be permitted to be selected, and a brief warning message will be printed on the bottom of the screen.
  - Added new feature, the ability to quit the argument selecting screen without entering an entry.
  - Updated headers in ``sldl.h``.
  - Added new file in ``Makefile``, and changed formatting style to K&R.
  - All ``*.c`` files have been reformatted.

  Version Beta 0.2.0 (2023/05/15)
  - Added new feature, the creation of ``bins.txt`` and ``iwad.txt`` in the case that they are not already created in the ``SLDL`` directory.
    - This is done by a new function, ``int fileinit()``. It first tries to open ``bins.txt``, and if it doesn't exist, it shall create ``bins.txt`` in the directory ``sldl`` is in, and subsequently fill it with an example of how to properly enter entries within the file. It repeats this process for ``iwad.txt``.
    - The function ``fileinit()`` is in a new file, ``src/tools/fileinit.c``.
    - ``main()`` has been updated to run ``fileinit()``, terminating the program early if ``fileinit()`` returns ``1``, indicating an absent file.
    - Headers have been added for ``fileinit.c`` in ``sldl.h``, and the file has been added to ``Makefile``.
  - Updated ``./Makefile`` to now use GNU styling for formatting.
  - All files not yet mentioned have been formatted in GNU style.

  Version Beta 0.1.2 (2023/05/13)
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
