#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 1000 

int main(int argc, char** argv) {
    int world_rank, world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int chunk_size = DATA_SIZE / world_size;  
    int data[chunk_size];

    #pragma omp parallel for
    for (int i = 0; i < chunk_size; i++) {
        data[i] = world_rank * chunk_size + i;
        printf("Node %d - Thread %d processed data[%d] = %d\n", world_rank, omp_get_thread_num(), i, data[i]);
    }

    MPI_Finalize();
    return 0;
}
