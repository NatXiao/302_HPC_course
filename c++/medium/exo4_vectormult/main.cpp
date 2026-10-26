#include <vector>
#include <cstdlib>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main(){
    int size[4] = {1'000'000, 10'000'000, 50'000'000, 100'000'000} ;
    // set up the 2 vectors
    for(int s= 0; s< 4; s++){
        int* v1 = new int[size[s]];
        int* v2 = new int[size[s]];
        for (int i = 0; i < s ;i++){
            v1[i] = rand();
            v2[i] = rand();
        } 
        // scalar product
        int scala_product = 0;
        auto time_now = high_resolution_clock::now();
        for (int i = 0; i < s ;i++){
            scala_product = scala_product + v1[i]* v2[i]; 
        } 
        cout << "produit scalaire : " << scala_product << "\n";
        auto time_then = high_resolution_clock::now();
        auto diff = duration_cast<milliseconds> (time_then - time_now);
        cout << "size : " << size[s] << " execution time : " << diff.count() << "ms\n";
        delete[] v1;
        delete[] v2;
    }
    return 0;
}