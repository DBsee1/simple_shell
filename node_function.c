#include "shell.h"
/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
	{
		// Print an error message
		_eputchar("Error: Invalid head pointer\n");
		return NULL;
	}

	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		// Print an error message
		_eputchar("Error: Memory allocation failed\n");
		return NULL;
	}

	_memset(new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			// Print an error message
			_eputchar("Error: String duplication failed\n");
			free(new_node);
			return NULL;
		}
	}

	new_node->next = *head;
	*head = new_node;
	return new_node;
}
/**
 * add_node_end - function name to add a node to the end of the list
 * @head: address of pointer to head node
 * @str: the str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
	{
		_eputchar("Error: Invalid head pointer\n");
		return NULL;
	}

	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		_eputchar("Error: Memory allocation failed\n");
		return NULL;
	}

	_memset(new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			_eputchar("Error: String duplication failed\n");
			free(new_node);
			return NULL;
		}
	}

	list_t **last_next = head;
	while (*last_next)
	{
		last_next = &((*last_next)->next);
	}
	
	*last_next = new_node;
	
	return new_node;
}
/**
 * print_list_str - function that prints only the str element of a list_t linked list
 * @h: the pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * free_list - function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * delete_node_at_index - function that deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
	{
		//Print an error message
		_eputchar("Error: Invalid head pointer or empty list\n");
		return 0;
	}

	list_t *node = *head;
	list_t *prev_node = NULL;

	if (index == 0)
	{
		*head = node->next;
		free(node->str);
		free(node);
		return 1;
	}

	unsigned int i = 0;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return 1;
		}

		i++;
		prev_node = node;
		node = node->next;
	}

	// Print an error message
	_eputchar("Error: Index out of bounds\n");

	return 0;
}
