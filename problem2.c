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
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
	int mode,m1, n1, m2, n2,my_size,first_i,mod;
	char filename[] = "input.txt";
    int** mat1;
    int** mat2;
    int** result;

	/* Start up MPI */
	MPI_Init( &argc , &argv );
	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(my_rank == 0){
		printf("Welcome to matrix multiplication program!\n\n");
        printf("To read dimensions and values from file press 1\n");
        printf("To read dimensions and values from console press 2\n");
        scanf("%d", &mode);

		if(mode == 1){
			 FILE* file = fopen(filename, "r");
            fscanf(file, "%d %d", &m1, &n1);

			// mat 1 input
			mat1 = (int**) malloc(m1 * sizeof(int));
            int i = 0;
            for (; i < m1; i++) {
                mat1[i] = (int*) malloc(n1 * sizeof(int));
                int j = 0;
                for (; j < n1; j++) {
                    fscanf(file, "%d", &mat1[i][j]);
                }
            }

			fscanf(file, "%d %d", &m2, &n2);
			if (n1 != m2) {
            printf("Invalid matrix dimensions.\n");
            return 0;
            }
			// mat 2 input
			mat2 = (int**) malloc(m1 * sizeof(int));
            i = 0;
            for (; i < m1; i++) {
                mat2[i] = (int*) malloc(n1 * sizeof(int));
                int j = 0;
                for (; j < n1; j++) {
                    fscanf(file, "%d", &mat2[i][j]);
                }
            }

			// close file
			fclose(file);
		}
		else if(mode == 2){
			printf("Please enter dimensions of the first matrix: ");
			scanf( "%d %d", &m1, &n1);
            printf("\nPlease enter its elements:\n");
			// mat 1 input
			mat1 = (int**) malloc(m1 * sizeof(int));
            int i = 0;
            for (; i < m1; i++) {
                mat1[i] = (int*) malloc(n1 * sizeof(int));
                int j = 0;
                for (; j < n1; j++) {
                    scanf( "%d", &mat1[i][j]);
                }
            }

			printf("\nPlease enter dimensions of the second matrix: ");
			scanf( "%d %d", &m2, &n2);
            printf("\nPlease enter its elements:\n");
			if (n1 != m2) {
            printf("Invalid matrix dimensions.\n");
            return 0;
            }
			// mat 2 input
			mat2 = (int**) malloc(m1 * sizeof(int));
            i = 0;
            for (; i < m2; i++) {
                mat2[i] = (int*) malloc(n1 * sizeof(int));
                int j = 0;
                for (; j < n2; j++) {
                    scanf( "%d", &mat2[i][j]);
                }
            }
            printf("\n\n");
			         

		}
		else{
			printf("error please select correct mode!!\n");
			return 0;
		}

        
		my_size = m1 /(p - 1);
		mod = m1 % (p - 1);
        int stop = m1;
        source = 1;
		for( ; source < p ; source++)
		{
            first_i =  (source - 1) *my_size  ;
            if(m1 <p-1){
                my_size=1;
            }

			if(source == p - 1){
				my_size+=mod;
			}
            
			
            MPI_Send(&m1, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
            if(m1 < p - 1){
                if(stop>0){
                    // send row of Array size
			        
			        MPI_Send(&n1, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
			        // send row of Array 1 
                    MPI_Send(&mat1[first_i][0], n1, MPI_INT, source, 0, MPI_COMM_WORLD);

                    // // second mat
			        MPI_Send(&n2, 1, MPI_INT, source, tag, MPI_COMM_WORLD);

                    int i = 0;
                    for(;i < m2;i++){
                    MPI_Send(&mat2[i][0], n2, MPI_INT, source, 0, MPI_COMM_WORLD);
                    }
                    stop--;
                }
                
            }
            else{
                // send row of Array size
			    
			    MPI_Send(&n1, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
			    // send row of Array 1 
                int i = 0; 
                for(;i < my_size;i++){
                    MPI_Send(&mat1[first_i][0], n1, MPI_INT, source, 0, MPI_COMM_WORLD);
                    first_i++;
                }

                // second mat
			    MPI_Send(&n2, 1, MPI_INT, source, tag, MPI_COMM_WORLD);

                i = 0;
                for(;i < m2;i++){
                    MPI_Send(&mat2[i][0], n2, MPI_INT, source, 0, MPI_COMM_WORLD);
                }
            }

			
		}
    }
    else
    {

        MPI_Recv(&m1, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
        my_size = m1 /(p - 1);
             mod = m1 % (p - 1);
		    if(my_rank == p - 1){
			    my_size+=mod;
		    }
             if(m1<p-1){
                my_size=1;
                if(my_rank>m1){
                    goto start;
		            getch();
                    
                }
            }
		    
		    MPI_Recv(&n1, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
            //printf("m1 is %d n1 is %d\n",m1,n1);
            m2 = n1;
            //printf("my size is %d\n",my_size);
		   


            int *row1 = malloc(n1* sizeof(int));
		    // mat 1 input
		    mat1 = (int**) malloc(m1 * sizeof(int));
            int i = 0;
            for (; i < m1; i++) {
                mat1[i] = (int*) malloc(n1 * sizeof(int));
            }

            i = 0;
            for (; i < my_size; i++) {
                MPI_Recv(row1,n1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // printf("Process %d received row %d: ", my_rank, i);
		        int j = 0;
                for (; j < n1; j++) {
                    
                    mat1[i][j] = row1[j];
                    // printf("%d ", mat1[i][j]);

                }
                //printf("\n");  
            }



            MPI_Recv(&n2, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
            //printf("m2 is %d n2 is %d\n",m2,n2);
            
            int *row = malloc(n2* sizeof(int));
            // mat 2 input
		    mat2 = (int**) malloc(m2 * sizeof(int));
            i = 0;
            for (; i < m2; i++) {
                mat2[i] = (int*) malloc(n2 * sizeof(int));
            }

            i = 0;
            for (; i < m2; i++) {
                MPI_Recv(row,n2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // printf("Process %d received row %d: ", my_rank, i);
		        int j = 0;
                for (; j < n2; j++) {
                    
                    mat2[i][j] = row[j];
                    // printf("%d ", mat2[i][j]);

                }
                //printf("\n");  
            }


            // dynamic array 
            result = (int**) malloc(m1 * sizeof(int));
            i = 0;
            for (; i < m1; i++) {
                result[i] = (int*) malloc(n2 * sizeof(int));
            }


            // Multiply the matrices
        i = 0;
        for (; i < m1; i++) {
            int j = 0;
            for (; j < n2; j++) {
                result[i][j] = 0;
                int k = 0;
                for (; k < n1; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }

        // send result 
        MPI_Send(&my_size, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        i = 0;
        for(;i <my_size;i++){
            MPI_Send(&result[i][0], n2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }


        
        }

        start:

    if(my_rank == 0){
            //recv the result mat.
            printf("Result Matrix is (%dx%d):\n",m1,n2);
            source=1;
            for(;source<p-1;source++){
                // recv from all slave
                MPI_Recv(&my_size, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
                // dynamic array 
                int *row = malloc(n2* sizeof(int));

                result = (int**) malloc(m1 * sizeof(int));
                int i = 0;
                for (; i < m1; i++) {
                    result[i] = (int*) malloc(n2 * sizeof(int));
                }

                i = 0;
                for (; i < my_size; i++) {
                    MPI_Recv(row,n2, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    //printf("Process %d received row %d: ", my_rank, i);
		            int j = 0;
                    for (; j < n2; j++) {
                    
                        result[i][j] = row[j];
                        printf("%d ", result[i][j]);

                    }
                    printf("\n");  
                }


            } 
            
    }


	
    
    /* shutdown MPI */
	MPI_Finalize();
	return 0;
}

