# sldl
A Curses-based Doom Launcher operating under the Suckless philosophy.

Current Version:

Alpha 0.0.3 | 2023/04/20 (Haha, weed.)


# Description

  SLDL (SuckLess Doom Launcher) is a launcher for the 1993 hit *Doom*. The major aim of SLDL is to provide a very simple and very clean experience for users wishing to play Doom, and the variety of other games made in the Doom engine (and source ports), alongside the plentiful mods made for Doom and the different games made in the Doom engine.


# Compiling

  To compile SLDL, simply navigate to the directory in which the repository is in, and run the command ``make``. It will create a binary, ``sldl``, which is the program.


# Usage

  Currently, the usage of SLDL is as follows:

  1) Create a file where ``sldl`` is located (The binary, not the repo.) called ``bins.txt`` and ``iwad.txt``.
  2) Enter name/path information in the two .txt files, example below.
  3) Run ``sldl`` and select your Source Port/IWAD.

  *bins.txt*
  ```
  Source Port
  /path/to/source/port
  ```


# Changelog

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