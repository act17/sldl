#include <stdio.h>
#include <stdlib.h>

// This function checks to see if the files used by SLDL are valid.
int fileinit()
{
  int returnvalue = 0;
  char defaultname[13] = "Display Name";
  char defaultpath[13] = "/path/to/file";
  defaultname[12] = '\n';


  FILE* bins = fopen("bins.txt","r");
  if(!bins) {
    FILE* bins = fopen("bins.txt","w+");
    printf("\nError!\n");
    printf("bins.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,bins);
    fwrite(defaultpath,1,13,bins);
    fclose(bins);
    returnvalue++;
  } else
    fclose(bins);

  FILE* iwad = fopen("iwad.txt","r");
  if(!iwad) {
    FILE* iwad = fopen("iwad.txt","w+");
    printf("\nError!\n");
    printf("iwad.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,iwad);
    fwrite(defaultpath,1,13,iwad);
    fclose(iwad);
    returnvalue++;
  } else
    fclose(iwad);

  FILE* pwad = fopen("pwad.txt","r");
  if(!pwad) {
    FILE* pwad = fopen("pwad.txt","w+");
    printf("\nError!\n");
    printf("pwad.txt does not exist, and has been created in your directory with an example provided.\n");
    fwrite(defaultname,1,13,pwad);
    fwrite(defaultpath,1,13,pwad);
    fclose(pwad);
    returnvalue++;
  } else
    fclose(pwad);

  return returnvalue;
}
