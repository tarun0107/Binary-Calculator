#ifndef MAIN_SUPPL_FUNS
#define MAIN_SUPPL_FUNS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct snode {
    int data;
    struct snode *next;
}snode;
typedef struct integer{
    snode *head;
    int len;
    int par;
    int dec;
}integer;
void initi(integer *a);
void length(integer *a);
void addDigit(integer *a, char c);
integer copy(integer a);
integer Createintegerfromstring(char *str);
void printInteger(integer a);
void freeInteger(integer *a);
int compare(integer a, integer b);
void match(integer *a, integer *b);
void reverse(integer *a);
void addPrev(integer *a, char c);
integer INTMIN();
integer subtraction(integer *a, integer *b);
integer addition(integer *a, integer *b);
integer multiplication(integer *a, integer *b);
int value(integer a);
integer division(integer *a, integer *b);
integer mod(integer *a, integer *b);
integer power(integer *a, integer *b);



typedef struct inode{
    integer a;
    struct inode *next;
}inode;
typedef inode* istack;
void initistack(istack *s);
void ipush(istack *s, integer a);
integer ipop(istack *s);
int iisempty(istack *s);
typedef struct cnode{
    char ch;
    struct cnode *nex;
}cnode;
typedef cnode* cstack;
void init(cstack *s1);
void push(cstack *s1, char ch);
char pop(cstack *s1);
int isempty(cstack *s1);

#endif
