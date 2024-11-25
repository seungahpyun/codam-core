/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:37:03 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 15:07:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h> 

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	ft_free(t_stack **lst)
{
	t_stack	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		(*lst)->nbr = 0;
		free(*lst);
		*lst = temp;
	}
}
