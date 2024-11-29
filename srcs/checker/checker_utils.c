/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 15:53:37 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/27 14:03:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <stdlib.h>

void	ft_error_ch(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
