#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*
 * Sorted list type that will hold all the data to be sorted.
 */

int compareStrings(void *p1, void *p2);
 
int compareInts(void* a, void * b);

typedef int (*CompareFuncT)( void *, void * );


typedef struct PathOccurance 
{
	char *filePathName;
	int count;
	
	struct PathOccurance *next, *prev;
	
}PathOccurance;


typedef struct Token
{
    char* data;//word
    
    struct Token *next, *prev;
    
    struct PathOccurance *littleHead;
    
}Token;


struct SortedList 
{
	CompareFuncT compare;
	
	Token *bigHead;
		
};
typedef struct SortedList* SortedListPtr;

struct SortedListIterator
{
	//Node *ptr;
	int count;
	int tracker;
};

typedef struct SortedListIterator* SortedListIteratorPtr;


SortedListPtr SLCreate(CompareFuncT cf);

int SLInsert(SortedListPtr list, void *newObj, char* name);

int SLCheck(SortedListPtr list,char* word, char* name);


#endif
