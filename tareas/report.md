# Design analysis
===================

## INTRODUCTION 
-----------------

The Goldbach Conjecture states that every number greater than 5 can be calculated as the sum of 2 primes, if the number is even, or the sum of 3 primes if the number is odd. This program can calculate the goldbach sums of any number that is 64 bits in size or smaller.

## Pthreads-OpenMP comparison
-------------------------------

The pthreads implementation of the progrma lasted 516 seconds, which showed a speeup of 1.81 against the original 934 seconds that the serial program lasted. This was improved even further through the OpenMP technology, lasting as little as 315 seconds with a speedup of 2.965. OpenMP demonstrated great improvement over pthreads, some of the reasons to this behaviour could include the lack of semaphores that were used in the pthreads implementation, but the main reason is that openMP is distributing the sums of each input Number instead of distributing separate input numbers giving more equivalent jobs to each thread. Threads still wait for their turn to print their sums, if they just stored them and printed them at the end, the progmam would be way faster as threads would be able to calculate sums nonstop, this would also make efficiency levels higher, as the 2 implementations have an efficiency value of 0.226 and 0.371 respectively.

## OpenMP-MPI comparison
-------------------------------

The MPI implementation distributes separate input numbers to different processes, and each of these processes utilizes the OpenMP technology to concurrently calculate the sums of each of the inputNumbers.
Tested with the 3 slave nodes of the UCR's Arenal cluster the program lasted 259 seconds, and a speedup of 3.606. This is a great improvement to the OpenMP implementation and it also proves that the greater the amount of nodes used, the greater the resulting speedup that will be achieved. the main weakness of this implementation is that the numbers are statically distributed between the nodes, so theres a chance that some nodes will have larger inputNumbers and take longer to finish calculating their sums than the nodes that get the smallest numbers, this lowered the efficiency of each node to 0.15, the lowest efficiency of all the implementations.

