#include<stdlib.h>
#include<stdint.h>

#define HEAP_SIZE 1024*50 /*50 Kbyte*/ 

// Basic structure for memory management
typedef struct {
    void* memory_start;
    size_t total_size;
    size_t used_size;
} MemoryPool;

// Basic block header
typedef struct Block {
    size_t size;
    uint8_t is_free;
    struct Block* next;
} Block;

void init_heap();
void* my_malloc(size_t size);
void my_free(void *ptr);

static char heap[HEAP_SIZE]; // Static memory pool
static Block* free_list = (Block*)heap; // Pointer to the first free block
