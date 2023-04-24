# Problem1 Statement:
- develop a parallel program that outputs max number in a given array using Master-Slave paradigm where :
- ## Master:
    1. Reads size of array.
    2. Reads elements inside array.
    3. Distributes the work among slaves processes:

        • Sends size of the array.

        • Sends the assigned partition of the array.

- After each slave finishes its work, master process receives max number and its index from each process.
- Then master computes the max number from max numbers returned from each slave.
- Output the final max number and its index in the original array to user.
## Slaves each one will:
- Receives size of the array.
- Receives the portion of the array.
- Calculates max number.
- Sends max number and its index back to master process.
### Note: 
Size of array may not be divisible by number of processes. So, you
should handle this case.


## Screenshots
![problem1](https://user-images.githubusercontent.com/100792508/226145982-06209968-13cb-4fdc-b989-204c7ecd106b.png)


# Problem2 Statement :
develop a parallel program that calculate matrix multiplication .

- Matrices’ dimensions and values are taken as an input. 
- Multiply the two matrices together then print the result. 
- implement this program in two modes.
  1. First mode reads the input from the console 
  2. the second one reads the input from a file.
### Note: useing dynamic allocation.

## Screenshots
![problem2_file](https://user-images.githubusercontent.com/100792508/226146012-c7a978e2-55b4-4bb7-80cb-36cc21dcb5a7.png)

![problem2_input](https://user-images.githubusercontent.com/100792508/226146025-8403f103-4cdd-4899-bb5d-c5b568fb88cd.png)


# Problem 3 Statement: “Counting Primes”
Write a parallel C program to count the prime numbers within an input range using the
following two methods, then compare the execution times of both programs:


- MPI_Bcast and MPI_Reduce ONLY
- MPI_Send and MPI_RecvONLY
-       Given
       - Lower bound number x
       - Upper bound number y
-       Output
       - Count of prime numbers occurring between x and y.
Parallelization Scenario
## MasterProcess:
- Calculate the subrange size r = (y ‐ x) / p (if including master) or (y ‐ x) / (p - 1)
processes (without master).
- Broadcast x and r to each slave process using MPI_Bcast (or loop of MPI_Send).
- Receive sub-count from each slave process using MPI_Reduce (or loop of MPI_Recv).
- Print total count of primes between x and y.
## Slave Process:
- Receive x and r through the MPI_Bcast call (or MPI_Recv).
- Calculate the lower bound a, and upper bound b according to its rank.
- Count primes in its subrange (between a and b).
- Send this partial count to the master process using the MPI_Reduce call (or
MPI_Send).


## Example:
-n = 4, x = 1, y = 16 → r = (16 - 1) / (4 - 1) = 5
-p1: calculate partial count of prime numbers from 1 to 5 → Count = 3 (2, 3, 5)
-p2: calculate partial count of prime numbers from 6 to 10 → Count = 1 (7)
-p3: calculate partial count of prime numbers from 11 to 15 → Count = 2 (11, 13)
-After reduction, P0 will have Count = 6 (2, 3, 5, 7, 11, 13)

## Note: The length of the rangemay not be divisible by the number of processes. So, you should
handle this case.


# Problem 4 Statement : Encrypt a Message (Caesar Cipher)
    [Using BCast, Scatter and Gather ONLY]
You are required to take a message from a file and encrypt the message using
caesar cipher and store the output in a new file. The encryption can be
represented using modular arithmetic by first transforming the letters into
numbers, according to the scheme, A = 0, B = 1,…, Z = 25. Encryption of a letter x by
a shift n can be described mathematically as:
En(x) = (x + n) mod 26


Any other character outside the range from A to Z (or a to z) is transferred to the
output file as it is.
Input: filename and key/shift value.
Output: new file that contains the encrypted message.


## Master Scenario:
- Read the entire message in a char array from the given file.
- Read the key (shift) value from the user.
- Broadcast the key value to all slaves
- Scatter message on all slaves
- Handle remaining part of a message (if exists)
- Gather encrypted message parts from slaves.
- Write the entire encrypted message to a file.
## Slave Scenario:
- Receive the key (shift) value from master.
- Get the part of the message to be encrypted using scatter.
- Do the encryption on the received part.
- Send the encrypted part to the master using gather.
## Sample input/output:
- KEY/SHIFT: 23
- Plaintext.txt: THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG
- Ciphertext.txt: QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD



## Screenshots
![0d3b382a-9b91-45c8-bae1-8dea09044d98](https://user-images.githubusercontent.com/100792508/229607590-e9391741-9e35-4428-92e5-c48b2f1b0dfe.jpg)

![b4a8c5a2-d284-47f9-a6dd-9f3428250271](https://user-images.githubusercontent.com/100792508/229607717-346a8858-65ca-4871-9c80-9a1a447aa16b.jpg)




## Authors

- [@Mahmoudadel17](https://www.github.com/Mahmoudadel17)
