/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_utils.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/24 11:17:34 by spyun          #+#    #+#                */
/*   Updated: 2024/10/24 11:17:36 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	find_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->str_buffer[i] && i < BUFFER_SIZE)
		{
			if (list->str_buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	append_buffer_to_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (free(buffer));
	new_node->str_buffer = buffer;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

void	free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str_buffer);
		free(*list);
		*list = temp;
	}
}

char	*create_line_buffer(t_list *list, int *total_len)
{
	t_list	*temp;
	int		i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->str_buffer[i] && temp->str_buffer[i] != '\n')
			i++;
		*total_len += i;
		if (temp->str_buffer[i] == '\n')
		{
			(*total_len)++;
			break ;
		}
		temp = temp->next;
	}
	return (malloc(*total_len + 1));
}

void	copy_line(t_list *list, char *line, int total_len)
{
	int		i;
	int		j;
	t_list	*temp;

	j = 0;
	temp = list;
	while (temp && j < total_len)
	{
		i = 0;
		while (temp->str_buffer[i]
			&& temp->str_buffer[i] != '\n' && j < total_len)
			line[j++] = temp->str_buffer[i++];
		if (temp->str_buffer[i] == '\n' && j < total_len)
		{
			line[j++] = '\n';
			break ;
		}
		temp = temp->next;
	}
	line[j] = '\0';
}
