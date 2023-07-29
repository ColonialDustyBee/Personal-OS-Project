#include "mem.h"
 
#define POOL_SIZE 4096 // Total size of the memory pool, which is 4mb

static uint8_t memoryPool[POOL_SIZE]; // Allocates memory pool which are the chunks of heap that the application can use


// Signifies a single memory block that can be utilized when kmalloc is used
struct memory_block{
    size_t size;
    struct mem_block* next;
};

static struct memory_block* freeList = NULL; // Used to keep track of the free blocks available


void init_memory_manager() { // Initializes memory manager. This is to be initialized when the kernel begins. It's very barebones
   freeList = (struct memory_block*)memoryPool;
   freeList->size = POOL_SIZE - sizeof(struct memory_block); // initializes total number of bytes available
   freeList->next = NULL;
}
// Very very simple version of kmalloc, no kfree cause prior implementations resulted in memory leakage and inherent fatal flaws
void* kmalloc(size_t size) { // Will allocate block of memory from heap based on the size of type in bytes
    struct memory_block* previous = NULL;
    struct memory_block* current = freeList;
    while(current){
        if(current->size >= size){ // If the size of our block is bigger than the size that is requested
            struct memory_block* new_block = (struct memory_block*)((char*)current + sizeof(struct memory_block) + size); // Allocates block
            new_block->size = current->size - sizeof(struct memory_block) - size; // Subtracts from freelist's memory pool and allocates it to the new block
            new_block->next = current->next;

            current->size = size;
            current->next = new_block;
        }
        if(previous){
            previous->next = current->next; // Links the node of the linked list together
        }
        else{
            freeList = current->next; // If head is null
        }
        return (void*)((char*)current + sizeof(struct memory_block)); // returns bytes
    }
    return NULL; // If block can't be allocated (perhaps the memory in heap has been exhausted)
}


void memory_copy(uint8_t* source, uint8_t *destination, int numberOfBytes){ // Basically acts like memcpy but is more simplified
    int index;
    for(index = 0; index < numberOfBytes; index++){
        *(destination + index) = *(source + index);
    }
}

void memory_set(uint8_t *destination, uint8_t value, uint32_t length){
    uint8_t *temp = (uint8_t*)destination;
    for(; length != 0; length--){
        *temp++ = value;
    }
}