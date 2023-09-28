#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
void getcomments(const char *file);

void lexitKey(const char *Ofile);
void getComment(int testChar,FILE *fptr,const char *Ofile);

void lexitOp(const char *Ofile);

int lexitDig(FILE *Iptr,char Digchar ,FILE *Optr);

void skipComment(FILE *Sptr,char testChar,FILE *Optr);
void skipString(FILE *Sptr,char testChar,FILE *Optr);
void skipStringLit(FILE *Sptr,char testChar,FILE *Optr);

void skipAnser(FILE *Iptr,char Digchar ,FILE *Optr);



#endif