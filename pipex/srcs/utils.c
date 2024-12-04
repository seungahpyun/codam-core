/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:58:18 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 09:59:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

void	error_exit(char *msg)
{
	ft_put(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
