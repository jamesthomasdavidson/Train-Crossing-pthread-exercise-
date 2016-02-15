/*
 * train.c
 */
 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "train.h"
 
/* A global to assign IDs to our trains */ 
int idNumber = 0;
int tn;

/* If this value is set to 1, trains lengths
 * etc will be generated randomly.
 * 
 * If it is set to 0, the lengths etc will be
 * input from a file.
 */
int doRandom = 0;

/* The file to input train data from */
FILE *inputFile;
char **fileParam;

/* You can assume that no more than 80 characters
 * will be on any line in the input file
 */
#define MAXLINE		80

void	initTrain ( char *filename, int trainCount )
{
	doRandom = 0;
	tn = trainCount;
	
	/* If no filename is specified, generate randomly */
	if ( !filename )
	{
		doRandom = 1;
		srandom(getpid());
	}
	else
	{
		fileParam = malloc(sizeof(char*)*trainCount);
		inputFile = fopen(filename, "r");
		int i;
		for(i = 0; i < trainCount; i++)
		{
			fileParam[i] = malloc(sizeof(char)*10);
			fgets(fileParam[i], 10, inputFile);
		}
	}
}
 
/*
 * Allocate a new train structure with a new trainId, trainIds are
 * assigned consecutively, starting at 0
 *
 * Either randomly create the train structures or read them from a file
 *
 * This function malloc's space for the TrainInfo structure.  
 * The caller is responsible for freeing it.
 */
TrainInfo *createTrain ( void )
{
	TrainInfo *info = (TrainInfo *)malloc(sizeof(TrainInfo));

	/* I'm assigning the random values here in case
	 * there is a problem with the input file.  Then
	 * at least we know all the fields are initialized.
	 */	 
	info->trainId = idNumber++;
	info->arrival = 0;
	info->direction = (random() % 2 + 1);
	info->length = (random() % MAX_LENGTH) + MIN_LENGTH;

	static int n = 0;
	const char s[2] = "\n";
	char *num;


	if (!doRandom)
	{
		if(fileParam[n][0] == 'e' || fileParam[n][0] == 'E')
		{
			info->direction = 2;
		}else{
			info->direction = 1;
		}
		num = strtok(fileParam[n++]+1, s);
		info->length = atoi(num);
	}
	if(idNumber == tn)
	{
		free(fileParam);
	}
	return info;
}



