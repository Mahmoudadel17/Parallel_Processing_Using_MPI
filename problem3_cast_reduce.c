
#include <stdio.h>
#include "mpi.h"
#include <time.h>


int check_prime(int a)
{
   int c;
 
   for ( c = 2 ; c <= a - 1 ; c++ )
   { 
      if ( a%c == 0 )
     return 0;
   }
   return 1;
}


int main(int argc, char *argv[])
{
  	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
    int mode,Lower_bound_num,Upper_bound_num,r,mod,my_count_primes=0,count_primes=0;
    clock_t start, end;
    double duration;

      /* Start up MPI */
	MPI_Init( &argc , &argv );
	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

       if(my_rank==0){
            printf("Please enter the lower bound and upper bound numbers: ");

            scanf("%d %d", &Lower_bound_num,&Upper_bound_num);


            // check the input is correct (upper !< lower).
            if(Upper_bound_num <= Lower_bound_num){
                 printf("range not correcct!!\n");
                 return 0;
            }
            /* Store start time here */
            start = clock();

            // calc size of numbers for each slave and reminder.
            r = (Upper_bound_num - Lower_bound_num) / ( p - 1);
            mod = (Upper_bound_num - Lower_bound_num) % ( p - 1);

        }
        
        MPI_Bcast(&r, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&Lower_bound_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&mod, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if(my_rank!=0){
                 

        int a=0,b=0;
        //printf("slave # %d r is %d\n",my_rank,r);

        a = (my_rank-1)*(r) + Lower_bound_num ;
        b = a + (r-1);

        if(my_rank == p-1){
            b+=mod;
        }

         ////////////////////////////////////////////////
        int i=a;
        for(;i<=b;i++){

            if(check_prime(i)&& i!=1 && i!=0)
            {
                my_count_primes++;
                //printf("slave num# %d number %d is prime\n",my_rank,i);
            }
        }
        /////////////////////////////////////////////////

        printf("slave num# %d  my count primes is %d \n",my_rank,my_count_primes);

       

        }
         // Reduce this partial count to the master process
        MPI_Reduce(&my_count_primes, &count_primes, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);

         
        if(my_rank== 0){
            /* program logic ends here */
            end = clock();
             /* Get the time taken by program to execute in seconds */
            duration = ((double)(end - start))/CLOCKS_PER_SEC;
            printf("total count of primes between %d and %d is %d \n: ",Lower_bound_num,Upper_bound_num,count_primes);

            printf("Time taken to execute using mpi_cast_reduce in seconds : %f\n", duration);
            printf("start = %lf , end = %lf\n", (double)start / CLOCKS_PER_SEC, (double)end / CLOCKS_PER_SEC);
             
        }
        
        MPI_Finalize();
return 0;
}