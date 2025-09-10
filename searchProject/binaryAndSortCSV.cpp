#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std;


vector<int> generateRandomIntVector(int size, unsigned int seed = 0) {
    mt19937 gen(seed == 0 ? random_device{}() : seed);
    uniform_int_distribution<int> dis(0, 100);
    vector<int> result;
    result.reserve(size);
    for (int i = 0; i < size; ++i) {
        result.push_back(dis(gen));
    }
    return result;
}

int customBinaryFind(vector<int> &vec, int target) {
    int left = 0;
    int right = vec.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] == target) {
            return mid;
        } else if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void benchmarkCustomBinary(vector<int> &vec, int count, int size) {
    double totalTime = 0;
    int n = vec.size();
    for (int i = 0; i < count; i++) {
        int idx = rand() % n;
        int target = vec[idx];
        auto startTime = chrono::high_resolution_clock::now();
        sort(vec.begin(), vec.end());
        customBinaryFind(vec, target);
        auto endTime = chrono::high_resolution_clock::now();
        totalTime += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    }
    double avgTime = totalTime / count;
    // Output in CSV: size,totalTime(ms),averageTime(ms)
    cout << size << "," << totalTime / 1000000.0 << "," << avgTime / 1000000.0 << endl;
}


int main() {
    int N = 28; // You can change N to generate more/less vectors
    cout << "size,totalTime,averageTime" << endl;
    for (int i = 1; i <= N; ++i) {
        int size = pow(2, i);
        vector<int> randomVec = generateRandomIntVector(size);
        benchmarkCustomBinary(randomVec, 1000000, size);
    }
    return 0;
}