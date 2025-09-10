#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
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

int customLinearFindInt(vector<int> &vec, int target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;
        }
    }
    return -1;
}

void benchmarkCustomLinearInt(vector<int> &vec, int count) {
    double totalTime = 0;
    int n = vec.size();
    for (int i = 0; i < count; i++) {
        int idx = rand() % n;
        int target = vec[idx];
        auto startTime = chrono::high_resolution_clock::now();
        customLinearFindInt(vec, target);
        auto endTime = chrono::high_resolution_clock::now();
        totalTime += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    }
    double avgTime = totalTime / count;
    cout << "Total time for " << count << " searches: " << totalTime / 1000000.0 << " ms" << endl;
    cout << "Average time per search: " << avgTime / 1000000.0 << " ms for vector size " << n << endl;
}


int main() {
    int N = 28; // You can change N to generate more/less vectors
    for (int i = 1; i <= N; ++i) {
        int size = pow(2, i);
        auto genStart = chrono::high_resolution_clock::now();
        vector<int> randomVec = generateRandomIntVector(size);
        auto genEnd = chrono::high_resolution_clock::now();
        double genTime = chrono::duration_cast<chrono::nanoseconds>(genEnd - genStart).count() / 1000000.0;
        cout << "Random vector of size 2^" << i << " (" << size << ") generated in " << genTime << " ms" << endl;
        benchmarkCustomLinearInt(randomVec, 1000000);
    }
    return 0;
}