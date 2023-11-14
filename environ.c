#include "shell.h"
/**
 * _myenv - function that prints the current environment
 * @info: structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - function name to get the value of an environ variable
 * @info: the structure that contains potential arguments
 * @name: the environ variable
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		{
			return (p);
        }
		node = node->next;
	}

	return NULL;
}
/**
 * _mysetenv - function to initialize a new environment variable,
 * or modify an existing one
 * @info: the structure that holds potential arguments.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
		_eputs("Wrong number of arguments\n");
		return (1);
    }

	if (!_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
    }

    return (1);
}
/**
 * _myunsetenv - funtion to remove an environment variable
 * @info: the structure that holds potential arguments
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	if (info->argc <= 1)
	{
		_eputs("Not enough arguments.\n");
		return 1;
    }

	for (int i = 1; i < info->argc; i++)
	{
		_unsetenv(info, info->argv[i]);
	}

    return 0;
}
/**
 * populate_env_list - function that populates env linked list
 * @info: the structure that holds potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node_end(&node, environ[i], 0);
    }

	info->env = node;
	return 0;
}
