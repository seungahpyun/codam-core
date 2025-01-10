/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_bonus.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:38:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 11:53:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdbool.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals_eaten;
	long long		last_meal;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	long long	start_time;
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*dead_sem;
	t_philo		*philos;
}	t_data;

#endif
