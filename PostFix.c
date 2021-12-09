//Evaluate postfix expression (input will be postfix expression).

#include<stdio.h>
#include<conio.h>
#define MAX 100

void push(int pushedItem);
int pop();
void postFix(char postfix[]);

int stack[MAX];
int top = -1;

int main()
{
	int i;
	char postfix[MAX];
	printf("Enter the PostFix expression to evaluate: ");
	for(i = 0; i <= MAX - 1; i++)
	{
		scanf("%c", &postfix[i]);
		if(postfix[i] == '\n')
		{
			break;
		}
	}
	postFix(postfix);
	return 0;
    getch();
}

void push(int pushedItem)
{
    if(top >= (MAX - 1))
    {
        printf("Stack has overflowed!\n");
        return;
    }
    else
    {
        //printf("Enter the value to be Pushed into the stack: ");
        //scanf("%d", &pushedItem);
        top++;
        stack[top] = pushedItem;
    }
}

int pop()
{
	int poppedItem;
    if(top <= -1)
    {
        printf("Stack has underflowed!\n");
    }
    else
    {
    	poppedItem = stack[top];
        //printf("The popped element is %d\n", stack[top]);
        top--;
        return poppedItem;
    }
}

void postFix(char postfix[])
{
	int i, A, B, val;
	char c;
	for(i = 0; postfix[i] != '\n'; i++)
	{
		c = postfix[i];
		if(isdigit(c))
		{
			push(c - '0'); //Gives digit instead of ASCII
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/')
		{
			A = pop();
			B = pop();
			switch(c)
			{
				case '*': {
					val = B * A;
					break;
				}
				case '/': {
					val = B / A;
					break;
				}
				case '+': {
					val = B + A;
					break;
				}
				case '-': {
					val = B - A;
					break;
				}
			}
			push(val);
		}
	}
	printf("The Evaluation of the PostFix expression is: %d\n", pop());
}
