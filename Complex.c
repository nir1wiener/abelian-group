/**
* @file Complex.c
* @author nirWiener
* @version 1.0
* @date 18 Nov 2015
*
* @brief an Complex number system
*
*
* @section LICENSE
* This program is not a free software;
* 
*
*
* @section DESCRIPTION
* holds an struct of Complex number
* an the oper mult,scalar mult and add
* and an compare func.
*
* @Output
*
-----------------------------------------------------------------------*/
#include "Epsilon.h"
#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
// ------------------------------ includes -------------------------

#define VALID_INPUT 2
#define I_SIMBUL 'i'
#define END_OF_STR '\0'
#define COMMA ','
#define FACTOR 10
#define NUMBER_OF_BYTS_AFTER_POINT 8
#define END_OF_STRING_SIMBUL 1
#define EQULE 0
#define NUM1_IS_BIGGER 1
#define NUM2_IS_BIGGER -1
#define VALID_INPUT_FOR_TO_CHAR 0

// --------------------------  definitions -------------------------

/**
 *a complex struct of the complex num
 */
typedef struct Complex
{
	double _real;
	double _img;

}Complex;


/**
*==================================================================================================
 * @brief create a new complex number
 *   
 * @param s the string that contain the number. the syntax for Complex number is 
 *'<double number>,<double number>i'
 * for example : "0,0i","1.878,78i","-768,1i".
 * @return ComplexP that is repesneted by the string. if the string do not match the 
 *syntax return NULL;
 *==================================================================================================
 */
 ComplexP fromCharFunc(char * s)
 { 

 	ComplexP newComplexNum = (ComplexP)malloc(sizeof(Complex));
 	if(newComplexNum == NULL)
 	{

 		return NULL;
 	}
 	if(sscanf(s , "%lf,%lfi", &newComplexNum->_real , &newComplexNum->_img) != VALID_INPUT)
 	{

		freeComplex(newComplexNum);
 		return NULL;		
 	}

	return newComplexNum;
 }

/**
*==================================================================================================
* @brief given a double return the number of digit before the decimal point
* exmpale:
* input: 234.55
* output: 3
*==================================================================================================
*/
 int getNumOfDigit(double num)
 {
 	int len = 0;
 	
 	if(num < 0)
 	{
 		num = num * -1;

 	}
 	while(num > 1)
 	{
 		num = num / FACTOR;
 		len++;
 	}
 	return len;

 }


 /**
 *==================================================================================================
 * @brief a string repesnets the complex number
 *   
 * @param num is the number.
 * @ str - Pointer to a buffer where the resulting C-string is stored.
 *    The buffer should have a size of at least n characters
 * @ n - Maximum number of bytes to be used in the buffer.
 *     The generated string has a length of at most n-1, leaving space for the additional 
 * terminating null character.
 * the syntax of the string should be '<double number>,<double number>i'
 * for example : "0,0i","1.878,78i","-768,1i".
 * @return  The number of characters that would have been written if n had been sufficiently large, 
 *  not counting the terminating null character.If an encoding error occurs,a negative number is 
 *returned.
 *==================================================================================================
 */
int toChar(char * str, const int n, ConstComplexP num)
{
	int error = -1;
	int real_ind = 0;
	int len = 0;
	int img_ind = 0; 
 	char * real = (char*)malloc(getNumOfDigit(num->_real) + NUMBER_OF_BYTS_AFTER_POINT);
 	char * img = (char*)malloc(getNumOfDigit(num->_img) + NUMBER_OF_BYTS_AFTER_POINT) ;
 	if(real == NULL || img == NULL)
 	{
 		free(real);
 		free(img);
 		return error;
 	} 
 	if((sprintf(real, "%lf" , num -> _real) < VALID_INPUT_FOR_TO_CHAR) || \
        (sprintf(img, "%lf" , num -> _img) < VALID_INPUT_FOR_TO_CHAR))
 	{
 	 	free(real);
 		free(img);
 		return error;	
 	}

 	while((real_ind < (int)(strlen(real))) && (real_ind < (n-END_OF_STRING_SIMBUL)))
 	{
 		str[real_ind] = real[real_ind];
 		real_ind++;
 	}
 	if ( real_ind < n-END_OF_STRING_SIMBUL)
 	{
 		str[real_ind] = COMMA;
 		
 	}
 	real_ind++;
 	while((img_ind < (int)(strlen(img))) && (real_ind + img_ind < (n-END_OF_STRING_SIMBUL)))
 	{

 		str[real_ind + img_ind] = img[img_ind];
 		img_ind++;
 		
 	}
 	if ((img_ind + real_ind) < n-END_OF_STRING_SIMBUL)
 	{
 		str[img_ind + real_ind] = I_SIMBUL;
 	}
 	str[img_ind + real_ind + END_OF_STRING_SIMBUL] = END_OF_STR;
 	
 	len = strlen(real) + strlen(img) + VALID_INPUT;
 	free(real);
 	free(img);
 	return len;
}

/**
*==================================================================================================
 * @brief create a new complex number which is the result of addition num2 to num1.
 *   
 * @param num1 - the first Complex
 * @param num1 - the second Complex
 * @return ComplexP that = num1+num2 . if num1/num2 is NULL return NULL;
*==================================================================================================
*/
ComplexP add(ConstComplexP num1, ConstComplexP num2)
{
	if(num1 == NULL || num2 == NULL)
	{
		return NULL;
	}
	ComplexP newComplexNum = (ComplexP)malloc(sizeof(Complex));
	if(newComplexNum == NULL)
	{
		return NULL;
	}
	newComplexNum->_real = num1->_real + num2->_real;
	newComplexNum->_img = num1->_img + num2->_img;
	return newComplexNum;
}


/**
*==================================================================================================
* @brief create a new complex number which is the result of multiplication of num1*num2
*   
* @param num1 - the first Complex
* @param num1 - the second Complex
* @return ComplexP that = num1*num2 . if num1/num2 is NULL return NULL;
*==================================================================================================
*/
ComplexP mult(ConstComplexP num1, ConstComplexP num2)
{
	

	if(num1 == NULL || num2 == NULL)
	{
		return NULL;
	}

 	ComplexP newComplexNum = (ComplexP)malloc(sizeof(Complex));
	if(newComplexNum == NULL)
	{
		return NULL;
	}
	newComplexNum->_real = ((num1->_real * num2->_real) - (num1->_img * num2->_img));
	newComplexNum->_img = ((num1->_real * num2->_img) + (num2->_real * num1->_img));

	return newComplexNum;

}

/**
*==================================================================================================
* @brief free the complex object
*   
* @param num is the number. 
*==================================================================================================
*/
void freeComplex(ComplexP num)
{ 
	free(num);
}

 /**
*==================================================================================================
* @brief create a new complex number which is the result of multiplication of scalar*num1
*   
* @param num1 - scalar double number
* @param num1 - the  Complex
* @return ComplexP that = scalar*num . if num is NULL return NULL;
*==================================================================================================
*/
ComplexP multScalar(const double scalar, ConstComplexP num)
{

	if(num == NULL)
	{
 		return NULL;
	}
 	ComplexP tmpComplexNum = (ComplexP)malloc(sizeof(Complex));
	if(tmpComplexNum == NULL)
	{
		return NULL;
	}

	tmpComplexNum->_real = scalar;
	tmpComplexNum->_img = 0;
	return mult(num , tmpComplexNum);
}

/**
*==================================================================================================
 *a function that gets 2 Complex pointers (num1,num2) and return int as following:
 *        0 - iff |num1-num2| <EPSILON
 *        otherwize:
 *                >0 if num1>num2
 *                <0 if num2<num1
 *==================================================================================================
 */

static int compereToEpsilon(ConstComplexP num1 , ConstComplexP num2)
{
		
	double numReal = fabs((num1->_real) - (num2->_real));
	double numImg = fabs((num1->_img) - (num2->_img));

	if (numReal < EPSILON && numImg < EPSILON)
	{
		
			return EQULE;
	
	}
	if(num1->_real > num2->_real)
	{
		return NUM1_IS_BIGGER;
	}
	if(num1->_real < num2->_real)
	{
		return NUM2_IS_BIGGER;
	}
	if( num1->_img > num2->_img)
	{
		return NUM1_IS_BIGGER;
	}
	if(num1->_img < num2->_img)
	{
		return NUM2_IS_BIGGER;
	}	
	return EQULE;
}

 /**
 *==================================================================================================
 * @brief create a pointer to a function that compare complex numbers with EPSILON
 *  function name:getCompareFunc
 * use the lexicographic order, comparing the real parts and then comparing the imaginary ones if the 
 *real parts are equal
 * @return a pointer to a function that gets 2 Complex pointers  and return int as following:
 *        0 - iff |num1-num2| <EPSILON
 *        otherwize:
 *                >0 if num1>num2
 *                <0 if num2<num1
 *==================================================================================================
 */

 int ((*getCompareFunc())(ConstComplexP num1 , ConstComplexP num2))
{
	return &compereToEpsilon;
}

