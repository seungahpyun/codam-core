/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 08:53:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 09:25:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>
#include <stdio.h>

t_stack	*ft_process_single_input(char **argv)
{
	t_stack	*a;
	int		i;
	int		j;
	char	**temp;

	a = NULL;
	i = 0;
	temp = ft_split(argv[1], 32);
	if (!temp)
		ft_error();
	while (temp[i])
	{
		if (!is_valid_number(temp[i]))
		{
			ft_free(&a);
			ft_free_split(temp);
			ft_error();
		}
		j = ft_atoi(temp[i]);
		ft_stack_add_back(&a, ft_stack_new(j));
		i++;
	}
	ft_free_split(temp);
	return (a);
}

t_stack	*ft_parse_input(int argc, char **argv)
{
	t_stack	*a;
	int		i;
	int		j;

	a = NULL;
	i = 1;
	if (argc == 2)
		a = ft_process_single_input(argv);
	else
	{
		while (i < argc)
		{
			if ((!is_valid_number(argv[i])))
			{
				ft_free(&a);
				ft_error();
			}
			j = ft_atoi(argv[i]);
			ft_stack_add_back(&a, ft_stack_new(j));
			i++;
		}
	}
	return (a);
}
