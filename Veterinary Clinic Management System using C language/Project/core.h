
// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
//guarantee an integer value is entered and returned.
int inputInt(void);

//guarantee a positive integer value is entered and returned.
int inputIntPositive(void);

//guarantee an integer value is entered within the range (inclusive) and returned.
int inputIntRange(int Min, int Max);

//Guarantee a single character value is entered within the list of valid
//characters (as defined by the C string argument received) and returned.
char inputCharOption(const char inputChar[]);

//guarantees a C string value is entered containing the number of characters
//within the range specified by the 2nd and 3rd arguments (and return via the 1st
//argument pointer).
void inputCString(char *string, int Min, int Max);

// guarantees a number is only printed when it is correct
void displayFormattedPhone(const char *string);





// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
