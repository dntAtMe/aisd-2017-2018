#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define QUEUE_OK 		0
#define QUEUE_FULL_ERR 		1
#define QUEUE_ALLOC_ERR		2

typedef struct queue_t
{
    int front, rear;
    size_t current_size;
    size_t max_size;
    int *array;
} queue_t;

uint8_t		create_queue( queue_t **q, size_t max_size );
uint8_t		is_full( queue_t *queue );
uint8_t		is_empty( queue_t *queue );
uint8_t		enqueue( queue_t *queue, int data );
int		dequeue( queue_t *queue );
int		front_lookup( queue_t *queue );
int		rear_lookup( queue_t *queue );

