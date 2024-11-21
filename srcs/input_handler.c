/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 08:53:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/21 09:44:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*ft_process_single_input(char **argv)
{
	t_stack	*a;
	int		i;
	int		j;
	char	**temp;

	a = NULL;
	i = 0;
	temp = ft_split(argv[1], 32);
	while (temp[i])
	{
		j = ft_atoi(temp[i]);
		ft_lstadd_back(&a, ft_lstnew(j));
		free(temp[i]);
		i++;
	}
	free(temp);
	return (a);
}

t_stack	*ft_parse_input(int argc, char **argv)
{
	t_stack *a;
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
		ft_lstadd_back(&a, ft_lstnew(j));
		i++;
		}
	}
	return (a);
}
