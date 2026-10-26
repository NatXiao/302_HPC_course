#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
    
    ifstream multiplicationfile(argv[1]); 
    int count = 0;
    string result;
    if(multiplicationfile.is_open()){
        while(count < 15 && getline(multiplicationfile, result)){
            cout << result << "\n";
            count ++;
        }    
        multiplicationfile.close();
    }else{
        cerr << "unable to open file multiple.txt";
        exit(1);
    }
    return 0;
}