/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:42:23 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 17:23:54 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->data->print_sem);
	printf("%ld %d %s\n", get_time() - philo->data->start_time,
		philo->id, status);
	sem_post(philo->data->print_sem);
}

void	custom_sleep(time_t time)
{
	time_t	start;
	time_t	current;

	start = get_time();
	while (get_time() - start < time)
	{
		current = get_time();
		if (current - start >= time)
			break ;
		usleep(100);
	}
}
