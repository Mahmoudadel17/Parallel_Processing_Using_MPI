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


## Screenshots
![0d3b382a-9b91-45c8-bae1-8dea09044d98](https://user-images.githubusercontent.com/100792508/229607590-e9391741-9e35-4428-92e5-c48b2f1b0dfe.jpg)

![b4a8c5a2-d284-47f9-a6dd-9f3428250271](https://user-images.githubusercontent.com/100792508/229607717-346a8858-65ca-4871-9c80-9a1a447aa16b.jpg)


# Problem 4 Statement : Encrypt a Message (Caesar Cipher)
   [Using BCast, Scatter and Gather ONLY]
- You are required to take a message from a file and encrypt the message using
caesar cipher and store the output in a new file. The encryption can be
represented using modular arithmetic by first transforming the letters into
numbers, according to the scheme, A = 0, B = 1,…, Z = 25. Encryption of a letter x by
a shift n can be described mathematically as:
                        En(x) = (x + n) mod 26


- Any other character outside the range from A to Z (or a to z) is transferred to the
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
![2023-04-24 13_54_59-SL5 5  Running  - Oracle VM VirtualBox](https://user-images.githubusercontent.com/100792508/233989987-908a7984-5e15-4bc4-ab58-f2ea604d0252.png)


# Problem 5  Statement : Value of PI
  [Using Bcast and Reduce ONLY]
- The following piece of code is a serial program to calculate the value of PI using
integration, give it a try and run it to see the output.

![2023-04-24 13_42_54-HPC_Parallel Processing-A3 -2023- pdf - Adobe Acrobat Reader (64-bit)](https://user-images.githubusercontent.com/100792508/233989976-01cfa23e-b59b-4735-898b-b953c4de588b.png)

You are required to parallelize the program by distributing the number of steps
on multiple processes and broadcast the step value to all slaves:
- Each slave process will receive the step and the range it will work on, then
calculate its partial sum.
- Master process will divide the number of steps into ranges and broadcast
the value of step, then perform reduce to output the value of PI using the
reduced sum.



## Screenshots

![2023-04-24 13_55_59-SL5 5  Running  - Oracle VM VirtualBox](https://user-images.githubusercontent.com/100792508/233989999-e417b251-f0e0-46bc-8368-4453582e8faf.png)



# Problem 6 & 7 : Mean, Variance, and Standard Deviation

Suppose that the entire population of interest is eight students in a particular
class. For a finite set of numbers, the population standard deviation is found by
taking the square root of the average of the squared deviations of the values
subtracted from their average value. The marks of a class of eight students (that
is, a statistical population) are the following eight values: 2, 4, 4, 4, 5, ,5, 7, 9
These eight data points have the mean (average) of 5:
First, calculate the deviations of each data point from the mean, and square the
result of each:
The variance is the mean of these values:
and the population standard deviation is equal to the square root of the
variance:
Write a parallel program to calculate the above mean, variance, and standard
deviation using the below algorithm:
- Each process calculates its local sum on its portion of data. If the division
result has a remainder, then send this remainder to the last process (the
process that has the rank "n-1" or let the master process work on it).

- The master process calculates the mean (dividing the total sum by the size
of the elements) and sends it to all processes.

- Each process calculates the squared difference on its portion of data.

- The master process then calculates the variance (dividing the total
squared difference by the size of the elements).

- The master process calculates the standard deviation by getting the
square root of the variance and prints the results..


Input: array size, array elements
Output: mean, variance, standard deviation


## Sample input/output:

## Sample1:
- Array size: 8
- Array elements: 2, 4, 4, 4, 5, ,5, 7, 9
- Output: Mean = 5.0, Variance = 4.0, Standard deviation = 2.0
## Sample2:
- Array size: 7
- Array elements: 4, 5, 6, 6, 7, 9, 12
- Output: Mean = 7.0, Variance = 6.2857, Standard deviation = 2.5071


## Authors

- [@Mahmoudadel17](https://www.github.com/Mahmoudadel17)
