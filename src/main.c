#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "main.h"

int main()
{
  init_heap();

  void *ptr1 = my_malloc(100);
  void *ptr2 = my_malloc(200);

  printf("Allocated ptr1: %p\n", ptr1);
  printf("Allocated ptr2: %p\n", ptr2);

  my_free(ptr1);
  printf("Freed ptr1\n");

  void *ptr3 = my_malloc(50);
  printf("Allocated ptr3: %p\n", ptr3);

  return 0;
}

// Initialize the heap
void init_heap()
{
  free_list->size = HEAP_SIZE - sizeof(Block);
  free_list->is_free = true;
  free_list->next = NULL;
}

/**
 * @brief my_malloc: allocate specific size of the heap.
 *
 * @param size: which specifies how much memory to allocate, measured in bytes.
 * @return void*: pointer to the start of allocated memory.
 */

void *my_malloc(size_t size)
{
  Block *current = free_list;

  while (current != NULL)
  {
    if (current->is_free && current->size >= size) {
      // Split the block if there's excess space
      if (current->size >= size + sizeof(Block))
      {
        Block *new_block = (Block *)((char *)current + sizeof(Block) + size);
        new_block->size = current->size - size - sizeof(Block);
        new_block->is_free = true;
        new_block->next = current->next;

        current->next = new_block;
        current->size = size;
      }

      current->is_free = false;
      return (char *)current + sizeof(Block);
    }
    current = current->next;
  }

  // No suitable block found
  return NULL;
}

// Free allocated memory
void my_free(void *ptr)
{
  if (ptr == NULL)
    return;

  Block *block = (Block *)((char *)ptr - sizeof(Block));
  block->is_free = true;

  // Coalesce adjacent free blocks
  Block *current = free_list;
  while (current != NULL)
  {
    if (current->is_free && current->next && current->next->is_free)
    {
      current->size += current->next->size + sizeof(Block);
      current->next = current->next->next;
    }
    current = current->next;
  }
}