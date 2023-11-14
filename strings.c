#include "shell.h"
/**
 * _strlen - function to show length of a string
 * @s: string whose length to checked
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * _strcmp - function that compares two strangs.
 * @s1: the first string
 * @s2: the second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	// Check for equality after the loop
	if (*s1 == *s2)
	{
		return 0;
	}
	else
	{
		return (*s1 < *s2) ? -1 : 1;
	}
}
/**
 * _strcat - function that concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, const char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return (ret);
}
/**
 * starts_with - function to check a particular string in haystack
 * @haystack: the string to search in haystack
 * @needle: the substring to locate
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
		{
			return NULL;  // Return NULL if characters don't match
		}
		needle++;
		haystack++;
	}
	return (char *)haystack;
}
