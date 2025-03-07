/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/07 11:53:12 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 15:00:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	time_t			last_meal;
	int				meals_eaten;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	time_t			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

time_t		get_time(void);
void		print_status(t_philo *philo, char *status);
void		custom_sleep(time_t time);

void		cleanup(t_data *data);
int			error_msg(char *msg);
int			error_cleanup(char *msg, t_data *data);

int			ft_atoi(const char *str);
bool		check_valid_input(char *str);

bool		init_data(t_data *data, int argc, char **argv);
bool		init_mutex(t_data *data);
bool		init_philos(t_data *data);

void		eat(t_philo *philo);
void		think(t_philo *philo);
void		*philo_routine(void *arg);

void		monitoring(t_data *data);

#endif
