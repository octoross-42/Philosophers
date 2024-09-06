/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:32:59 by octoross          #+#    #+#             */
/*   Updated: 2024/09/07 00:19:31 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "utils.h"

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	unsigned long	die_at;
	unsigned long	last_meal;
	int				id;
	int				is_eating;
	int				nbr_time_eaten;
	struct s_data	*data;
	pthread_t		*thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_data
{
	unsigned long	fasting_limit;
	unsigned long	meal_duration;
	unsigned long	sleep_duration;
	int				usleep_pace;
	int				nbr_philos;
	int				nbr_meals;
	int				finished_philos;
	int				stop;
	struct timeval	start;
	t_philo			*philos;
	pthread_mutex_t	write;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	stop_mutex;
}	t_data;

unsigned long	ft_get_time(struct timeval ref);
bool			ft_usleep(unsigned long sleep_duration, t_data *data);

void			ft_clear_data(t_data *data, int n, int thread, char *err);
bool			ft_parsing(t_data *data, int argc, char **argv);
bool			ft_case_one(t_data *data);
bool			ft_init(t_data *data);

bool			ft_print_action(t_philo *philo, char *action);
bool			ft_eat(t_philo *philo);
bool			ft_sleep(t_philo *philo);
bool			ft_the_end(t_data *data);

void			*ft_start_routine(void *philo_ptr);
void			ft_monitor(void *data_ptr);

#endif