/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:37:03 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 15:21:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_free(t_stack **stack_ptr)
{
	t_stack	*next_node;

	if (!stack_ptr || !*stack_ptr)
		return ;
	while (*stack_ptr)
	{
		next_node = (*stack_ptr)->next;
		(*stack_ptr)->nbr = 0;
		free(*stack_ptr);
		*stack_ptr = next_node;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
