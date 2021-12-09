//Implement database management using array of structures (WITHOUT POINTERS TO ARRAYS)

#include<stdio.h>
#include<conio.h>

struct component
{
	char name[50];
	char symbol[10];
	int value;
	float cost;
};

void display(struct component cmp[15], int count);
void append(struct component cmp[15], int count, int append_val);
void search(struct component cmp[15], int count);
void sort(struct component cmp[15], int count);
void modify(struct component cmp[15], int count);

void main()
{
	struct component cmp[15];
	int count;
	printf("How many components do you initially want to add? Enter the value: ");
	scanf("%d", &count);
	if(count < 1)
	{
		do
		{
			printf("Entered value is INVALID, try again now: ");
			scanf("%d", &count);
		} while(count < 0);
	}
	//printf("%d", count); --> debugging
	int i;
	for(i = 0; i < count; i++)
	{
		printf("Enter the name for component no. %d: ", i + 1);
		scanf("%s", &cmp[i].name);
		printf("Enter the symbol for component no. %d: ", i + 1);
		scanf("%s", &cmp[i].symbol);
		printf("Enter the value of component no. %d: ", i + 1);
		scanf("%d", &cmp[i].value);
		printf("Enter the cost of component no. %d: ", i + 1);
		scanf("%f", &cmp[i].cost);
	}
	printf("The entered components are:\n");
	display(cmp, count);
	int selection, reSelection;
	do
	{
		printf("What do you want to do now?\n1.) Append\n2.) Search\n3.) Sort\n4.) Modify\n");
		printf("Enter number corresponding to the serial number to perform respective action: ");
		scanf("%d", &selection);
		switch(selection)
		{
			case 1: {
				int append_val;
				printf("How many components do you want to append?: ");
				scanf("%d", &append_val);
				if((count + append_val) >= 15)
				{
					printf("Adding %d more components will surpass the MAX allowed number of components(15)! Delete some to add more.\n", append_val);
					break;
				}
				else
				{
					append(cmp, count, append_val);
					count += append_val;
					//clrscr();
					printf("The table of components with appended value is\n");
					display(cmp, count);
					break;
				}
			}
			case 2: {
				search(cmp, count);
				break;
			}
			case 3: {
				sort(cmp, count);
				break;
			}
			case 4: {
				modify(cmp, count);
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

void display(struct component cmp[15], int count)
{
	printf("\tSr. No.\tName of Component\tSymbol Letter\t\tValue\t\tCost(Rs.)\n");
	int j;
	for(j = 0; j < count; j++)
	{
		printf("\t%6d.\t%-17s\t%-13s\t\t%9d\t%9.2f\n", j + 1, cmp[j].name, cmp[j].symbol, cmp[j].value, cmp[j].cost);
	}
}

void append(struct component cmp[15], int count, int append_val)
{
	int i;
	for(i = count; i < (count + append_val); i++)
	{
		printf("Enter the name for component to append at no. %d: ", i + 1);
		scanf("%s", &cmp[i].name);
		printf("Enter the symbol for component to append at no. %d: ", i + 1);
		scanf("%s", &cmp[i].symbol);
		printf("Enter the value of component to append at no. %d: ", i + 1);
		scanf("%d", &cmp[i].value);
		printf("Enter the cost of component to append at no. %d: ", i + 1);
		scanf("%f", &cmp[i].cost);
	}
}

void search(struct component cmp[15], int count)
{
	int reSearchSelection;
	printf("What parameter of the component do you want to search? Please enter its Sr. No.\n");
	do
	{
		int searchSerial;
		printf("Enter the serial number you want to search: ");
		scanf("%d", &searchSerial);
		if(searchSerial > count)
		{
			printf("Serial number entered DOES NOT EXIST!\n");
		}
		else
		{
			printf("The component is:\n");
			printf("\tSr. No.\tName of Component\tSymbol Letter\t\tValue\t\tCost(Rs.)\n");
			printf("\t%6d.\t%-17s\t%-13s\t\t%9d\t%9.2f\n", searchSerial, cmp[searchSerial - 1].name, cmp[searchSerial - 1].symbol, cmp[searchSerial - 1].value, cmp[searchSerial - 1].cost);
		}
		printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT SEARCH PROGRAM!\n");
        scanf("%d", &reSearchSelection);
	}while(reSearchSelection == 1);
}

void sort(struct component cmp[15], int count)
{
	printf("The components will be sorted according to their respective costs. The sorted table is as follows:\n");
	int i, j;
	for (i = 0; i < count - 1; i++)
    {
        for (j = i; j < count; j++)
        {
            if (cmp[i].cost > cmp[j].cost)
            {
                struct component temp = cmp[i];
                cmp[i] = cmp[j];
                cmp[j] = temp;
            }
        }
    }
    display(cmp, count);
}

void modify(struct component cmp[15], int count)
{
	int selection, reSelection;
	printf("Which component do you want to want to modify? Enter Sr. No.: ");
	scanf("%d", &selection);
	if((selection < 1) || (selection > count))
	{
		do
		{
			printf("Entered value is INVALID, try again now: ");
			scanf("%d", &selection);
		} while((selection > 1) && (selection < count));
	}
	printf("Which parameter of the selected component do you want to modify?\n");
	printf("1.) Component Name\n2.) Component Symbol\n3.) Component Value\n4.) Component Cost\n");
	printf("Enter number corresponding to the serial number to perform respective action: ");
	scanf("%d", &reSelection);
	switch(reSelection)
	{
		case 1: {
			printf("Enter the Name to be changed as: ");
			scanf("%s", &cmp[selection - 1].name);
			break;
		}
		case 2: {
			printf("Enter the Symbol to be changed as: ");
			scanf("%s", &cmp[selection - 1].symbol);
			break;
		}
		case 3: {
			printf("Enter the Value to be changed as: ");
			scanf("%d", &cmp[selection - 1].value);
			break;
		}
		case 4: {
			printf("Enter the Cost to be changed as: ");
			scanf("%f", &cmp[selection - 1].cost);
			break;
		}
		default: {
			printf("Please choose a VALID option and try again!\n");
			break;
		}
	}
	printf("The table of components with Modified value is\n");
	display(cmp, count);
}

