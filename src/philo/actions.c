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

int	ft_the_end(t_params *params)
{
	pthread_mutex_lock(&params->stop_mutex);
	if (params->stop)
	{
		pthread_mutex_unlock(&params->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&params->stop_mutex);
	return (0);
}

int	ft_print_action(t_philo *philo, char *action)
{
	double	time;

	if (ft_get_time(&time, philo->params->start))
		return (printf("%s", ERR_TIME), 1);
	pthread_mutex_lock(&philo->params->write);
	printf("%d %d %s\n", (int)(time / 1000), philo->id, action);
	pthread_mutex_unlock(&philo->params->write);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	double	time;

	pthread_mutex_lock(philo->left_fork);
	if (ft_the_end(philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (2);
	}
	if (ft_print_action(philo, ACTION_FORK))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (ft_the_end(philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (2);
	}
	pthread_mutex_lock(&philo->lock);
	if (ft_print_action(philo, ACTION_FORK))
		return (1);
	if (ft_print_action(philo, ACTION_EAT))
		return (1);
	ft_get_time(&time, philo->params->start);
	philo->die_at = time + philo->params->fasting_limit * 1000;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->lock);
	if (ft_the_end(philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (2);
	}
	ft_usleep(philo->params->meal_duration * 1000, philo->params);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->nbr_time_eaten ++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	double	time;
	int		sleep;

	if (ft_the_end(philo->params))
		return (2);
	if (ft_print_action(philo, ACTION_SLEEP))
		return (1);
	if (ft_usleep(philo->params->sleep_duration * 1000, philo->params))
		return (1);
	// TODO return err
	return (0);
}

int	ft_monitor(void *params_ptr)
{
	t_params	*params;
	int			i;
	double		time;

	params = (t_params *)params_ptr;
	while (!params->stop)
	{
		pthread_mutex_lock(&params->finished_philos_mutex);
		if (params->finished_philos == params->nbr_philos)
		{
			pthread_mutex_lock(&params->stop_mutex);
			params->stop = 1;
			pthread_mutex_unlock(&params->stop_mutex);
			pthread_mutex_unlock(&params->finished_philos_mutex);
			return (0);
		}
		pthread_mutex_unlock(&params->finished_philos_mutex);
		i = 0;
		while (i < params->nbr_philos)
		{
			pthread_mutex_lock(&params->philos[i].lock);
			if (ft_get_time(&time, params->start))
				return (1);
			// TODO return err
			if ((int)(time / 1000) > (int)(params->philos[i].die_at / 1000))
			{
				pthread_mutex_lock(&params->stop_mutex);
				params->stop = 1;
				pthread_mutex_unlock(&params->stop_mutex);
				ft_print_action(&params->philos[i], ACTION_DIED);
			}
			pthread_mutex_unlock(&params->philos[i].lock);
			i ++;
		}
	}
	return (0);
}

int	ft_routine(t_philo *philo)
{
	ft_eat(philo);
	if (ft_the_end(philo->params))
		return (2);
	if (philo->nbr_time_eaten == philo->params->nbr_meals)
	{
		pthread_mutex_lock(&philo->params->finished_philos_mutex);
		philo->params->finished_philos ++;
		pthread_mutex_unlock(&philo->params->finished_philos_mutex);
		return (2);
	}
	ft_sleep(philo);
	if (ft_the_end(philo->params))
		return (2);
	if (ft_print_action(philo, ACTION_THINK))
		return (1);
	ft_usleep(1, philo->params);
	return (0);
}

void	*ft_start_routine(void *philo_ptr)
{
	t_philo	*philo;
	double	time;
	int		routine;

	philo = (t_philo *)philo_ptr;
	ft_get_time(&time, philo->params->start);
	pthread_mutex_lock(&philo->lock);
	philo->die_at = time + philo->params->fasting_limit * 1000;
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->lock);
	// printf("die_at %f, last_meal %f, id %d, over %d, is_eating %d, nbr_time_eaten %d\n", philo->die_at, philo->last_meal, philo->id, philo->over, philo->is_eating, philo->nbr_time_eaten);	
	if (!(philo->id % 2))
		ft_usleep(philo->params->meal_duration * 500, philo->params);
	while (!ft_the_end(philo->params))
	{
		routine = ft_routine(philo);
		if (routine == 1)
		// TODO message erreur
			return (NULL);
		else if (routine == 2)
			return (NULL);
	}
	// pthread_mutex_lock(&philo->params->write);
	// printf("philo %d stop\n", philo->id);
	// pthread_mutex_unlock(&philo->params->write);
	return (NULL);
}
