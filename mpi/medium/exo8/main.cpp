#include <cstdlib>
#include <iostream>
#include <string>

// MPI
#include "mpi.h"

using namespace std;

int main(int argc, char** argv) {

    // MPI: initialization
    MPI_Init(&argc, &argv);

    // MPI: get the number of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // MPI: get the processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the scaling mode and the size
    if (argc != 3 || (string(argv[1]) != "strong" && string(argv[1]) != "weak")) {
        if (rank == 0) {
            cerr << "Usage: mpirun -np <processes> ./run <strong|weak> <size>\n";
        }
        MPI_Finalize();
        return 1;
    }
    string mode = argv[1];
    long long size = stoll(argv[2]);

    // Strong scaling: the global size is fixed. Weak scaling: the size per process is fixed.
    long long global_size = (mode == "strong") ? size : size * world_size;
    if (global_size % world_size != 0) {
        if (rank == 0) {
            cerr << "Error: the global size must be divisible by the number of processes.\n";
        }
        MPI_Finalize();
        return 1;
    }
    int local_size = global_size / world_size;

    // Vectors
    int* global_vector1 = nullptr;
    int* global_vector2 = nullptr;
    int* local_vector1 = new int[local_size];
    int* local_vector2 = new int[local_size];

    if (rank == 0){
        global_vector1 = new int[global_size];
        global_vector2 = new int[global_size];

        for (long long i = 0; i < global_size; i++){
            global_vector1[i] = rand() % 1000;
            global_vector2[i] = rand() % 10;
        }
    }

    MPI_Scatter(global_vector1, local_size, MPI_INT, local_vector1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(global_vector2, local_size, MPI_INT, local_vector2, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Repeat the measure and keep the best time
    const int repetitions = 10;
    double best_time = 0;
    long long global_result = 0;

    for (int r = 0; r < repetitions; r++){

        // MPI: synchronize all the processes before starting the chrono
        MPI_Barrier(MPI_COMM_WORLD);
        double start = MPI_Wtime();

        // vector-vector
        long long local_result = 0;
        for (int i = 0; i < local_size; i++){
            local_result += (long long)local_vector1[i] * local_vector2[i];
        }

        // MPI: sum of the local results on the rank 0
        MPI_Reduce(&local_result, &global_result, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

        // MPI: the time of a parallel run is the time of the slowest process
        double local_time = MPI_Wtime() - start;
        double max_time;
        MPI_Reduce(&local_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        if (rank == 0 && (r == 0 || max_time < best_time)){
            best_time = max_time;
        }
    }

    // Print the result and the time
    if (rank == 0){
        cout << "Mode: " << mode << ", processes: " << world_size << ", global size: " << global_size << "\n";
        cout << "Result: " << global_result << "\n";
        cout << "Time: " << best_time * 1000 << " ms\n";
    }

    if (rank == 0){
        delete[] global_vector1;
        delete[] global_vector2;
    }
    delete[] local_vector1;
    delete[] local_vector2;

    // Finalisation de MPI
    MPI_Finalize();

    return 0;
}
