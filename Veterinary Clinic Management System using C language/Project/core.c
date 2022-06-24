
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

#include "core.h"

// As demonstrated in the course notes:

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
// guarantee an integer value is entered and returned.
int inputInt(void)
{
    char newline;
    int number;
    do
    {
        scanf("%d%c", &number, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newline != '\n');
    return number;
}
// guarantee a positive integer value is entered and returned.
int inputIntPositive(void)
{
    int number;
    int repeat = 0;
    do
    {
        number = inputInt();
        if (number <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            repeat = 1;
        }

    } while (repeat != 1);
    return number;
}
// guarantee an integer value is entered within the range (inclusive) and returned.
int inputIntRange(int Min, int Max)
{
    int number;
    int repeat = 0;
    do
    {
        number = inputInt();
        if (number < Min || number > Max)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", Min, Max);
        }
        else
        {
            repeat = 1;
        }
    } while (repeat != 1);
    return number;
}

// Guarantee a single character value is entered within the list of valid
// characters (as defined by the C string argument received) and returned.
char inputCharOption(const char inputChar[])
{
    char input;
    int repeat = 1;
    char newline;
    do
    {
        scanf("%c%c", &input, &newline);
        if (strchr(inputChar, input) == NULL || newline != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", inputChar);
            clearInputBuffer();
        }
        else
        {
            repeat = 0;
        }
    } while (repeat == 1);
    return input;
}

// guarantees a C string value is entered containing the number of characters
// within the range specified by the 2nd and 3rd arguments (and return via the 1st
// argument pointer).
void inputCString(char *string, int Min, int Max)
{
    int length = 0;
    int repeat = 1;
    char tmp[100] = {0};
    int i;
    do
    {
        scanf("%[^\n]", tmp);
        clearInputBuffer();
        length = strlen(tmp);
        if ((length < Min || length > Max) && (Min == Max))
        {
            printf("Invalid %d-digit number! ", Max);
            printf("Number: ");
        }
        else if (length > Max && Min != Max)
        {
            printf("ERROR: String length must be no more than %d chars: ", Max);
            printf("Number: ");
        }
        else if ((length < Min || length > Max) && (Min != Max))
        {
            printf("ERROR: String length must be between %d and %d chars: ", Min, Max);
            printf("Number: ");
        }
        else
        {
            repeat = 0;
        }

    } while (repeat);
    for (i = 0; i < length; i++)
    {
        string[i] = tmp[i];
    }
    string[i] = '\0';
    // printf("%s\n", string);
}

// guarantees a number is only printed when it is correct
void displayFormattedPhone(const char *string)
{
    int i;
    int length = 0;
    int correct = 1;
    // char *address = string;
    if (string != NULL)
    {
        length = strlen(string);
    }
    if (length != 10)
    {
        printf("(___)___-____");
        correct = 0;
    }
    for (i = 0; i < length; i++)
    {
        if (!((string[i] > 47) && (string[i] < 58)))
        {
            printf("(___)___-____");
            correct = 0;
        }
    }
    if (correct == 1)
    {
        printf("(%c%c%c)%c%c%c-%c%c%c%c",
               *string,
               string[1],
               string[2],
               string[3],
               string[4],
               string[5],
               string[6],
               string[7],
               string[8],
               string[9]);
    }
}