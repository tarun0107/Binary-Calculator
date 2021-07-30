/*#ifndef MAIN_SUPPL_FUNS
#define MAIN_SUPPL_FUNS
#include<stdio.h>
#include"integer.h"
#include<stdlib.h>

typedef struct inode{
    integer a;
    struct inode* next;
}inode;
typedef inode* istack;
void INITistack(istack *s);
void PUSHistack(istack *s, integer a);
integer POPistack(istack *s);
int isEMPTYistack(istack *s);
typedef struct cnode{
    char ch;
    struct cnode* next;
}cnode;
typedef cnode* cstack;
void init(cstack *s1);
void push(cstack *s1, char ch);
char pop(cstack *s1);
int isempty(cstack *s1);

#endif*/
