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


## Authors

- [@Mahmoudadel17](https://www.github.com/Mahmoudadel17)