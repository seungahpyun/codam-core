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

<<<<<<< HEAD:get_next_line/get_next_line.c
t_list	*ft_clear_until_newline(t_list *list)
{
	t_list	*next_start = NULL;
	int		i;
	int		j;

	while (list)
	{
		i = 0;
		while (list->str_buffer[i] && list->str_buffer[i] != '\n')
			i++;
		if (list->str_buffer[i] == '\n')
		{
			if (list->str_buffer[i + 1] != '\0')
			{
				next_start = malloc(sizeof(t_list));
				if (!next_start)
					return (NULL);
				next_start->str_buffer = malloc(BUFFER_SIZE + 1 - i - 1);
				if (!next_start->str_buffer)
				{
					free(next_start);
					return (NULL);
				}
				j = 0;
				while (list->str_buffer[i + 1 + j] && j < BUFFER_SIZE - i - 1)
				{
					next_start->str_buffer[j] = list->str_buffer[i + 1 + j];
					j++;
				}
				next_start->str_buffer[j] = '\0';
				next_start->next = list->next;
			}
			list->str_buffer[i + 1] = '\0';
			list->next = NULL;
			break;
		}
		list = list->next;
	}
	return (next_start);
}


char	*ft_get_line(t_list *list)
=======
static t_list	*get_fd_node(t_list **head, int fd)
>>>>>>> origin/master:get_next_line.c
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
<<<<<<< HEAD:get_next_line/get_next_line.c
	int		total_len = 0;
	t_list	*temp = list;

	while (temp)
	{
		i = 0;
		while (temp->str_buffer[i] && temp->str_buffer[i] != '\n')
			i++;
		total_len += i;
		if (temp->str_buffer[i] == '\n')
		{
			total_len++;
			break ;
		}
		temp = temp->next;
	}
	return (ft_create_line_from_list(list, total_len));
}

void	ft_append_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		return ;
	}
	new_node->str_buffer = buffer;
	new_node->next = NULL;
	last_node = ft_find_lstlast(*list);
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
}

int	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	while (!ft_find_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			ft_free_list(list);
			*list = NULL;
		}
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buffer);
			ft_free_list(list);
			*list = NULL;
			return (-1);
		}
		if (char_read == 0)
		{
			free(buffer);
			return (0);
		}
		buffer[char_read] = '\0';
		ft_append_list(list, buffer);
	}
	return (1);
=======

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
>>>>>>> origin/master:get_next_line.c
}

char	*get_next_line(int fd)
{
<<<<<<< HEAD:get_next_line/get_next_line.c
	static t_list	*list;
	char			*next_line;
	t_list			*remaining;
	int				read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_status = ft_create_list(&list, fd);
	if (read_status == -1)
	{
		ft_free_list(&list);
		list = NULL;
		return (NULL);
	}
	if (!list)
		return (NULL);
	next_line = ft_get_line(list);
	remaining = ft_clear_until_newline(list);
	ft_free_list(&list);
	list = remaining;
	return (next_line);
=======
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
		return (remove_fd_node(&head, fd), NULL);
	line = extract_line(&node->buffer);
	if (!line)
		return (remove_fd_node(&head, fd), NULL);
	if (!node->buffer || !*node->buffer)
		remove_fd_node(&head, fd);
	return (line);
>>>>>>> origin/master:get_next_line.c
}
