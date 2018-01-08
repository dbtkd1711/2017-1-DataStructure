#include <stdio.h>
#include <stdlib.h>

typedef struct stack * Stack;

struct stack {
	char * array;
	int size;
	int top;
};

Stack create_stack(int c);
int is_empty(Stack S);
void make_empty_stack(Stack S);
void push(Stack S, char X);
char pop(Stack S);
void delete_stack(Stack S);

int main() {

	char input;
    // For output string
	char str[100];
    // Index of ouput string
	int idx = 0;

	Stack mystack = create_stack(100);

	while (1) {
		scanf(" %c", &input);
        // Case1. Stack is empty
		if (is_empty(mystack)==1) {
			if (input == '(') {
				push(mystack, input);
			}
            // If input is ')' when stack is empty
            // -> ignore all following characters execpt '#'
			else if (input == ')') {
				while (1) {
					scanf(" %c", &input);
					if (input != '#')
						continue;
					else {
						printf("wrong. ");
						for (int i=0; i < idx ; i++) {
							printf("%c ", str[i]);
						}
						printf("\n");
						idx = 0;
						break;
					}
				}
			}
            // Inspect the stack and print the output string
            // -> Empty stack means the same number of '(' and ')'
			else if (input == '#') {
				printf("right. ");
				for (int i = 0; i < idx; i++) {
					printf("%c ", str[i]);
				}
				printf("\n");
				idx = 0;
				continue;
			}
            // Free the stack and terminate the process
			else if (input == '!') {
				delete_stack(mystack);
				break;
			}
            // If input is any alphabet when stack is empty
            // -> put it in the output string
			else {
				str[idx] = input;
				idx++;
			}
		}
        // Case2. Stack is not empty
		else {
			if (input == '(') {
				push(mystack, input);
			}
            // If input is ')' when stack is not empty
            // -> Pop all elements in the stack until '(' is popped
            // -> then put them into the output string
			else if (input == ')') {
				while (mystack->array[mystack->top] != '(') {
					str[idx++] = pop(mystack);
				}
				(mystack->top)--;
			}
            // Inspect the stack and print the output string
            // -> Not empty stack means the different number of '(' and ')'
			else if (input == '#') {
				printf("wrong. ");
				for (int i = 0; i < idx; i++) {
					printf("%c ", str[i]);
				}
				printf("\n");
				idx = 0;
				make_empty_stack(mystack);
				continue;
			}
			else if (input == '!') {
				delete_stack(mystack);
				break;
			}
            // If input is any alphabet when stack is not empty
            // -> put it in the stack
			else {
				push(mystack, input);
			}
		}
	}
	return 0;
}

// Create the stack
Stack create_stack(int array_size) {

	Stack S = (Stack)malloc(sizeof(struct stack));

	S->size = array_size;
	S->top = -1;
	S->array = (char*)malloc(sizeof(char)*array_size);

	return S;
}

// Check whether the stack is empty or not
int is_empty(Stack S) {

	if (S->top == -1)
		return 1;
	else
		return 0;
}

// Input = '#'
void make_empty_stack(Stack S) {

	S->top = -1;
}

// Push the character into the stack
void push(Stack S, char X) {

	S->array[(S->top++) + 1] = X;
}

// Pop the character from the stack
char pop(Stack S) {

	if (is_empty(S)==0)
		return S->array[(S->top--)];
}

// Execute when the program is terminated
void delete_stack(Stack S) {
    free(S->array);
	free(S);
}
