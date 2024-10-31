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
		return ;
	new_node->str_buffer = buffer;
	new_node->next = NULL;
	last_node = ft_find_lstlast(*list);
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
}

void	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	while (!ft_find_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_append_list(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	ft_create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = ft_get_line(list);
	ft_free_list(&list);
	return (next_line);
}
