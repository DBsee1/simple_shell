#include "shell.h"
/**
 * clear_info - function to start info_t struct
 * @info: the struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - function name to start info_t struct
 * @info: the struct address
 * @av: the argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		if (info->argv)
		{
		for (i = 0; info->argv[i]; i++)
		{
			// Additional debugging for checking each argv entry
			_putchar("Argv[%d]: %s\n", i, info->argv[i]);
		}
		}

		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - function to free info_t struct fields
 * @info: the struct address
 * @all: if freeing all places returns as true
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
