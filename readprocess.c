#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include "readprocess.h"

int readprocess(char *pt,SortedListPtr list)
{
	

//-=-=-=-=--=-=-=-READS ENTIRE FILE CONTENTS-=-=-=-=--=-=-=-=-=-=-=--=-
	FILE *myFile = fopen(pt, "r");
	
   	if(myFile == NULL)
   {
        printf("File Doesn't Exist: ");
   }
   	
   fseek(myFile, 0, SEEK_END);
   long fsize = ftell(myFile);
   fseek(myFile, 0, SEEK_SET);

   char *string = malloc(fsize + 1);
   fread(string, fsize, 1, myFile);
 
						
   string[fsize] = 0;
 	
//-=-=-=-=--=-DUMPS CONTENTS INTO LIST=-=--=-=-=--=-=-=-=--==-=-=--=-=-=-=--=-

	//SortedListPtr list = SLCreate(compareStrings);
	
	TokenizerT *tk = TKCreate(string);	
	
	fclose(myFile);   
	free(string);
	
	char *tempToken;
		
	tempToken = TKGetNextToken(tk);
	
	if(tempToken == NULL)
	{	
		printf("ERROR");
		exit(0);
	}
	while(tempToken != NULL)
	{	
		char* word = malloc(strlen(tempToken)+1);
		strcpy(word, tempToken);
		
				
		if(SLCheck(list, word, pt) == 0)
		{	
			//adds word
			SLInsert(list,word,pt);
		}
		//else word has been found	
		
		tempToken = TKGetNextToken(tk);			
	}					
	resetFileCounter();

	return 0;
}

int outputAll(SortedListPtr list, FILE *ofp, char* pathName)
{
		Token *current = list->bigHead;
		PathOccurance *sideNode;
		
		fprintf(ofp, "{%s\n\t", pathName);
		while(current != NULL)
		{
			fprintf(ofp,"\t\n\"%s\":[\n",current->data); 
			sideNode = current->littleHead;
			
			while(sideNode != NULL)
			{
				fprintf(ofp,"\t{\"%s\" : %d}\n",sideNode->filePathName, sideNode->count);
				sideNode = sideNode->next;
			}			
			fprintf(ofp,"]}");
			
			current = current->next;
		}
		fprintf(ofp, "\n}");
		printf("\n");
		
		return 1;
		//check for last character in files
}
