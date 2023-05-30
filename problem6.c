#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"
#include <time.h>



double squareRoot(double num) {
    double epsilon = 0.00001;
    double guess = num / 2.0;

    while ((guess * guess - num) > epsilon) {
        guess = (guess + num / guess) / 2.0;
    }

    return guess;
}

int main(int argc, char *argv[])
{
  	int my_rank;		/* rank of process	*/
	int size;			   /* number of process	*/
	int source;		  /* rank of sender	*/
	int dest;		 /* rank of reciever	*/
	int tag = 0;    /* tag for messages	*/
	MPI_Status status;	/* return status for recieve		*/


    int arrSize,userArraySize,sumOfArrayElemets=0;
    int* array;
    double  Mean , Variance=0, Standard_deviation = 0;

      /* Start up MPI */
	MPI_Init( &argc , &argv );
	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(my_rank==0){
        // take size of array from user
        printf("Enter Array Size: ");
        scanf("%d" , &userArraySize);
        arrSize = userArraySize;
        if(userArraySize % size != 0){
            arrSize +=  (size - (arrSize%size));
        }
        
        // take array from user
        array = malloc(arrSize * sizeof(int));

        memset(array, 0, arrSize * sizeof(int));
        if(array != NULL){
             printf("Enter Array elements: ");
            int i = 0;
            for(; i< userArraySize; i++){
                scanf("%d" , &array[i]);
                sumOfArrayElemets+=array[i];
            }

        }else{ printf("Error: Memory allocation failed\n");  }

       Mean = sumOfArrayElemets / userArraySize;
       // printf("Mean : %f \n",Mean);


    }

    // Broadcast array and Mean to all processes
    MPI_Bcast(&userArraySize , 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&Mean , 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&arrSize , 1, MPI_INT, 0, MPI_COMM_WORLD);

    int size_per_process = arrSize / size;

    // Scatter array to all processes
    int array_part[size_per_process];
    MPI_Scatter(array, size_per_process, MPI_INT, array_part,size_per_process, MPI_INT, 0, MPI_COMM_WORLD);


    // Dont compute 0 we handele reminnig
    if(my_rank == size - 1){
        if(userArraySize % size != 0){
            size_per_process = size_per_process - (size - (userArraySize%size));
        }
        
    }

    double sum = 0;
    int i = 0;
    for( ; i < size_per_process ; i++){
        sum += abs((array_part[i] - Mean) * (array_part[i] - Mean));
        // printf("Mean = %d \n",abs((array_part[i] - Mean) * (array_part[i] - Mean)));
    }
     // Reduce this partial Variance and Standard deviation to the master process
    MPI_Reduce(&sum, &Variance, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

   if(my_rank == 0){
    Variance = Variance / userArraySize;
    Standard_deviation = squareRoot(Variance);
    printf("Mean = %f, Variance = %f, Standard deviation = %f \n",Mean,Variance,Standard_deviation);
   }
        
    MPI_Finalize();
return 0;
}