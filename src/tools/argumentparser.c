#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Currently, this function presents all the options
// in the file given, and then alters argument to reflect
// the one selected by the user. In the future, this will likely
// be changed to exclusively determine the argument the user
// wishes to give.
void argumentparser(FILE* filestream, char* argument) {
  // First step is to call a series of strings for the sake of
  // accessing them down the road:
  char argumentstorage[16][64];
  // And we have a buffer for storing the current result of fgets():
  char buffer[64];
  // We call an int used in the for-loop below to count the number of
  // entries the current text file has:
  int i = 0;
  // Then we write the information to the storage:
  for( ; strcmp(argumentstorage[i],argumentstorage[i - 1]) != 0; i++) {
    fgets(buffer, 64, filestream);
    memcpy(argumentstorage[i], buffer, 64);
  }
  // Then we have this for-loop that goes up by twos. It only prints the
  // names of the entries.
  for(int a = 0; a < i; a = a + 2)
    printf("\n%s",argumentstorage[a]);

  // This is to be deleted; it simply takes the number of the entry
  // the user would like to use.
  int choice;
  printf("\nEnter your selection:	");
  scanf("%d",&choice);


  // Then we copy the information.
  memcpy(argument,argumentstorage[choice],64);
  // And then we go through each element of argument, and replace '\n' with '\0',
  // and '\0' with NULL.
  for(int i = 0; argument[i] != '\0'; i++)
    if(argument[i] == '\n')
      argument[i] = '\0';

  // And then we dip out of this hell of a function and pray for it to work.
  return;
}
// I really shouldn't have smoked that shit before doing this.
