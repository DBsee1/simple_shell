#include "shell.h"
/**
 * **strtow - function name that splits a string into words,
 * delimiters repeated are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	if (str == NULL || str[0] == '\0')
		return NULL;

	if (!d)
		d = " ";

	int i, j, k, m, numwords = 0;
	char **s;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || str[i + 1] == '\0'))
		{
			numwords++;
		}
	}

	if (numwords == 0)
		return NULL;

	s = (char **)malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return NULL;

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		s[j] = (char *)malloc((k + 1) * sizeof(char));

		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return NULL;
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL;

	return s;
}
/**
 * **strtow2 - function to splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	if (str == NULL || str[0] == '\0')
		return NULL;

	int i, j, k, m, numwords = 0;
	char **s;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
		{
			numwords++;
		}
	}

	if (numwords == 0)
		return NULL;

	s = (char **)malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return NULL;

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d)
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		s[j] = (char *)malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return NULL;
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL;

	return s;
}
