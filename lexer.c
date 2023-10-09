#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*
    Creates testfile.txt 

    It takes the original file and will find the (comments), charchter literals,numerics,and string in the file.

*/

void startLexer(const char *file) // This functions  splits the  function into lines of a file, It also speperates
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

    // Code used to elimate whitespace at the start of the program
    testChar = getc(fptr);
    if (testChar == '\n')
    {
        while ((testChar = getc(fptr)) == '\n')
        {
        }
        ungetc(testChar, fptr);
    }
    else
    {
        ungetc(testChar, fptr);
    }

    // Main program

    while ((testChar = getc(fptr)) != EOF)
    {
        /*
            This next section of the program will find comments and split them off from the main group keepign the whiespace.
        */

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

                } while (testChar != '/' || testChar == EOF); // Code used to print out hte comments

                // Aaron said that this was legal
                fprintf(Ofile, " (comment)");

                if ((testChar = fgetc(fptr)) != '\n')
                {

                    fprintf(Ofile, "\n");
                    ungetc(testChar, fptr);
                }
                else
                {
                    ungetc(testChar, fptr);
                }
            }
            else
            {
                fprintf(Ofile, "/");
                ungetc(testChar, fptr);
            }
        }

        // Same program but used to create string literals I will need to alter this to be its own function
        else if (testChar == '\'') // statement used to sperate string literals into their own lines.
        {
            fprintf(Ofile, "%c", testChar); // prints the first "
            testChar = getc(fptr);          // Gets the next letter

            while (testChar != '\'')
            {

                fprintf(Ofile, "%c", testChar); // prints it
                testChar = getc(fptr);          // gets next leter
            }

            fprintf(Ofile, "%c", testChar); // prints final "
            fprintf(Ofile, " (character literal)");

            if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
            {

                fprintf(Ofile, "\n");
                ungetc(testChar, fptr);
            }
            else
            {
                ungetc(testChar, fptr);
            }
        }

        // Find strings

        else if (testChar == '"') // statement used to sperate strings  literals into their own lines.
        {

            fprintf(Ofile, "%c", testChar); // prints the first "
            testChar = getc(fptr);          // Gets the next letter

            while (testChar != '"')
            {

                fprintf(Ofile, "%c", testChar); // prints it
                testChar = getc(fptr);          // gets next leter
            }

            fprintf(Ofile, "%c", testChar); // prints final "
            fprintf(Ofile, " (string)");
            if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
            {

                fprintf(Ofile, "\n");
                ungetc(testChar, fptr);
            }
            else
            {
                ungetc(testChar, fptr);
            }
        }

        // If it is is a space or new line charchter
        // Add a new line to seperated things
        // Else paste the charchter to the new file.

        // The issue that I am having is that I need to

        else // If it is not a comment
        {

            // check to makesure that the previous information is not an alphanumeric charhcter or _
            if ((!isalnum(testChar)) && testChar != '_')
            {
                if (testChar == delim || testChar == '\n')
                {

                    fprintf(Ofile, "\n");
                    while ((testChar = getc(fptr)) == delim || testChar == '\n')
                    {
                        ;
                    }

                    int Digtest = lexitDig(fptr, testChar, Ofile); // test to see if it is a numeric 
                    if (Digtest == 1)                              // If it is a numeric print numeric.
                    {
                        fprintf(Ofile, " (numeric literal)");
                        if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
                        {

                            fprintf(Ofile, "\n");
                            ungetc(testChar, fptr);
                        }
                        else
                        {
                            ungetc(testChar, fptr);
                        }
                    }
                    else if (Digtest == -1)
                    {
                        fprintf(Ofile, " (numeric literal)");
                        if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
                        {

                            fprintf(Ofile, "\n");
                            ungetc(testChar, fptr);
                        }
                        else
                        {
                            ungetc(testChar, fptr);
                        }
                    }

                    else
                    {
                        ungetc(testChar, fptr);
                    }
                }

                else
                {
                    fprintf(Ofile, "%c", testChar);
                    testChar = getc(fptr);
                    int Digtest = lexitDig(fptr, testChar, Ofile); // test to see if it is a numeric
                    if (Digtest == 1)                              // If it is a numeric print numeric.
                    {
                        fprintf(Ofile, " (numeric literal)");
                        if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
                        {

                            fprintf(Ofile, "\n");
                            ungetc(testChar, fptr);
                        }
                        else
                        {
                            ungetc(testChar, fptr);
                        }
                    }
                    else if (Digtest == -1)
                    {
                        fprintf(Ofile, " (numeric literal)");
                        if ((testChar = fgetc(fptr)) != '\n' && testChar != ' ')
                        {

                            fprintf(Ofile, "\n");
                            ungetc(testChar, fptr);
                        }
                        else
                        {
                            ungetc(testChar, fptr);
                        }
                    }
                    else
                    {
                        ungetc(testChar, fptr);
                    }
                }
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
    Function created to try and find the keywords and opcodes in a file

    takes testfile and returns testfile2 with keywords and opcodes



*/


void lexitKey(const char *Ofile) // accepts the file being worked on
{
    FILE *Ofptr = fopen(Ofile, "r+");
    FILE *Zfptr = fopen("Testfile2.txt", "w");

    // Make a string and allocated up to ten memory locations for it.
    // Need to make sure that it doesn't start with a null terminator so I can add things to it and compare it with string cmpr.
    char word[256];
    strcpy(word, "");
    char Ktest;
    char Keywords[37][10] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant",
                             "else", "elsif", "end", "exit", "function", "if",
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
        keyValue = -1; // Setting the key = -1  this is to test if it is an identifer
        skipComment(Ofptr, Ktest, Zfptr);
        skipString(Ofptr, Ktest, Zfptr);
        skipStringLit(Ofptr, Ktest, Zfptr);
        skipAnser(Ofptr, Ktest, Zfptr);

        if (isalpha(Ktest))
        {
            keyValue = 0;

            // if true then add it to the string

            strncat(word, &Ktest, 1);

            for (int i = 0; i < 37; i++)
            {
                isKeyword = strcmp(word, Keywords[i]); // Compare the new string with every string in the Keywords

                if (isKeyword == 0) // Checking to see if it
                {
                    isKeyword = strcmp(word, "in"); // Checking to see if stars with in first becuase there are multiple keywords that start with in
                    if (isKeyword == 0)
                    {

                        if ((Ktest = fgetc(Ofptr)) == '\n' || Ktest == ' ')

                        {
                            fprintf(Zfptr, " (keyword)");
                            keyValue = 1;
                            if ((Ktest = fgetc(Ofptr)) != '\n' || ' ') // If the keyword is not a
                            {
                                fprintf(Zfptr, "\n");
                                strcpy(word, "");
                                ungetc(Ktest, Ofptr);
                                break;
                            }
                            else
                            {
                                strcpy(word, "");
                                ungetc(Ktest, Ofptr);
                                break; // Break statements so it doesn't have to test the whole array evertime.
                            }
                        }

                        else
                        {
                            ungetc(Ktest, Ofptr);
                            keyValue = 8;
                            break;
                        }
                    }
                    else //
                    {
                        // Check to see if the word ends and there are not more letters after it .
                        Ktest = fgetc(Ofptr);
                        if (!isalnum(Ktest) && Ktest != '_')
                        {
                            ungetc(Ktest, Ofptr);
                            fprintf(Zfptr, " (keyword)");
                            keyValue = 1;
                            if ((Ktest = fgetc(Ofptr)) != '\n') // If the keyword is not a
                            {
                                strcpy(word, "");

                                fprintf(Zfptr, "\n");
                                ungetc(Ktest, Ofptr);
                                break;
                            }
                            else
                            {
                                strcpy(word, "");
                                ungetc(Ktest, Ofptr);
                                break;
                            }
                        }
                        else
                        {
                            ungetc(Ktest, Ofptr);
                        }
                    }
                }
                // // If true then print the string or something like that
            }
            if (keyValue == 0)
            {
                Ktest = fgetc(Ofptr);
                if ((!isalpha(Ktest)))
                {
                    if (Ktest == '_' || isdigit(Ktest))
                    {
                        while (Ktest == '_' || isdigit(Ktest) || isalpha(Ktest))
                        {
                            fprintf(Zfptr, "%c", Ktest);
                            Ktest = fgetc(Ofptr);
                        }

                        fprintf(Zfptr, " (identifier)");
                        if (Ktest != '\n')
                        {
                            fprintf(Zfptr, "\n");
                        }

                        strcpy(word, "");
                        fprintf(Zfptr, "%c", Ktest);
                    }
                    else
                    {
                        fprintf(Zfptr, " (identifier)");
                        if (Ktest != '\n')
                        {
                            fprintf(Zfptr, "\n");
                        }
                        strcpy(word, "");
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
    fclose(Zfptr);
}


/*

    Finds the opcodes in the writing  and makes the final file for the program

    Inputs testfile2 and ends with the .lexer file

*/

void lexitOp(const char *Ofile, char *EndFile)
{
    FILE *Ofptr = fopen(Ofile, "r");
    FILE *Pfptr = fopen(EndFile, "w");

    // rewind(Ofptr);

    if (NULL == Ofptr)
    {
        printf("file can't be opened \n");
    }

    // Make a string and allocated up to ten memory locations for it.
    // Need to make sure that it doesn't start with a null terminator so I can add things to it and compare it with string cmpr.
    char Ktest;
    char *Opcodes[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":",
                         "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};

    // int isKeyword = -5;
    while ((Ktest = fgetc(Ofptr)) != EOF)
    {
        fprintf(Pfptr, "%c", Ktest);
        if (skipComment(Ofptr, Ktest, Pfptr) == true)
        {
            Ktest = fgetc(Ofptr);
            fprintf(Pfptr, "%c", Ktest);
        }
        skipString(Ofptr, Ktest, Pfptr);
        skipStringLit(Ofptr, Ktest, Pfptr);
        skipAnser(Ofptr, Ktest, Pfptr);

        //      if (Comfirm == 1)
        //    {
        //    Ktest = fgetc(Ofptr);
        //}

        for (int i = 0; i < 25; i++)
        {

            // Section of opcodes that  in order to print things.
            if (Ktest == *Opcodes[i])
            {
                if (Ktest == '<')
                {
                    if ((Ktest = fgetc(Ofptr)) == '<') // I am reading one charhcter at a time so I after to try to finsh this
                    {
                        fprintf(Pfptr, "%c", Ktest);

                        fprintf(Pfptr, " (operator)");
                    }
                    else if (Ktest == '>')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else if (Ktest == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        fprintf(Pfptr, " (operator)");
                    }
                }
                else if (Ktest == '>')
                {

                    if ((Ktest = fgetc(Ofptr)) == '>')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }

                    else if (Ktest == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        fprintf(Pfptr, " (operator)");
                    }
                }
                else if (Ktest == '.')
                {

                    if ((Ktest = fgetc(Ofptr)) == '.')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        ungetc(Ktest, Ofptr);
                        fprintf(Pfptr, " (operator)");
                    }
                }
                else if (Ktest == ':')
                {

                    if ((Ktest = fgetc(Ofptr)) == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        fprintf(Pfptr, " (operator)");
                    }
                }

                else if (Ktest == '*')
                {

                    if ((Ktest = fgetc(Ofptr)) == '*')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        fprintf(Pfptr, " (operator)");
                    }
                }

                else if (Ktest == '!')
                {

                    if ((Ktest = fgetc(Ofptr)) == '=')
                    {
                        fprintf(Pfptr, "%c", Ktest);
                        fprintf(Pfptr, " (operator)");
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
                        fprintf(Pfptr, " (operator)");
                    }
                    else
                    {
                        fprintf(Pfptr, " (operator)");
                    }
                }

                else if (Ktest == ')')
                {
                    fprintf(Pfptr, " (operator)");
                }

                else
                {
                    fprintf(Pfptr, " (operator)");
                }

                // These are used after the main program  this is best place to put it even thouhg

                if ((Ktest = fgetc(Ofptr)) != '\n')
                {

                    fprintf(Pfptr, "\n");
                    ungetc(Ktest, Ofptr);
                    break;
                }
                else
                {
                    fprintf(Pfptr, "%c", Ktest);
                }

                // Trying to clear the spacing issue
            }
        }
    }


}

/*
    Skips the commments in a program. 
*/

bool skipComment(FILE *Sptr, char testChar, FILE *Optr)
{

    if (testChar == '/') // Checking if it is this
    {

        testChar = getc(Sptr); // If it is a / get the next to charchter to check if it is the start of a comment

        if (testChar == '*')
        {
            fprintf(Optr, "*"); // Start the comment

            do
            {
                // Print the rest of the comment
                testChar = getc(Sptr);
                fprintf(Optr, "%c", testChar);

            } while (testChar != '/'); // Code used to print out hte comments
            return true;
            // Aaron told me this is legal
        }
        else
        {
            //
            ungetc(testChar, Sptr);
            return false;
        }
    }
    else
    {
        return false;
    }
}


/*
    THis finds numeric charchters and returns a value to let it know if it is a real number . or an opcode. 



*/

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
                    ungetc(Digchar, Iptr);
                    return -1;
                }
                else
                {
                    ungetc(Digchar, Iptr);
                    fprintf(Optr, "%c", Digchar);
                    Digchar = fgetc(Iptr);
                }
            }
            else
            {
                fprintf(Optr, "%c", Digchar);
                Digchar = fgetc(Iptr);
            }
        }
        fseek(Iptr, -1, SEEK_CUR);
        return 1;
    }
    else
    {
        return 0;
    }
}
/*

    skipString 

    This function will skip the strings in the files so that I don't reprint anything 

*/
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


/*
    skips charchter literals 
    
    this way it doesn't identify identifers or opcodes in the next part of the programs. 

*/
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
    Skips the   things like (identifer)  (operator)
        This is so that it can skip these to make sure that it works. 

*/

int skipAnser(FILE *Sptr, char testChar, FILE *Optr)
{

    // Only to be used by functions that look for  ( or  letters

    int isWord = 0;
    if (testChar == ' ')
    {
        testChar = getc(Sptr);
        if (testChar == '(')
        {
            fprintf(Optr, "%c", testChar);
            while ((testChar = getc(Sptr)) != '\n')
            {
                fprintf(Optr, "%c", testChar);
            }
            fprintf(Optr, "%c", testChar);
            isWord = 1;
            return isWord;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}