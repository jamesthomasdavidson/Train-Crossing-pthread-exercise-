# TrainCrossing-pthreads
Assignment 2 for CSC360

Read a2.pdf for the full description of the codes functionality



In essence, It simulates trains arriving at two different ends of a bridge.  

Each train gets a thread.  

1. Each train sleeps for some independant amount of time (< 1 second) to simulate loading the trains cargo/passengers.

2. After loading, the trains arrive at either side of the bridge and get added to either the westQueue or EastQueue train queue.

3. Trains wait for a turn to cross the bridge, with the following exceptions.

  3 a). For every train IN THE QUEUE going west, up to 2 trains going east must be allowed to finish crossing the bridge
        first (if two or more exist) before the westbound train can pass.
        
  3 b). EX. Suppose there are three trains, with two trains (in order: train 1, then train 2) in the eastbound queue and one on the bridge travelling (also) eastbound (train 0).  Now suppose two trains arrive at the westbound Queue (train 3, then train 4). Once train 0 is finished crossing the bridge, train 1 will cross before train 3.  After train 3 has crossed, train 2 will go, followed by train 4.
             

