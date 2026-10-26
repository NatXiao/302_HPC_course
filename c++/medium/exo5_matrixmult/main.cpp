#include <cstdlib>
#include <chrono>
#include <iostream>
using namespace std::chrono;


int main(int argc, char* argv[]){
    //init
    int size = atoi(argv[1]);
    int* matrix1 = new int[size*size]();
    int* matrix2 = new int[size*size]();
    int* product_matrix = new int[size*size]();
    for(int i = 0; i < size; i++ ){
        for(int j = 0; j < size; j++){
            matrix1[i*size+j] = rand();
            matrix2[i*size+j] = rand();
        }
    }
    //time
    auto time_now = high_resolution_clock::now();
    for(int n= 0; n < size; n++){
        for(int i = 0; i < size; i++ ){
            int result = 0;
            for(int j = 0; j < size; j++){
                result = result + matrix1[i*size+ j] * matrix2[j*size +i];
            }
            product_matrix[n * size + i ] = result;
        }
    }

    auto time_then = high_resolution_clock::now();
    auto diff = duration_cast<milliseconds> (time_then - time_now);
    std::cout << "size : " << size << " execution time : " << diff.count() << "ms\n";

    delete[] matrix1;
    delete[] matrix2;
    delete[] product_matrix;
    return 0;
}