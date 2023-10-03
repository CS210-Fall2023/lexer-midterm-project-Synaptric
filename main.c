#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[])
{

    printf("Program name is: %s", argv[0]);

    if (argc == 1)
        printf("\nNo Extra Command Line Argument Passed "
               "Other Than Program Name");

    if (argc >= 2)
    {
        printf("\nNumber Of Arguments Passed: %d", argc);
        printf("\n----Following Are The Command Line "
               "Arguments Passed----");
        for (int i = 0; i < argc; i++)
            printf("\nargv[%d]: %s", i, argv[i]);
    }

    char *File = calloc(strlen(argv[1] + 8), sizeof(char)); // This is just for testing proupose to workon the logic of the file.
    strcpy(File, argv[1]);
    const char *accssesMode;
    int mystring;

    // File = "files/hello_world.ccx"; //Test file for the program
    accssesMode = "r";

    FILE *fptr = fopen(File, accssesMode);

    //char *EndFile = strcat(File, ".lexer");
    // FILE *EndPtr =fopen(File,"w");

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

    // const char *Ofile ="Testfile.txt";
    lexitKey("Testfile.txt");
    lexitOp("Testfile2.txt");

    free(File);
    return 0;
}

/*
    How to actaulyl search and paste the machine


        Create a function to check if the area is a coment / string     check if string every time a new pass is made

        scan and check for symbols  and write them

        then check keywords

        then check ints

        then check the final


*/