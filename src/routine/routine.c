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

int	ft_the_end(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

int	ft_routine(t_philo *philo)
{
	if (ft_eat(philo))
		return (1);
	if (philo->nbr_time_eaten == philo->data->nbr_meals)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		philo->data->finished_philos ++;
		pthread_mutex_unlock(&philo->data->finished_mutex);
		return (1);
	}
	if (ft_sleep(philo))
		return (1);
	if (ft_print_action(philo, ACTION_THINK))
		return (1);
	return (0);
}

void	*ft_start_routine(void *philo_ptr)
{
	int			routine;
	unsigned long	time;
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	time = ft_get_time(philo->data->start);
	pthread_mutex_lock(&philo->lock);
	philo->die_at = time + philo->data->fasting_limit * 1000;
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->lock);
	if (!(philo->id % 2))
		ft_usleep(philo->data->meal_duration * 900, philo->data);
	while (!ft_the_end(philo->data))
	{
		routine = ft_routine(philo);
		if (routine)
			return (NULL);
	}
	
	return (NULL);
}

void	ft_monitor_philo(t_philo *philo, t_data *data)
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

int	ft_monitor(void *data_ptr)
{
	int			i;
	t_data		*data;

	data = (t_data *)data_ptr;
	while (!data->stop)
	{
		pthread_mutex_lock(&data->finished_mutex);
		if (data->finished_philos == data->nbr_philos)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			pthread_mutex_unlock(&data->finished_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->finished_mutex);
		i = 0;
		while (i < data->nbr_philos)
			ft_monitor_philo(&data->philos[i ++], data);
		usleep(10);
	}
	return (0);
}
