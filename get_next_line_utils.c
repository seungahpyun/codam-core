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

int	ft_found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (NULL);
	while (list)
	{
		i = 0;
		if (list->str_buffer[i] && i < BUFFER_SIZE)
		{
			if(list->str_buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}
