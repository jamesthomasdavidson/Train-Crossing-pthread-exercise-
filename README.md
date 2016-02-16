# TrainCrossing-pthreads
Assignment 2 for CSC360

Read a2.pdf for the full description of the codes functionality



In essence, It simulates trains arriving at two different ends of a bridge.  

Each train gets a thread.  

1. Each train sleeps for some independant amount of time (< 1 second) to simulate loading the trains cargo/passengers.

2. After loading, the trains arrive at either side of the bridge and get added to either the "westQueue" or "eastQueue" Train queue.

3. Trains wait for a turn to cross the bridge, with the following exceptions.

  3 a). For every train in the queue going West, up to 2 trains going East must be allowed to finish crossing the bridge
        first (if at least two exist) before the Westbound train can pass.
        
  3 b). EX: Suppose there are 3 trains, with 2 trains waiting at the Eastbound queue (in order: train B, then train C) and 1 train on the bridge also travelling Eastbound (train A).  Now suppose two trains arrive at the Westbound Queue (in order: train D, then train E). Once train A (EB->) is finished crossing the bridge, train B (EB->) will cross the bridge followed by train D (<-WB).  After train D has crossed, train C (EB->) will go, followed by train E (<-WB).
             

xxx EXECUTION xxx

Download the files train.c, train.h, assign2.c and Makefile.

Run make.

Invoking assign2.c on the command line (after running make) looks like the following:

  ./assign2 NUMBER              <<will generate NUMBER of random trains.
  
  ./assign2 NUMBER filename     <<will load NUMBER trains from file filename.  Assumes filename is a syntactically valid file and contains at least NUMBER of trains.


