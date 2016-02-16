# TrainCrossing-pthreads
Assignment 2 for CSC360

Read a2.pdf for the full description of the codes functionality



In essence, It simulates trains arriving at two different ends of a bridge.  

Each train gets a thread.  

1. Each train sleeps for some independant amount of time (< 1 second) to simulate loading the trains cargo/passengers.

2. After loading, the trains arrive at either side of the bridge and get added to either the westQueue or wastQueue Train queue.

3. Trains wait for a turn to cross the bridge, with the following exceptions.

  3 a). For every train IN THE QUEUE going West, up to 2 trains going east must be allowed to finish crossing the bridge
        first (if at least two exist) before the Westbound train can pass.
        
  3 b). EX: Suppose there are three trains, with two trains (in order: train 1, then train 2) waiting at the Eastbound queue and one on the bridge (also) travelling Eastbound (train 0).  Now suppose two trains arrive at the Westbound Queue (train 3, then train 4). Once train 0 is finished crossing the bridge, train 1 will cross before train 3.  After train 3 has crossed, train 2 will go, followed by train 4.
             

xxx EXECUTION xxx

download the files train.c, train.h, assign2.c and Makefile

run make

command line (after running make) looks like the following:

  ./assign2 NUMBER            *Will generate random NUMBER of trains*
  
  ./assign2 NUMBER filename   *will load NUMBER trains from file filename.  Assumes filename is a syntactically valid file and contains at least NUMBER of trains*


