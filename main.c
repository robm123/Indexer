#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "readprocess.h"
#include "tokenizer.h"
#include "sorted-list.h"

/* Remember that the arguments to start this program are

	target      output file	               path
	index <inverted-index file name> <directory or file name>
*/

static char* charptr[999][999];
static int i = 0;
	
int exist(char *filename)
{
	struct stat   buffer;   
	return (stat (filename, &buffer) == 0);
}
	
void subDirectory(char*, char*, SortedListPtr list);	

int main(int argc, char **argv)  
{
  
	char *outputFile = argv[1]; 
	char *pathName = argv[2];	
	char ans[0];
	char strp[999];		 
	struct stat status;
	struct dirent *pDirent;
	//struct dirent *ini;
	DIR* dir;
	SortedListPtr list = SLCreate(compareStrings);	
	int st = 0;

	if(argc != 3)
	{
		printf("Incorrect amount of arguments");
		return 0;
	}

	FILE *ofp;
	ofp = fopen(outputFile, "w");
	if(!ofp)
	{
		perror("Cannot open output file");
		exit(EXIT_FAILURE);
	}
	
	st = stat(pathName,&status);	
	if(st != 0)
	{
		printf("Error");
		return 1;
	}
	
	if(S_ISREG(status.st_mode))
	{		
		readprocess(pathName, list);
		outputAll(list, ofp, pathName);
		fclose(ofp);						
		return 1;
	}

	dir = opendir(pathName); //returns pointer to stream
	
	if(dir == NULL)
		printf("Could not open directory: %s\n", pathName);
	else
		printf("\nWe are inside:  %s \n", pathName);
			
	char *currentPath = malloc(strlen(pathName)+1);	
	currentPath = pathName;

	pDirent = readdir(dir);
	 
	while(pDirent != NULL)
	{	
		if(pDirent->d_type == DT_REG)
		{
			char thePath[9999];
			strcpy(thePath, currentPath);
			strcat(strcat(thePath,"/"),pDirent->d_name);

			char *sv = thePath; 
			strcpy(charptr[i], sv);
			readprocess(charptr[i], list);			
			i++;
		}
		if(pDirent->d_type == DT_DIR && strcmp(pDirent->d_name, ".") != 0  && strcmp(pDirent->d_name, "..") != 0 )
		{															  	
			//printf("%s\n\n", pDirent->d_name);													
			subDirectory(pDirent->d_name, currentPath, list);
	
		}

		pDirent = readdir(dir);	
	}
	//closes parent directory
	closedir(dir);
	
//-=-=-=-=--=-==-=-=-==-THIS WILL OUTPUT TO FILE-=-=--=-==-=-=-==-==--=-=	

	//pass the list and print it 
	outputAll(list, ofp, pathName);
	fclose(ofp);
	printf("Goodbye\n");
//-=-=-=-=-=-=--=-==-=-=-=-=-=-=--=-==-=-=-==-==--=-=-===-==-=-=-=-==-=-=-	
	return 0;
}

// recursively calls itself if the pointer reaches another directory
void subDirectory(char* sub, char* fullPath, SortedListPtr list)
{
	char subdirectory[999];
	char current[999];
	
	struct dirent* pD;
	DIR* dir2;
	
	strcpy(subdirectory, sub);
	strcpy(current, fullPath);
	strcat((strcat(current,"/")),subdirectory); 
	dir2 = opendir(current);

	if(dir2 == NULL)
		printf("*****\n\nCould not open directory:   \n%s\n", current);

	pD = readdir(dir2);
	
	while(pD != NULL)
	{	
		if(pD->d_type == DT_REG)
		{
			char fn2[9999];	
			strcpy(fn2, current);
			strcat(strcat(fn2,"/"),pD->d_name);		
	
			
			char *sv = fn2; 
			strcpy(charptr[i], sv);
			printf("About to open file: %s\n",charptr[i]);				
			readprocess(charptr[i], list);			
			i++;			
		}
	    if(pD->d_type == DT_DIR && strcmp(pD->d_name, ".") != 0  && strcmp(pD->d_name, "..") != 0 )
		{														  												             
			subDirectory(pD->d_name, current, list);
		}
		
		pD = readdir(dir2);	
	}
	closedir(dir2);
	return;
}
