#include<stdio.h>
#include"integer.h"
#include<stdlib.h>

void initi(integer *a) {
    a->head = NULL;
    a->dec = 0;
    a->len = 0;
    a->par = 0;
}
void length(integer *a) {
    snode *p = a->head;
    int len = 0;
    while(p) {
        p = p->next;
        len++;
    }
    a->len = len;
}
int len(integer a) {
    int i = 0;
    snode *p;
    p = a.head;
    while(p) {
        p = p->next;
        i++;
    }
    return i;
}
int value(integer a) {
    snode *p;
    int k;
    int sum = 0;
    p = a.head;
    while(p) {
        k = p->data;
        sum = sum * 10 + k;
        p = p->next;
    }
    if(a.par == 1) {
        sum = sum * (-1);
    }
    return sum;
}
void addDigit(integer *a, char c) {
	int k;
	snode *p;
	p = a->head;
	if(c == '.')
		a->dec = a->len;
    else if(c == '-')
		a->par = 1;
    else if(c >= '0' && c <= '9') {
        snode *nn = (snode *)malloc(sizeof(snode));
        k = c - '0';
        nn->data = k;
        if(a->head == NULL) {
            nn->next = NULL;
            a->head = nn;
        }
        else {
            nn->next = NULL;
            while(p->next) {
                p = p->next;
            }
            p->next = nn;
        }
        length(a);
    }
}
void printInteger(integer a) {
    snode *p = a.head;
    int m = 0;
    if(a.par ==1)
		printf("-");
    while(p){
        printf("%d", p->data);
        p = p->next;
        m++;
        if(m == a.dec)
            printf(".");
    }
    printf("\n");
}
void freeInteger(integer *a) {
    snode *p, *q;
    p = a->head;
    while(p) {
        q = p;
        p = p->next;
        free(q);
    }
    initi(a);
}
integer copy(integer a) {
	int i, no, l;
	integer b;
	initi(&b);
	char ch;
	l = len(a);
	snode *t1 = a.head;
	for(i = 0; i < l; i++) {
		no = t1->data;
		ch = no + 48;
		addDigit(&b, ch);
		t1 = t1->next;
	}
	b.dec = a.dec;
	b.par = a.par;
	return b;
}
int compare(integer a, integer b) {
	snode *p, *q;
	int i1 = 0, i2 = 0;
	p = a.head;
	q = b.head;
	while(p) {
		if(p->data == 0) {
			a.head = p->next;
			p = p->next;
		}
		else
			break;
	}
	while(q) {
		if(q->data == 0) {
			b.head = q->next;
			q = q->next;
		}
		else
			break;
	}
	p = a.head;
	q = b.head;
	while(p) {
		i1++;
		p = p->next;
	}
	while(q) {
		i2++;
		q = q->next;
	}
	if(i2 > i1)
		return 0;
	else if(i1 > i2)
		return 1;
	else if(i1 == i2) {
		p = a.head;
		q = b.head;
		while(p) {
			if(p->data < q->data) {
				return 0;
			}
			else if(p->data > q->data) {
				return 1;
			}
			else if(p->data == q->data) {
				p = p->next;
				q = q->next;
			}
		}
		if(p == NULL)
			return 1;
	}
	return 1;
}
void match(integer *a, integer *b) {
	int post, i;
	if(a->dec == 0 && b->dec != 0) {
		addDigit(a, '.');
		addDigit(a, '0');
	}
	else if(b->dec == 0 && a->dec != 0) {
		addDigit(b, '.');
		addDigit(b, '0');
	}
	if(a->dec != 0 && b->len != 0) {
		post = (a->len - a->dec) - (b->len - b->dec);
		if(post > 0) {
			for(i = 0; i < post; i++)
				addDigit(b, '0');
		}
		else if(post < 0) {
			post = 0 - post;
			for(i = 0; i < post; i++)
				addDigit(a, '0');
		}
	}
}
void reverse(integer *a) {
    snode *cur, *next, *prev;
    prev = NULL;
    next = NULL;
    cur = a->head;
    while(cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    a->head = prev;
}
void addPrev(integer *a, char c) {
	int k;
	if(c >= '0' && c <= '9') {
	snode *tmp = (snode*)malloc(sizeof(snode));
		k = c - '0';
		tmp->data = k;
		tmp->next = a->head;
		a->head = tmp;
    }
	length(a);
}
integer INTMIN() {
	integer a;
	initi(&a);
	addDigit(&a, '2');
	addDigit(&a, '8');
	addDigit(&a, '0');
	addDigit(&a, '4');
	addDigit(&a, '3');
	addDigit(&a, '8');
	addDigit(&a, '0');
	addDigit(&a, '7');
	addDigit(&a, '3');
	addDigit(&a, '9');
	return a;
}
integer addition(integer *a, integer *b) {

	int i1 = 0, i2 = 0, carry = 0, data, rem;
	integer e, c;
	char f;
	initi(&c);
	initi(&e);
	snode *ptr1, *ptr2;
	match(a, b);

	ptr1 = a->head;
	ptr2 = b->head;
	if(a->par == 1 && b->par == 0) {
		a->par = 0;
		c = subtraction(b, a);
		return c;
	}
	if(a->par == 0 && b->par == 1) {
		b->par = 0;
		c = subtraction(a, b);
		return c;
	}
	while(ptr1){
		i1++;
		ptr1 = ptr1->next;
	}
	while(ptr2){
		i2++;
		ptr2 = ptr2->next;
	}
	if(i2 > i1) {
		c = *a;
		*a = *b;
		*b = c;
	}

	reverse(a);
	reverse(b);
	ptr1 = a->head;
	ptr2 = b->head;
	while(ptr1) {
        while(ptr2) {
            data = ptr1->data + ptr2->data + carry;
            rem = data % 10;
            carry = data / 10;
            f = rem + 48;
            addDigit(&e, f);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        if(ptr1 != NULL) {
            data = ptr1->data + carry;
            rem = data % 10;
            carry = data / 10;
            f = rem + 48;
            addDigit(&e, f);
            ptr1 = ptr1->next;
        }
        if(ptr1 == NULL) {
            while(carry != 0) {
                f = carry + 48;
                addDigit(&e, f);
            }
        }
	}
	reverse(&e);
	reverse(a);
	reverse(b);
	if(a->par == 1 && b->par == 1)
        e.par = 1;
    length(&e);
	e.dec = e.len - (a->len - a->dec);
	if(a->dec == 0 && b->dec == 0)
		e.dec = 0;
	return e;
}
integer subtraction(integer *a, integer *b) {
    int i1 = 0, i2 = 0, borrow = 0, data, par = 0;
	char f;
	integer c, e, z;
	initi(&z);
	initi(&c);
	initi(&e);
	if(a->par == 1 && b->par == 0) {
		b->par = 1;
		z = addition(a, b);
		length(&z);
		return z;
	}
	if(a->par == 0 && b->par == 1) {
		b->par = 0;
		z = addition(a, b);
		length(&z);
		return z;
	}
	match(a, b);
	snode *ptr1, *ptr2;
	ptr1 = a->head;
	ptr2 = b->head;
	while(ptr1){
		i1++;
		ptr1 = ptr1->next;
	}
	while(ptr2){
		i2++;
		ptr2 = ptr2->next;
	}
	ptr1 = a->head;
	ptr2 = b->head;
	if(i1 == i2) {
		while(ptr1) {
			if(ptr1->data < ptr2->data) {
				par++;
				c = *a;
				*a = *b;
				*b = c;
				break;
			}
			else if(ptr1->data > ptr2->data) {
				break;
			}
			else if(ptr1->data == ptr2->data) {
				ptr1 = ptr1->next;
				ptr2 = ptr2->next;
			}
		}
	}
	if(i1 < i2) {
		par++;
		c = *a;
		*a = *b;
		*b = c;
	}
	reverse(a);
	ptr1 = a->head;
	reverse(b);
	ptr2 = b->head;
	while(ptr1) {
        while(ptr2) {
            if(ptr1->data + borrow < ptr2->data) {
                data = 10 + ptr1->data - ptr2->data + borrow;
                borrow = -1;
            }
            else{
                if(borrow != 0)
                    data = ptr1->data - ptr2->data + borrow;
                else
                    data = ptr1->data - ptr2->data;
                borrow = 0;
            }
            f = data + 48;
            addDigit(&e, f);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        if(ptr1 != NULL) {
            data = borrow + ptr1->data;
            if(data < 0) {
                data = 10 + ptr1->data + borrow;
                borrow = -1;
            }
            else
                borrow = 0;
            f = 48 + data;
            addDigit(&e, f);
            ptr1 = ptr1->next;

	}
	}
	reverse(&e);
	reverse(a);
	reverse(b);
	freeInteger(&c);
	if(par == 1)
        e.par = 1;
    if(a->par == 1 && b->par == 1) {
        if(e.par == 1)
            e.par = 0;
        else
            e.par = 1;
    }
    if(a->dec != 0 || b->dec != 0) {
		length(&e);
		e.dec = e.len - (a->len - a->dec);
	}
	ptr1 = e.head;
	while(ptr1) {
		if(ptr1->data == 0 && e.len > 1) {
			e.head = ptr1->next;
			ptr1 = ptr1->next;
			length(&e);
		}
		else
			break;
	}
	e.dec = e.len - (a->len - a->dec);
	if(e.dec < 0)
		e.dec = 0;
	return e;
}

integer multiplication(integer *a, integer *b) {
	integer sum, c3, e;
	initi(&c3);
	initi(&sum);
	initi(&e);
	length(a);
	length(b);
	char c1 = '0';
	int i, par = 0, z1, z2, dec1, dec2;
	dec1 = a->dec;
	dec2 = b->dec;
	z1 = a->len - a->dec;
	z2 = b->len - b->dec;
	if(b->par == 1)
		par++;
	if(a->par == 1)
		par++;
	if(par == 1)
		sum.par = 1;
	else
		sum.par = 0;
    match(a, b);
    int k1 = len(*a);
    int k2 = len(*b);
    for(i = 0; i < k1+k2+1; i++) {
        addDigit(&sum, c1);
    }
    snode *p, *q, *r, *s;
    reverse(a);
    reverse(b);
    p = a->head;
    q = b->head;
    r = sum.head;
    while(q) {
        int carry = 0;
        s = r;
        p = a->head;
        while(p) {
            int data = p->data * q->data + carry;
            s->data += data % 10;
            carry = data / 10 + s->data / 10;
            s->data = s->data % 10;
            p = p->next;
            s = s->next;
        }
        if(carry > 0) {
            s->data += carry;
        }
        r = r->next;
        q = q->next;
}
    reverse(&sum);
    reverse(a);
    reverse(b);
    p = sum.head;
    while(p->data == 0) {
        snode *q = p;
        p = p->next;
        free(q);
    }
    sum.head = p;
    /*integer c ;
    initi(&c);//= copy(*a);
    snode *q;
    q = b->head;
    while(q) {
        int k = q->data;
		for(int i = 0; i < k - 1; i++) {
			c = addition(a, a);
		}
		q = q->next;
		addDigit(&sum, '0');
		if(k != 0)
			sum = addition(&sum, &c);
		//*a = copy(c);
    }*/
    //addDigit(&sum, '0');

	sum.dec = sum.len - (z1 + z2);
	if(b->dec != b->len) {
        sum.dec = sum.len - z2*2 - z2;
	}
	if(a->dec != a->len) {
        sum.dec = sum.len - z1*2 - z1;
	}
	if(dec1 == 0 && dec2 == 0)
		sum.dec = 0;
	if(dec1 != 0 && dec2 != 0 && sum.dec == 0) {
		for(i = 0; i <= sum.dec; i++)
			addPrev(&sum, '0');
		sum.dec = sum.len - (z1 + z2);
	}
	length(&sum);
	return sum;
}

integer division(integer *a, integer *b) {
    integer c, d, e;
    initi(&c);
    initi(&d);
    initi(&e);
    int  quo = 0, m, n;
    char f;
    match(a, b);
    m = value(*b);
    if(m == 0) {
        printf("Syntax Error : Can't Divide by Zero\n");
    }
    int j = compare(*a, *b);
    if(j == 0) {
        f = 48;
        addDigit(&d, f);
        return d;
    }
    if(a->par == 1 && b->par == 0) {
        c.par = 1;
        a->par = 0;
    }
    else if(a->par == 0 && b->par == 1) {
        c.par = 1;
        b->par = 0;
    }
    else
        c.par = 0;
    d = copy(*a);
    e = copy(*b);
    while(1) {
        d = subtraction(&d, &e);
        quo++;
        int i = compare(d, e);
        if(i == 0) {
            break;
        }
    }
    m = quo;
    while(m) {
        n = m % 10;
        m = m / 10;
        f = 48 + n;
        addDigit(&c, f);
    }
    reverse(&c);
    length(&c);
    return c;
}
integer power(integer *a, integer *b) {
    integer c, e;
    initi(&c);
    initi(&e);
    snode *p;
    p = b->head;
    int k, i = 0, val;
    k = b->dec;
    if(k >= 1) {
        for(i = 0; i < k - 1; i++) {
            p = p->next;
        }
        //b->head = p->next;
        b->head->next = NULL;
        //b->head = q;
    }
    val = value(*b);
    if(b->par == 1) {
        addDigit(&c, '0');
        length(&c);
        return c;
    }
    if(val == 0) {
        length(a);
        return *a;
    }
    addDigit(&e, '1');
    while(val) {
        e = multiplication(&e, a);
        val--;
    }
    length(&e);
    return e;
}
integer mod(integer *a, integer *b) {
    integer c, d;
    char f;
    initi(&c);
    initi(&d);
    snode *p = b->head;
    if(p->data == 0) {
        f = 48;
        addDigit(&d, f);
        return d;
    }
    if(b->par == 1) {
        c.par = 1;
        b->par = 0;
    }
    if(a->par == 1) {
        c.par = 1;
        a->par = 0;
    }
    d = *a;
    while(compare(d, *b)) {
        d = subtraction(&d, b);
    }
    length(&d);
    return d;
}
void initistack(istack *s) {
    *s = NULL;
}
void ipush (istack *s, integer a) {
	inode *temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = a;
	temp->next = *s;
	*s = temp;
}
integer ipop(istack *s) {
	integer t;
	inode *temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->next;
	free(temp);
	return t;
}
int iisempty (istack *s) {
	if(*s == NULL)
        return 0;
    else
        return 1;
}
void init(cstack *s1) {
    *s1 = NULL;
}
void push(cstack *s1, char ch) {
    cnode *temp;
    temp = (cnode *)malloc(sizeof(cnode));
    temp->ch = ch;
    temp->nex = *s1;
    *s1 = temp;
}
char pop(cstack *s1) {
    char c;
    c = (*s1)->ch;
    cnode *temp;
    temp = *s1;
    *s1 = (*s1)->nex;
    free(temp);
    return c;
}
int isempty(cstack *s1) {
    if(*s1 == NULL)
        return 0;
    else
        return 1;
}
