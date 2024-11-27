/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 10:33:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 15:48:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_sort_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		i;

	while (*stack_b)
	{
		tmp = *stack_b;
		i = ft_rotate_type_ba(*stack_a, *stack_b);
		while (i >= 0 && tmp)
		{
			if (i == ft_calc_rarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_calc_rarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarrb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_calc_rrarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarrb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_calc_rrarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarb(stack_a, stack_b, tmp->nbr, 'b');
			else
				tmp = tmp->next;
		}
	}
}

static t_stack	*ft_sort_b(t_stack **stack_a)
{
	t_stack	*stack_b;

	if (!stack_a || !*stack_a)
		return (NULL);
	stack_b = NULL;
	if (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
	{
		ft_pb(stack_a, &stack_b, 0);
		if (ft_stack_size(*stack_a) > 3)
			ft_pb(stack_a, &stack_b, 0);
		if (ft_stack_size(*stack_a) > 3)
			ft_sort_b_until_3(stack_a, &stack_b);
		if (!ft_is_sorted(*stack_a))
			ft_sort_three(stack_a);
	}
	return (stack_b);
}

static void	ft_sort_b_until_3(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		i;

	if (!stack_a || !*stack_a || !stack_b)
		return ;
	while (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
	{
		tmp = *stack_a;
		i = ft_rotate_type_ab(*stack_a, *stack_b);
		while (tmp && i >= 0)
		{
			if (i == ft_calc_rarb_b(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rrarrb_b(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rarrb_b(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rrarb_b(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarb(stack_a, stack_b, tmp->nbr, 'a');
			else
				tmp = tmp->next;
		}
	}
}

void	ft_sort(t_stack **stack_a)
{
	t_stack	*stack_b;

	if (!stack_a || !*stack_a
	|| ft_stack_size(*stack_a) <= 1 || ft_is_sorted(*stack_a))
		return ;
	if (ft_stack_size(*stack_a) <= 3)
		return (ft_sort_small_stack(stack_a));
	stack_b = ft_sort_b(stack_a);
	if (stack_b)
		ft_sort_a(stack_a, &stack_b);
	ft_align_stack(stack_a);
}
