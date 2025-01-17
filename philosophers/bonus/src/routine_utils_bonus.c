/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 14:40:21 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/17 14:40:24 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	handle_single_philo(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	custom_sleep(philo->data->time_to_die);
	print_status(philo, "died");
	exit(EXIT_FAILURE);
}
