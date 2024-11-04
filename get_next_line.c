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

static t_list	*get_fd_node(t_list **head, int fd)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buffer = ft_strdup("");
	if (!node->buffer)
	{
		free(node);
		return (NULL);
	}
	node->next = *head;
	*head = node;
	return (node);
}

static void	remove_fd_node(t_list **head, int fd)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->buffer);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	read_into_buffer(t_list *node)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bytes_read = read(node->fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buf);
		return (bytes_read);
	}
	buf[bytes_read] = '\0';
	temp = ft_strjoin(node->buffer, buf);
	free(buf);
	if (!temp)
		return (-1);
	free(node->buffer);
	node->buffer = temp;
	return (1);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*buffer || !**buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	if (!line)
		return (NULL);
	temp = ft_strdup((*buffer) + i + ((*buffer)[i] == '\n'));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*node;
	char			*line;
	int				res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_fd_node(&head, fd);
	if (!node)
		return (NULL);
	res = 1;
	while (res > 0 && !ft_strchr(node->buffer, '\n'))
		res = read_into_buffer(node);
	if (res == -1)
	{
		remove_fd_node(&head, fd);
		return (NULL);
	}
	line = extract_line(&node->buffer);
	if (!line)
	{
		remove_fd_node(&head, fd);
		return (NULL);
	}
	if (!node->buffer || !*node->buffer)
		remove_fd_node(&head, fd);
	return (line);
}
