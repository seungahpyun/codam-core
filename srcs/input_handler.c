/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 08:53:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 15:31:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>

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
		j = ft_atoi(temp[i]);
		ft_stack_add_back(&a, ft_stack_new(j));
		free(temp[i]);
		i++;
	}
	free(temp);
	return (a);
}

t_stack	*ft_parse_input(int argc, char **argv)
{
	t_stack	*a;
	int		i;
	int		j;

	a = NULL;
	i = 1;
	if (argc < 2)
		ft_error();
	if (argc == 2)
		a = ft_process_single_input(argv);
	else
	{
		while (i < argc)
		{
			j = ft_atoi(argv[i]);
			ft_stack_add_back(&a, ft_stack_new(j));
			i++;
		}
	}
	return (a);
}
