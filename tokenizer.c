#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include <ctype.h>

/*
 * This file tokenizers the entire string to spit out tokens when called
 **/


TokenizerT *TKCreate(char *ts ) 
{
	TokenizerT *tokenizer = malloc(sizeof(struct TokenizerT_));
		
	tokenizer->strArray = malloc(sizeof(char)*strlen(ts)+1);
	
	tokenizer->token = malloc(sizeof(char)*strlen(ts)+1);
	
	strcpy(tokenizer->strArray,ts);
	
	return tokenizer;
}


void TKDestroy( TokenizerT * tk ) 
{
	free (tk->token);
	free (tk->strArray);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 */
static int counter = 0; 
void resetFileCounter()
{
	counter = 0;
}
char *TKGetNextToken( TokenizerT * tk ) 
{
	while(tk->strArray[counter] == ' ' || ispunct(tk->strArray[counter]) ) //skips initial white spaces
	{	
		counter++;
	}
	
	int tokenCount = 0;
	while(   (tk->strArray[counter] != ' ') && (tk->strArray[counter] != '\0') && (!ispunct(tk->strArray[counter]))  )//checks seperator and gets 1 token
	{

		tk->token[tokenCount] = tk->strArray[counter];
		
		counter++;
		tokenCount++;
		
	}
	
	tk->token[tokenCount] = '\0';
	
	if(!(isalnum(tk->token[tokenCount = tokenCount-2])))
	{
			return NULL;
	}
	else
	{	

		char* mine = tk->token;
		const int l = strlen(mine);
		char* low = (char*)malloc(l+1);
		low[l] = 0;
		
		// copy all character bytes to the new buffer using tolower
		int i;
		for(i = 0; i < l; i++ )
		{
			low[ i ] = tolower( mine[ i ] );
		}		
		tk->token = low;
		
		return tk->token;
	}
 
}
