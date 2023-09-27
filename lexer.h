#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void getcomments(const char *file);

void lexitKey(const char *Ofile);
void getComment(int testChar,FILE *fptr,const char *Ofile);

void lexitOp(const char *Ofile);

void skipComment(FILE *Sptr,char testChar,FILE *Optr);



#endif