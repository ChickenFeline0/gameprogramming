#include <iostream>
#include <random>
using namespace std;

int main() {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    
    // Generate a random number between 1 and 100
    uniform_int_distribution<> dis(1, 100);
    
    while(true){
        cout << dis(gen) << " ";
    }
    
    return 0;
}