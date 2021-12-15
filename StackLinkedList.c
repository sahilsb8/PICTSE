//implement stack and queue using linked list. (Stack)

#include <stdio.h>
#include <stdlib.h>

struct node
{
	int val;
	struct node *next;
};

struct node *head;

void push();
void pop();
void display();

void main ()
{
    int choice, reSelection;
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
            }
    	}
    	printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT MAIN PROGRAM!\n");
        scanf("%d", &reSelection);
	} while(reSelection == 1);
}

void push ()
{
    int val;
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    if(ptr == NULL)
    {
        printf("Stack has overflowed!\n");
    }
    else
    {
        printf("Enter the value to be Pushed into the stack: ");
        scanf("%d",&val);
        if(head == NULL)
        {
            ptr->val = val;
            ptr -> next = NULL;
            head = ptr;
        }
        else
        {
            ptr->val = val;
            ptr->next = head;
            head = ptr;

        }
        printf("Item pushed!\n");
    }
}

void pop()
{
    int item;
    struct node *ptr;
    if (head == NULL)
    {
        printf("Stack has underflowed!\n");
    }
    else
    {
        item = head->val;
        ptr = head;
        head = head->next;
        free(ptr);
        printf("Item popped!\n");

    }
}

void display()
{
    int i;
    struct node *ptr;
    ptr=head;
    if(ptr == NULL)
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("The elements in the Stack are:\n");
        while(ptr!=NULL)
        {
            printf("%d\n", ptr->val);
            ptr = ptr->next;
        }
    }
}
