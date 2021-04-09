#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 


struct stack
{
	int top;
	unsigned size;
	int* array;
};
typedef struct stack Stack;


Stack * create(unsigned size);
int isFull(Stack *stackk);
int isEmpty(Stack *stackk);
void push(Stack *stackk, int item);
int pop(Stack *stackk);
int peek(Stack *stackk);


int main()
{ 
	int val,n;
	Stack *stackk = create(100);

	do
	{
		printf("\n************************* MENU ************************");
		printf("\n1.PUSH");
		printf("\n2.POP");
		printf("\n3.PEEK");
		printf("\n4 IS EMPTY");
		printf("\n5.EXIT");
		printf("\n enter ur choice : ");
		scanf("%d",&n);

		switch(n)
		{
			case 1: 
				printf("\nenter the value ");
				scanf("%d",&val);
				push(stackk , val);
				break;
			case 2: 
				printf("\n popped element : %d",pop(stackk));
				break;
			case 3: 
				printf("\n top element : %d",peek(stackk));
				break;
			case 4:
				printf("\n is empty : %d",isEmpty(stackk));
				break;
			case 5:
				exit(0);
				break;
			default:
				printf("\n Wrong Choice!");
				break;
		}
		printf("\n do u want to cont... ");
	}while('y'==getchar());
}

Stack * create(unsigned size)
{ 
	Stack *stackk = (Stack *) malloc(sizeof(Stack));
	stackk->size = size;
	stackk->top = -1;
	stackk->array = (int *) malloc(stackk->size * sizeof(int));
	return stackk;
}

int isFull(Stack *stackk)
{ 
	return stackk->top == stackk->size - 1;
}

int isEmpty(Stack *stackk)
{ 
	return stackk->top == -1;
}

void push(Stack *stackk, int item)
{ 
	if (isFull(stackk))
		return;
	stackk->array[++stackk->top] = item;
}


int pop(Stack *stackk)
{ 
	if (isEmpty(stackk))
		return -1;
	return stackk->array[stackk->top--];
}

int peek(Stack *stackk)
{ 
	if (isEmpty(stackk))
		return INT_MIN;
	return stackk->array[stackk->top];
}
