

/**
* @file MyGroupMain.c
* @author nirWiener
* @version 1.0
* @date 18 Nov 2015
*
* @brief chekc's if the given group is an ablien group
*
*
* @section LICENSE
* This program is not a free software;
* 
*
*
* @section DESCRIPTION
*
* @Output
*
-----------------------------------------------------------------------*/
#include "Epsilon.h"
#include "GenGroup.h"
#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//------------------------------------------------------------------------

#define EQUALE 0
#define NUM_1_IS_BIGGER 1
#define NUM_2_IS_BIGGER -1
#define INT_ARRAY_LEN 2
#define COMPLEX_ARRAY_LEN 4
//------------------------------------------------------------------------

static int gRes = 0;

/*
*==================================================================================================
*@brief given too number's return the wich is bigger.
*@param num1 - an int number.
*@param num2 - an int number.
*@return 0 if thre equle 1 if the first number is bigger else -1.
*==================================================================================================
*/
static int compareInt(const int *num1 , const int *num2)
{


	if(*num1 == *num2)
	{
		return EQUALE;
	}
	if (*num1 > *num2)
	{
		return NUM_1_IS_BIGGER;
	}
	return NUM_2_IS_BIGGER;
}

/*
*==================================================================================================
@brief given an int free the int.
* becuase we cant  free int that func do not do enthing, it does do num = num in order to not get
* an warning from the compiler!!!!
*==================================================================================================
*/
static void freeInt(const int *num)
{
	
	num = num;
}

/*
*==================================================================================================
*@brief given too number's return the result of the mult between them.
*@param num1 - an int number.
*@param num2 - an int number.
*@return the new number.
*==================================================================================================
*/
static int* multInt(const int *num1 , const int *num2)
{
	
	int *result;
	gRes = (*num1) * (*num2);
	result = &gRes;
	
	return result;
}

/**
*==================================================================================================
*@brief create an int number group and check's if the group is an ablien group.
*print the information to the user.
*this is an example of an not int ablien group. 
*==================================================================================================
*/
static void intNotAblienGroup()
{

	int a = 1;
	int b = 0; 
	int  *idnum1;
	int  *num2;
	idnum1 = &a;
	num2 = &b;
	int* members[INT_ARRAY_LEN] = {idnum1 , num2};
	printf("/////////////////////////////////////////////////////\n");
	printf("Int Group with regular Int add function\n");
	printf("Identity number: %d\n", *idnum1);
	printf("Grup members : %d ; %d \n", *idnum1 , *num2 );
	if(isAbelianGroup(idnum1 , (GroupMemberP*)members , INT_ARRAY_LEN, (GroupMemberP)&multInt, 
	   (GroupMemberP)&freeInt , (GroupMemberP)&compareInt))
	{
		printf("This is an Ablien group\n");
	}
	else
	{
		printf("This is not an Ablien group\n");
	}
	printf("/////////////////////////////////////////////////////\n");
}

/**
*==================================================================================================
*@brief create an int number group and check's if the group is an ablien group.
*print the information to the user.
*this is an example of an int ablien group. 
*==================================================================================================
*/
static void intAblienGroup()
{
	
	int a = 1;
	int b = -1; 
	int  *idnum1;
	int  *num2;
	idnum1 = &a;
	num2 = &b;
	int* members[INT_ARRAY_LEN] = {idnum1 , num2};
	printf("/////////////////////////////////////////////////////\n");
	printf("Int Group with regular Int add function\n");
	printf("Identity number: %d\n", *idnum1);
	printf("Grup members : %d ; %d \n", *idnum1 , *num2 );
	if(isAbelianGroup(idnum1 , (GroupMemberP*)members , INT_ARRAY_LEN, (GroupMemberP)&multInt, 
	   (GroupMemberP)&freeInt , (GroupMemberP)&compareInt))
	{
		printf("This is an Ablien group\n");
	}
	else
	{
		printf("This is not an Ablien group\n");
	}
	printf("/////////////////////////////////////////////////////\n");
}

/**
*==================================================================================================
*@brief create an complex number group and check's if the group is an ablien group.
*print the information to the user.
*this is an example of an not complex ablien group. 
*==================================================================================================
*/
static void complexNotAblienGroup()
{
	
	
	char * idnum1 = "1,0i";
	char * num2 = "0,0i";
	char *num3 = "-1,0i";
	char *num4 = "0,-1i"; 
	ComplexP ComplexNum1 = fromCharFunc(idnum1);
	ComplexP ComplexNum2 = fromCharFunc(num2);
	ComplexP ComplexNum3 = fromCharFunc(num3);
	ComplexP ComplexNum4 = fromCharFunc(num4);
	ComplexP members[COMPLEX_ARRAY_LEN] = {ComplexNum1, ComplexNum2, ComplexNum3, ComplexNum4};
	printf("/////////////////////////////////////////////////////\n");
	printf("Complex Group with regular Complex mult function\n");
	printf("Identity number: %s\n", idnum1);
	printf("Grup members : %s ; %s ; %s ; %s\n" , idnum1 , num2 , num3 , num4);
	if(isAbelianGroup(ComplexNum1 , (GroupMemberP*)members , COMPLEX_ARRAY_LEN, (GroupMemberP)&mult, 
	   (GroupMemberP)&freeComplex , (GroupMemberP)getCompareFunc()))
	{
		printf("This is an Ablien group\n");
	}
	else
	{
		printf("This is not an Ablien group\n");
	}
	printf("/////////////////////////////////////////////////////\n");
	freeComplex(ComplexNum1);
	freeComplex(ComplexNum2);
	freeComplex(ComplexNum3);
	freeComplex(ComplexNum4);

}

/**
*==================================================================================================
*@brief create an complex number group and check's if the group is an ablien group.
*print the information to the user.
*this is an example of an complex ablien group. 
*==================================================================================================
*/
static void complexAblienGroup()
{
	
	
	char * idnum1 = "1,0i";
	char * num2 = "0,1i";
	char *num3 = "-1,0i";
	char *num4 = "0,-1i"; 
	ComplexP ComplexNum1 = fromCharFunc(idnum1);
	ComplexP ComplexNum2 = fromCharFunc(num2);
	ComplexP ComplexNum3 = fromCharFunc(num3);
	ComplexP ComplexNum4 = fromCharFunc(num4);
	ComplexP members[COMPLEX_ARRAY_LEN] = {ComplexNum1, ComplexNum2, ComplexNum3, ComplexNum4};


	printf("/////////////////////////////////////////////////////\n");
	printf("Complex Group with regular Complex mult function\n");
	printf("Identity number: %s\n", idnum1);
	printf("Grup members : %s ; %s ; %s ; %s\n", idnum1 , num2 , num3 , num4);
	if(isAbelianGroup(ComplexNum1 , (GroupMemberP*)members , COMPLEX_ARRAY_LEN, (GroupMemberP)&mult, 
	   (GroupMemberP)&freeComplex, (GroupMemberP)getCompareFunc()))
	{
		printf("This is an Ablien group\n");
	}
	else
	{
		printf("This is not an Ablien group\n");
	}
	printf("/////////////////////////////////////////////////////\n");
	freeComplex(ComplexNum1);
	freeComplex(ComplexNum2);
	freeComplex(ComplexNum3);
	freeComplex(ComplexNum4);
}

/**
*==================================================================================================
*@brief run the check's for the ablien groups. 
*==================================================================================================
*/
int main()
{
	complexAblienGroup();
	complexNotAblienGroup();
	intNotAblienGroup();
	intAblienGroup();
    return 0;
}
