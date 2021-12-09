//Implementation of stack using Arrays

#include<stdio.h>
#include<conio.h>

void push();
void pop();
void display();
void queuef();
void enqueue();
void displayQ();

int stack[100], sizeS, top, pushElement, i;
int queue[100], sizeQ, front, rear;

int main()
{
    top = -1;
    rear = - 1;
	front = - 1;
    int choice, selection, reSelection, StackReSelection, QueueReSelection;
    do
    {
    	printf("Do you want to perform actions on:\n1.) Stack\n2.) Queue\n");
    	printf("Enter number corresponding to the serial number to perform respective action: ");
        scanf("%d",&selection);
    	switch(selection)
    	{
    		case 1: {
    			printf("Enter the size of Stack(Max = 100): ");
    			scanf("%d",&sizeS);
    			do
    			{
    				printf("What do you want to do now?\n1.) Push\n2.) Pop\n3.) Display\n");
					printf("Enter number corresponding to the serial number to perform respective action: ");
        			scanf("%d",&choice);
        			switch(choice)
        			{
            			case 1:
            			{
                			push();
                			break;
            			}
            			case 2:
            			{
               				pop();
                			break;
            			}
            			case 3:
            			{
                			display();
                			break;
            			}
            			default:
            			{
                			printf("Please choose a VALID option and try again!\n");
                			break;
            			} 
        			}
        			printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT STACK PROGRAM!\n");
        			scanf("%d", &StackReSelection);
				} while(StackReSelection == 1);
				break;
			}
			case 2: {
				printf("Enter the size of Queue(Max = 100): ");
    			scanf("%d",&sizeQ);
				do
				{
					printf("What do you want to do now?\n1.) Queue\n2.) Enqueue\n3.) Display\n");
					printf("Enter number corresponding to the serial number to perform respective action: ");
        			scanf("%d",&choice);
        			switch(choice)
        			{
        				case 1: {
        					queuef();
							break;
						}
						case 2: {
							enqueue();
							break;
						}
						case 3: {
							displayQ();
							break;
						}
						default:
						{
							printf("Please choose a VALID option and try again!\n");
                			break;
						}
					}
					printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT QUEUE PROGRAM!\n");
        			scanf("%d", &QueueReSelection);
				} while(QueueReSelection == 1);
				break;
			}
		}
		printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT MAIN PROGRAM!\n");
        scanf("%d", &reSelection);
	} while(reSelection == 1);
    return 0;
    getch();
}

void push()
{
    if(top >= (sizeS - 1))
    {
        printf("Stack has overflowed!\n");
    }
    else
    {
        printf("Enter the value to be Pushed into the stack: ");
        scanf("%d", &pushElement);
        top++;
        stack[top] = pushElement;
    }
}

void pop()
{
    if(top <= -1)
    {
        printf("Stack has underflowed!\n");
    }
    else
    {
        printf("The popped element is %d\n", stack[top]);
        top--;
    }
}

void display()
{
    if(top >= 0)
    {
        printf("The elements in the Stack are:\n");
        for(i = top; i >= 0; i--)
        {
        	printf("%d\n", stack[i]);
		}
    }
    else
    {
        printf("The Stack is empty!\n");
    }
}

void queuef()
{
    int queueItem;
    if(rear == (sizeQ - 1))
    {
    	printf("Queue has overflowed!\n");
	}
    else
	{
		if(front == -1)
		{
			front = 0;
		}
        printf("Enter the value to be queued into the Queue: ");
        scanf("%d", &queueItem);
        rear++;
        queue[rear] = queueItem;
    }
}

void enqueue()
{
    if ((front == -1) || (front > rear))
    {
        printf("Queue has underflowed!\n");
        return ;
    }
    else
    {
        printf("Element enqueued from queue is %d\n", queue[front]);
        front++;
    }
}

void displayQ()
{
    int j;
    if (front == -1)
	{
		printf("The Queue is empty!\n");
	}
    else
    {
        printf("The elements in the Queue are:\n");
        for (j = front; j <= rear; j++)
		{
			printf("%d\n", queue[j]);
		}
    }
}
