#include "alx.h"
/**
 * run_command - Custom function to output a string similar to puts in C
 * @cmd: Set the value pointed to by the integer pointer to 402
 *
 * Return: int
 */
void run_command(char **cmd)
{

	char *parameter = (*(cmd + 1));
	char *s, *slash = "/";
	char *o;

	char *print_cmd = *cmd;
	char *argv[4];

	if ((access(cmd[0], F_OK) == 0))
	{
		argv[0] = cmd[0];
		argv[1] = parameter;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		o = find_command(print_cmd);

		slash = str_concat(o, slash);

		s = str_concat(slash, *cmd);

		argv[0] = s;
		argv[1] = parameter;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
}

