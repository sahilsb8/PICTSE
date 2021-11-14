/*Perform string operations without using the
library functions (Without pointers to array).*/

#include <stdio.h>
#include<conio.h>
#define size 100

int length(char str[]);
void subStringOp(char str[], char subStr[]);
void palindrome(char str[]);
void compare(char str[],char str2[]);
void copy(char str[], char strCpy[]);
void reverse(char str[]);

void main()
{
    char a[size];
    char b[size];
    int selection, subSelection, reSelection;
    printf("Enter the  first string(1): ");
    gets(a);
    printf("Enter the  second string(2): ");
    gets(b);
    printf("String (1) is: %s\n", a);
    printf("String (2) is: %s\n", b);
    do
    {
    	printf("What action do you want to perform?\n1.) Substring\n2.) Palindrome\n3.) Compare\n4.) Copy\n5.) Reverse\n");
		printf("Enter number corresponding to the serial number to perform respective action: ");
        scanf("%d",&selection);
        switch(selection)
        {
        case 1: {
        	subStringOp(a, b);
			break;
		}
        case 2: {
        	printf("Which string would you like to choose?\n1.) String(1)\n2.) String(2)\n");
 			printf("Enter number corresponding to the serial number to perform respective action: ");
            scanf("%d",&subSelection);
            switch(subSelection)
            {
            case 1: {
            	palindrome(a);
				break;
			}
            case 2: {
            	palindrome(b);
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
        	compare(a, b);
			break;
		}
        case 4: {
        	copy(a, b);
			break;
		}
        case 5: {
        	printf("Which string would you like to choose?\n1.) String(1)\n2.) String(2)\n");
 			printf("Enter number corresponding to the serial number to perform respective action: ");
            scanf("%d",&subSelection);
            switch(subSelection)
            {
            case 1: {
            	reverse(a);
				break;
			}
			case 2: {
				reverse(b);
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
    getch();
}

int length(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        i++;
    }
    return i;
}

void subStringOp(char str[], char subStr[])
{
    int i = 0;
    int j = 0;
    while(str[i] != '\0')
    {
        if(str[i] == subStr[j])
        {
            j++;
        }
        else
        {
            j = 0;
        } 
        i++;
        if(j == length(subStr))
        {
            printf("Substring found!\n");
            break;
        }  
    }
    if(j != length(subStr))
    {
        printf("Substring NOT found!\n");
    }       
}

void palindrome(char str[])
{
    int i = 0;
    int j = length(str) - 1;
    while(i < (length(str) / 2))
    {
        if (str[i] == str[j])
        {
            i++;
            j--;
        }
        else
        {
            printf("String is not palindrome!\n");
            break;
        }
    }
    if (i == (length(str) / 2))
    {
        printf("String is palindrome!\n");
    } 
}

void compare(char str[],char str2[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != str2[i])
        {
            printf("Strings DONT match and are different!\n");
            break;
        }
        else if (i == (length(str) - 1))
        {
            printf("The strings match!\n");
            break;
        }
        else
        {
            i++;   
        }   
    }
}

void copy(char str[], char strCpy[])
{
    int i;
    for(i = 0; i <= (length(str) - 1); i++)
    {
        strCpy[i] = str[i];
        if(str[i] == '\0')
        {
            break;
        }      
    }
    printf("The Original String is: %s\n", str);
    printf("The copied string is: %s\n", strCpy); 
}

void reverse(char str[])
{
    int i;
	int j = length(str)-1;
    char temp;
    for (i = 0; i <= (j / 2); i++)
    {
        temp = str[i];
        str[i] = str[j - i];
        str[j - i] = temp;
    } 
    printf("After reversing the string is: %s\n", str);
}

