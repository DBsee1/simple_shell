#include "shell.h"
/**
 * _erratoi - function that converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}
/**
 * print_error - function that prints an error message
 * @estr: string that holds specified error type
 * @info: the parameter & return info struct
 * Return: 0 if no numbers in string, -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
