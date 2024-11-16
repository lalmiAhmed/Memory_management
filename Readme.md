Project Plan: Custom Memory Management System

Phase 1: Basic Memory Allocator (2-3 weeks)

1. Create a simple memory pool

```c
// Basic structure for memory management
typedef struct {
    void* memory_start;
    size_t total_size;
    size_t used_size;
} MemoryPool;

// Basic block header
typedef struct BlockHeader {
    size_t size;
    uint8_t is_free;
    struct BlockHeader* next;
} BlockHeader;

```

1. Implement basic functions:

```c
void* my_malloc(size_t size);
void my_free(void* ptr);
void init_memory_pool(size_t size);

```

1. Key concepts to implement:
- First-fit/Best-fit allocation strategies
- Block splitting and merging
- Memory alignment handling
- Basic memory statistics tracking