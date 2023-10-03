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

    char *File = calloc(strlen(argv[1] + 8), sizeof(char));
     char *EndFile = calloc(strlen(argv[1] + 8), sizeof(char));

    strcpy(File, argv[1]);
     strcpy(EndFile, argv[1]);
    const char *accssesMode;
    int mystring;

    // File = "files/hello_world.ccx"; //Test file for the program
    accssesMode = "r";

    FILE *fptr = fopen(File, accssesMode);

    //    strcat(EndFile, ".lexer");
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
    free(EndFile);
    return 0;
}

/*
    Program checks copies everyhting from one file into another file

    The first file created will seperate comments,strings,charchter literals,and numerics  and create a second file

    This second file will contain the () statements to identify the lexers

    Then it will find keywords and lexers

    Then it will create the final file  that highlets operators


    the primary issue that I have right now is needing to skip over the  statemtns without rewriting thme


    I need to fix this method so that it doesn't skip things in parnetheses or make a method to avoid writing things in the panrethes.s


    // I need to rewrite this as a series of Boolean values

*/