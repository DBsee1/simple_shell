#include "shell.h"
/**
 **_memset - function that fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: a pointer to the memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
/**
 * ffree - function that frees a string of strings
 * @pp: the string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - function that reallocates a block of memory
 * @ptr: the pointer to previous mallocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (!ptr)
		return malloc(new_size);

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}

	if (new_size == old_size)
		return ptr;

	char *new_ptr = malloc(new_size);

	if (!new_ptr)
		return NULL;

	// Copy the data from the old pointer to the new pointer
	if (old_size < new_size)
		new_size = old_size;

	for (unsigned int i = 0; i < new_size; i++)
	{
		new_ptr[i] = ((char *)ptr)[i];
	}

	free(ptr);
	return new_ptr;
}
