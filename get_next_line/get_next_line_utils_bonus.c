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

int	ft_find_newline(t_list *list)
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

t_list	*ft_find_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_free_list(t_list **list)
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

int	ft_copy_to_line(t_list *temp, char *line, int total_len)
{
	int	i;
	int	j;

	j = 0;
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
	return (j);
}

char	*ft_create_line_from_list(t_list *list, int total_len)
{
	char	*line;
	int		final_len;

	line = malloc(total_len + 1);
	if (!line)
		return (NULL);
	final_len = ft_copy_to_line(list, line, total_len);
	line[final_len] = '\0';
	return (line);
}
