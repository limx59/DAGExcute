#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <unordered_map>
#include <time.h>

using namespace std;

// 自定义哈希函数，用于 unordered_map 的键
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // 为了避免碰撞，可以使用混合哈希算法
        return h1 ^ h2;
    }
};

struct Job {
    int id;
    int executionTime;
    vector<int> dependencies;  // 依赖的作业列表
};

struct Schedule {
    vector<vector<int>> assignments; // 分配到每台机器的作业
    int completionTime; // 总完成时间
};

// 随机生成一个初始调度
Schedule generateRandomSchedule(const vector<Job>& jobs, int K);

// 评估一个调度的适应度
int evaluateSchedule(const Schedule& schedule, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime);

// 交叉操作，生成子代调度
Schedule crossover(const Schedule& parent1, const Schedule& parent2, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime);

// 变异操作，对调度进行随机变异
void mutate(Schedule& schedule, const vector<Job>& jobs, const unordered_map<pair<int, int>, int, pair_hash>& communicationTime);

