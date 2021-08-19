# Design analysis
===================

## INTRODUCTION 
-----------------

The enchanted forest project is a simulation that updates a forest after every midnight altering it according to a series of rules that determine wether a tree, a lake or a meadow should last the night or be transformed into one of the other terrain types.

The challenge is to program it using the openMP and MPI technologies in order to speed up its calculations, therefore obtaining the desired results faster.

## TASK DESCOMPOSITION AND MAPPING
-----------------------------------

# MPI:
    Descomposition type: Single job maps.
    Mapping type: Block mapping.

# OpenMP:
    Descomposition type: Single matrix cells.
    Mapping type: Block mapping.

# Advantage and disadvantage:
    *MPI: The main advantage provided by this implementation is the fact that each process doesn't need to communicate with other processes to receive or send each number,from the beginning each process has a certain amount of numbers and when it finishes calculating them it knows that it ends executing. While the downside is that there is a chance that the maps may be very varied in sizes meaning that some processes will finish their task very quickly and then stop working while the processes that handle the bigger maps finish working because of the block mapping, dynamic mapping would fix this issue. There is also the possibility for having as few as one map to be worked on and all the processes (except for one) would be wasted, a more granulated descomposition would fix this issue.

    *OpenMP: One advantage of dividing it by cells, is that the threads will always be working even though there is a matrix with fewer columns or rows than threads, by cells there will always be work for the threads. The main advantage of using block mapping is that since all cells take the same time to process, therefore no dynamism is needed. A disadvantage of block mappping is that if some cells were to vary in processing time, some threads would work for more or less time than others but this does not happen in this project, if it did, dynamic mapping would fix the issue.

## Input and Outup
--------------------

Since every process will handle separate maps by calculating which ones are set to be assigned to them, and each thread will handle separate matrix cells, the program is conditionally safe. Processes will create the expected file once they finish simulating their respective forests and midnights wont advance until every cell has been reviewed.


