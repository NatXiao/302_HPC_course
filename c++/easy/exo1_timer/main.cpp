#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    auto time_now = high_resolution_clock::now();
    cout << "Hello World! \n";
    auto time_then = high_resolution_clock::now();
    auto diff = duration_cast<microseconds> (time_then - time_now);
    cout << "execution time : " << diff.count() << "ms\n";
    return 0;
}