/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_bonus.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:38:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 09:49:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	time_t			last_meal;
	int				meals_eaten;
	struct s_data	*data;
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
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*meal_sem;
	t_philo			*philos;
}	t_data;

/* init_bonus.c */
bool	init_data(t_data *data, int argc, char **argv);
bool	init_semaphores(t_data *data);
bool	init_philos(t_data *data);

/* routine_bonus.c */
void	philo_routine(t_philo *philo);
/* routine_utils_bonus.c */
void	handle_single_philo(t_philo *philo);

/* utils_bonus.c */
time_t	get_time(void);
void	print_status(t_philo *philo, char *status);
void	custom_sleep(time_t time);
int		ft_atoi(const char *str);
bool	check_valid_input(char *str);
int		error_msg(char *msg);
int		error_cleanup(char *msg, t_data *data);

/* cleanup_bonus.c */
void	cleanup(t_data *data);

/* error_bonus.c */
void	emergency_cleanup(t_data *data);
int		error_msg(char *msg);
int		error_cleanup(char *msg, t_data *data);

#endif
