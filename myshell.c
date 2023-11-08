#include "alx.h"

/**
 * main - function with an  infinite loop
 * @ac: Not use in this function
 * @av: Not use in this function
 * Return: This function runs infinite loop.
 **/
int main(int ac, char **av)
{
	(void)av;
	(void)ac;

	signal(SIGINT, controlC);
	prompt();
	return (0);
}
