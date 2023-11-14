#include "shell.h"
/**
 * print_d - function prints a decimal and base 10
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*output_char)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;

	if (input < 0)
	{
		output_char('-');
		count++;
		input = -input;
	}

	int divisor = 1000000000;
	
	while (divisor > 0)
	{
		int digit = input / divisor;
		
		if (digit > 0 || divisor == 1)
	{
		output_char('0' + digit);
			count++;
	}
		input %= divisor;
		divisor /= 10;
	}

	return count;
}

/**
 * convert_number - the converter function name
 * @num: the number
 * @base: the base
 * @flags: the argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		if (ptr == buffer)
		{
			// Handle potential buffer overflow
			_eputchar(stderr, "Buffer overflow in convert_number\n");
			return NULL;
		}

		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return ptr;
}


/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: the address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	if (buf == NULL)
	{
		// Handle NULL input
        _eputchar("Error: NULL input in remove_comments\n");
		return;
	}

	int i;
	
	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			// Found '#' at the beginning or after a space, remove the comment
			buf[i] = '\0';
			return;  // Stop processing after the comment
		}
	}
    // If no comment is found, the loop will reach here
}

int main()
{
	char buffer[100] = "This is a # comment";
	_putchar("Before: %s\n", buffer);
	
	remove_comments(buffer);
    
	_putchar("After: %s\n", buffer);

	return 0;
}
