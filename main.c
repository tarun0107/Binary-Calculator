#include <stdio.h>
#include <stdlib.h>
#include"integer.h"
#include<ctype.h>
#include<limits.h>
#include<string.h>
#define OPERAND 100
#define OPERATOR 200
#define END 300
#define ERR 400
typedef struct token {
	int type; // OPERAND, OPERATOR or END
	union data{
       integer num; // will be used if type==OPERAND
	   char op; // will e used if type == OPERATOR
       }data;
}token;
enum state { NUMBER, OP, FINISH, ERROR, SPC };
token gettoken(char *expr, int *reset) {
	static int i = 0;
    integer a;
    initi(&a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	initi(&t.data.num);
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0': case '1': case '2': case '3':
					case '4': case '5': case '6': case '7':
					case '8': case '9': case '.':
						nextstate = NUMBER;
						//printInteger(a);
						addDigit(&a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' : case '^' :
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;
                case OP:
                    switch(currchar) {
                        case '0':case '1':case '2': case '3':
                        case '4':case '5':case '6': case '7':
                        case '8':case '9':case '.':
                            t.type = OPERATOR;
                            t.data.op = expr[i - 1];
                            nextstate = NUMBER;
                            currstate = nextstate;
                            //i++;
                            return t;
                            break;
                        case '+': case '-': case '*': case '/': case '%': case  '(' : case ')' : case '^' :
                            nextstate = OP;
                            t.type = OPERATOR;
                            t.data.op = expr[i - 1];
                            currstate = nextstate;
                            i++;
                            return t;
                            break;
                        case '\0':
                            nextstate = FINISH;
                            t.type = OPERATOR;
                            t.data.op = expr[i - 1];
                            currstate = nextstate;
                            return t;
                            break;
                        case ' ':
                            nextstate = SPC;
                            t.type = OPERATOR;
                            t.data.op = expr[i - 1];
                            currstate = nextstate;
                            i++;
                            return t;
                            break;
                        default: // anything else
                            nextstate = ERROR;
                            t.type = OPERATOR;
                            t.data.op = expr[i - 1];
                            currstate = nextstate;
                            return t;
                            break;
				}
				break;
				case FINISH:
                    t.type = END;
                    return t;
                    break;
                case ERROR:
                    t.type = ERR;
                    return t;
                    break;
                case SPC:
                    switch(currchar) {
                        case '0':case '1':case '2': case '3':
                        case '4':case '5':case '6': case '7':
                        case '8':case '9':case '.':
                            addDigit(&a, currchar);
                            nextstate = NUMBER;
                            i++;
                            //printf("here2\n");
                            break;
                        case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
                        case '^':
                            nextstate = OP;
                            i++;
                            break;
                        case '\0':
                            nextstate = FINISH;
                            break;
                        case ' ':
                            nextstate = SPC;
                            i++;
                            break;
                        default: // anything else
                            nextstate = ERROR;
                            break;
				}
				currstate = nextstate;
                break;
		}
    }
}
int precedance(char o) {
	switch(o) {
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
        }
	return 5;
}
char ctop(cstack *s) {
	char ca;
	ca = pop(s);
	push(s, ca);
	return ca;
}
integer infixeval(char *expr) {
	//printf("Here\n");
	token t1;
	char prevop, currop, ch;
	integer a, b, c, z, y;
	initi(&a);
	initi(&b);
	initi(&c);
	initi(&z);
	initi(&y);
	int ctcb = 0, ctob = 0, reset = 1, prev, curr;
	istack i;
	cstack cs;
	initistack(&i);
	init(&cs);
	prev = ERR;
	while(1) {
		t1 = gettoken(expr, &reset);
		curr = t1.type;
		if(curr == prev && (prev == OPERAND || prev == OPERATOR)) {
            printf("Syntax Error\n");
            return INTMIN();
		}
		if(t1.type == OPERAND) {
			ipush(&i, t1.data.num);
			//printf("here\n");
		}
		else if(t1.type == OPERATOR) {
			currop = t1.data.op;
			//1515printf("HereOp\n");
			if(currop == '(')
				ctob++;
			if(currop == ')')
				ctcb++;
			if(isempty(&cs)) {
				prevop = pop(&cs);
				if(precedance(prevop) >= precedance(currop)) {
					if(iisempty(&i)) {
						a = ipop(&i);
					}
					else{
						push(&cs, prevop);
						break;
					}
					if(iisempty(&i)) {
						b = ipop(&i);
					}
					else {
						push(&cs, prevop);
						ipush(&i, a);
						break;
					}
					switch (prevop) {
						case '+' :
							//z = b + a;
							z = addition(&a, &b);
							ipush(&i, z);
							break;
						case '-' :
							//z = b - a;
							z = subtraction(&b, &a);
							ipush(&i, z);
							break;
						case '*' :
							//z = b * a;
							z = multiplication(&b, &a);
							ipush(&i, z);
							break;
						case '/' :
							//z = b / a;
							z = division(&b, &a);
							ipush(&i, z);
							break;
						case '%' :
							//z = b % a;
							z = mod(&b, &a);
							ipush(&i, z);
							break;
						case '^' :
							//z = b^a;
							z = power(&b, &a);
							ipush(&i, z);
							break;
						case '(' :
							push(&cs, prevop);
							ipush(&i, b);
							ipush(&i, a);
							break;
						}
						/*if(isempty(&cs))
							prevop = ctop(&cs);
						else
							break;*/
						}
                    else
                        push(&cs, prevop);
		}
		push(&cs, t1.data.op);
		if(currop == ')') {
				ch = pop(&cs);
				ctcb--;
				ch = pop(&cs);
				ctob--;
			}
	}
		else if(t1.type == END) {
			if(ctcb == ctob) {
				while(isempty(&cs)) {
					if(iisempty(&i))
						a = ipop(&i);
					else {
						printf("Less Operands\n");
						return INTMIN();
					}
					if(iisempty(&i))
						b = ipop(&i);
					else {
						printf("Less Operands\n");
						return INTMIN();
					}
					ch = pop(&cs);
					switch(ch) {
                        case '+':
                            c = addition(&b, &a);
                            ipush(&i, c);
                            break;
                        case '-':
                            c = subtraction(&b, &a);
                            ipush(&i, c);
                            break;
                        case '*':
                            c = multiplication(&b, &a);
                            ipush(&i, c);
                            break;
                        case '/':
                            c = division(&b, &a);
                            ipush(&i, c);
                            break;
                        case '%':
                            c = mod(&b, &a);
                            ipush(&i, c);
                            break;
                        case '^':
                            c = power(&b, &a);
                            ipush(&i, c);
                            break;
					}
                }
            }
            else {
                printf("Syntax Error\n");
                return INTMIN();
            }
            if(iisempty(&i)) {
                y = ipop(&i);
                if(iisempty(&i)) {
                    printf("Less Operators\n");
                    return INTMIN();
                }
                else
                    return y;
            }

        }
        else if(t1.type == ERR) {
            printf("Syntax Error\n");
            return INTMIN();
        }
        prev = curr;
    }
}
int main()
{
    integer a;
    char ch[2048];
    printf("Enter Expression:");
    gets(ch);
    a = infixeval(ch);
    printInteger(a);
    return 0;
}
