/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   small_sort_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 14:33:58 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 09:29:45 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_three(t_stack **a)
{
	if (ft_min(*a) == (*a)->nbr)
	{
		ft_rra(a, 0);
		ft_sa(a, 0);
	}
	else if (ft_max(*a) == (*a)->nbr)
	{
		ft_ra(a, 0);
		if (!ft_is_sorted(*a))
			ft_sa(a, 0);
	}
	else
	{
		if (ft_find_index(*a, ft_max(*a)) == 1)
			ft_rra(a, 0);
		else
			ft_sa(a, 0);
	}
}
