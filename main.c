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

    char *File = calloc(strlen(argv[1]), sizeof(char));

    char *EndFile = calloc(strlen(argv[1])+8, sizeof(char)); //Allocating space for the file brought in and the file brought out 

    strcpy(File, argv[1]);

    strcat(EndFile, File); //
    strcat(EndFile, ".lexer");

    const char *accssesMode;

    // File = "files/hello_world.ccx"; //Test file for the program
    accssesMode = "r";

    FILE *fptr = fopen(File, accssesMode);

    // FILE *EndPtr =fopen(File,"w");

    if (NULL == fptr)
    {
        printf("file can't be opened \n");
    }

    fclose(fptr);

    startLexer(File);

    // const char *Ofile ="Testfile.txt";
    lexitKey("Testfile.txt");
    lexitOp("Testfile2.txt",EndFile);

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




    I need to fix this method so that it doesn't skip things in parnetheses or make a method to avoid writing things in the panrethes.s


    // I need to rewrite this as a series of Boolean values

*/