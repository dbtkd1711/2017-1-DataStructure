#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;
}node;

typedef struct list {
	int count;
	node * head;
}list;

void init(list * lptr);
node * getcur(list * lptr, int n);
node * getprev(list * lptr, int n);
void insert(list * lptr, int m, int n);
void del(list * lptr, int n);
void showprev(list * lptr, int n);
void showall(list * lptr);
void deletelist(list * lptr);

int main() {

	char command;
	int m, n;

	list * mylist = (list*)malloc(sizeof(list));

	init(mylist);

	while (1) {
		scanf("%c", &command);
		if (command == 'i') {
			scanf("%d %d", &m, &n);
			insert(mylist, m, n);
		}
		else if (command == 'd') {
			scanf("%d", &n);
			del(mylist, n);
		}
		else if (command == 'f') {
			scanf("%d", &n);
			showprev(mylist, n);
		}
		else if (command == 's') {
			showall(mylist);
		}
		else if (command == 'e') {
			deletelist(mylist);
			return 0;
		}
        else {
            printf("Try again\n");
        }
        getchar();
	}
}

void init(list * lptr) {

	lptr->count = 0;
	lptr->head = NULL;
}

node * getcur(list * lptr, int n) {

    // List is empty
	if (lptr->count == 0)
		return NULL;
    // List is not empty
    else {
		node * p = lptr->head;
		while (p != NULL) {
			if (p->value == n)
				return p;
			else
				p = p->next;
		}
		return NULL;
	}
}

node * getprev(list * lptr, int n) {

    // List is empty
	if (lptr->count == 0)
		return NULL;
    // List is not empty
	else {
		node * p = lptr->head;
		node * q = NULL;

		while (p!=NULL) {
			if (p->value != n) {
				q = p;
				p = p->next;
			}
			else
				return q;
		}
		return NULL;
	}
}

void insert(list * lptr, int m, int n) {

    // Case1. n=0
    // Insert the node next to the head
	if (n == 0) {
		node * tmp = (node*)malloc(sizeof(node));
        // List is empty
		if (lptr->count == 0) {
			tmp->value = m;
			tmp->next = NULL;
			lptr->head = tmp;
		}
        // List is not empty
		else {
			tmp->value = m;
			tmp->next = lptr->head;
			lptr->head = tmp;
		}
		(lptr->count)++;
	}
    // Case2. n!=0
    // Insert the node which have value 'm' next to the node which have value 'n'
	else {
        // If there is any node which have value 'n'
		if (getcur(lptr, n) == NULL)
			printf("insert error : %d is not in list \n", n);
		else {
			node * tmp = (node*)malloc(sizeof(node));
			tmp->value = m;
			tmp->next = getcur(lptr, n)->next;
			getcur(lptr, n)->next = tmp;
			(lptr->count)++;
		}
	}
}

void del(list * lptr, int n) {

	node * tmp;
    // If there is no node which has the value 'n'
	if (getcur(lptr, n) == NULL)
		printf("delete error : %d is not in list \n", n);
    // There exists the node which has the value 'n'
	else {
        // There is only 1 node
		if (lptr->count == 1) {
			tmp = lptr->head;
			lptr->head = NULL;
		}
		else
			getprev(lptr, n)->next = getcur(lptr, n)->next;

        free(tmp);
        (lptr->count)--;
	}
}

void showprev(list * lptr, int n) {

    // List is empty
	if (lptr->count==0)
		printf("showprev error : %d is not in list \n", n);

    // List is not empty
	else {
        // If there is no node which has the value 'n'
		if (getcur(lptr, n)==NULL)
			printf("showprev error : %d is not in list \n", n);
        // There exists the node which has the value 'n'
        // and that node is the first in the list
		else if (getcur(lptr, n) != NULL && getprev(lptr, n)==NULL)
			printf("%d is next of the head \n", n);
        // There exists the node which has the value 'n'
        // and that node is not the first in the list
		else
			printf("%d is next of the %d \n", n, getprev(lptr, n)->value);
	}
}

void showall(list * lptr) {

    // List is empty
	if (lptr->count ==0)
		printf("showall error : list is empty \n");
    // List is not empty
    else {
		node * p = lptr->head;
		while (p != NULL) {
			printf("%d ", p->value);
			p = p->next;
		}
		printf("\n");
	}
    return;
}

void deletelist(list * lptr) {

    // List is empty
	if (lptr->count == 0)
        free(lptr);
    // List is not empty
    else {
		node * p = lptr->head;
        // There is only 1 node in the list
		if (lptr->count == 1)
			free(p);
		else {
			node * p = lptr->head;
			node * q = p->next;
			while (q != NULL) {
				free(p);
				lptr->head = q;
				p = q;
				q = q->next;
			}
			free(p);
		}
        free(lptr);
	}

    return;
}
