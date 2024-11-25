/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_operations.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 10:54:24 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 10:57:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rra(t_stack **a, int j)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!*a || !(*a)->next)
		return ;
	last = *a;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *a;
	*a = last;
	if (j == 0)
		ft_putstr_fd("rra\n", 1);
}

void	ft_rrb(t_stack **b, int j)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!*b || !(*b)->next)
		return ;
	last = *b;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *b;
	*b = last;
	if (j == 0)
		ft_putstr_fd("rrb\n", 1);
}

static void	ft_rrr_sub(t_stack **b, int j)
{
	t_stack	*last_b;
	t_stack	*second_last_b;

	last_b = *b;
	second_last_b = NULL;
	while (last_b->next)
	{
		second_last_b = last_b;
		last_b = last_b->next;
	}
	second_last_b->next = NULL;
	last_b->next = *b;
	*b = last_b;
	if (j == 0)
		ft_putstr_fd("rrr\n", 1);
}

void	ft_rrr(t_stack **a, t_stack **b, int j)
{
	t_stack	*last_a;
	t_stack	*second_last_a;

	if (!*a || !(*a)->next || !*b || !(*b)->next)
		return ;
	last_a = *a;
	second_last_a = NULL;
	while (last_a->next)
	{
		second_last_a = last_a;
		last_a = last_a->next;
	}
	second_last_a->next = NULL;
	last_a->next = *a;
	*a = last_a;
	ft_rrr_sub(b, j);
}
