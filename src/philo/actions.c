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
	double	time;

	if (ft_get_time(&time, philo->params->start))
		return (printf("%s", ERR_TIME), 1);
	printf("%llums %d %s\n", time * 1000, philo->id, action);
	return (0);
}

int	ft_eat(t_philo *philo, pthread_mutex_t *write_mutex)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_print_action(philo, ACTION_FORK))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (ft_print_action(philo, ACTION_FORK))
		return (1);
	pthread_mutex_lock(write_mutex);
	if (ft_print_action(philo, ACTION_EAT))
		return (1);
	pthread_mutex_unlock(write_mutex);
	ft_usleep(philo->params->meal_duration * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_sleep(t_philo *philo, pthread_mutex_t *write_mutex)
{
	double	time;

	pthread_mutex_lock(write_mutex);
	if (ft_get_time(&time, philo->params->start))
		return (printf("%s", ERR_TIME), 1);
	if (ft_print_action(philo, ACTION_SLEEP))
		return (1);
	pthread_mutex_unlock(write_mutex);
	ft_usleep(philo->params->sleep_duration * 1000);
	return (0);
}

void	*ft_monitor(void *params)
{
	return (NULL);
}

void	*ft_routine(void *philo)
{
	return (NULL);
}
