/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:50:23 by octoross          #+#    #+#             */
/*   Updated: 2024/09/03 18:50:23 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_the_end(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (false);
}

static bool	ft_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!ft_eat(philo))
		return (false);
	if (philo->nbr_time_eaten == data->nbr_meals)
	{
		pthread_mutex_lock(&data->finished_mutex);
		data->finished_philos ++;
		pthread_mutex_unlock(&data->finished_mutex);
		return (false);
	}
	if (!ft_print_action(philo, ACTION_SLEEP))
		return (false);
	if (!ft_usleep(data->sleep_duration * 1000, data))
		return (false);
	if (!ft_print_action(philo, ACTION_THINK))
		return (false);
	if (data->meal_duration >= data->sleep_duration)
		ft_usleep((data->meal_duration - data->sleep_duration + 1)
			* 1000, data);
	return (true);
}

void	*ft_start_routine(void *philo_ptr)
{
	unsigned long	time;
	t_philo			*philo;

	philo = (t_philo *)philo_ptr;
	time = ft_get_time(philo->data->start);
	pthread_mutex_lock(&philo->lock);
	philo->die_at = time + philo->data->fasting_limit * 1000;
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->lock);
	while (!ft_the_end(philo->data) && ft_routine(philo))
		;
	return (NULL);
}

static void	ft_monitor_philo(t_philo *philo, t_data *data)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->lock);
	if ((philo->die_at == 0) || (philo->nbr_time_eaten == data->nbr_meals))
	{
		pthread_mutex_unlock(&philo->lock);
		return ;
	}
	time = ft_get_time(data->start);
	if ((time / 1000) >= (philo->die_at / 1000))
	{
		ft_print_action(philo, ACTION_DIED);
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->lock);
}

void	ft_monitor(void *data_ptr)
{
	t_philo		*philo;
	t_data		*data;

	data = (t_data *)data_ptr;
	while (!data->stop)
	{
		ft_usleep(data->monitor_pace * 1000, data);
		pthread_mutex_lock(&data->finished_mutex);
		if (data->finished_philos == data->nbr_philos)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			pthread_mutex_unlock(&data->finished_mutex);
		}
		pthread_mutex_unlock(&data->finished_mutex);
		philo = data->philos;
		while (philo)
		{
			ft_monitor_philo(philo, data);
			philo = philo->next;
		}
	}
}
