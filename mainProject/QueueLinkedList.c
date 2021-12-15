//implement stack and queue using linked list. (Queue)

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *front;
struct node *rear;

void insert();
void delete1();
void display();

void main()
{
    int choice, reSelection;
    do
    {
        printf("What do you want to do now?\n1.) Insert\n2.) Delete\n3.) Display\n");
        printf("Enter number corresponding to the serial number to perform respective action: ");
        scanf("%d",& choice);
        switch(choice)
        {
            case 1: {
            	insert();
				break;
			}
            case 2: {
            	delete1();
				break;
			}
            case 3: {
            	display();
				break;
			}
            default: {
            	printf("Please choose a VALID option and try again!\n");
				break;
			}
        }
        printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT MAIN PROGRAM!\n");
        scanf("%d", &reSelection);
    } while(reSelection == 1);
}

void insert()
{
    struct node *ptr;
    int item;
    ptr = (struct node *) malloc (sizeof(struct node));
    if(ptr == NULL)
    {
        printf("Queue has overflowed!\n");
        return;
    }
    else
    {
        printf("Enter the value to be queued into the Queue: ");
        scanf("%d",&item);
        ptr -> data = item;
        if(front == NULL)
        {
            front = ptr;
            rear = ptr;
            front -> next = NULL;
            rear -> next = NULL;
        }
        else
        {
            rear -> next = ptr;
            rear = ptr;
            rear->next = NULL;
        }
    }
}

void delete1()
{
    struct node *ptr;
    if(front == NULL)
    {
        printf("Queue has underflowed!\n");
        return;
    }
    else
    {
        ptr = front;
        front = front -> next;
        free(ptr);
    }
}

void display()
{
    struct node *ptr;
    ptr = front;
    if(front == NULL)
    {
        printf("The Queue is empty!\n");
    }
    else
    {   printf("The elements in the Queue are:\n");
        while(ptr != NULL)
        {
            printf("%d\n",ptr -> data);
            ptr = ptr -> next;
        }
    }
}
