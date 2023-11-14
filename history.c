#include "shell.h"
/**
 * write_history - function to create a file or append to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	
	if (!filename)
	{
		return -1;
	}

	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
	{
		return -1;
	}

	for (list_t *node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);

	close(fd);
	return 1;
}
/**
 * get_history_file - function to get the history file
 * @info: the parameter struct
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME");
	if (!dir)
	{
		return NULL;
	}

	size_t buf_size = _strlen(dir) + _strlen(HIST_FILE) + 2;
	buf = malloc(sizeof(char) * buf_size);
	if (!buf)
	{
		return NULL;
	}

	buf[0] = '\0';
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	free(dir);  // Free the result of _getenv as it's not needed anymore

	return buf;
}
/**
 * read_history - function to read history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
	{
		return 0;
	}

	int fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
	{
		return 0;
	}

	if (!fstat(fd, &st))
	{
		fsize = st.st_size;
	}

	if (fsize < 2)
	{
		close(fd);
		return 0;
	}

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	{
		close(fd);
		return 0;
	}

	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';

	if (rdlen <= 0)
	{
		free(buf);
		close(fd);
		return 0;
    }

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
	{
		build_history_list(info, buf + last, linecount++);
	}

	free(buf);

	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
	}

	renumber_history(info);

	return info->histcount;
}
/**
 * build_history_list - function name to add entry to a history linked list
 * @info: the structure containing potential arguments
 * @buf: the buffer
 * @linecount: history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = create_node(buf, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	else
	{
		add_node_end(&(info->history), buf, linecount);
		free(node);
	}

	return 0;
}
/**
 * renumber_history - function that renumbers the history
 * linked list after changes.
 * @info: structure that holds potential arguments
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	info->histcount = i;
	return info->histcount;
}
