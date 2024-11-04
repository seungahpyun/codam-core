/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/24 11:17:17 by spyun          #+#    #+#                */
/*   Updated: 2024/10/24 11:17:18 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	read_and_store(t_list **list, int fd)
{
	int		read_chars;
	char	*buffer;

	while (!find_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (free_list(list), -1);
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars < 0)
			return (free(buffer), free_list(list), -1);
		if (read_chars == 0)
			return (free(buffer), 0);
		buffer[read_chars] = '\0';
		append_buffer_to_list(list, buffer);
	}
	return (1);
}

char	*extract_line(t_list *list)
{
	int		total_len;
	char	*line;

	total_len = 0;
	line = create_line_buffer(list, &total_len);
	if (!line)
		return (NULL);
	copy_line(list, line, total_len);
	return (line);
}

t_list	*store_remaining(t_list *list)
{
	t_list	*remaining;
	int		i;
	int		j;

	while (list)
	{
		i = 0;
		while (list->str_buffer[i] && list->str_buffer[i] != '\n')
			i++;
		if (list->str_buffer[i] == '\n' && list->str_buffer[i + 1])
		{
			remaining = malloc(sizeof(t_list));
			if (!remaining)
				return (NULL);
			remaining->str_buffer = malloc(BUFFER_SIZE - i);
			if (!remaining->str_buffer)
				return (free(remaining), NULL);
			j = 0;
			while (list->str_buffer[++i])
				remaining->str_buffer[j++] = list->str_buffer[i];
			remaining->str_buffer[j] = '\0';
			remaining->next = NULL;
			return (remaining);
		}
		list = list->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;
	t_list			*remaining;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_and_store(&list, fd) == -1)
	{
		free_list(&list);
		return (NULL);
	}
	if (!list)
		return (NULL);
	line = extract_line(list);
	remaining = store_remaining(list);
	free_list(&list);
	list = remaining;
	return (line);
}
