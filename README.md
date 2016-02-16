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
        
  3 b). EX: Suppose there are three trains, with two trains waiting at the Eastbound queue (in order: train 1, then train 2) with one on the bridge also travelling Eastbound (train 0).  Now suppose two trains arrive at the Westbound Queue (in order: train 3, then train 4). Once train 0 (EB) is finished crossing the bridge, train 1 (EB) will cross the bridge followed by train 3 (WB).  After train 3 has crossed, train 2 (EB) will go, followed by train 4 (WB).
             

xxx EXECUTION xxx

Download the files train.c, train.h, assign2.c and Makefile.

Run make.

Invoking assign2.c on the command line (after running make) looks like the following:

  ./assign2 NUMBER              <<will generate NUMBER of random trains.
  
  ./assign2 NUMBER filename     <<will load NUMBER trains from file filename.  Assumes filename is a syntactically valid file and contains at least NUMBER of trains.


