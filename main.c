#include <stdio.h>
#include "lexer.h"

int main()
{
    const char *File;
    const char *accssesMode;
    int mystring;

    File = "files/hello_world.ccx"; //Test file for the program 
    accssesMode = "r";

    FILE *fptr = fopen(File, accssesMode);

    if (NULL == fptr)
    {
        printf("file can't be opened \n");
    }

    while ((mystring = fgetc(fptr)) != EOF)
    {

        printf("%c", mystring);
    }

    fclose(fptr);


    getcomments(File);

  const char *Ofile ="Testfile.txt";

    lexitKey(Ofile);

    return 0;
}
