#include <iostream>
#include <chrono>

#include "mpi.h"
using namespace std;
using namespace std::chrono;

int main() {
    MPI_Init(&argc, &argv);
    int world_size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0){
        cout << "Number of processors: " << world_size << "\n";
    }
    cout << "Processor " << rank << " - Hello World\n";
    MPI_Finalize();
    return 0;
}