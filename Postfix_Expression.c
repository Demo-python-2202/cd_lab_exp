#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure to hold operators
typedef struct {
    int top;
    char items[MAX];
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push an item onto the stack
void push(Stack *s, char c) {
    s->items[++(s->top)] = c;
}

// Pop an item from the stack
char pop(Stack *s) {
    return isEmpty(s) ? 0 : s->items[(s->top)--];
}

// Return the precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

// Check if a character is an operator
int isOperator(char c) {
    return strchr("+-*/^", c) != NULL;
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;

    for (i = 0; infix[i]; i++) {
        char token = infix[i];

        // Skip spaces
        if (isspace(token)) continue;

        // If token is operand (alphabetic or numeric), add to postfix
        if (isalnum(token)) {
            postfix[j++] = token;
        }
        // If token is '(', push it to the stack
        else if (token == '(') {
            push(&s, token);
        }
        // If token is ')', pop from stack to postfix until '(' is found
        else if (token == ')') {
            while (!isEmpty(&s) && s.items[s.top] != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);  // pop the '(' from the stack
        }
        // If token is an operator, pop operators from the stack
        else if (isOperator(token)) {
            while (!isEmpty(&s) && precedence(s.items[s.top]) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    // Pop any remaining operators in the stack
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
}

int main() {
    char infix[MAX], postfix[MAX];

    // Input the infix expression
    printf("Enter the expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0;  // Remove trailing newline character

    // Convert infix to postfix
    infixToPostfix(infix, postfix);

    // Output the postfix expression
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}

// (a+b)*(c+d)
