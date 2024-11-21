/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 16:33:42 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/21 10:13:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_stack
{
	long			nbr;
	long			index;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

void	ft_error(void);
void	ft_free(t_stack **lst);

t_stack	*ft_parse_input(int argc, char **argv);

bool	ft_has_duplicates(t_stack *a);
bool	ft_is_sorted(t_stack *a);

#endif
