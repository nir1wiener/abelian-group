/**
* @file GenGroup.c
* @author nirWiener
* @version 1.0
* @date 18 Nov 2015
*
* @brief an gen progrem to check if the given group is ablien
*
*
* @section LICENSE
* This program is not a free software;
* 
*
*
* @section DESCRIPTION
* given an group check if the group hold's all
* the exsioms of an ablien group.
*
*
* @Output
: true if the group is ablien 
* else false.

*
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ------------------------------ includes -------------------------

#define NUM_ARE_EQUALE 0
#define NUM_IN_LIST 1
#define NUM_NOT_IN_LIST -1
// --------------------------  definitions -------------------------


typedef void * GroupMemberP;

/**
*==================================================================================================
 * @brief return the result of add(f(n),g(n))
 *   function name:addFunctions  
 * @param add pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that 
 *is the result of the an opreation  on them.
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @return the result of add(f(n),g(n)).  In case of an error return NULL.
*==================================================================================================
 */
GroupMemberP addFunctions(GroupMemberP (*add)(GroupMemberP a , GroupMemberP b), 
						  GroupMemberP (*f)(GroupMemberP a),
						  GroupMemberP (*g)(GroupMemberP b), GroupMemberP n,
						  void (*freeMember)(GroupMemberP c))
{

	if (add == NULL || f == NULL || g == NULL || n == NULL || freeMember == NULL)
	{
		return NULL;
	}
	GroupMemberP fFunc = f(n);
	GroupMemberP gFunc = g(n);

	if( gFunc == NULL || fFunc == NULL)
	{
		freeMember(gFunc);
		freeMember(fFunc);
		return NULL;
	}
	GroupMemberP addFunc = add(fFunc , gFunc);
	if (addFunc == NULL)
	{
		freeMember(gFunc);
		freeMember(fFunc);
		return NULL;
	}
	
	freeMember(gFunc);
	freeMember(fFunc);
	return addFunc;
}

/**
*==================================================================================================
 * @brief return the result of f(g(n))
 *   function name:composeFunctions
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @return the result of f(g(n)).  In case of an error return NULL.
*==================================================================================================
 */
GroupMemberP composeFunctions(GroupMemberP (*f)(GroupMemberP a) , 
							  GroupMemberP(*g)(GroupMemberP b) , GroupMemberP n,
							  void (*freeMember)(GroupMemberP c))
{
	if(f == NULL || g == NULL || n == NULL || freeMember == NULL)
	{
		return NULL;
	}
	GroupMemberP gFunc = g(n);
	if (gFunc == NULL)
	{
		return NULL;
	}
	GroupMemberP fgFunc = f(gFunc);
	if(fgFunc == NULL)
	{
		freeMember(gFunc);
		return NULL;
	}	
	
	freeMember(gFunc);

	return fgFunc;

}

/**
*==================================================================================================
 * @brief check if the given number is in the list
 *   function name:isNumInList
 * @param members - the list to check if the number is in  
 * @param len - thr len of the list.
 * @param numToFind - the number to check.
 * @param compare - the compare the func.
 * @return 1 if the number is in the  list -1 else.
 * runing time:
 *      o(n): to check if an num is an a list, in the worst case we will go on the the 
 *      elements in the  list, and do a compare between them in o(1) so we will get  o(n)
*==================================================================================================
 */
static int isNumInList(GroupMemberP members[], const int len , GroupMemberP numToFind, 
					   int (*compare)(GroupMemberP a , GroupMemberP b))
{

	for(int i = 0 ; i < len ; i++)
	{

		if(compare(members[i] , numToFind) == NUM_ARE_EQUALE)
		{
			return NUM_IN_LIST;
		}
	}

	return NUM_NOT_IN_LIST;
}

/**
*==================================================================================================
* @brief check if the given arguments  
* are NULL print the if so print error message to stderr :
* "Error : <argument_name> is NULL\n"
*   
* @param IdentityElement - The  identity element.
* @param members A struct of GroupMemberP which contain ALL the group members 
* @param oper pointer to A function that gets 2 GroupMemberP objects and return
* a GroupMemberP that is the result of the opreation  on them.
* @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
* @param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff 
*the first is bigger; 
        <0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the 
        diffrent between them is <EPSILON).
* @return true if the pramters are not null.  In case of an null parmeter return false.
 * runing time:
 *      o(1): to check if an argu is null  or not
*==================================================================================================
*/
static bool isNull(GroupMemberP IdentityElement, GroupMemberP members[],
				   GroupMemberP (*oper)(GroupMemberP a, GroupMemberP b)
				   , void (*freeMember)(GroupMemberP a), int (*compare)(GroupMemberP a, 
				   GroupMemberP b))
{
	
	if(IdentityElement == NULL)
	{
		printf("Error : IdentityElement is NULL\n");
		return false;
	}
	if(members == NULL)
	{
		printf("Error : memberst is NULL\n");
		return false;
	}
	if(oper == NULL)
	{
		printf("Error : oper is NULL\n");
		return false;
	}
	if(freeMember == NULL)
	{
		printf("Error : freeMember is NULL\n");
		return false;
	}
	if(compare == NULL)
	{
		printf("Error : compare is NULL\n");
		return false;
	}
	return true;
}

/**
*==================================================================================================
*
*@brief check if the given group is an ablien group Associative
*@param IdentityElement - The  identity element.
*@param members A struct of GroupMemberP which contain ALL the group members
*@param membersLen The length of members.
*@param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that 
*is the result of the opreation  on them.
*@param freeMember pointer to A function that get GroupMemberP and frees it from memory.
*@param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff the 
*first is bigger; 
*<0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent 
*between them is <EPSILON).
*@return true if the group is Associative else false.
* runing time:
*      o(n):  we check all the memebres in the list if the oper on 3 of them is equle, and there
*      for we get o(n); 
*      
*==================================================================================================
*/
static bool checkAssociative(GroupMemberP num1OperNum2 , GroupMemberP members[], const int membersLen, 
							 GroupMemberP (*oper)(GroupMemberP a, GroupMemberP b), void (*freeMember)(GroupMemberP a),
							 int (*compare)(GroupMemberP a , GroupMemberP b) , const int j , const int i)
{

	GroupMemberP tmpNum3;
	GroupMemberP tmpNum4;
	GroupMemberP tmpNum5;
	int k = 0 ;

	for(k = 0 ; k < membersLen ; k++ )
	{

		tmpNum3  = oper(members[j] , members[k]);
		tmpNum4 = oper(members[i] , tmpNum3);
		tmpNum5 = oper(num1OperNum2 , members[k]);
		if(compare(tmpNum5 , tmpNum4) != NUM_ARE_EQUALE)
		{	
			freeMember(tmpNum5);
			freeMember(tmpNum4);
			freeMember(tmpNum3);
			return false;
		}
		freeMember(tmpNum5);
		freeMember(tmpNum4);
		freeMember(tmpNum3);
	}
	
	return true;
}

/**
*==================================================================================================
*
*@brief check if the given  num oper with the IdentityElement is equale to the given num
*@param IdentityElement - The  identity element.
*@param num - the num to check
*@param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that 
*is the result of the opreation  on them.
*@param freeMember pointer to A function that get GroupMemberP and frees it from memory.
*@param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff the 
*first is bigger; 
*<0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent 
*between them is <EPSILON).
*@return true if num oper IdentityElement = num, else false.
 * runing time:
 *      o(1): to check if an num is equle to an num oper the IdentityElement;
 *     
*==================================================================================================
*/
static bool checkIdentityEquale(GroupMemberP IdentityElement, GroupMemberP num , GroupMemberP (*oper)
								(GroupMemberP a, GroupMemberP b), void (*freeMember)(GroupMemberP a), int (*compare)
								(GroupMemberP a , GroupMemberP b))
{

	GroupMemberP tmpNum;
	tmpNum = oper(num, IdentityElement);
	if(tmpNum == NULL)
	{
		freeMember(tmpNum);
		return false;
	}
	if(compare(tmpNum , num) != NUM_ARE_EQUALE)
	{
		freeMember(tmpNum);
		return false;
	}
	freeMember(tmpNum);
	tmpNum = oper(IdentityElement , num);
	if(tmpNum == NULL)
	{
		freeMember(tmpNum);
		return false;
	}
	if(compare(tmpNum, num) != NUM_ARE_EQUALE)
	{
		freeMember(tmpNum);
		return false;
	}
	freeMember(tmpNum);
	return true;


}

/**
*==================================================================================================
*
*@brief check if the given group is an ablien group
*@param IdentityElement - The  identity element.
*@param members A struct of GroupMemberP which contain ALL the group members
*@param membersLen The length of members.
*@param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that 
*is the result of the opreation  on them.
*@param freeMember pointer to A function that get GroupMemberP and frees it from memory.
*@param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff the 
*first is bigger; 
*<0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent 
*between them is <EPSILON).
*@return true if the group is ablien else false.
 * runing time:
 *      o(n^3): becuse we run on all the elemnts in the list  and for each element we run on all
 *      the elements in the list o(n^2) then we for each to num we check Associative so we get
 *     o(n^3) , and we add the  checkIdentityEquale -o(1) ,isNumInList- o(n) compare - o(1)
 *     so in the total because o(n) ,0(1) are niglet to O(n^3) we get o(n^3);
 *     
*==================================================================================================
*/
static bool checkAblienGroup(GroupMemberP IdentityElement, GroupMemberP members[], const int membersLen, 
							 GroupMemberP (*oper)(GroupMemberP a, GroupMemberP b), void (*freeMember)(GroupMemberP a),
							 int (*compare)(GroupMemberP a , GroupMemberP b))
{

	GroupMemberP tmpNum1;
	GroupMemberP tmpNum2;
	bool stopCheck = false;
	bool inverse = false;
	int i = 0;
	int j = 0;
	//check if the identityelement is in the given list
	if((isNumInList(members , membersLen , IdentityElement , compare) == NUM_NOT_IN_LIST))
	{
		return false;
	}

	for(i = 0 ; i < membersLen ; i++)
	{
		if(!checkIdentityEquale(IdentityElement , members[i] , oper , freeMember, compare))
		{
			return false;
		}
		inverse = false;
		for(j = 0; j < membersLen ; j++)
		{
			tmpNum1 = oper(members[i] , members[j]);
			tmpNum2 = oper(members[j] , members[i]);
			if(tmpNum2 == NULL || tmpNum2 == NULL)
			{
				stopCheck  = true ;
			}
			//check comtitivity
			if(compare(tmpNum1 , tmpNum2) != NUM_ARE_EQUALE)
			{

				stopCheck  = true ;
			}
			//check equle with identityElement
			if(compare(tmpNum1 , IdentityElement) == NUM_ARE_EQUALE)
			{
				inverse = true;
			}
			if(isNumInList(members , membersLen , tmpNum1 , compare) == NUM_NOT_IN_LIST)
			{
				stopCheck  = true ;
			}
			if(!checkAssociative(tmpNum1, members, membersLen, oper, freeMember, compare, j, i))
			{
				stopCheck  = true ;	
			}
			freeMember(tmpNum1);
			freeMember(tmpNum2);
			if (stopCheck)
			{
				return false;
			}
		}
		if(!inverse)
		{
			return false;
		}
	}
	return true;
}

/**
*==================================================================================================
* @brief check if the given arguments define a an Abelian Group 
* if some arguments are NULL print the following error message to stderr :
* "Error : <argument_name> is NULL\n"
*   
* @param IdentityElement - The  identity element.
* @param members A struct of GroupMemberP which contain ALL the group members .
* @param membersLen The length of members.
* @param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP 
*that is the result of the opreation  on them.
* @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
* @param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff 
*the first is bigger; 
* <0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent 
*between them is <EPSILON).
* @return true iff the pramters an Abelian Group group.  In case of an error return false.
 * runing time:
 *      o(n^3): becuse we call to  checkAblienGroup = o(n^3); 
*==================================================================================================
*/
bool isAbelianGroup(GroupMemberP IdentityElement, GroupMemberP members[], int membersLen, 
					GroupMemberP (*oper)(GroupMemberP a, GroupMemberP b), void (*freeMember)(GroupMemberP a),
					int (*compare)(GroupMemberP a , GroupMemberP b))
{
	bool answer;

	if(!isNull(IdentityElement , members , oper , freeMember , compare))
	{
		return false;
	}

	answer = checkAblienGroup(IdentityElement, members, membersLen, oper, freeMember, compare);

	return answer;
}