/*#include"stack.h"
#include<stdio.h>
#include<stdlib.h>


void INITistack(istack *s) {
    *s = NULL;
}
void PUSHistack (istack *s, integer a) {
	inode *temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = a;
	temp->next = *s;
	*s = temp;
}
integer POPistack(istack *s) {
	integer t;
	inode *temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->next;
	free(temp);
	return t;
}
int isEMPTYistack (istack *s) {
	return NULL;
}
void init(cstack *s1) {
    *s1 = NULL;
}
void push(cstack *s1, char ch) {
    cnode *temp;
    temp = (cnode *)malloc(sizeof(cnode));
    temp->ch = ch;
    temp->next = *s1;
    *s1 = temp;
}
char pop(cstack *s1) {
    char c;
    c = (*s1)->ch;
    cnode *temp;
    temp = *s1;
    *s1 = (*s1)->next;
    free(temp);
    return c;
}
int isempty(cstack *s1) {
    return NULL;
}
*/
