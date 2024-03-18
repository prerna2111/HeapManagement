This program demonstrates heap management using the First Fit strategy in C. It allocates and deallocates memory blocks dynamically, maintaining a free list of memory blocks available for allocation.
Allocate Memory: Allocate memory of a specified size using the First Fit strategy.
Free Memory: Deallocate previously allocated memory blocks.
Print Free List: Display the current state of the free list, showing available memory blocks.
Exit Program: Terminate the program.

The program initializes a heap block with a predefined size and maintains a free list to track available memory blocks.
Memory allocation is performed using the First Fit strategy, where the first available memory block that satisfies the requested size is allocated.
Memory deallocation updates the free list and coalesces adjacent free blocks if possible.
