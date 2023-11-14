#include "shell.h"
/**
 * list_len - function to determine length of linked list
 * @h: the pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * list_to_strings - function that returns an array of strings of the list->str
 * @head: the pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t num_strings = list_len(head);

	if (!head || num_strings == 0)
	{
		return NULL;
	}

	char **strs = malloc(sizeof(char *) * (num_strings + 1));
	if (!strs)
	{
		return NULL;
	}

	size_t i;
	for (i = 0; node; node = node->next, i++)
	{
		strs[i] = _strcpy(malloc(_strlen(node->str) + 1), node->str);

		if (!strs[i])
		{
			// Clean up on failure
			while (i > 0)
			{
			free(strs[--i]);
		}
			free(strs);
			return NULL;
		}
	}

	//Free the last allocated memory in case of failure
	if (!strs[i])
	{
		free(strs);
		return NULL;
	}

	strs[i] = NULL;
	return strs;
}
/**
 * print_list - function that prints all elements of a list_t linked list
 * @h: the pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_puts(": ");
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return i;
}
/**
 * get_node_index - function to get the index of a node
 * @head: the pointer to list head
 * @node: the pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
/**
 * node_starts_with - function to return node whose string starts with prefix
 * @node: the pointer to list head
 * @prefix: the string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, const char *prefix, char c)
{
	while (node)
	{
		if (node->str && prefix)
		{
			char *p = starts_with(node->str, prefix);
			if (p && (c == -1 || *p == c))
			{
				return node;
			}
		}
		node = node->next;
	}

	return NULL;
}
