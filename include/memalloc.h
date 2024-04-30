#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stddef.h>

// Function declarations
void *allocateMemory(size_t size);
void freeMemory(void *memory);
void *allocateClearedMemory(size_t num, size_t size);
void *reallocateMemory(void *memory, size_t size);

#endif /* MEMALLOC_H */
