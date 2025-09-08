#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

vector<double> generateRandomVector(int size, unsigned int seed = 0) {
    // Use provided seed or generate random seed if seed is 0
    mt19937 gen(seed == 0 ? random_device{}() : seed);
    
    // Create uniform distribution for values between 0.0 and 100.0
    uniform_real_distribution<double> dis(0.0, 100.0);
    
    vector<double> result;
    result.reserve(size);
    
    for (int i = 0; i < size; ++i) {
        result.push_back(dis(gen));
    }
    
    return result;
}

int customLinearFind(vector<double> &vec, double target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;  // Return the index where found
        }
    }
    return -1;  // Return -1 if not found
}

void benchmarkCustomLinear(vector<double> &vec, int count) {
    cout << "\nBenchmarking linear search..." << endl;
    double totalTime = 0;
    for (int i = 0; i < count; i++) {
        auto startTime = chrono::high_resolution_clock::now();
        cout << customLinearFind(vec, vec[i]) << endl;
        auto endTime = chrono::high_resolution_clock::now();
        totalTime += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    }
    double avgTime = totalTime / count;
    cout << "Average time per search: " << avgTime / 1000000.0 << " milliseconds" << endl;
    cout << "Total time: " << totalTime / 1000000000.0 << " seconds" << endl;
}


int main() {
    // Generate random vector with default seed
    vector<double> randomVec1 = generateRandomVector(5);
    cout << "Random vector (default seed): ";
    for (double val : randomVec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // Generate random vector with specific seed
    vector<double> randomVec2 = generateRandomVector(1000000);
    cout << "Random vector (seed=42): ";
    for (double val : randomVec2) {
        cout << val << " ";
    }
    cout << endl;
    
    // Benchmark the linear search
    benchmarkCustomLinear(randomVec2, 1000);
    
    return 0;
}