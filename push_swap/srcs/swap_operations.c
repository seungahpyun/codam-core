/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:29 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/02 17:04:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <unistd.h>

void	ft_sa(t_stack **stack_a, int print_flag)
{
	t_stack	*temp;

	if (!*stack_a || !((*stack_a)->next))
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
	if (print_flag == 0)
		ft_putendl_fd("sa", STDOUT_FILENO);
}

void	ft_sb(t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_b || !((*stack_b)->next))
		return ;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
	if (print_flag == 0)
		ft_putendl_fd("sb", STDOUT_FILENO);
}

void	ft_ss(t_stack **stack_a, t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_a || !(*stack_a)->next || !*stack_b || !(*stack_b)->next)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
	if (print_flag == 0)
		ft_putendl_fd("ss", STDOUT_FILENO);
}
