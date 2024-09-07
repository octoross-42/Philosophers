/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:05:59 by octoross          #+#    #+#             */
/*   Updated: 2024/09/03 16:05:59 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_data(t_data *data, int thread, char *err)
{
	int		i;
	t_philo	*philo;
	t_philo	*to_free;

	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->finished_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	thread = (data->nbr_philos + 1) * (thread == -1) - 1;
	i = 0;
	philo = data->philos;
	while (philo)
	{
		pthread_mutex_destroy(&philo->lock);
		pthread_mutex_destroy(philo->left_fork);
		free(philo->left_fork);
		if ((i < thread) && pthread_join(philo->thread, NULL))
			printf("%s", ERR_DESTROY_THREAD);
		to_free = philo;
		philo = philo->next;
		free(to_free);
	}
	if (err)
		printf("%s", err);
}

static bool	ft_init_threads(t_data *data)
{
	t_philo	*philo;

	if (gettimeofday(&data->start, NULL) == -1)
		return (ft_clear_data(data, 0, ERR_TIME), false);
	philo = data->philos;
	while (philo)
	{
		if (pthread_create(&philo->thread,
				NULL, &ft_start_routine, philo))
			return (ft_clear_data(data, philo->id - 1, ERR_INIT_THREAD), false);
		philo = philo->next;
	}
	ft_monitor(data);
	philo = data->philos;
	while (philo)
	{
		if (pthread_join(philo->thread, NULL))
			printf("%s", ERR_DESTROY_THREAD);
		philo = philo->next;
	}
	return (true);
}

static bool	ft_init_philo(t_philo *philo, int i, t_data *data)
{
	philo->die_at = 0;
	philo->last_meal = 0;
	philo->id = i + 1;
	philo->nbr_time_eaten = 0;
	philo->data = data;
	philo->next = NULL;
	philo->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(philo->left_fork))
		return (printf("%s", ERR_MALLOC), false);
	if (pthread_mutex_init(philo->left_fork, NULL))
		return (printf("%s", ERR_INIT_MUTEX),
			free(philo->left_fork), false);
	if (i > 0)
		philo->previous->right_fork = philo->left_fork;
	if (pthread_mutex_init(&philo->lock, NULL))
		return (printf("%s", ERR_INIT_MUTEX),
			pthread_mutex_destroy(philo->left_fork),
			free(philo->left_fork), false);
	return (true);
}

static bool	ft_init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*previous;

	previous = NULL;
	i = 0;
	while (i < data->nbr_philos)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (ft_clear_data(data, 0, ERR_MALLOC), false);
		philo->previous = previous;
		if (!previous)
			data->philos = philo;
		else
			previous->next = philo;
		if (!ft_init_philo(philo, i ++, data))
			return (free(philo), ft_clear_data(data, 0, NULL), false);
		previous = philo;
	}
	philo->right_fork = data->philos->left_fork;
	return (true);
}

bool	ft_init(t_data *data)
{
	data->finished_philos = 0;
	data->stop = 0;
	if (USLEEP_PACE <= 0 || USLEEP_PACE >= 10000
		|| (USLEEP_PACE % data->meal_duration)
		|| (USLEEP_PACE % data->sleep_duration))
		data->usleep_pace = 50;
	else
		data->usleep_pace = USLEEP_PACE;
	data->monitor_pace = ft_pgcd(data->meal_duration, data->sleep_duration);
	if (pthread_mutex_init(&data->write, NULL))
		return (printf("%s", ERR_INIT_MUTEX), true);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (pthread_mutex_destroy(&data->write),
			printf("%s", ERR_INIT_MUTEX), true);
	if (pthread_mutex_init(&data->finished_mutex, NULL))
		return (pthread_mutex_destroy(&data->write),
			pthread_mutex_destroy(&data->stop_mutex),
			printf("%s", ERR_INIT_MUTEX), true);
	if (!ft_init_philos(data))
		return (true);
	if (!ft_init_threads(data))
		return (true);
	return (false);
}
