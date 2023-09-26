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

                fprintf(Ofile, "%c", testChar); // prints final "
                fprintf(Ofile, "(comment)");
            }
            else
            {
                ungetc(testChar, fptr);
            }
        }

        // Same program but used to create string literals I will need to alter this to be its own function
        else if (testChar == '\'') // statement used to sperate strings into their own lines.
        {
            fprintf(Ofile, "\n");

            fprintf(Ofile, "%c", testChar); // prints the first "
            testChar = getc(fptr);          // Gets the next letter

            while (testChar != '\'')
            {

                fprintf(Ofile, "%c", testChar); // prints it
                testChar = getc(fptr);          // gets next leter
            }

            fprintf(Ofile, "%c", testChar); // prints final "
            fprintf(Ofile, "(string literal)");
            fprintf(Ofile, "\n");
        }

        else if (testChar == '"') // statement used to sperate strings  literals into their own lines.
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
        }

        else if (testChar == delim || testChar == '\n')
        {
            fprintf(Ofile, "\n");
            while ((testChar = getc(fptr)) == delim || testChar == '\n')
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

void lexitKey(const char *Ofile) // accepts the file being worked on
{
    FILE *Ofptr = fopen(Ofile, "r+");
    FILE *Zfptr = fopen("test2.txt", "w");

    // Make a string and allocated up to ten memory locations for it.
    // Need to make sure that it doesn't start with a null terminator so I can add things to it and compare it with string cmpr.
    char word[50];
    char Ktest;
    char Keywords[37][10] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant",
                             "else", "elsif", "end", "exit", "function"
                                                             "if",
                             "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                             "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};

    int isKeyword = -5;

    while ((Ktest = fgetc(Ofptr)) != EOF)
    {
        fprintf(Zfptr, "%c", Ktest);
        if (Ktest > 96 && Ktest < 123)
        {

            // if true then add it to the string

            strncat(word, &Ktest, 1);

            for (int i = 0; i < 37; i++)
            {
                isKeyword = strcmp(word, Keywords[i]); // Compare the new string with every string in the Keywords

                if (isKeyword == 0)
                {
                    isKeyword = strcmp(word, "in");
                    if (isKeyword == 0)
                    {

                        if ((Ktest = fgetc(Ofptr)) == 't')
                        {
                            ungetc(Ktest, Ofptr);
                        }
                        else
                        {
                            fprintf(Zfptr, "(keyword)");
                            if ((Ktest = fgetc(Ofptr)) != '\n') // If the keyword is not a
                            {
                                fprintf(Zfptr, "\n");
                                ungetc(Ktest, Ofptr);
                            }
                            else
                            {
                                ungetc(Ktest, Ofptr);
                            }
                        }
                    }
                    else
                    {

                        fprintf(Zfptr, "(keyword)");
                        if ((Ktest = fgetc(Ofptr)) != '\n') // If the keyword is not a
                        {
                            fprintf(Zfptr, "\n");
                            ungetc(Ktest, Ofptr);
                        }
                        else
                        {
                            ungetc(Ktest, Ofptr);
                        }
                    }
                }
                // // If true then print the string or something like that
            }
        }

        else
        {
            strcpy(word, "");
        }
    }
}
