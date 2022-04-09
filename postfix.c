/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') {
		if (getPriority(*exp) == operand) {	//exp가 피연산자일때
			x = *exp;		//exp를 x에 저장
			charCat(&x);	//함수를 호출해 x를 postfixExp에 추가
		}
		else if (getPriority(*exp) == lparen) {	//exp가 '(' 일때
			postfixPush(*exp);	//함수를 호출해 exp를 postfixStack에 추가
		}
		else if (getPriority(*exp) == rparen) {	//exp가 ')' 일때
			while ((x = postfixPop()) != '(') {	//postfixPop함수를 호출해서 리턴 받은 값이 '(' 일때까지 반복
				charCat(&x);	//함수를 호출해 x를 postfixExp에 추가
			}	
		}
		else {	//exp가 연산자 '+', '-', '*', '/' 일때
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) {	//postfixStack의 우선순위가 exp보다 낮아질때까지 반복
				x = postfixPop();	//postfixStack 스택 최상위 원소 값을 x에 저장
				charCat(&x);		//함수를 호출해 x를 postfixExp에 추가
			}
			postfixPush(*exp);	//함수를 호출해 exp를 postfixStack에 추가
		}
		exp++;	//exp 증가
	}
	while(postfixStackTop != -1) {	//postfixStack 스택이 공백이 될때까지 반복
		x = postfixPop();
		charCat(&x);		//postfixStack 스택에서 최상위 원소를 postfixExp에 추가
	}

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	char symbol;
	int op1, op2;
	int n = strlen(postfixExp);	//postfixExp의 길이를 변수 n에 저장

	for (int i = 0; i < n; i++) {	//postfixExp 길이만큼 반복
		symbol = postfixExp[i];		//symbol 변수를 postfixExp의 i+1번째 값으로 초기화
		if (getToken(symbol) == operand) {	//symbol이 피연산자 일때
			evalPush(symbol - '0');	//symbol의 ASCII값에 '0'의 ASCII 값인 48을 빼서 symbol의 결과를 숫자로 바꾸고 함수를 호출해 evalStack에 추가
		}
		else {	//sybol이 피연산자가 아닐때
			op2 = evalPop();	//evalStack 스택의 최상위 원소를 op2에 저장
			op1 = evalPop();	//evalStack 스택의 최상위 원소를 op1에 저장
			switch(getToken(symbol)) {
				case plus: evalPush(op1 + op2);		//op1 + op2 값을 evalStack에 추가
				break;
				case minus: evalPush(op1 - op2);	//op1 - op2 값을 evalStack에 추가
				break;
				case times: evalPush(op1 * op2);	//op1 * op2 값을 evalStack에 추가
				break;
				case divide: evalPush(op1 / op2);	//op1 / op2 값을 evalStack에 추가
				break;
			}
		}
	}
	evalResult = evalPop();	//evalStack의 최종 계산 결과를 변수 evalResult에 저장
}

