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

int	ft_print_action(t_philo *philo, char *action)
{
	unsigned long	time;

	time = ft_get_time(philo->data->start);
	pthread_mutex_lock(&philo->data->write);
	if (ft_the_end(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write);
		return (1);
	}
	printf("%lu %d %s\n", (time / 1000), philo->id, action);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

int	ft_take_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (ft_print_action(philo, ACTION_FORK))
		return (pthread_mutex_unlock(left), 1);
	pthread_mutex_lock(right);
	pthread_mutex_lock(&philo->lock);
	if (ft_print_action(philo, ACTION_FORK))
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	if (ft_print_action(philo, ACTION_EAT))
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	philo->die_at = ft_get_time(philo->data->start)
		+ philo->data->fasting_limit * 1000;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	ft_drop_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
	philo->nbr_time_eaten ++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	int				stop;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = philo->left_fork;
	right = philo->right_fork;
	if (!(philo->id % 2))
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	if (ft_take_forks(philo, left, right))
		return (1);
	stop = ft_usleep(philo->data->meal_duration * 1000, philo->data);
	if (ft_drop_forks(philo, left, right))
		return (1);
	return (stop);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_print_action(philo, ACTION_SLEEP))
		return (1);
	return (ft_usleep(philo->data->sleep_duration * 1000, philo->data));
}
