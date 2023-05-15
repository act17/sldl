#include <stdio.h>
#include <stdlib.h>

// This function checks to see if the files used by SLDL are valid.
int fileinit()
{
  char defaultname[13] = "Display Name";
  defaultname[12] = '\n';
  char defaultpath[13] = "/path/to/file";

  FILE* bins = fopen("bins.txt","r");
  if(!bins)
    {
      FILE* bins = fopen("bins.txt","w+");
      printf("\nError!\n");
      printf("bins.txt does not exist, and has been created in your directory with an example provided.\n");
      fwrite(defaultname,1,13,bins);
      fwrite(defaultpath,1,13,bins);
      fclose(bins);
      return 1;
    }

  FILE* iwad = fopen("iwad.txt","r");
  if(!iwad)
    {
      FILE* iwad = fopen("iwad.txt","w+");
      printf("\nError!\n");
      printf("iwad.txt does not exist, and has been created in your directory with an example provided.\n");
      fwrite(defaultname,1,13,iwad);
      fwrite(defaultpath,1,13,iwad);
      fclose(iwad);
      return 1;
    }

  fclose(iwad);
  fclose(bins);
  return 0;
}
