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
{
	int		i;
	int		total_len;
	t_list	*temp;

	total_len = 0;
	temp = list;
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
			return (-1);
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
}

char	*get_next_line(int fd)
{
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
}
