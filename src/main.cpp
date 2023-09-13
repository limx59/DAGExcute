#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <unordered_map>
#include <time.h>
#include "DAGexcute.h"

using namespace std;


int main() {
    srand(time(NULL));

    int K = 6; // 机器数量
    vector<Job> jobs = {
        {0, 5, {}},
        {1, 3, {}},
        {2, 2, {0}},
        {3, 4, {1}},
        {4, 6, {2, 3}},
    };

    // 使用稀疏矩阵表示通信时间
    unordered_map<pair<int, int>, int, pair_hash> communicationTime = {
        {make_pair(0, 1), 1}, // 作业0传输到作业1需要1个时间单位
        {make_pair(0, 2), 2}, // 作业0传输到作业2需要2个时间单位
        {make_pair(0, 3), 3}, // 作业0传输到作业3需要3个时间单位
        {make_pair(0, 4), 4}, // 作业0传输到作业4需要4个时间单位
        {make_pair(1, 0), 1}, // 作业1传输到作业0需要1个时间单位
        {make_pair(1, 2), 1}, // 作业1传输到作业2需要1个时间单位
        {make_pair(1, 3), 2}, // 作业1传输到作业3需要2个时间单位
        {make_pair(1, 4), 3}, // 作业1传输到作业4需要3个时间单位
        {make_pair(2, 0), 2}, // 作业2传输到作业0需要2个时间单位
        {make_pair(2, 1), 1}, // 作业2传输到作业1需要1个时间单位
        {make_pair(2, 3), 1}, // 作业2传输到作业3需要1个时间单位
        {make_pair(2, 4), 2}, // 作业2传输到作业4需要2个时间单位
        {make_pair(3, 0), 3}, // 作业3传输到作业0需要3个时间单位
        {make_pair(3, 1), 2}, // 作业3传输到作业1需要2个时间单位
        {make_pair(3, 2), 1}, // 作业3传输到作业2需要1个时间单位
        {make_pair(3, 4), 1}, // 作业3传输到作业4需要1个时间单位
        {make_pair(4, 0), 4}, // 作业4传输到作业0需要4个时间单位
        {make_pair(4, 1), 3}, // 作业4传输到作业1需要3个时间单位
        {make_pair(4, 2), 2}, // 作业4传输到作业2需要2个时间单位
        {make_pair(4, 3), 1}, // 作业4传输到作业3需要1个时间单位
    };

    int populationSize = 5; // 较小的种群大小
    int generations = 5;

    // 初始化种群
    vector<Schedule> population;
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(generateRandomSchedule(jobs, K));
    }

    for (int gen = 0; gen < generations; ++gen) {
        // 评估种群中每个调度的适应度
        for (Schedule& schedule : population) {
            schedule.completionTime = evaluateSchedule(schedule, jobs, communicationTime);
        }

        // 对种群按适应度排序
        sort(population.begin(), population.end(), [](const Schedule& a, const Schedule& b) {
            return a.completionTime < b.completionTime;
        });

        // 输出每代最佳完成时间
        cout << "Generation " << gen << ": Best Completion Time = " << population[0].completionTime << endl;

        // 选择最佳的一部分调度作为父代
        int eliteSize = populationSize / 5;
        vector<Schedule> newPopulation(population.begin(), population.begin() + eliteSize);

        // 生成子代调度
        for (int i = 0; i < populationSize - eliteSize; ++i) {
            int parent1Index = rand() % eliteSize;
            int parent2Index = rand() % eliteSize;

            Schedule child = crossover(population[parent1Index], population[parent2Index], jobs, communicationTime);

            // 随机进行变异
            if (rand() % 100 < 5) { // 设定一定的变异概率
                mutate(child, jobs, communicationTime);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    // 输出最终最佳完成时间和分配情况
    cout << "Final Best Completion Time = " << population[0].completionTime << endl;
    cout << "Final Schedule:" << endl;
    for (int i = 0; i < K; ++i) {
        cout << "Machine " << i << ": ";
        for (int jobId : population[0].assignments[i]) {
            cout << "Job " << jobId << " ";
        }
        cout << endl;
    }

    return 0;
}


