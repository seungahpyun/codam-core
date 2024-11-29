/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 15:53:57 by spyun         #+#    #+#                */
/*   Updated: 2024/11/29 11:36:13 by spyun         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <unistd.h>
#include <stdlib.h>

static void	ft_execute_instruction(t_stack **a, t_stack **b, char *line)
{
	if (!ft_strncmp(line, "sa", 2))
		ft_sa(a, 1);
	else if (!ft_strncmp(line, "sb", 2))
		ft_sb(b, 1);
	else if (!ft_strncmp(line, "ss", 2))
		ft_ss(a, b, 1);
	else if (!ft_strncmp(line, "pa", 2))
		ft_pa(a, b, 1);
	else if (!ft_strncmp(line, "pb", 2))
		ft_pb(a, b, 1);
	else if (!ft_strncmp(line, "ra", 2))
		ft_ra(a, 1);
	else if (!ft_strncmp(line, "rb", 2))
		ft_rb(b, 1);
	else if (!ft_strncmp(line, "rr", 2))
		ft_rr(a, b, 1);
	else if (!ft_strncmp(line, "rra", 3))
		ft_rra(a, 1);
	else if (!ft_strncmp(line, "rrb", 3))
		ft_rrb(b, 1);
	else if (!ft_strncmp(line, "rrr", 3))
		ft_rrr(a, b, 1);
	else
		ft_error();
}

static void	ft_read_and_execute(t_stack **a, t_stack **b)
{
	char	instr[4];
	int		i;
	int		ret;
	char	c;

	i = 0;
	while ((ret = read(0, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			if (i == 0)
				continue ;
			instr[i] = '\0';
			ft_execute_instruction(a, b, instr);
			i = 0;
		}
		else if (i < 3)
			instr[i++] = c;
		else
			ft_error();
	}
	if (ret == -1)
		ft_error();
	if (i != 0)
		ft_error();
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (EXIT_SUCCESS);
	a = ft_parse_input(argc, argv);
	if (!a || ft_has_duplicates(a))
	{
		ft_free(&a);
		ft_error();
	}
	b = NULL;
	ft_read_and_execute(&a, &b);
	if (ft_is_sorted(a) && !b)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	ft_free(&a);
	ft_free(&b);
	return (EXIT_SUCCESS);
}
