/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isalnum.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 08:22:23 by spyun          #+#    #+#                */
/*   Updated: 2024/10/08 08:22:27 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) != 0 || ft_isdigit(c) != 0);
}
