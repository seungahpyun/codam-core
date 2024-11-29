/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_operations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 15:38:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <unistd.h>

void	ft_ra(t_stack **stack_a, int print_flag)
{
	t_stack	*temp;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = NULL;
	ft_stack_add_back(stack_a, temp);
	if (print_flag == 0)
		ft_putendl_fd("ra", STDOUT_FILENO);
}

void	ft_rb(t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	temp = *stack_b;
	*stack_b = ft_stack_last(*stack_b);
	(*stack_b)->next = temp;
	*stack_b = temp->next;
	temp->next = NULL;
	if (print_flag == 0)
		ft_putendl_fd("rb", STDOUT_FILENO);
}

void	ft_rr(t_stack **stack_a, t_stack **stack_b, int print_flag)
{
	t_stack	*temp;

	if (!*stack_a || !((*stack_a)->next) || !*stack_b || !((*stack_b)->next))
		return ;
	temp = *stack_a;
	*stack_a = ft_stack_last(*stack_a);
	(*stack_a)->next = temp;
	*stack_a = temp->next;
	temp->next = NULL;
	temp = *stack_b;
	*stack_b = ft_stack_last(*stack_b);
	(*stack_b)->next = temp;
	*stack_b = temp->next;
	temp->next = NULL;
	if (print_flag == 0)
		ft_putendl_fd("rr", STDOUT_FILENO);
}
