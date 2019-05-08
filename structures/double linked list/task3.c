#include "task3.h"

uint8_t
append (node **head, int data)
{
	if (!*head)
	{
		node *new_node = (node*) malloc(sizeof(node));
		if (!new_node)
			return LIST_ALLOC_ERR;
		new_node->data = data;
		new_node->prev = new_node->next = new_node;
		*head = new_node;
		return LIST_OK;
	}

	//node *last = (*head)->prev;
	node *new_node = (node*) malloc(sizeof(node));
	
	new_node->data = data;
	new_node->prev = (*head)->prev;
	new_node->next = *head;
	(*head)->prev->next = new_node;
	(*head)->prev = new_node;

	return LIST_OK;
}

uint8_t
push (node **head, int data)
{
	if (!*head)
	{
		if (append(head, data) == LIST_OK)
			return LIST_OK;
	}

	node *new_node = (node*) malloc(sizeof(node));
	if(!new_node)
		return LIST_ALLOC_ERR;

	new_node->data = data;
	new_node->next = *head;
	new_node->prev = (*head)->prev;
	(*head)->prev->next = new_node;
	(*head)->prev = new_node;
	*head = new_node;

	return LIST_OK;
}

uint8_t delete(node **head, int data)
{
	if (!head)
		return LIST_EMPTY_ERR;

	node *current = *head;
	node *prev = NULL;

	while (current->data != data)
	{
		if (current->next == *head)
			return LIST_OOB_ERR;	
		prev = current;
		current = current->next;		
	}

	if (current == *head)
	{
		prev = (*head)->prev;
		*head = (*head)->next;

		prev->next = *head;
		(*head)->prev = prev;
		free (current);
	} 
	else if (current->next == *head)
	{
		prev->next = *head;
		(*head)->prev = prev;
		free (current);
	}
	else
	{
		node *next = current->next;
		prev->next = next;
		next->prev = prev;
		free (current);
	}	
	return LIST_OK;	
}

int
length (node *head)
{
	if (!head)
		return 0;

	node* tmp = head;
	
	int length = 0;
	do
	{
		length++;
		tmp = tmp->next;
	} while (tmp != head);

	return length;
}

void 
print_list (node *head)
{
	if (!head)
		return;
	node *tmp = head;

	do 
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	} while(tmp != head);

	printf("\n");
	return;
}

int get_3(node *head, int index, int length)
{
	if (!head)
		return INT_MIN;
	if (index < length / 2)
	{
		while (index-- > 0)
		{
			head = head->next;
		}

		return head->data;
	}
	else
	{
		 index = length - index;

		 while(index-- > 0)
		 {
			 head = head->prev;
		 }
		 return head->data;
	}
	
}

int get(node *head, int index) 
{
	if (!head)
		return INT_MIN;

	node *tmp = head;
	while (tmp->next != head && index-- > 0)
	{
		tmp = tmp->next;
	}

	return tmp->data;
}

void merge(node **head1, node **head2)
{
	node *tail1 = (*head1)->prev;
	node *tail2 = (*head2)->prev;

	/*(*head1)->prev->next = *head2;
	(*head2)->prev->next = *head1;
	(*head2)->prev = tail1;
	(*head1)->prev = tail2;*/
	tail1->next = *head2;
	(*head2)->prev = tail1;

	tail2->next = *head1;
	(*head1)->prev = tail2;

}


int
main()
{
	node *head = NULL; 

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
        get_3(head, num, 1000);

    avg = ((clock() - start_time) / no_tries);
    printf("avg access time: %g\n", avg);
    
    start_time = clock();

    for (int i = 0; i < no_tries; i++)
        get_3(head, random()%1000, 1000);

    avg = ((clock() - start_time) / no_tries);
    printf("avg random access time: %g\n", avg);

    
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

	node *head1 = NULL;
	node *head2 = NULL;
	append(&head1, 1);
	append(&head1, 3);
	append(&head2, 4);
	append(&head2, 2);
	print_list(head1);
	print_list(head2);
	merge(&head1, &head2);
	print_list(head1);
	print_list(head2);
	
}
