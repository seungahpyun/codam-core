/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:07:30 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 11:43:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		printf("%ld %d %s\n", get_time()
			- philo->data->start_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
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
