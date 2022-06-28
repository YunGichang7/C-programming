#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)
#define MAX_STACK_SIZE 60

int stack[MAX_STACK_SIZE];
int top;


void init_stack(void)
{
	top = -1;
}

int push(int t) {

	if (top >= MAX_STACK_SIZE - 1)
	{
		return -1;
	}

	stack[++top] = t; 
	return t;
}

int pop(void) {
	if (top < 0)
	{
		return -1;
	}
	return stack[top--];
}


void print_stack(void)
{
	int i;
	for (i = top; i >= 0; i--) {
		printf("%-6d", stack[i]);
	}
}


int get_stack_top(void) {
	return (top < 0) ? -1 : stack[top];
}


int is_stack_empty(void) {
	return (top < 0);
}


int is_operator(int s) {
	return (s == '+' || s == '-' || s == '*' || s == '/' || s == '%');
}


int is_legal(char* s) {
	int l = 0;

	while (*s) 
	{
		while (*s == ' ') 
		{
			s++;
		}

		if (is_operator(*s))
		{
			l--;
		}
		else
		{
			l++;
			while (*s != ' ')
			{
				s++;
			}
		}
		if (l < 1) break;
		s++;
	}
	return (l == 1);
}


int precedence(int op)
{
	if (op == '(') return 0;
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/' || op == '%') return 2;
	else return 3;
}


void postfix(char* pn, char* in)
{
	char c;
	init_stack();
	while (*in) {
		if (*in == '(') {
			push(*in);
			in++;
		}
		else if (*in == ')')
		{
			while (get_stack_top() != '(')
			{
				*pn++ = pop();
				*pn++ = ' ';
			}
			pop();
			in++;
		}
		else if (is_operator(*in))
		{
			while (!is_stack_empty() &&
				precedence(get_stack_top()) >= precedence(*in))
			{

				*pn++ = pop();
				*pn++ = ' ';
			}
			push(*in);
			in++;
		}
		else if (*in >= '0' && *in <= '9')
		{
			do
			{
				*pn++ = *in++;
			} while (*in >= '0' && *in <= '9');
			*pn++ = ' ';
		}
		else
		{
			in++;
		}
	}

	while (!is_stack_empty())
	{
		*pn++ = pop();
		*pn++ = ' ';
	}
	--pn;
	*pn = NULL;
}


int eval(char* p)
{
	int i;
	init_stack();
	while (*p)
	{
		if (*p >= '0' && *p <= '9')
		{
			i = 0;
			do
			{
				i = i * 10 + *p - '0';
				p++;
			} while (*p >= '0' && *p <= '9');
			push(i);
		}
		else if (*p == '+')
		{
			push(pop() + pop());
			p++;
		}
		else if (*p == '*')
		{
			push(pop() * pop());
			p++;
		}
		else if (*p == '-')
		{
			i = pop();
			push(pop() - i);
			p++;
		}
		else if (*p == '/')
		{
			i = pop();
			push(pop() / i);
			p++;
		}
		else if (*p == '%')
		{
			i = pop();
			push(pop() % i);
			p++;
		}
		else
		{
			p++;
		}
	}
	return pop();
}

void bufcleaner()
{
	char ch;
	do
	{
		ch = getchar();
	} while ((ch != EOF) && (ch != '\n'));
}

int main()
{
	char in[256];
	while (1)
	{

		int r, i;
		char in[256];
		char pf[256];
		printf("입력 스트링:");
		gets_s(in);
		postfix(pf, in);


		if (!is_legal(pf))
		{
			printf("");
			printf("\n");
		}

		else
		{
			printf("Postfix 형태: %s\n", pf);
			r = eval(pf);   //후위표기식 계산한 값 저장
			printf("계산 결과: %d\n", r);
		}
		if (!strcmp(in, "END-OF-OUTPUT")) break;
	}
	return 0;
}
