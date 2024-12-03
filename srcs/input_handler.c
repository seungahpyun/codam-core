/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 08:53:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/03 08:48:54 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <limits.h>

static int	check_int_range(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= sign;
	return (num <= INT_MAX && num >= INT_MIN);
}

t_stack	*ft_process_single_input(char **argv)
{
	t_stack	*stack_a;
	int		i;
	int		j;
	char	**split_array;

	stack_a = NULL;
	i = 0;
	split_array = ft_split(argv[1], ' ');
	if (!split_array)
		ft_error();
	while (split_array[i])
	{
		if (!is_valid_number(split_array[i])
			|| !check_int_range(split_array[i]))
		{
			ft_free(&stack_a);
			ft_free_split(split_array);
			ft_error();
		}
		j = ft_atoi(split_array[i]);
		ft_stack_add_back(&stack_a, ft_stack_new(j));
		i++;
	}
	ft_free_split(split_array);
	return (stack_a);
}

t_stack	*ft_parse_input(int argc, char **argv)
{
	t_stack	*stack_a;
	int		i;
	int		j;

	stack_a = NULL;
	i = 1;
	if (argc == 2)
		return (ft_process_single_input(argv));
	while (i < argc)
	{
		if (!is_valid_number(argv[i]) || !check_int_range(argv[i]))
		{
			ft_free(&stack_a);
			ft_error();
		}
		j = ft_atoi(argv[i]);
		ft_stack_add_back(&stack_a, ft_stack_new(j));
		i++;
	}
	return (stack_a);
}
