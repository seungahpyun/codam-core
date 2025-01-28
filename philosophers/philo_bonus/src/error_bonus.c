/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 14:42:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 17:27:50 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int	error_cleanup(char *msg, t_data *data)
{
	printf("%s\n", msg);
	cleanup(data);
	return (EXIT_FAILURE);
}
