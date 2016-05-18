#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sorted-list.h"
#include <string.h>
#include "tokenizer.h"
#include "readprocess.h"

/* this file creates a linked list inside of a linked list to keep count of occurences of words
 * and the files in which these words are found
*/


int compareStrings(void *p1, void *p2)
 {
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int compareInts(void *a, void *b)
{
	int i = *(int*)a;
	int j = *(int*)b;
	
	return i - j;
}


SortedListPtr SLCreate(CompareFuncT cf)
{       
        SortedListPtr sl = malloc(sizeof(struct SortedList));
        
        sl->compare = cf;
        
        sl->bigHead = NULL;

        return sl;         
} 

int SLCheck(SortedListPtr list,char* word, char* pathName)
{	
	
	Token* bigNode = list->bigHead;
	
	if(bigNode == NULL)	//list is empty no comparisons
		return 0;			
		
	
	while(bigNode !=  NULL)
	{
		//IF Words MATCH AND PATH  --> increments counter 
		if( strcmp(bigNode->data,word) == 0 &&  strcmp(bigNode->littleHead->filePathName,pathName) == 0) //(bigNode->data == word) && (bigNode->littleHead->filePathName == pathName)) 
		{	
			bigNode->littleHead->count++;
			return 1;
		}


		if( (strcmp(bigNode->data,word) == 0) &&  (strcmp(bigNode->littleHead->filePathName,pathName) != 0) )
		{
			
			PathOccurance* sideNode = malloc(sizeof(struct PathOccurance));	
			PathOccurance* tinyCurrent = bigNode->littleHead;
			
			while(tinyCurrent->next != NULL)
			{	
				tinyCurrent = tinyCurrent->next;
			}

			tinyCurrent->next = sideNode;
			sideNode->prev = tinyCurrent;	
			
			sideNode->filePathName = pathName;
			sideNode->count = 1;
			sideNode->next = NULL;
			return 1;
		}
		
		if(strcmp(bigNode->data,word) != 0) //if the words dont match keep going
			bigNode = bigNode->next;
	}
	
	return 0;
}


int SLInsert(SortedListPtr list, void *newObj,char* nameOfPath)
{
	
    if(list == NULL)
    {
        printf("NUll List Cannot ADD ELEMENTS!");    
        return 0;
    }
     	
	Token* tokenNode = malloc(sizeof(struct Token));				//creates token node
	
	PathOccurance* link = malloc(sizeof(struct PathOccurance));		//creates sidechick Node [matrix LL has been created]
	
	tokenNode->data = newObj;
	tokenNode->next = NULL;
	tokenNode->prev = NULL;
		
	link->filePathName = NULL;
	link->count = 0;
	link->next = NULL;
	link->prev = NULL;
	
	tokenNode->littleHead = link;  //now the tokenNode->littleHead 
	PathOccurance* node = tokenNode->littleHead;
	
    if(list->bigHead == NULL)			//TestCase 1
    {
		tokenNode->next = NULL;
		list->bigHead = tokenNode;
		tokenNode->prev = list->bigHead;
		
		//added the first side node and initialize it	
		node->count = 1;
		node->filePathName = nameOfPath;
		node->next = NULL;			
	}
	else
	{	
		
		Token* current = list->bigHead;

		if( strcmp(tokenNode->data, current->data) < 0) //Adds at HEAD
		{
			list->bigHead = tokenNode;
			tokenNode->prev = list->bigHead;
			tokenNode->next = current;
			current->prev = tokenNode;
			
		//-------------------------------	
			tokenNode->littleHead->count = 1;
			tokenNode->littleHead->filePathName = nameOfPath;
			tokenNode->littleHead->next = NULL;			
		//--------------------------------							
		}
		else
		{
			
			Token* temp = current;
			while(current->next != NULL && (strcmp(tokenNode->data ,current->data) > 0 ||  strcmp(tokenNode->data ,current->data) < 0))
			{
				
				if(strcmp(tokenNode->data ,current->data) < 0)
					break;
				else
				{		
					temp->prev = current; //follows alog a prev pointer to add in the middle
					current = current->next;
				}
			}
				
				if(strcmp(tokenNode->data ,current->data) > 0)
				{	
					if(current->next == NULL)//ADDS at END/NULL
					{
						current->next = tokenNode;
						tokenNode->prev = current;
						tokenNode->next = NULL;
						//-------------------------------	
						tokenNode->littleHead->count = 1;
						tokenNode->littleHead->filePathName = nameOfPath;
						tokenNode->littleHead->next = NULL;							
						//--------------------------------								
					}
					else
					{
						temp->next = tokenNode;
						tokenNode->prev = temp;
				
						tokenNode->next = current;
						current->prev = tokenNode;
						//-------------------------------	
						tokenNode->littleHead->count = 1;
						tokenNode->littleHead->filePathName = nameOfPath;
						tokenNode->littleHead->next = NULL;							
						//--------------------------------					
					}
				}
				if(strcmp(tokenNode->data ,current->data) < 0)
				{
					Token *temp2 = current->prev; 
					temp2->next = tokenNode;
					tokenNode->prev = temp2;
					tokenNode->next = current;
					current->prev = tokenNode;
					//-------------------------------	
					tokenNode->littleHead->count = 1;
					tokenNode->littleHead->filePathName = nameOfPath;
					tokenNode->littleHead->next = NULL;							
					//--------------------------------			
				}
		}	
	}
    return 0;   
}
