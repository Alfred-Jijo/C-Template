#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <memalloc.h>

typedef char ALIGN[16];

union MemoryBlock {
	struct {
		size_t size;
		unsigned int isFree;
		union MemoryBlock *next;
	} data;
	ALIGN alignment;
};

typedef union MemoryBlock MemoryBlock_t;

MemoryBlock_t *headBlock, *tailBlock;
pthread_mutex_t memoryAllocationLock;

MemoryBlock_t *findFreeBlock(size_t size);

void *allocateMemory(size_t size) {

	size_t totalSize;
	void *memory;
	MemoryBlock_t *memoryBlock;
	
	if (!size) { return NULL; }
	
	pthread_mutex_lock(&memoryAllocationLock);
	memoryBlock = findFreeBlock(size);
	
	if (memoryBlock) {
		memoryBlock->data.isFree = 0;
		pthread_mutex_unlock(&memoryAllocationLock);
		return (void*)(memoryBlock + 1);
	}
	
	totalSize = sizeof(MemoryBlock_t) + size;
	memory = sbrk(totalSize);
	
	if (memory == (void*) -1) {
		pthread_mutex_unlock(&memoryAllocationLock);
		return NULL;
	}
	
	memoryBlock = memory;
	memoryBlock->data.size = size;
	memoryBlock->data.isFree = 0;
	memoryBlock->data.next = NULL;
	
	if (!headBlock) { headBlock = memoryBlock; }
	if (tailBlock) { tailBlock->data.next = memoryBlock; }
	
	tailBlock = memoryBlock;
	pthread_mutex_unlock(&memoryAllocationLock);
	
	return (void*)(memoryBlock + 1);
}

MemoryBlock_t *findFreeBlock(size_t size) {
	
	MemoryBlock_t *currentBlock = headBlock;
	
	while(currentBlock) {
		
		if (currentBlock->data.isFree && currentBlock->data.size >= size) {
			return currentBlock;
		}
		currentBlock = currentBlock->data.next;
	}
	return NULL;
}

void freeMemory(void *memory) {
	
	MemoryBlock_t *memoryBlock, *tempBlock;
	void *programBreak;
	
	if (!memory) { return; }
	
	pthread_mutex_lock(&memoryAllocationLock);
	memoryBlock = (MemoryBlock_t*)memory - 1;
	programBreak = sbrk(0);
	
	if ((char*)memory + memoryBlock->data.size == programBreak) {
		
		if (headBlock == tailBlock) {
			headBlock = tailBlock = NULL;
		} else {
			tempBlock = headBlock;
			
			while (tempBlock) {
				
				if(tempBlock->data.next == tailBlock) {
					tempBlock->data.next = NULL;
					tailBlock = tempBlock;
				}
				tempBlock = tempBlock->data.next;
			}
		}
		
		sbrk(0 - sizeof(MemoryBlock_t) - memoryBlock->data.size);
		pthread_mutex_unlock(&memoryAllocationLock);
		return;
	}
	
	memoryBlock->data.isFree = 1;
	pthread_mutex_unlock(&memoryAllocationLock);
}

void *allocateClearedMemory(size_t num, size_t size) {
	
	size_t totalSize;
	void *memory;
	
	if (!num || !size) { return NULL; }
	
	totalSize = num * size;
	/* Check for multiplication overflow */
	
	if (size != totalSize / num) { return NULL; }
	
	memory = allocateMemory(totalSize);
	
	if (!memory) { return NULL; }
	
	memset(memory, 0, totalSize);
	return memory;
}

void *reallocateMemory(void *memory, size_t size) {
	
	MemoryBlock_t *memoryBlock;
	void *newMemory;
	
	if (!memory || !size) { return allocateMemory(size); }
	
	memoryBlock = (MemoryBlock_t*)memory - 1;
	
	if (memoryBlock->data.size >= size) { return memory; }
	
	newMemory = allocateMemory(size);
	
	if (newMemory) {
		memcpy(newMemory, memory, memoryBlock->data.size);
		freeMemory(memory);
	}
	
	return newMemory;
}
