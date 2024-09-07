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
		return (false);
	}
	printf("%lu %d %s\n", (time / 1000), philo->id, action);
	pthread_mutex_unlock(&philo->data->write);
	return (true);
}

static bool	ft_take_forks(t_philo *philo,
	pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_lock(left);
	if (!ft_print_action(philo, ACTION_FORK))
		return (pthread_mutex_unlock(left), false);
	pthread_mutex_lock(right);
	pthread_mutex_lock(&philo->lock);
	if (!ft_print_action(philo, ACTION_FORK))
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(&philo->lock);
		return (false);
	}
	if (!ft_print_action(philo, ACTION_EAT))
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(&philo->lock);
		return (false);
	}
	philo->die_at = ft_get_time(philo->data->start)
		+ philo->data->fasting_limit * 1000;
	pthread_mutex_unlock(&philo->lock);
	return (true);
}

static void	ft_drop_forks(t_philo *philo,
	pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
	philo->nbr_time_eaten ++;
	pthread_mutex_unlock(&philo->lock);
}

bool	ft_eat(t_philo *philo)
{
	bool			stop;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	if (philo->id % 2)
	{
		left = philo->left_fork;
		right = philo->right_fork;
	}
	else
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	if (!ft_take_forks(philo, left, right))
		return (false);
	stop = ft_usleep(philo->data->meal_duration * 1000, philo->data);
	ft_drop_forks(philo, left, right);
	return (stop);
}
