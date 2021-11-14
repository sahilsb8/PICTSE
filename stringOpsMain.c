/*Perform string operations without using the
library functions (With pointers to array).*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#define size 100

void subStringOp(char*,char*);
void palindrome(char*);
void compare(char*,char*);
void copy(char[]);
void reverse(char*);

void main()
{
    char a[size];
    char b[size];
    char *x,*y;
    int selection, subSelection, reSelection;
    printf("Enter the  first string(1): ");
    gets(a);
    printf("Enter the  second string(2): ");
    gets(b);
    printf("String (1) is: %s\n", a);
    printf("String (2) is: %s\n", b);
    x = a;
    y = b;
    do
    {
    	printf("What action do you want to perform?\n1.) Substring\n2.) Palindrome\n3.) Compare\n4.) Copy\n5.) Reverse\n");
		printf("Enter number corresponding to the serial number to perform respective action: ");
        scanf("%d",&selection);
        switch(selection)
        {
        case 1: {
        	subStringOp(x,y);
			break;
		}
        case 2: {
        	printf("Which string would you like to choose?\n1.) String(1)\n2.) String(2)\n");
 			printf("Enter number corresponding to the serial number to perform respective action: ");
            scanf("%d",&subSelection);
            switch(subSelection)
            {
            case 1: {
            	palindrome(x);
				break;
			}
            case 2: {
            	palindrome(y);
				break;
			}
			default: {
				printf("Please choose a VALID option and try again!");
				break;
			}
            }
			break;
		}
        case 3: {
        	compare(x,y);
			break;
		}
        case 4: {
        	printf("Which string would you like to choose?\n1.) String(1)\n2.) String(2)\n");
 			printf("Enter number corresponding to the serial number to perform respective action: ");
            scanf("%d",&subSelection);
            switch(subSelection)
            {
            case 1: {
            	copy(a);
				break;
			}
			case 2: {
				copy(b);
				break;
			}
			default: {
				printf("Please choose a VALID option and try again!");
				break;
			}
			}
			break;
		}
        case 5: {
        	printf("Which string would you like to choose?\n1.) String(1)\n2.) String(2)\n");
 			printf("Enter number corresponding to the serial number to perform respective action: ");
            scanf("%d",&subSelection);
            switch(subSelection)
            {
            case 1: {
            	reverse(x);
				break;
			}
			case 2: {
				reverse(y);
				break;
			}
			default: {
				printf("Please choose a VALID option and try again!");
				break;
			}
            }
			break;
		}        
        default: {
        	printf("Please choose a VALID option and try again!");
			break;
		}
        }
        printf("Do you want to perform any of the actions again? If YES enter 1 else enter 0 to EXIT!\n");
        scanf("%d", &reSelection);
    } while(reSelection == 1);
}

void copy(char *str)
{
	char strCpy[size];
	char *temp;
	temp = strCpy;
	while(*str != '\0')
	{
	    *temp = *str;
		temp++;
		str++;
	}
	printf("The copied string is %s\n", strCpy);
	//puts(strCpy);
}

void compare(char *str,char *str2)
{
    int i = 0;
    int flag = 0;
    while ((*str != '\0') && (*str2 != '\0'))
    {
        if (*str2 == *str)
        {
            str2++;
            str++;
        }
        else
		{
            flag = 1;
            printf("Strings DONT match and are different!\n");
            break;
        }
    }
    if (flag==0)
    {
        printf("The strings match!\n");
    }
}

void subStringOp(char *str,char *subStr)
{
    int i = 0;
    int j = 0;
	while(*str != '\0' && *subStr != '\0')
	{
		if(*str != *subStr)
		{
			i++;
			j = 0;
			str++;
		}
		else
		{
			i++;
			j++;
			subStr++;
		}
	}
	if(*subStr == '\0')
	{
		printf("Substring found!\n");
	}
	else
	{
		printf("Substring NOT found!\n");
	}
}

void palindrome(char* str)
{
	int i;
	int j = strlen(str) - 1;
	int flag = 1;
	for(i = 0; i <= strlen(str) / 2; i++)
	{
		if(str[i] == str[j])
		{
			j--;
		}
		else
		{
			flag = 0;
			printf("String is not palindrome!\n");
			break;
		}
	}	
	if(flag == 1)
	{
		printf("String is palindrome!\n");
	}
}

void reverse(char* str)
{
	printf("Before reversing the string is: %s\n", str);
	int i, len, temp;
	len = strlen(str);
	for(i = 0; i < len / 2; i++)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
	printf("After reversing the string is: %s\n", str);
}
