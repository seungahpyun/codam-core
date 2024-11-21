/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:31 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/21 15:09:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_pa(t_stack **a, t_stack **b, int j)
{
	t_stack	*temp;

	if(!*b)
		return ;
	temp = *a;
	*a = *b;
	*b = (*b)->next;
	(*a)->next = temp;
	if (j == 0)
		ft_putstr_fd("pa\n", 1);
}

void	ft_pb(t_stack **a, t_stack **b, int j)
{
	t_stack *temp;

	if(!*a)
		return ;
	temp = *b;
	*b = *a;
	*a = (*a)->next;
	(*b)->next = temp;
	if (j == 0)
		ft_putchar_fd("pb\n", 1);
}
