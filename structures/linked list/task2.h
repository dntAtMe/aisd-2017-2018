#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>

#define LIST_OK		0
#define LIST_ALLOC_ERR	1
#define LIST_EMPTY_ERR  2
#define LIST_VALUE_ERR  3
#define LIST_OOB_ERR	4

typedef struct node_t
{
    int data;
    struct node_t *next;
} node_t;

uint8_t push(node_t **head, int data);
uint8_t append(node_t **head, int data);
uint8_t delete_data(node_t **head, int data);
uint8_t delete_position(node_t **head, unsigned position);
uint8_t merge_sort(node_t ** head);
node_t* merge_sorted(node_t *first, node_t *second);
int get(node_t* head, int index);
void split_list(node_t *head, node_t **first, node_t **second);


