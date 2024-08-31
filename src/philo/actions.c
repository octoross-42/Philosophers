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

int	ft_eat(t_philo *philo)
{
	double	time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&params->write);
	if (ft_get_time(&time, philo->params->start))
		return (printf("%s", ERR_TIME), 1);
	else
		print("%llums %d is eating\n", time * 1000, philo->id);
	pthread_mutex_unlock(&params->write);
	ft_usleep(philo->params->meal_duration * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	double	time;

	pthread_mutex_lock(&params->write);
	if (ft_get_time(&time, philo->params->start))
		return (printf("%s", ERR_TIME), 1);
	else
		print("%llums %d is sleeping\n", time * 1000, philo->id);
	pthread_mutex_unlock(&params->write);
	ft_usleep(philo->params->sleep_duration * 1000);
	return (0);
}
