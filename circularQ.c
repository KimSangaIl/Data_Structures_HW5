/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	printf("[----- [Kim Sangil] [2019038041] -----]");
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear) {		//원형 큐의 front와 rear가 같다면
		printf("Queue is Empty!\n");	//큐는 공백이다.
		return 1;
	}
	else return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) {	//rear의 다음 위치 값을 큐의 크기로 나눈 나머지 값이 front와 같다면
		printf("Queue is Full!\n");	//큐는 포화상태 이다.
		return 1;
	}
   	else return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ) == 1) return;	//큐가 포화 상태라면 원소 삽입 불가
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	//rear 위치를 다음 칸으로 초기화
		cQ->queue[cQ->rear] = item;	//초기화된 rear 위치에 원소 삽입
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ) == 1) return;	//큐가 공백 상태라면 원소 삭제 불가
    else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	//front의 위치를 한칸 뒤로 초기화
		*item = cQ->queue[cQ->front];	//원소의 값을 한칸 뒤로 옮겨진 front 값으로 초기화
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


