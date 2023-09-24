#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getcomments(const char *file)
{

    FILE *fptr;
    // char *buffer;
    int testChar;
    //char delim = ' ';
    // int status;
    // int buffersize = 70;

    // buffer = (char *)malloc(buffersize * sizeof(char));

    fptr = fopen(file, "r");

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
                printf("/*");
                do
                {
                    testChar = getc(fptr);
                    printf("%c", testChar);

                } while (testChar != '*' || (testChar = getc(fptr)) != '/' || testChar == EOF);

                printf("*/(comment)\n");
            }
            else
            {
                ungetc(testChar, fptr);
            }
        }
        
        else
        {
            Arrange(testChar,fptr);
        }
    }
}
 void Arrange(int AChar,FILE *fptr)
 {
    char delim =' ';
    if (AChar == delim || AChar == '\n')
    {
        printf("\n");
        while ((AChar = getc(fptr)) == delim)
        {
            ;
        }
        ungetc(AChar, fptr);
    }
        else if (AChar == '(' || AChar == ')')
        {
            printf("\n");
            printf("%c", AChar);
            printf("\n");
        }
    else if (AChar == ';')
    {
        printf("\n");
        printf("%c", AChar);
    }
    else
    {
        printf("%c", AChar);
        if ((AChar = getc(fptr)) == ':')
        {
            printf("\n");
            printf("%c", AChar);
        }
        else
        {
            ungetc(AChar, fptr);
        }
    }
 }
    
