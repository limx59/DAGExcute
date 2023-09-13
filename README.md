# DAGExcute
DAG job scheduling based on genetic algorithm

GIVEN:
An arbitrary workflow, i.e. directed acyclic graph (DAG) G=(V, E), where each node v is a job and each directed edge (u, v) shows that the output data of job u is transferred as the input data of job v, K homogeneous machines, the execution time t(v) of each job on a single machine, and the communication time t(u, v) of each data transfer between jobs u and v running in different machines.

任意工作流程，即有向无环图 (DAG) G=(V, E)，其中每个节点 v 是一个作业，每个有向边 (u, v) 表明作业 u 的输出数据被传输为作业 u 的输入数据 作业 v，K 个同构机器，每个作业在单机上的执行时间 t(v)，以及运行在不同机器上的作业 u 和 v 之间每次数据传输的通信时间 t(u, v)。

QUESTION:
Find the minimum execution time of the entire workflow along with a feasible schedule mapping all the jobs onto no more than K machines
找到整个工作流程的最短执行时间以及将所有作业映射到不超过 K 台机器上的可行计划

REQUIREMENT:
Comment on the difficulty (i.e., computational complexity) of the above problem, design an efficient algorithm, implement the solution, (which may be an exact, approximation, or heuristic algorithm), and show the execution results. (C/C++ in Linux and Makefile are required.)
评论上述问题的难度（即计算复杂度），设计有效的算法，实现解决方案（可以是精确的、近似的或启发式的算法），并显示执行结果。 （需要 Linux 中的 C/C++ 和 Makefile。）

SOLUTION:
1. Initialize the population: At the beginning, a population is randomly generated, in which each individual represents a possible job scheduling solution. Each individual includes which machine each job is assigned to and the order in which the jobs are executed on each machine.
1. 初始化种群：开始时，随机生成一个种群，其中每个个体表示一个可能的作业调度方案。每个个体包括每个作业分配哪台机器以及每台机器上的作业执行顺序。

2. Evaluate fitness: For each individual in the population, calculate its fitness, that is, the completion time of the schedule. This is accomplished by simulating the assignment and execution of jobs for each individual. Consider the execution time of each job and the communication time t(u,v) between jobs.
2. 评估适应度：对种群中的每个个体，计算其适应度，即该调度的完成时间。这是通过模拟每个个体的作业分配和执行来完成的。考虑每个作业的执行时间以及作业之间的通信时间t（u,v）。

3. Selection: Select a part of individuals as parents, usually individuals with higher fitness. This is achieved through fitness-based selection probabilities.
3. 选择：选择一部分个体作为父代，通常选择适应度较高的个体。这通过基于适应度的选择概率来实现。

4. Crossover: Randomly select two individuals from the parent generation and perform a crossover operation to combine their characteristics to generate one or more offspring. This allows the introduction of new genetic information.
4. 交叉：从父代中随机选择两个个体，并执行交叉操作，将它们的特征组合起来生成一个或多个子代。这样可以引入新的遗传信息。

5. Mutation: Randomly mutate newly generated individuals to increase diversity. This can be achieved by changing job assignments or job execution order.
5. 变异：对新生成的个体进行随机变异，以增加多样性。这可以通过改变作业分配或作业执行顺序来实现。

6. Evaluate fitness: Evaluate the fitness of newly generated individuals to determine their completion time.
6. 评估适应度：对新生成的个体进行适应度评估，以确定它们的完成时间。

7. Select a new generation: Select a part from the current population and newly generated individuals as the next generation population. Usually, the selection method is to sort according to fitness and select the top few.
7. 选择新一代：从当前种群和新生成的个体中选择一部分作为下一代种群。通常，选择的方式是根据适应度排序并选择前几名。

8. Iterate: Repeat the above steps, usually for multiple generations (a predetermined number of iterations), to gradually improve job scheduling.
8. 迭代：重复上述步骤，通常进行多代（迭代次数预先设定），以逐步改进作业调度。

9. Output the best solution: At the end of the algorithm, output the individual with the best completion time as the final job scheduling plan.
9. 输出最佳解：在算法结束时，输出具有最佳完成时间的个体作为最终作业调度方案。

Computational Complexity：

1. 种群初始化 (Population Initialization)：
The time complexity of population initialization mainly depends on the process of generating the initial schedule. In this example, we randomly generate a certain number of initial schedules, so the time complexity of initialization is O(populationSize).
种群初始化的时间复杂度主要取决于生成初始调度的过程。在这个示例中，我们随机生成了一定数量的初始调度，因此初始化的时间复杂度为 O(populationSize)。

2. 评估 (Evaluation)：
Evaluating the fitness of each schedule requires iterating through each job and calculating the total completion time. In the worst case, K comparisons are required for each job, so the time complexity of the evaluation is O(KV).
评估每个调度的适应度需要遍历每个作业和计算总完成时间。在最坏情况下，需要对每个作业进行 K 次比较，因此评估的时间复杂度为 O(KV)。

3. 选择 (Selection)：
The selection operation involves only sorting the schedules in the population and has a time complexity of O(populationSize * log(populationSize)).
选择操作只涉及对种群中的调度进行排序，时间复杂度为 O(populationSize * log(populationSize))。

4. 交叉 (Crossover)：
The time complexity of the crossover operation depends on the actual crossover strategy. In this example, we perform a simple merge operation with time complexity of O(1).
交叉操作的时间复杂度取决于实际的交叉策略。在这个示例中，我们执行了一个简单的合并操作，时间复杂度为 O(1)。

5. 变异 (Mutation)：
The time complexity of the mutation operation depends on the actual mutation strategy. In this example, we perform a mutation operation with a time complexity of O(1).
变异操作的时间复杂度取决于实际的变异策略。在这个示例中，我们执行了一次变异操作，时间复杂度为 O(1)。

To sum up, the time complexity of the entire genetic algorithm can be approximately expressed as
综上所述，整个遗传算法的时间复杂度可以近似表示为 
O(populationSize×(KV+log⁡(populationSize))

where KV represents the complexity of the evaluation operation.
其中 KV 代表评估操作的复杂度。

Experimental Results:

1.Job拓扑DAG(Job topology DAG)：
    0 ---> 2 ---> 4
    ↓          ↑
    1 ------- 3

Job(0, 1, 2, 3, 4)
edge(0,2), edge(1, 3)
edge(2,4), edge(3, 4)

2.参数配置(Parameter configuration):
K=5, populationSize= 5, generations=5

 

