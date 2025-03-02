#include <stdio.h>
#include <stdlib.h>

// Define the structure for a stack node
typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

// Define the structure for a stack
typedef struct Stack {
    StackNode* top;
} Stack;

// Function to create a new stack node
StackNode* createStackNode(char data) {
    StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new stack
Stack* createStack() {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    if (!newStack) {
        printf("Memory error\n");
        return NULL;
    }
    newStack->top = NULL;
    return newStack;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, char data) {
    StackNode* newNode = createStackNode(data);
    if (stack->top) {
        newNode->next = stack->top;
    }
    stack->top = newNode;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return '\0';
    }
    char data = stack->top->data;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to check the balance of parentheses
int checkBalance(char* str) {
    Stack* stack = createStack();
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            push(stack, str[i]);
        } else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (isEmpty(stack)) {
                printf("Unbalanced parentheses: closing parenthesis without opening one\n");
                return 0;
            }
            char opening = pop(stack);
            if ((str[i] == ')' && opening != '(') ||
                (str[i] == '}' && opening != '{') ||
                (str[i] == ']' && opening != '[')) {
                printf("Unbalanced parentheses: mismatched opening and closing parentheses\n");
                return 0;
            }
        }
    }
    if (!isEmpty(stack)) {
        printf("Unbalanced parentheses: opening parentheses without closing ones\n");
        return 0;
    }
    printf("Balanced parentheses\n");
    return 1;
}

int main() {
    char str[] = "(a + b) * {x - [y / (z - 1)]}";
    checkBalance(str);
    return 0;
}
