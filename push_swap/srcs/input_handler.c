/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 08:53:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 15:25:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>
#include <stdio.h>

t_stack	*ft_process_single_input(char **argv)
{
	t_stack	*stack_a;
	int		i;
	int		j;
	char	**split_array;

	stack_a = NULL;
	i = 0;
	split_array = ft_split(argv[1], 32);
	if (!split_array)
		ft_error();
	while (split_array[i])
	{
		if (!is_valid_number(split_array[i]))
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
		stack_a = ft_process_single_input(argv);
	else
	{
		while (i < argc)
		{
			if ((!is_valid_number(argv[i])))
			{
				ft_free(&stack_a);
				ft_error();
			}
			j = ft_atoi(argv[i]);
			ft_stack_add_back(&stack_a, ft_stack_new(j));
			i++;
		}
	}
	return (stack_a);
}
