#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <unordered_map>
#include "DAGexcute.h"

using namespace std;

// 随机生成一个初始调度
Schedule generateRandomSchedule(const vector<Job>& jobs, int K) {
    Schedule schedule;
    schedule.assignments.resize(K);
    schedule.completionTime = 0;

    vector<Job> shuffledJobs = jobs;
    random_shuffle(shuffledJobs.begin(), shuffledJobs.end());

    for (const Job& job : shuffledJobs) {
        int minLoadMachine = min_element(schedule.assignments.begin(), schedule.assignments.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return accumulate(a.begin(), a.end(), 0) < accumulate(b.begin(), b.end(), 0);
            }) - schedule.assignments.begin();

        schedule.assignments[minLoadMachine].push_back(job.id);
        schedule.completionTime += job.executionTime;
    }

    return schedule;
}

// 评估一个调度的适应度
int evaluateSchedule(const Schedule& schedule, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime) {
    int maxCompletionTime = 0;
    int K = schedule.assignments.size();

    for (int machine = 0; machine < K; ++machine) {
        vector<int> machineJobs = schedule.assignments[machine];
        int machineCompletionTime = 0;

        for (int jobId : machineJobs) {
            int executionTime = jobs[jobId].executionTime;
            int communication = 0;

            for (int dependentJobId : jobs[jobId].dependencies) {
                if (find(machineJobs.begin(), machineJobs.end(), dependentJobId) == machineJobs.end()) {
                    // 如果依赖的作业不在同一台机器上，需要通信
                    communication += communicationTime.at(make_pair(dependentJobId, jobId));
                }
            }

            machineCompletionTime = max(machineCompletionTime, executionTime + communication);
        }

        maxCompletionTime = max(maxCompletionTime, machineCompletionTime);
    }

    return maxCompletionTime;
}

// 交叉操作，生成子代调度
Schedule crossover(const Schedule& parent1, const Schedule& parent2, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime) {
    Schedule child = parent1;

    // 随机选择一个切割点
    int splitPoint = rand() % child.assignments.size();

    // 将parent2的一部分分配给child
    for (int i = splitPoint; i < child.assignments.size(); ++i) {
        child.assignments[i] = parent2.assignments[i];
    }

    // 重新计算子代的总完成时间
    child.completionTime = evaluateSchedule(child, jobs, communicationTime);

    return child;
}

// 变异操作，对调度进行随机变异
void mutate(Schedule& schedule, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime) {
    int K = schedule.assignments.size();

    // 随机选择一个机器
    int machine = rand() % K;

    if (!schedule.assignments[machine].empty()) {
        // 随机选择两个作业
        int jobIndex1 = rand() % schedule.assignments[machine].size();
        int jobIndex2;
        do {
            jobIndex2 = rand() % schedule.assignments[machine].size();
        } while (jobIndex1 == jobIndex2);

        // 交换两个作业的位置
        swap(schedule.assignments[machine][jobIndex1], schedule.assignments[machine][jobIndex2]);

        // 更新完成时间
        schedule.completionTime = evaluateSchedule(schedule, jobs, communicationTime);
    }
}

