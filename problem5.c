#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int rank, size;
    static long num_steps = 1000000;
    double step, sum = 0.0, pi = 0.0;
    int i, my_start, my_end;
    double x;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    step = 1.0/(double)num_steps;

    // Divide the work among processes
    int chunk_size = num_steps/size;
    my_start = rank * chunk_size;
    my_end = my_start + (chunk_size-1);
    
    if(rank==size-1){
        my_end++;
    }
    printf("start = %d \n",my_start);
    printf("end = %d \n",my_end);
    // Calculate the sum for this process
    for(i = my_start; i < my_end; i++)
    {
        x = ((double)(i + 0.5))*step;
        sum += 4.0/(1.0+x*x);
    }

    // Combine the sums
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Output the final value of pi
    if(rank == 0)
    {
        pi *= step;
        printf("PI = %.20f \n", pi);
    }

    MPI_Finalize();
    return 0;
}




