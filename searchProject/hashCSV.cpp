#include <iostream>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cmath>
using namespace std;

unordered_set<int> generateRandomIntSet(int size, unsigned int seed = 0) {
    mt19937 gen(seed == 0 ? random_device{}() : seed);
    uniform_int_distribution<int> dis(0, size * 10); // Increased range to reduce collisions
    unordered_set<int> result;
    while (result.size() < size) {
        //cout << "Current set size: " << result.size() << endl;

        result.insert(dis(gen));
    }
    return result;
}

int customHashFind(const unordered_set<int> &uset, int target) {
    return uset.find(target) != uset.end();
}

void benchmarkCustomHash(unordered_set<int> &uset, int count, int size) {
    vector<int> values(uset.begin(), uset.end());
    double totalTime = 0;
    int n = values.size();
    for (int i = 0; i < count; i++) {
        int idx = rand() % n;
        int target = values[idx];
        auto startTime = chrono::high_resolution_clock::now();
        auto endTime = chrono::high_resolution_clock::now();
        totalTime += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    }
    double avgTime = totalTime / count;
    cout << size << "," << totalTime / 1000000.0 << "," << avgTime / 1000000.0 << endl;
}

int main() {
    int N = 28; // You can change N to generate more/less sets
    cout << "size,totalTime,averageTime" << endl;
    for (int i = 1; i <= N; ++i) {
        int size = pow(2, i);
        unordered_set<int> randomSet = generateRandomIntSet(size);
        benchmarkCustomHash(randomSet, 1000000, size);
    }
    return 0;
}