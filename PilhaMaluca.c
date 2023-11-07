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
char push2(Stack*, char);
char pop(Stack*);
int empty(Stack*);
char stackTop(Stack*);
int stackSize(Stack*);
void showStack(Stack*);
void errorTreatment(char i);
void generateStackByString(Stack*, Stack*, Stack*, char*);
char stackConference(Stack*, Stack*, Stack*);
void clearStack(Stack*);

int main() {
	Stack *stackOpen;
	Stack *stackClose;
	Stack *stackCloseReserva;
	stackOpen = stackStart();
	stackClose = stackStart();
	stackCloseReserva = stackStart();
	char string[101];
	
	
	while(stackOpen->top == -1 && stackClose->top == -1){
		printf("Type the equation: ");
		fgets(string, sizeof(string), stdin);
		string[strcspn(string, "\n")] = '\0';
		generateStackByString(stackOpen, stackClose, stackCloseReserva, string);
		showStack(stackOpen);
		showStack(stackClose);
		showStack(stackCloseReserva);
		errorTreatment(stackConference(stackOpen, stackClose, stackCloseReserva));
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
	if (stack->top == STACK_SIZE){
		return 'a'; 
	}
	else {
		stack->item[++stack->top] = i;
	}
}

char push2(Stack *stack, char i){
	if (stack->top == STACK_SIZE){
		return 'a'; 
	}
	else {
		int p;
		stack->top++;
		for (p = stack->top; p > -1; p--){
			int o = (p - 1);
			if(p > 0){
				stack->item[p] = stack->item[o];
			} else{
				stack->item[p] = i;
			}
		}
	}
}

char pop(Stack *stack){
	if(stack->top >=0){
		return stack->item[stack->top--];
	} else {
		return 'b'; 
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
		printf("Valid\n");
	} else if (i == 'd'){
		printf("Invalid\n");
	}
}

void generateStackByString(Stack *stackOpen, Stack *stackClose, Stack *stackCloseReserva, char *string){
	int i;
	for (i = 0; i < strlen(string); i++){
		if(string[i] == '(' || string[i] == '{' || string[i] == '[' ){
			errorTreatment(push(stackOpen, string[i]));
		}
		else if(string[i] == ')' || string[i] == '}' || string[i] == ']' ){
			errorTreatment(push(stackCloseReserva, string[i]));
			errorTreatment(push2(stackClose, string[i]));
		}
	}
}

char stackConference(Stack *stackOpen, Stack *stackClose, Stack *stackCloseReserva){
	int different = 0, choice = 0;
	while(stackOpen->top > -1 && stackClose->top > -1 && stackCloseReserva->top > -1 && different == 0){
		char a1 = stackTop(stackOpen);
		char a2 = stackTop(stackClose);
		char a3 = stackTop(stackCloseReserva);
		if((a1 == '(' && a2 == ')') || (a1 == '{' && a2 == '}') || (a1 == '[' && a2 == ']') && (choice == 0 || choice == 1)){
			printf("\n%c\n", a1);
			printf("\n%c\n", a2);
			errorTreatment(pop(stackOpen));
			errorTreatment(pop(stackClose));
			choice = 1;
		} else if((a1 == '(' && a3 == ')') || (a1 == '{' && a3 == '}') || (a1 == '[' && a3 == ']') && (choice == 0 || choice == 2)){
			errorTreatment(pop(stackOpen));
			errorTreatment(pop(stackCloseReserva));
			choice = 2;
		} else {
			different = 1;
		}
	}
	printf("%i\n", different);
	printf("%i\n", choice);
	printf("%i\n", stackOpen->top);
	printf("%i\n", stackClose->top);
	printf("%i\n", stackCloseReserva->top);
	if(different == 0 && ((stackOpen->top == 0 && stackClose->top == 0) || (stackOpen->top == 0 && stackCloseReserva->top == 0))){
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












