#include "task2.h"
	
uint8_t 
push(node_t **head, int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if(!node)
    {
        return LIST_ALLOC_ERR;
    }
    node->data = data;
    node->next = *head;
    *head = node;
    printf("%d pushed\n", data);

    return LIST_OK;
}

uint8_t
append(node_t **head, int data)
{
    node_t *node  = (node_t*) malloc(sizeof(node_t));
    if(!node)
    {
	return LIST_ALLOC_ERR;
    }
    node->data = data;
    node->next = NULL;

    if(!*head)
    {
        *head = node;
        printf("%d appended to head\n", (*head)->data);
        return LIST_OK; 
    }

    node_t *last = *head;
    
    while(last->next)
        last = last->next;
    
    last->next = node;

    printf("%d appended\n", last->next->data);
    return LIST_OK;
}
uint8_t
delete_data(node_t **head, int data)
{
    if  (!*head)
    {
        perror("List is empty");
        return LIST_EMPTY_ERR;
    }

    node_t *tmp = *head;

    if (tmp->data == data)
    {
        *head = (*head)->next;
        free(tmp);
        return LIST_OK;
    }

    node_t *prev;

    while (tmp && tmp->data != data)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (!tmp)
    {
        perror("No such value found");
        return LIST_VALUE_ERR;
    }

    prev->next = tmp->next;
    free(tmp);
    return LIST_OK;
}
uint8_t 
delete_position(node_t **head, unsigned position)
{
    if (!*head)
    {
        perror("List is empty");
        return LIST_EMPTY_ERR;
    }

    node_t *tmp = *head;

    if (!position)
    {
        *head = (*head)->next;
        free(tmp);
        return LIST_OK;
    }

    for (unsigned i = 0; i < position - 1; i++)
        tmp = tmp->next;
    
    if (!tmp || !(tmp->next))
    {
        perror("Out of bounds");
        return LIST_OOB_ERR;
    }

    node_t *to_delete = tmp->next;
    tmp->next = to_delete->next;
    free(to_delete);
    return LIST_OK;
}

uint8_t 
merge_sort(node_t ** head)
{
    node_t *first, *second;

    if (!(*head) || !(*head)->next)
    {
        return LIST_EMPTY_ERR;
    }

    split_list(*head, &first, &second);
    merge_sort(&first);
    merge_sort(&second);

    *head = merge_sorted(first, second);
    return LIST_OK;
}

node_t* 
merge_sorted(node_t *first, node_t *second)
{
    node_t *node;

    if (!first)
        return second;
    if (!second)
        return first;
    
    if (first->data <= second->data)
    {
        node = first;
        node->next = merge_sorted(first->next, second);
    }
    else
    {
        node = second;
        node->next = merge_sorted(first, second->next);
    }
    return node;
}

int get(node_t* head, int index)
{
    while(head && index > 0)
    {
        index--;
        head = head->next;
    }

    if (!head)
    {
        printf("get: OOB");
        return INT_MIN;
    }

    return head->data;
}

void 
split_list(node_t *head, node_t **first, node_t **second)
{
    node_t *mid;
    node_t *end;

    mid = head;
    end = head->next;

    while (end)
    {
        end = end->next;
        if (end)
        {
            end = end->next;
            mid = mid->next;
        }
    }

    *first = head;
    *second = mid->next;
    mid->next = NULL;
}

void 
print_out(const node_t *node)
{
    while(node)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}



int 
main(void)
{
    
    node_t *head = NULL; 
    /*
    append(&head, 2);
    push(&head, 3);
    push(&head->next, 4);
    print_out(head);
    //delete_position(&head, 0);
    //print_out(head);
    //delete_data(&head, 2);
    merge_sort(&head);
    print_out(head);
    printf("get: %d\n", get(head, 2));
    */

    srand(time(0));
    double start_time;
    double avg;
    int num;
    
    int no_tries = 100000;

    for (int i = 0; i < 1000; i++)
        append(&head, rand());

    printf("index access check:\n");
    scanf("%d", &num);
    
    start_time = clock();

    for (int i = 0; i < no_tries; i++)
        get(head, num);

    avg = ((clock() - start_time) / no_tries);
    printf("avg access time: %g\n", avg);
    
    start_time = clock();

    for (int i = 0; i < no_tries; i++)
        get(head, random()%1000);

    avg = ((clock() - start_time) / no_tries);
    printf("avg random access time: %g\n", avg);

    return 0;
}
