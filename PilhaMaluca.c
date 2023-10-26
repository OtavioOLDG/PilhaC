#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct{
    int top;
    char item[STACK_SIZE];
} Stack;

Stack* stackStart();
char push(Stack*, char);
char pop(Stack*);
int empty(Stack*);
char stackTop(Stack*);
int stackSize(Stack*);
void showStack(Stack*);
void errorTreatment(char i);
void generateStackByString(Stack*, char*);
char stackConference(Stack*);
void clearStack(Stack*);

int main() {
	Stack *stack;
	stack = stackStart();
	char string[101];
	
	
	while(stack->top == -1){
		printf("Type the equation: ");
		fgets(string, sizeof(string), stdin);
		string[strcspn(string, "\n")] = '\0';
		generateStackByString(stack, string);
		showStack(stack);
		errorTreatment(stackConference(stack));
	}

	return 0;
}

Stack* stackStart(){
	Stack *stack;
	stack = (Stack*) malloc(sizeof(Stack));
	stack->top = -1;
	return stack;
}

char push(Stack *stack, char i){
	printf("Stack's top': %i\n", stack->top);
	if (stack->top == STACK_SIZE){
		return 'a'; 
	}
	else {
		stack->item[++stack->top] = i;
	}
}

char pop(Stack *stack){
	if(empty(stack)){
		return stack->item[stack->top--];
	} else {
		return 'b'; // Erro de underflow
	}
}

int empty(Stack *stack){
	if(stack->top < 0){
	       return 1;
	}else{
		return 0;
	}
}

char stackTop(Stack *stack){
	return stack->item[stack->top];
}

int stackSize(Stack *stack){
	return stack->top + 1;
}

void showStack(Stack *stack){
	int i;
	for (i = 0; i < stackSize(stack); i++){
       	printf("%c", stack->item[i]);
	}
	printf("\n");
}

void errorTreatment(char i){
	if(i == 'a'){
		printf("Overflow error\n");
	} else if (i == 'b'){
		printf("Underflow error\n");
	} else if (i == 'c'){
		printf("Invalid\n");
	} else if (i == 'd'){
		printf("Valid\n");
	}
}

void generateStackByString(Stack *stack, char *string){
	int i;
	for (i = 0; i < strlen(string); i++){
		errorTreatment(push(stack, string[i]));
	}
}

char stackConference(Stack *stack){
	int i, openBrackets = 0, endBrackets = 0;
	int openSqrParentheses = 0, endSqrParentheses = 0;
	int openRoundParentheses = 0, endRoundParentheses = 0;
	for(i = 0; i < (stackTop(stack) - 1);i++){
		if(stack->item[i] == '{'){
			openBrackets++;
		} else if(stack->item[i] == '}') {
			endBrackets++;
		} else if(stack->item[i] == '[') {
			openSqrParentheses++;
		} else if(stack->item[i] == ']') {
			endSqrParentheses++;
		}else if(stack->item[i] == '(') {
			openRoundParentheses++;
		} else if(stack->item[i] == ')') {
			endRoundParentheses++;
		}
	}
	
	if(((openBrackets - endBrackets) != 0) || ((openRoundParentheses - endRoundParentheses) != 0) || ((openSqrParentheses - endSqrParentheses) != 0)){
		return 'c';
	} else{
		return 'd';
	}
}

void clearStack(Stack *stack) {
	int i;
	for(i = 0; i < STACK_SIZE; i++){
		stack->item[i] = ' ';
	}
	stack->top = -1;  
}












