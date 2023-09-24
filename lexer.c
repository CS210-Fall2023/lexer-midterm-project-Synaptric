#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getcomments(const char *file)
{

    FILE *fptr;
    FILE *Ofile;
    int testChar;
    char delim = ' ';

    fptr = fopen(file, "r");

    Ofile = fopen("Testfile.txt", "w");

    if (NULL == fptr)
    {
        printf("file can't be opened \n");
    }

    while ((testChar = getc(fptr)) != EOF)
    {

        if (testChar == '/')
        {
            testChar = getc(fptr);

            if (testChar == '*')
            {
                fprintf(Ofile, "/*");

                do
                {
                    testChar = getc(fptr);
                    fprintf(Ofile, "%c", testChar);

                } while (testChar != '*' || (testChar = getc(fptr)) != '/' || testChar == EOF); // Code used to print out hte comments

                printf("*/(comment)\n");
            }
            else
            {
                ungetc(testChar, fptr);
            }
        }
        else if (testChar == '"') // statement used to sperate strings into their own lines.
        {
            fprintf(Ofile, "\n");

            fprintf(Ofile, "%c", testChar); // prints the first "
            testChar = getc(fptr);          // Gets the next letter

            while (testChar != '"')
            {

                fprintf(Ofile, "%c", testChar); // prints it
                testChar = getc(fptr);          // gets next leter
            }

            fprintf(Ofile, "%c", testChar); // prints final "
            fprintf(Ofile, "(string)");
            fprintf(Ofile, "\n");
            testChar = getc(fptr);
        }

        if (testChar == delim || testChar == '\n')
        {
            fprintf(Ofile, "\n");
            while ((testChar = getc(fptr)) == delim)
            {
                ;
            }
            ungetc(testChar, fptr);
        }
        else
        {
            fprintf(Ofile, "%c", testChar);
        }
    }

    fclose(Ofile);
}

/*
    Function created to try and find the keywords in the text


*/
void lexit(FILE *Ofptr) // accepts the file being worked on
{
    Ofptr = fopen("testfile.txt", "W+");

    int Ktest;
    char Keywords[37][10] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function"
                                                                                                                                           "if",
                             "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                             "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};

    while ((Ktest = fgetc(Ofptr)) != EOF)
    {
        int Back=0;
        for (int i = 0; i < 37; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (Ktest == Keywords[i][j] && Keywords[i][j] != '\0')
                {
                    
                }
                else
                {
                    Back++;
                }
            }
        }
    }
}


