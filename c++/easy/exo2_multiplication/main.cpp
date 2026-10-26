#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    int x;
    cout << "Enter a number ";
    cin >> x;
    // \n
    auto time_now = high_resolution_clock::now();
    ofstream file("multiple.txt");
    for(int i = 0;i < 100000; i++){
        file << x*i << "\n";
    }
    file.close();
    auto time_then = high_resolution_clock::now();
    auto diff = duration_cast<milliseconds> (time_then - time_now);
    cout << "execution time : " << diff.count() << "ms\n";
    // endl
    auto time_now2 = high_resolution_clock::now();
    ofstream file2("multiple_endl.txt");
    for(int i = 0;i < 100000; i++){
        file2 << x*i << endl;
    }
    auto time_then2 = high_resolution_clock::now();
    file2.close();
    auto diff2 = duration_cast<milliseconds> (time_then - time_now);
        cout << "execution time : " << diff2.count() << "ms\n";
    return 0;
}