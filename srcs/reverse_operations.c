/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_operations.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:24 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 17:27:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <unistd.h>

void	ft_rra(t_stack **stack_a, int print_flag)
{
	t_stack	*temp;
	int		i;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	i = 0;
	temp = *stack_a;
	while ((*stack_a)->next)
	{
		*stack_a = (*stack_a)->next;
		i++;
	}
	(*stack_a)->next = temp;
	while (i > 1)
	{
		temp = temp->next;
		i--;
	}
	temp->next = NULL;
	if (print_flag == 0)
		ft_putendl_fd("rra", STDOUT_FILENO);
}

void	ft_rrb(t_stack **stack_b, int print_flag)
{
	t_stack	*temp;
	int		i;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	i = 0;
	temp = *stack_b;
	while ((*stack_b)->next)
	{
		i++;
		*stack_b = (*stack_b)->next;
	}
	(*stack_b)->next = temp;
	while (i > 1)
	{
		temp = temp->next;
		i--;
	}
	temp->next = NULL;
	if (print_flag == 0)
		ft_putendl_fd("rrb", STDOUT_FILENO);
}

static void	ft_rrr_sub(t_stack **stack_b, int print_flag)
{
	t_stack	*temp;
	int		i;

	i = 0;
	temp = *stack_b;
	while ((*stack_b)->next)
	{
		i++;
		*stack_b = (*stack_b)->next;
	}
	(*stack_b)->next = temp;
	while (i > 1)
	{
		temp = temp->next;
		i--;
	}
	temp->next = NULL;
	if (print_flag == 0)
		ft_putendl_fd("rrr", STDOUT_FILENO);
}

void	ft_rrr(t_stack **stack_a, t_stack **stack_b, int print_flag)
{
	t_stack	*temp;
	int		i;

	if (!*stack_a || !((*stack_a)->next) || !*stack_b || !((*stack_b)->next))
		return ;
	i = 0;
	temp = *stack_a;
	while ((*stack_a)->next)
	{
		i++;
		*stack_a = (*stack_a)->next;
	}
	(*stack_a)->next = temp;
	while (i > 1)
	{
		temp = temp->next;
		i--;
	}
	temp->next = NULL;
	ft_rrr_sub(stack_b, print_flag);
}
