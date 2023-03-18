#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	char message[100];	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
    int sizeArr ,my_size , my_max  = 0 , my_index , max = 0 , index , mod ,first_i,last_i ;
    int* array;
    int* partition;
	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank == 0)
	{
		printf("Hello from master process.\n");
        printf("Number of slave processes is %d\n\n" , p-1);
        printf("Please enter size of array...\n");
        scanf("%d" , &sizeArr);
        printf("Please enter array elements ...\n");
        array = malloc(sizeArr * sizeof(int));
        if(array != NULL){
            int i = 0;
            for(; i< sizeArr; i++){
                scanf("%d" , &array[i]);
            }
        }

		mod = sizeArr % (p-1);
		my_size = sizeArr / (p-1);
		

        //master Distributes the work among slaves processes:
	    source = 1;
		for( ; source < p ; source++)
		{
			// send Array size
			MPI_Send(&sizeArr, 1, MPI_INT, source, tag, MPI_COMM_WORLD);

			first_i = (source-1)*my_size;
			if(source == p -1){
				my_size+=mod;
			}
			// send Array 
			MPI_Send(&array[first_i],my_size, MPI_INT, source, tag, MPI_COMM_WORLD);

		}
		

	}
	else{

		MPI_Recv(&sizeArr, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
		// printf("size is  %d\n" ,sizeArr);

		mod = sizeArr % (p-1);
		my_size = sizeArr / (p-1);
		
		if(my_rank == p -1){
			my_size+=mod;
		}
		// dynamic array
		int *partion = malloc(my_size* sizeof(int));

		MPI_Recv(partion, my_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
		//printf("first elem  %d\n" ,partion[0]);
		my_max=partion[0];
		my_index = 0;
		int i=1;
		for(;i<my_size;i++){
			if(my_max < partion[i]){
				my_max = partion[i];
				my_index = i;
			}
		}

		MPI_Send(&sizeArr, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
		MPI_Send(&my_max, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
		MPI_Send(&my_index, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}

	if(my_rank == 0){
		 source = 1;
		for( ; source < p ; source++)
		{
			MPI_Recv(&my_size, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
			MPI_Recv(&my_max, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
			MPI_Recv(&my_index, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
			printf("Hello from slave# %d Max number in my partition is %d and index is %d \n",source,my_max,my_index);
			if(max < my_max){
				max = my_max;
				int newSize = my_size /(p - 1);
				index = (source - 1)*newSize + my_index;
			}
		}

		printf("Master process announce the final max which is %d and its index is %d\n ",max,index);
		printf("Thanks for using our program \n");


	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}

//  1 2 3 // 4 5 6 // 7 8 9 10
// 


