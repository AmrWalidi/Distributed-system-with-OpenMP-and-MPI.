#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 1000  
#define MASTER 0

int main(int argc, char* argv[]) {
    int rank, size, chunk_size;
    int data[N], local_data[N];

    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;  

    if (rank == MASTER) {
        printf("Original Data: ");
        for (int i = 0; i < N; i++) {
            data[i] = i + 1;
            printf("%d\n", data[i]);
        }
        printf("\n");
    }

    MPI_Scatter(data, chunk_size, MPI_INT, local_data, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    #pragma omp parallel for
    for (int i = 0; i < chunk_size; i++) {
        local_data[i] *= 2;  
    }

    MPI_Gather(local_data, chunk_size, MPI_INT, data, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

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

