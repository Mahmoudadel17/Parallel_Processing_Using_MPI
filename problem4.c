
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>


#define FILE_NAME_SIZE 100

int main(int argc, char *argv[]) {
    int rank, size;
    char *message;
    int MAX_MESSAGE_SIZE=0;
    int message_size_per_process=0;
    char *encrypted_message;
    char *encrypted_message2;
    int key;
    FILE *file_pointer;
    
    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Master process reads message from file
    if (rank == 0) {
        char filename[FILE_NAME_SIZE];
        long file_size;

        
        // Get file name from user
        printf("Enter file name: ");
        scanf("%s", filename);
        
        // Open file for reading
        file_pointer = fopen(filename, "rb");
        
        if (file_pointer == NULL) {
            printf("Error opening file!");
            MPI_Finalize();
            return 1;
        }
        
        fseek(file_pointer, 0, SEEK_END); // move file pointer to end of file
        file_size = ftell(file_pointer); // get current position of file pointer, which is the size of the file
        printf("file size = %ld\n",file_size);

        // // Handle remaining part of message (if exists)
        if(file_size % size !=0){
            fclose(file_pointer);
            FILE *file_ptr = fopen(filename, "a");

            if (file_ptr == NULL) {
                printf("Error: Failed to open file.\n");
                return 1;
            }
            // loop 
            int i=0;
            for(;i<size - (file_size % size);i++){
                fprintf(file_ptr," ");
                printf("fffffffffffffffff\n");
            }
             fclose(file_ptr);
            // Open file for reading
            file_pointer = fopen(filename, "rb");
            fseek(file_pointer, 0, SEEK_END); // move file pointer to end of file
            file_size = ftell(file_pointer); // get current position of file pointer, which is the size of the file
            printf("file size = %ld\n",file_size);
        }
        rewind(file_pointer); // move file pointer back to beginning of file
    
        message = (char*) malloc(sizeof(char) * file_size); // allocate memory for the message
    
        if (message == NULL) {
            printf("Error allocating memory!");
            return 1;
        }
    
        fread(message, sizeof(char), file_size, file_pointer); // read the message from the file

        fclose(file_pointer); // close the file
        
        // print the message
        printf("Message: %s\n", message);

        MAX_MESSAGE_SIZE = strlen(message);
        printf("M M S: %d\n", MAX_MESSAGE_SIZE);

        // Get key from user
        printf("Enter key value: ");
        scanf("%d", &key);
         
    }
    
    // Broadcast key to all processes
    MPI_Bcast(&MAX_MESSAGE_SIZE , 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);


    // Calculate message size per process
    message_size_per_process = MAX_MESSAGE_SIZE / size;
    
    // Scatter message to all processes
   char message_part[message_size_per_process];
   MPI_Scatter(message, message_size_per_process, MPI_CHAR, message_part,message_size_per_process, MPI_CHAR, 0, MPI_COMM_WORLD);
    

    int i = 0;
    for ( ;i < message_size_per_process; i++) {
        char c = message_part[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
           message_part[i] = ((c - base + key) % 26) + base;
        } else {
           message_part[i] = c;
        }
    }

    // allocate memory for the message
    encrypted_message2 = (char*) malloc(sizeof(char) *  MAX_MESSAGE_SIZE);

    
    printf("message_size_per_process  out = %d \n", message_size_per_process);
    // Gather encrypted message parts
    MPI_Gather(message_part, message_size_per_process, MPI_CHAR, encrypted_message2,message_size_per_process, MPI_CHAR, 0, MPI_COMM_WORLD);


    // Write encrypted message to file
    if (rank == 0) {
        file_pointer = fopen("encrypted_message.txt", "w");
        fputs(encrypted_message2, file_pointer);
        printf("Encrypt a Message Done Successfully \n");
         
    }
   
    MPI_Finalize();
    
    return 0;

}

