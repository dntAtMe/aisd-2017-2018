#include "task1.h"

uint8_t 
create_queue(queue_t **q, size_t max_size)
{
    queue_t *queue = (queue_t*) malloc(sizeof(queue_t));
    
    if (queue == NULL)
        return QUEUE_ALLOC_ERR;

    queue->max_size = max_size;
    queue->front = 0;
    queue->current_size = 0;
    queue->rear = max_size - 1;
    queue->array = (int*) malloc(max_size * (sizeof(int)));
    
    if (queue->array == NULL)
	return QUEUE_ALLOC_ERR;

    *q = queue;

    return QUEUE_OK;
}

uint8_t 
is_full(queue_t* queue)
{
    return (queue->current_size == queue->max_size);
}

uint8_t 
is_empty(queue_t* queue)
{
    return (queue->current_size == 0);
}
uint8_t 
enqueue(queue_t* queue, int data)
{
    if(is_full(queue))
    	return QUEUE_FULL_ERR;

    queue->rear = (queue->rear + 1) % queue->max_size;
    queue->array[queue->rear] = data;
    queue->current_size++;
    printf("%d enqueued to %d\n", data, queue->rear);
    return QUEUE_OK;
}

int 
dequeue(queue_t* queue)
{
    if (is_empty(queue))
    {
        printf("Sorry, queue is empty\n");
        return INT_MIN;
    }
    int data;
    data = queue->array[queue->front];
    printf("%d dequeued from %d\n", data, queue->front);
    queue->front = (queue->front + 1) % queue->max_size;
    queue->current_size--;
    return data;
}

int 
front_lookup(queue_t* queue)
{
    if (is_empty(queue))
    {
        printf("Lookup: Queue is empty\n");
        return INT_MIN;
    }
    return queue->array[queue->front];
}

int 
rear_lookup(queue_t* queue)
{
    if (is_empty(queue))
    {
        printf("Lookup: Queue is empty\n");
        return INT_MIN;
    }
    return queue->array[queue->rear];
}

int 
main(void)
{
    queue_t *queue;
    create_queue(&queue, 2);
    dequeue(queue);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    return 0;
}
