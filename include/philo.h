/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:32:59 by octoross          #+#    #+#             */
/*   Updated: 2024/08/31 14:28:30 by octoross         ###   ########.fr       */
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

struct	s_params;

typedef struct s_philo
{
	double			die_at;
	double			last_meal;
	int				id;
	int				nbr_time_eaten;
	int				finished;
	int				died;
	struct s_params	*params;
	pthread_t		*thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	action_lock;
}	t_philo;

typedef struct s_params
{
	int				nbr_philos;
	double			fasting_limit;
	double			meal_duration;
	double			sleep_duration;
	int				nbr_meals;
	int				finished;
	struct timeval	start;
	t_philo			*philos;
	pthread_t		*monitor;
	pthread_mutex_t	write;
}	t_params;

int	ft_get_time(double *utime, struct timeval ref);
int	ft_usleep(double sleep_duration);

int	ft_parsing(t_params *params, int argc, char **argv);
int	ft_init(t_params *params);

#endif