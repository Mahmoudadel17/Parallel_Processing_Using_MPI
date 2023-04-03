

 
#include <stdio.h>
#include "mpi.h"
#include <time.h>

int check_prime(int a)
{
    int c;

    for (c = 2; c <= a - 1; c++)
    {
        if (a % c == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{

    int my_rank;       /* rank of process	*/
    int p;             /* number of process	*/
    int source;        /* rank of sender	*/
    int dest;          /* rank of reciever	*/
    int tag = 0;       /* tag for messages	*/
    MPI_Status status; /* return status for 	*/
    int mode, Lower_bound_num, Upper_bound_num, r, mod, my_count_primes = 0, count_primes = 0;

    /* Start up MPI */
    MPI_Init(&argc, &argv);
    /* Find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    /* Find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == 0)
    {

        clock_t start, end;
        double duration;
        // input from user
        printf("Please enter the lower bound and upper bound numbers: ");

        scanf("%d %d", &Lower_bound_num, &Upper_bound_num);

        // check the input is correct (upper !< lower).
        if (Upper_bound_num <= Lower_bound_num)
        {
            printf("range not correct!!\n");
            return 0;
        }

        /* Store start time here */
        start = clock();

        // calc size of numbers for each slave and reminder.
        r = (Upper_bound_num - Lower_bound_num) / (p - 1);
        mod = (Upper_bound_num - Lower_bound_num) % (p - 1);

        source = 1;
        for (; source < p; source++)
        {
            // send for each slave
            MPI_Send(&r, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
            MPI_Send(&Lower_bound_num, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
            MPI_Send(&mod, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
        }

        int source = 1;
        for (; source < p; source++)
        {
            MPI_Recv(&my_count_primes, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
            count_primes += my_count_primes;
        }
        printf("total count of primes between %d and %d is %d \n: ", Lower_bound_num, Upper_bound_num, count_primes);

        /* program logic ends here */
        end = clock();
        /* Get the time taken by program to execute in seconds */
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time taken to execute using mpi_send_recv in seconds : %f\n", duration);
        printf("start = %lf , end = %lf\n", (double)start / CLOCKS_PER_SEC, (double)end / CLOCKS_PER_SEC);
    }
    else
    {
        // slave code.
        MPI_Recv(&r, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&Lower_bound_num, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&mod, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        int a = 0, b = 0;
        // printf("slave # %d r is %d\n",my_rank,r);

        a = (my_rank - 1) * (r) + Lower_bound_num;
        b = a + (r - 1);

        if (my_rank == p - 1)
        {
            b += mod;
        }
        // printf("slave # %d a is %d and b is %d \n",my_rank,a,b);

        ////////////////////////////////////////////////
        int i = a;
        for (; i <= b; i++)
        {

            if (check_prime(i) && i != 1 && i != 0)
            {
                my_count_primes++;
                // printf("slave num# %d number %d is prime\n",my_rank,i);
            }
        }
        /////////////////////////////////////////////////

        printf("slave num# %d  my count primes is %d \n", my_rank, my_count_primes);

        // Send this partial count to the master process
        MPI_Send(&my_count_primes, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    /* shutdown MPI */
    MPI_Finalize();

    return 0;
}
// 1 >> 11         r = 3     mod = 2
//
//    s1             s2               s3
//  1 2 3        4 5 6         7 8 9 10 11