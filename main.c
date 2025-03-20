#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 1000  // Total data size
#define MASTER 0

int main(int argc, char* argv[]) {
    int rank, size, chunk_size;
    int data[N], local_data[N];

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;  // Divide data among MPI processes

    // Initialize data only in MASTER node
    if (rank == MASTER) {
        printf("Original Data: ");
        for (int i = 0; i < N; i++) {
            data[i] = i + 1;  // Example data
            printf("%d\n", data[i]);
        }
        printf("\n");
    }

    // Scatter data to all nodes
    MPI_Scatter(data, chunk_size, MPI_INT, local_data, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Parallel Processing with OpenMP
    #pragma omp parallel for
    for (int i = 0; i < chunk_size; i++) {
        local_data[i] *= 2;  // Example computation: doubling the value
    }

    // Gather processed chunks back to MASTER node
    MPI_Gather(local_data, chunk_size, MPI_INT, data, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    // MASTER node prints the final result
    if (rank == MASTER) {
        printf("Processed Data: ");
        for (int i = 0; i < N; i++) {
            printf("%d\n", data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

