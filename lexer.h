#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void getcomments(const char *file);

void Arrange(int Achar,FILE *fptr); //Used to keep the function in geting the comments from getting too big. 

#endif