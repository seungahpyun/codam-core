/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_operations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 14:49:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_ra(t_stack **a, int j)
{
	t_stack	*temp;

	if (!*a || !(*a)->next)
		return ;
	temp = *a;
	*a = ft_stack_last(*a);
	(*a)->next = temp;
	*a = temp->next;
	temp->next = NULL;
	if (j == 0)
		ft_putstr_fd("ra\n", 1);
}

void	ft_rb(t_stack **b, int j)
{
	t_stack	*temp;

	if (!*b || !(*b)->next)
		return ;
	temp = *b;
	*b = ft_stack_last(*b);
	(*b)->next = temp;
	*b = temp->next;
	temp->next = NULL;
	if (j == 0)
		ft_putstr_fd("rb\n", 1);
}

void	ft_rr(t_stack **a, t_stack **b, int j)
{
	t_stack	*temp;

	if (!*a || !(*a)->next || !*b || !(*b)->next)
		return ;
	temp = *a;
	*a = ft_stack_last(*a);
	(*a)->next = temp;
	*a = temp->next;
	temp->next = NULL;
	temp = *b;
	*b = ft_stack_last(*b);
	(*b)->next = temp;
	*b = temp->next;
	temp->next = NULL;
	if (j == 0)
		ft_putstr_fd("rr\n", 1);
}
