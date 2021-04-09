#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct que
{
	int front, rear, size;
	unsigned int actualSize;
	int* arr;
};
typedef struct que Queue;


Queue * createque(unsigned actualSize);
int isFull(Queue * que);
void enqueue(Queue* que, int item);
int isEmpty(Queue* que);
int dequeue(Queue* que);
int front(Queue* que);
int rear(Queue* que);


int main()
{
	int val,n;
	Queue* que = createque(1000);

	do
	{
		printf("\n************************* MENU ************************");
		printf("\n1.ENQUEUE");
		printf("\n2.DEQUEUE");
		printf("\n3.IS EMPTY");
		printf("\n4.IS FULL");
		printf("\n5.FIRST ELE");
		printf("\n6.LAST ELE");
		printf("\n7.EXIT");
		printf("\nenter ur choice : ");
		scanf("%d",&n);

		switch(n)
		{
			case 1:
				printf("\nenter the value ");
				scanf("%d", &val);
				enqueue(que, val);
				break;
			case 2:
				dequeue(que);
				break;
			case 3:
				printf("\nIsEmpty : %d",isEmpty(que));
				break;
			case 4:
				printf("\nIsFull : %d",isFull(que));
				break;
			case 5:
				printf("\nFront element: %d",front(que));
				break;
			case 6:
				printf("\nLast element : %d",  rear(que));
				break;
			case 7:
				exit(0);
				break;
			default:
				printf("\n Wrong Choice!");
				break;
		}
		printf("\ndo u want to cont... ");
	} while('y' == getchar());
}

Queue * createque(unsigned actualSize)
{
	Queue* que = (Queue *) malloc(sizeof(Queue));
	que->actualSize = actualSize;
	que->front = que->size = 0; 
	que->rear = actualSize - 1;
	que->arr = (int *) malloc(que->actualSize * sizeof(int));

	return que;
}

int isFull(Queue * que)
{
	return (que->size == que->actualSize);
}

void enqueue(Queue* que, int item)
{
	if (isFull(que))
		return;

	que->rear = (que->rear + 1)%que->actualSize;
	que->arr[que->rear] = item;
	que->size = que->size + 1;
	printf("%d enqueued to que\n", item);
}

int isEmpty(Queue* que)
{
	return (que->size == 0);
}

int dequeue(Queue* que)
{
	if (isEmpty(que))
		return INT_MIN;
	int item = que->arr[que->front];
	que->front = (que->front + 1)%que->actualSize;
	que->size = que->size - 1;

	return item;
}

int front(Queue* que)
{
	if (isEmpty(que))
		return INT_MIN;

	return que->arr[que->front];
}

int rear(Queue* que)
{
	if (isEmpty(que))
		return INT_MIN;

	return que->arr[que->rear];
}
