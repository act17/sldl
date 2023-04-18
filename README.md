# sldl
A Curses-based Doom Launcher operating under the Suckless philosophy.

Current Version:

Alpha 0.0.1 | 2023/04/17


# Description

  SLDL (SuckLess Doom Launcher) is a launcher for the 1993 hit *Doom*. The major aim of SLDL is to provide a very simple and very clean experience for users wishing to play Doom, and the variety of other games made in the Doom engine (and source ports), alongside the plentiful mods made for Doom and the different games made in the Doom engine.


# Compiling

  To compile SLDL, simply navigate to the directory in which the repository is in, and run the command ``make``. It will create a binary, ``sldl``, which is the program.


# Usage

  Currently, the usage of SLDL is as follows:

  1)  Enter the path to your source port of choice.
  2)  Enter the path to your IWAD of choice.


# Changelog

  Version Alpha 0.1.0 (2023/04/17)
  - Added ``./Makefile``.
  - Added ``./src/``.
    - Added ``./src/main.c``. It includes the function ``int main()``. It currently handles I/O for the path to the IWAD, the path to the source port/binary of the user's choice, the handling of all arguments, and the launching of the program. Obviously, these will be partitioned in the future.