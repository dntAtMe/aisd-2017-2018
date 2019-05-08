#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define LIST_OK 	0
#define LIST_ALLOC_ERR 	1
#define LIST_EMPTY_ERR 2
#define LIST_OOB_ERR 3

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
} node;

uint8_t append (node **head, int data);
uint8_t push (node **head, int data);
uint8_t delete(node **head, int data);
void  print_list (node *head);
int length(node *head);
int get(node *head, int data);



