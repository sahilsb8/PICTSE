//Create a singly linked list with options:
//a. Insert (at front, at end, in the middle), b. Delete (at front, at end, in the middle)
//c. Display,d. Display Reverse,e. Revert the SLL

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void create();
void display();
void insert_begin();
void insert_end();
void insert_pos();
void delete_begin();
void delete_end();
void delete_pos();
void reverseList();

struct node
{
	int info;
	struct node *next;
};

struct node *start=NULL;
struct node *last=NULL;

int main()
{
	int choice, reSelection;
	do
	{
		printf("What do you want to do now?\n1.) Create\n2.) Display\n3.) Insert(At the beginning)\n4.) Insert(At the end)\n5.) Insert(At a specified location)\n");
		printf("6.) Delete(At the beginning)\n7.) Delete(At the end)\n8.) Delete(At a specified location)\n9.) Reverse\n");
		printf("Enter number corresponding to the serial number to perform respective action: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: {
				create();
				break;
			}
			case 2: {
				display();
				break;
			}
			case 3: {
				insert_begin();
				break;
			}	
			case 4: {
				insert_end();
				break;
			}
			case 5: {
				insert_pos();
				break;
			}
			case 6: {
				delete_begin();
				break;
			}
			case 7: {
				delete_end();
				break;
			}
			case 8: {
				delete_pos();
				break;
			}
			case 9: {
				reverseList();
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
	return 0;
	getch();
}

void create()
{
	struct node *temp, *ptr;
	temp = (struct node *)malloc(sizeof(struct node));
	printf("Enter the data value for the node: ");
	scanf("%d", &temp->info);
	temp->next = NULL;
	if(start == NULL)
	{
		start = temp;
	}
	else
	{
		ptr = start;
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}

void display()
{
	struct node *ptr;
	if(start == NULL)
	{
		printf("List is EMPTY!\n");
		return;
	}
	else
	{
		ptr = start;
		printf("The elements in the List are:\n");
		while(ptr != NULL)
		{
			printf("%d\n", ptr->info);
			ptr = ptr->next;
		}
	}		
}

void insert_begin()
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	printf("Enter the element to be added at the START of the List: ");
	scanf("%d",&temp->info);
	temp->next = NULL;
	if(start == NULL)
	{
		start = temp;
	}
	else
	{
		temp->next = start;
		start = temp;
	}
}

void insert_end()
{
	struct node *temp,*ptr;
	temp = (struct node *)malloc(sizeof(struct node));
	printf("Enter the element to be added at the END of the List: ");
	scanf("%d",&temp->info);
	temp->next = NULL;
	if(start == NULL)
	{
		start = temp;
	}
	else
	{
		ptr = start;
		while(ptr->next != NULL)
		{
			ptr = ptr->next ;
		}
		ptr->next = temp;
	}
}

void insert_pos()
{
	struct node *ptr, *temp;
	int i, pos;
	temp = (struct node *)malloc(sizeof(struct node));
	printf("Enter the position in the list at which the element is to be inserted: ");
	scanf("%d", &pos);
	printf("Enter the element to be added at the that position of the List: ");
	scanf("%d", &temp->info) ;
	temp->next = NULL;
	if(pos == 0)
	{
		temp->next = start;
		start = temp;
	}
	else
	{
		for(i = 0, ptr = start; i < pos - 1; i++)
		{
			ptr = ptr->next;
			if(ptr == NULL)
			{
				printf("INVALID POSITION ENTERED! TRY AGAIN!\n");
				return;
			}
		}
		temp->next = ptr->next;
		ptr->next = temp;
	}
}

void delete_begin()
{
	struct node *ptr;
	if(ptr == NULL)
	{
		printf("List is EMPTY! Nothing to delete!\n");
		return;
	}
	else
	{
		ptr = start;
		start = start->next;
		printf("The deleted element is: %d\n", ptr->info);
		free(ptr);
	}
}

void delete_end()
{
	struct node *temp, *ptr;
	if(start == NULL)
	{
		printf("List is EMPTY! Nothing to delete!\n");
		exit(0);
	}
	else if(start->next == NULL)
	{
		ptr = start;
		start = NULL;
		printf("The deleted element is: %d\n", ptr->info);
		free(ptr);
	}
	else
	{
		ptr = start;
		while(ptr->next != NULL)
		{
			temp = ptr;
			ptr = ptr->next;
		}
		temp->next = NULL;
		printf("The deleted element is: %d\n", ptr->info);
		free(ptr);
	}
}

void delete_pos()
{
	int i,pos;
	struct node *temp,*ptr;
	if(start == NULL)
	{
		printf("List is EMPTY! Nothing to delete!\n");
		exit(0);
	}
	else
	{
		printf("Enter the position in the list at which the element is to be inserted: ");
		scanf("%d",&pos);
		if(pos == 0)
		{
			ptr = start;
			start = start->next;
			printf("The deleted element is: %d\n", ptr->info);
			free(ptr);
		}
		else
		{
			ptr = start;
			for(i = 0; i < pos; i++)
			{
				temp = ptr;
				ptr = ptr->next;
				if(ptr == NULL)
				{
					printf("INVALID POSITION ENTERED! TRY AGAIN!\n");
					return;
				}
			}
			temp->next = ptr->next ;
			printf("The deleted element is: %d\n",ptr->info);
			free(ptr);
		}
	}
}

void reverseList()
{
    struct node *prevNode, *curNode;
    if(start != NULL)
    {
        prevNode = start;
        curNode = start->next;
        start = start->next;
        prevNode->next = NULL;
        while(start != NULL)
        {
            start = start->next;
            curNode->next = prevNode;
            prevNode = curNode;
            curNode = start;
        }
        start = prevNode;
        printf("The List has been Reversed! It is now as follows:\n");
        display();
    }
}
