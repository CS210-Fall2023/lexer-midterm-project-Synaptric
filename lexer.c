#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getcomments(const char *file)
{

    FILE *fptr;
    FILE *Ofile;
    char testChar;
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
        else if (testChar == '\'') // statement used to sperate string literals into their own lines.
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

        // Find strings

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

        // If it is is a space or new line charchter
        // Add a new line to seperated things
        else if (testChar == delim || testChar == '\n')
        {
            fprintf(Ofile, "\n");
            while ((testChar = getc(fptr)) == delim || testChar == '\n')
            {
                ;
            }
            ungetc(testChar, fptr);
        }

        // Else paste the charchter to the new file.
        else
        {
            int Digtest = lexitDig(fptr, testChar, Ofile);
            if (Digtest == 1)
            {
                fprintf(Ofile, " (Numeric)\n");
            }
            else
            {
                fprintf(Ofile, "%c", testChar);
            }
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

    int isKeyword = -5; // To test if the word is a keyoerd or not

    // In order to find the keywords and the identifer

    // Build the word
    //  Test if it is a keyword

    // If it is not a keyword
    //  check if the next charchter is not letter
    //  If charchter is an underscore or digit keep going until it is not an underscore or a digit

    // print the charchter

    int keyValue = -1;

    while ((Ktest = fgetc(Ofptr)) != EOF)
    {
        fprintf(Zfptr, "%c", Ktest);
        keyValue = -1;
        skipComment(Ofptr, Ktest, Zfptr);
        skipString(Ofptr, Ktest, Zfptr);

        if (Ktest > 96 && Ktest < 123)
        {
            keyValue = 0;

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
                            keyValue = 1;
                            if ((Ktest = fgetc(Ofptr)) != '\n' || ' ') // If the keyword is not a
                            {
                                fprintf(Zfptr, "\n");
                                ungetc(Ktest, Ofptr);
                                break;
                            }
                            else
                            {
                                ungetc(Ktest, Ofptr);
                                break; // Break statements so it doesn't have to test the whole array evertime.
                            }
                        }
                    }
                    else
                    {

                        fprintf(Zfptr, "(keyword)");
                        keyValue = 1;
                        if ((Ktest = fgetc(Ofptr)) != '\n') // If the keyword is not a
                        {
                            fprintf(Zfptr, "\n");
                            ungetc(Ktest, Ofptr);
                            break;
                        }
                        else
                        {
                            ungetc(Ktest, Ofptr);
                            break;
                        }
                    }
                }
                // // If true then print the string or something like that
            }
            if (keyValue == 0)
            {
                if ((Ktest = fgetc(Ofptr)) < 97 || Ktest > 122)
                {
                    if (Ktest == '_' || isdigit(Ktest))
                    {
                        while (Ktest == '_' || isdigit(Ktest) || isalpha(Ktest))
                        {
                            fprintf(Zfptr, "%c", Ktest);
                            Ktest = fgetc(Ofptr);
                        }

                        fprintf(Zfptr, " (identifer)");
                        if(Ktest != '\n')
                        {
                            fprintf(Zfptr,"\n");
                        }

                        fprintf(Zfptr, "%c", Ktest);
                    }
                    else
                    {
                        fprintf(Zfptr, " (identifer)");
                          if(Ktest != '\n')
                        {
                            fprintf(Zfptr,"\n");
                        }
                        fprintf(Zfptr, "%c", Ktest);
                    }
                }
                else
                {
                    ungetc(Ktest, Ofptr);
                }
            }
        }
        // If it is not longer a letter clear the word
        else
        {
            strcpy(word, "");
        }
    }
}

void lexitOp(const char *Ofile)
{
    FILE *Ofptr = fopen(Ofile, "r+");
    FILE *Pfptr = fopen("test3.txt", "w");

    // Make a string and allocated up to ten memory locations for it.
    // Need to make sure that it doesn't start with a null terminator so I can add things to it and compare it with string cmpr.
    char Ktest;
    char *Opcodes[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":",
                         "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};

    // int isKeyword = -5;

    while ((Ktest = fgetc(Ofptr)) != EOF)
    {
        fprintf(Pfptr, "%c", Ktest);
        skipComment(Ofptr, Ktest, Pfptr);
        skipString(Ofptr, Ktest, Pfptr);

        for (int i = 0; i < 25; i++)
        {
            if (Ktest == *Opcodes[i])
            {
                if (Ktest == '<')
                {
                    if ((Ktest = fgetc(Ofptr)) == '<')
                    {
                        fprintf(Pfptr, "%c", Ktest);

                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else if (Ktest == '>')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else if (Ktest == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                }
                else if (Ktest == '>')
                {

                    if ((Ktest = fgetc(Ofptr)) == '>')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }

                    else if (Ktest == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }
                else if (Ktest == '.')
                {

                    if ((Ktest = fgetc(Ofptr)) == '.')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }
                else if (Ktest == ':')
                {

                    if ((Ktest = fgetc(Ofptr)) == ':')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }

                else if (Ktest == '*')
                {

                    if ((Ktest = fgetc(Ofptr)) == '*')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }

                else if (Ktest == '!')
                {

                    if ((Ktest = fgetc(Ofptr)) == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }
                else if (Ktest == '=')
                {

                    if ((Ktest = fgetc(Ofptr)) == '>')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, "(opcode)\n");
                    }
                    else
                    {
                        ;
                    }
                }

                else
                {
                    fprintf(Pfptr, "(opcode)\n");
                }
            }
        }
    }
}

void skipComment(FILE *Sptr, char testChar, FILE *Optr)
{
    if (testChar == '/')
    {

        testChar = getc(Sptr);

        if (testChar == '*')
        {
            fprintf(Optr, "*");

            do
            {
                testChar = getc(Sptr);
                fprintf(Optr, "%c", testChar);

            } while (((testChar != '*') || (testChar = getc(Sptr)) != '/')); // Code used to print out hte comments
            fprintf(Optr, "/");
            ungetc(testChar, Sptr);
            testChar = getc(Sptr);
        }
        else
        {
            fprintf(Optr, "%c", testChar);

            ungetc(testChar, Sptr);
        }
    }
}

int lexitDig(FILE *Iptr, char Digchar, FILE *Optr)
{
    if (isdigit(Digchar))
    {
        while (isdigit(Digchar) || Digchar == '#' || Digchar == '.')
        {
            if (Digchar == '.')
            {
                if ((Digchar = getc(Iptr)) == '.')

                {
                    ungetc(Digchar, Iptr);
                }
                else
                {
                    ungetc(Digchar, Iptr);
                    fprintf(Optr, "%c", Digchar);
                }
            }
            else
            {
                fprintf(Optr, "%c", Digchar);
            }
            Digchar = fgetc(Iptr);
        }
        fseek(Iptr, -1, SEEK_CUR);
        return 1;
    }
    else
    {
        return 0;
    }
}
void skipString(FILE *Sptr, char testChar, FILE *Optr) // Used to try and skip strings when checking for things
{
    if (testChar == '"') // statement used to sperate strings
    {

        testChar = getc(Sptr); // Gets the next letter

        while (testChar != '"')
        {

            fprintf(Optr, "%c", testChar); // prints it
            testChar = getc(Sptr);         // gets next leter
        }

        fprintf(Optr, "%c", testChar); // prints final "
    }
}

void skipStringLit(FILE *Sptr, char testChar, FILE *Optr)
{
    if (testChar == '\'') // statement used to sperate strings
    {

        testChar = getc(Sptr); // Gets the next letter

        while (testChar != '\'')
        {

            fprintf(Optr, "%c", testChar); // prints it
            testChar = getc(Sptr);         // gets next leter
        }

        fprintf(Optr, "%c", testChar); // prints final "
    }
}

/*

void skipAnser(FILE *Sptr, char testChar, FILE *Optr)
{
    // Only to be used by functions that look for  ( or  letters
    if(testChar == '(')
    {
         char word[50];
            char *Keywords[7] = {"string","comment","numeric","keyword","string literal","opcode","identifer" };

        while((testChar = getc(Sptr)) != ')')
        {
            strncat(word, &testChar, 1);
            for(int i=0; i<8; i++)
            {

            }
        }
    }
    // Check if there is a (   if there is then check to see if the opcode letters follow them
}
*/