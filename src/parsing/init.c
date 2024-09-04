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

void	ft_clear_data(t_data *data, int n, int thread, char *err)
{
	int	i;

	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->finished_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	n = (data->nbr_philos + 1) * (n == -1) - 1;
	thread = (data->nbr_philos + 1) * (thread == -1) - 1;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].lock);
		free(data->philos[i].left_fork);
		if (i < thread)
		{
			if (pthread_join(*data->philos[i].thread, NULL))
				printf("%s", ERR_DESTROY_THREAD);
		}
		free(data->philos[i ++].thread);
	}
	if (data->philos)
		free(data->philos);
	if (err)
		printf("%s", err);
}

int	ft_init_threads(t_data *data)
{
	int	i;

	if (gettimeofday(&data->start, NULL) == -1)
		return (ft_clear_data(data, -1, 0, ERR_TIME), 1);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(data->philos[i].thread,
				NULL, &ft_start_routine, &data->philos[i]))
			return (ft_clear_data(data, -1, i, ERR_INIT_THREAD), 1);
		i ++;
	}
	ft_monitor(data);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(*data->philos[i ++].thread, NULL))
			printf("%s", ERR_DESTROY_THREAD);
	}
	return (0);
}

int	ft_init_philo(t_philo *philos, int i, t_data *data)
{
	philos[i].die_at = 0;
	philos[i].last_meal = 0;
	philos[i].id = i + 1;
	philos[i].nbr_time_eaten = 0;
	philos[i].is_eating = 0;
	philos[i].data = data;
	philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!philos[i].thread)
		return (printf("%s", ERR_MALLOC), 1);
	philos[i].left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(philos[i].left_fork))
		return (printf("%s", ERR_MALLOC), free(philos[i].thread), 1);
	if (pthread_mutex_init(philos[i].left_fork, NULL))
		return (printf("%s", ERR_INIT_MUTEX),
			free(philos[i].left_fork), free(philos[i].thread), 1);
	if (i > 0)
		philos[i - 1].right_fork = philos[i].left_fork;
	if (i == data->nbr_philos - 1)
		philos[i].right_fork = philos[0].left_fork;
	if (pthread_mutex_init(&philos[i].lock, NULL))
		return (printf("%s", ERR_INIT_MUTEX),
			pthread_mutex_destroy(philos[i].left_fork),
			free(philos[i].left_fork), free(philos[i].thread), 1);
	return (0);
}

int	ft_init_philos(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_data) * data->nbr_philos);
	if (!data->philos)
		return (ft_clear_data(data, 0, 0, ERR_MALLOC), 1);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (ft_init_philo(data->philos, i ++, data))
			return (ft_clear_data(data, i - 1, 0, NULL), 1);
	}
	return (0);
}

int	ft_init(t_data *data)
{
	data->finished_philos = 0;
	data->stop = 0;
	if (USLEEP_PACE <= 0 || USLEEP_PACE >= 10000
		|| (USLEEP_PACE % data->meal_duration)
		|| (USLEEP_PACE % data->sleep_duration))
		data->usleep_pace = 50;
	else
		data->usleep_pace = USLEEP_PACE;
	if (pthread_mutex_init(&data->write, NULL))
		return (printf("%s", ERR_INIT_MUTEX), 1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (pthread_mutex_destroy(&data->write),
			printf("%s", ERR_INIT_MUTEX), 1);
	if (pthread_mutex_init(&data->finished_mutex, NULL))
		return (pthread_mutex_destroy(&data->write),
			pthread_mutex_destroy(&data->stop_mutex),
			printf("%s", ERR_INIT_MUTEX), 1);
	if (ft_init_philos(data))
		return (1);
	if (ft_init_threads(data))
		return (1);
	return (0);
}
