/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:43:54 by octoross          #+#    #+#             */
/*   Updated: 2024/08/19 19:43:54 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_print_action(t_philo *philo, char *action)
{
	unsigned long	time;

	time = ft_get_time(philo->data->start);
	pthread_mutex_lock(&philo->data->write);
	if (ft_the_end(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write);
		return (true);
	}
	printf("%lu %d %s\n", (time / 1000), philo->id, action);
	pthread_mutex_unlock(&philo->data->write);
	return (false);
}

static bool	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_print_action(philo, ACTION_FORK))
		return (pthread_mutex_unlock(philo->left_fork), true);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->lock);
	if (ft_print_action(philo, ACTION_FORK))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	if (ft_print_action(philo, ACTION_EAT))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	philo->die_at = ft_get_time(philo->data->start)
		+ philo->data->fasting_limit * 1000;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->lock);
	return (false);
}

static void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->nbr_time_eaten ++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
}

bool	ft_eat(t_philo *philo)
{
	bool	stop;

	if (ft_take_forks(philo))
		return (true);
	stop = ft_usleep(philo->data->meal_duration * 1000, philo->data);
	ft_drop_forks(philo);
	return (stop);
}

bool	ft_sleep(t_philo *philo)
{
	if (ft_print_action(philo, ACTION_SLEEP))
		return (true);
	return (ft_usleep(philo->data->sleep_duration * 1000, philo->data));
}
