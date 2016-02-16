/*
 * assign2.c
 *
 * Name: James Davidson
 * Student Number: V00812527
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include "train.h"

pthread_mutex_t bridgeLock;
pthread_mutex_t queueLock;
pthread_cond_t synchronizeCond;

Queue westQueue;
Queue eastQueue;

/* #define DEBUG	1 */

void ArriveBridge (TrainInfo *train);
void CrossBridge (TrainInfo *train);
void LeaveBridge (TrainInfo *train);

void lockQueues()
{
	pthread_mutex_lock(&queueLock);
}

void unlockQueues()
{
	pthread_mutex_unlock(&queueLock);
}

void lockBridge()
{
	pthread_mutex_lock(&bridgeLock);
}

void unlockBridge()
{
	pthread_mutex_unlock(&bridgeLock);
}

void signalNextTrain()
{
	pthread_cond_broadcast(&synchronizeCond);
}

void releaseBridgeAndWait()
{
	pthread_cond_wait(&synchronizeCond, &bridgeLock);
}

/* Frees the first train in the specified Queue, must have acquired both Queue locks  */
void removeTrain(Queue *direction)
{
	int i;
	
    for(i = 0; i < direction->size - 1; i++)
    {
    	direction->head[i] = direction->head[i + 1];
    }
    direction->size = direction->size - 1;
    if(direction == &westQueue)
    {
		westQueue.consecutiveTrainsCrossed = 0;
    }else{
		westQueue.consecutiveTrainsCrossed = westQueue.consecutiveTrainsCrossed + 1;
    }
}

int westTrainReady(TrainInfo* train)
{
	return ((eastQueue.size == 0 || westQueue.consecutiveTrainsCrossed == 2) && (train == westQueue.head[0]));
}

int eastTrainReady(TrainInfo* train)
{
	return ((westQueue.consecutiveTrainsCrossed < 2 || westQueue.size == 0) && (train == eastQueue.head[0]));
}

void * Train ( void *arguments )
{
	TrainInfo	*train = (TrainInfo *)arguments;

	/* Sleep to simulate different arrival times */
	usleep (train->length*SLEEP_MULTIPLE);

	ArriveBridge (train);
	CrossBridge  (train);
	LeaveBridge  (train); 

	free (train);
	return NULL;
}

void ArriveBridge ( TrainInfo *train )
{
	printf ("Train %2d arrives going %s\n", train->trainId, 
		(train->direction == DIRECTION_WEST ? "West" : "East"));

	lockQueues();
	if(train->direction == DIRECTION_WEST)
	{
		if(westQueue.size == 0)
		{
			westQueue.consecutiveTrainsCrossed = 0;
		}
		westQueue.head[westQueue.size++] = train;
	}else{
		eastQueue.head[eastQueue.size++] = train;
	}
	unlockQueues();

	lockBridge();

	/* Train is going West */
	if(train->direction == DIRECTION_WEST)
	{
		lockQueues();

		/* Still waiting for its turn */
		while(!westTrainReady(train))
		{
			unlockQueues();
			releaseBridgeAndWait();
			lockQueues();
		}

		unlockQueues();

	/*Train is going East */
	}
	else
	{
		lockQueues();

		/* Still waiting for its turn */
		while(!eastTrainReady(train))
		{
			unlockQueues();
			releaseBridgeAndWait();
			lockQueues();
		}
		unlockQueues();
	}
}

void CrossBridge ( TrainInfo *train )
{
	printf ("Train %2d is ON the bridge (%s)\n", train->trainId,
			(train->direction == DIRECTION_WEST ? "West" : "East"));
	fflush(stdout);
	
	usleep (train->length*SLEEP_MULTIPLE);

	printf ("Train %2d is OFF the bridge(%s)\n", train->trainId, 
			(train->direction == DIRECTION_WEST ? "West" : "East"));
	fflush(stdout);
}

void LeaveBridge ( TrainInfo *train )
{
	lockQueues();
	if(train->direction == DIRECTION_WEST)
	{
		removeTrain(&westQueue);
	}else{
		removeTrain(&eastQueue);
	}
	unlockQueues();
	signalNextTrain();
	unlockBridge();
}

int main ( int argc, char *argv[] )
{
	int		trainCount = 0;
	char 		*filename = NULL;
	pthread_t	*tids;
	int		i;

	
	/* Parse the arguments */
	if ( argc < 2 )
	{
		printf ("Usage: part1 n {filename}\n\t\tn is number of trains\n");
		printf ("\t\tfilename is input file to use (optional)\n");
		exit(0);
	}
	
	if ( argc >= 2 )
	{
		trainCount = atoi(argv[1]);
		westQueue.head = malloc(sizeof(TrainInfo*)*trainCount);
		westQueue.size = 0;
		westQueue.consecutiveTrainsCrossed = 0;
		eastQueue.head = malloc(sizeof(TrainInfo*)*trainCount);
		eastQueue.size = 0;
		eastQueue.consecutiveTrainsCrossed = 0;
	}
	if ( argc == 3 )
	{
		filename = argv[2];
	}	

	if (pthread_mutex_init(&queueLock, NULL) != 0)
    {
        printf("\nInit mutex queueLock failed\n");
        return 1;
    }
	if (pthread_mutex_init(&bridgeLock, NULL) != 0)
    {
        printf("\nInit mutex bridgeLock failed\n");
        return 1;
    }
	if (pthread_cond_init(&synchronizeCond, NULL) != 0)
    {
        printf("\nInit condition synchronizeCond failed\n");
        return 1;
    }
	initTrain(filename, trainCount);
	
	/*
	 * Since the number of trains to simulate is specified on the command
	 * line, we need to malloc space to store the thread ids of each train
	 * thread.
	 */
	tids = (pthread_t *) malloc(sizeof(pthread_t)*trainCount);
	
	/*
	 * Create all the train threads pass them the information about
	 * length and direction as a TrainInfo structure
	 */

	for (i=0;i<trainCount;i++)
	{
		TrainInfo *info = createTrain();

		printf ("Train %2d headed %s length is %d\n", info->trainId,
			(info->direction == DIRECTION_WEST ? "West" : "East"),
			info->length );

		if ( pthread_create (&tids[i],0, Train, (void *)info) != 0 )
		{
			printf ("Failed creation of Train.\n");
			exit(0);
		}
	}

	/*
	 * This code waits for all train threads to terminate
	 */
	for (i=0;i<trainCount;i++)
	{
		pthread_join (tids[i], NULL);
	}
	pthread_mutex_destroy(&queueLock);
	pthread_mutex_destroy(&bridgeLock);
	pthread_cond_destroy(&synchronizeCond);

	free(tids);
	return 0;
}

