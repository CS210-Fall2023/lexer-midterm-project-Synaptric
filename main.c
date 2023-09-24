#include <stdio.h>
#include "lexer.h"

int main()
{
    const char *File;
    const char *accssesMode;
    char mystring;

    File = "files/hello_world.ccx";
    accssesMode = "r";

    FILE *fptr = fopen(File, accssesMode);

    if (NULL == fptr)
    {
        printf("file can't be opened \n");
    }
    

    do {
    
    mystring =fgetc(fptr);


    printf("%c",mystring);

    }while(mystring != EOF);


    

     fclose(fptr);

    return 0;
}
