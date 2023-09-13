# DAGExcute
DAG job scheduling based on genetic algorithm

GIVEN:

An arbitrary workflow, i.e. directed acyclic graph (DAG) G=(V, E), where each node v is a job and each directed edge (u, v) shows that the output data of job u is transferred as the input data of job v, K homogeneous machines, the execution time t(v) of each job on a single machine, and the communication time t(u, v) of each data transfer between jobs u and v running in different machines.

QUESTION:

Find the minimum execution time of the entire workflow along with a feasible schedule mapping all the jobs onto no more than K machines


REQUIREMENT:

Comment on the difficulty (i.e., computational complexity) of the above problem, design an efficient algorithm, implement the solution, (which may be an exact, approximation, or heuristic algorithm), and show the execution results. (C/C++ in Linux and Makefile are required.)


SOLUTION:

1. Initialize the population: At the beginning, a population is randomly generated, in which each individual represents a possible job scheduling solution. Each individual includes which machine each job is assigned to and the order in which the jobs are executed on each machine.

2. Evaluate fitness: For each individual in the population, calculate its fitness, that is, the completion time of the schedule. This is accomplished by simulating the assignment and execution of jobs for each individual. Consider the execution time of each job and the communication time t(u,v) between jobs.

3. Selection: Select a part of individuals as parents, usually individuals with higher fitness. This is achieved through fitness-based selection probabilities.

4. Crossover: Randomly select two individuals from the parent generation and perform a crossover operation to combine their characteristics to generate one or more offspring. This allows the introduction of new genetic information.

5. Mutation: Randomly mutate newly generated individuals to increase diversity. This can be achieved by changing job assignments or job execution order.

6. Evaluate fitness: Evaluate the fitness of newly generated individuals to determine their completion time.

7. Select a new generation: Select a part from the current population and newly generated individuals as the next generation population. Usually, the selection method is to sort according to fitness and select the top few.

8. Iterate: Repeat the above steps, usually for multiple generations (a predetermined number of iterations), to gradually improve job scheduling.

9. Output the best solution: At the end of the algorithm, output the individual with the best completion time as the final job scheduling plan.

Computational Complexity：

1. Population Initialization: 

The time complexity of population initialization mainly depends on the process of generating the initial schedule. In this example, we randomly generate a certain number of initial schedules, so the time complexity of initialization is O(populationSize).

2. Evaluation:

Evaluating the fitness of each schedule requires iterating through each job and calculating the total completion time. In the worst case, K comparisons are required for each job, so the time complexity of the evaluation is O(KV).

3. Selection:

The selection operation involves only sorting the schedules in the population and has a time complexity of O(populationSize * log(populationSize)).

4. Crossover: 

The time complexity of the crossover operation depends on the actual crossover strategy. In this example, we perform a simple merge operation with time complexity of O(1).

5. Mutation: 

The time complexity of the mutation operation depends on the actual mutation strategy. In this example, we perform a mutation operation with a time complexity of O(1).

To sum up, the time complexity of the entire genetic algorithm can be approximately expressed as

O(populationSize×(KV+log⁡(populationSize))

where KV represents the complexity of the evaluation operation.


Experimental Results:

1. Job topology DAG：

    0 ---> 2 ---> 4
    ↓          ↑
    1 ------- 3

Job(0, 1, 2, 3, 4)
edge(0,2), edge(1, 3)
edge(2,4), edge(3, 4)

2. Parameter configuration:

K=5, populationSize= 5, generations=5

 

