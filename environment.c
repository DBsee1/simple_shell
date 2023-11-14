#include "shell.h"
/**
 * get_environ - function that returns the string array copy of our environ
 * @info: the structure containing potential arguments
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return info->environ;
}
/**
 * _unsetenv - funtion name to remove an environment variable
 * @info: the structure containing potential arguments
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	if (!info->env || !var)
		return 0;

	list_t *node = info->env;
	size_t i = 0;

	while (node)
	{
	char *p = starts_with(node->str, var);
	
	if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			node = info->env;
			i = 0;
			continue;
		}
		node = node->next;
		i++;
	}

	return info->env_changed;
}
/**
 * _setenv - function that initialize a new environment variable,
 * or modify an existing one
 * @info: the structure containing potential arguments
 * @value: the string env var value
 * @var: the string env var property
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	if (!var || !value)
		return 0;

	char *buf = malloc(strlen(var) + strlen(value) + 2);
	
	if (!buf)
		return 1;

	_putchar(buf, "%s=%s", var, value);

	list_t *node = info->env;
    
	while (node)
	{
		char *p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
