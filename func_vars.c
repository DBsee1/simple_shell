#include "shell.h"
/**
 * check_chain - function checks we should continue chaining based on last status
 * @info: the parameter struct
 * @i: starting position in buf
 * @buf: the char buffer
 * @p: address of current position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status) ||
		(info->cmd_buf_type == CMD_OR && !info->status))
	{
		buf[i] = '\0';
		j = len;
	}

	*p = j;
}

/**
 * is_chain - current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	if (!info || !buf || *p >= strlen(buf))
	{
		// Print an error message
		_eputchar("Error: Invalid input or index out of bounds\n");
		return 0;
	}

	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = '\0';
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		// Print an error message
		_eputchar("Error: Unrecognized chain operator\n");
		return 0;
	}

	*p = j;
	return 1;
}
/**
 * replace_string - function name that replaces string
 * @old: the address of old string
 * @new: the new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 * replace_vars - function to replace vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	for (int i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
		}
		else
		{
			list_t *node = node_starts_with(info->env, &info->argv[i][1], '=');
			if (node)
			{
				replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			}
			else
			{
				replace_string(&info->argv[i], _strdup(""));
			}
		}
	}

	return 0;
}
/**
 * replace_alias - function that replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
