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
	uint64_t	time;

	time = ft_get_time(philo->params->start);
	pthread_mutex_lock(&philo->params->write);
	if (ft_the_end(philo->params))
	{
		// printf("philo %d stop\n", philo->id);
		pthread_mutex_unlock(&philo->params->write);
		return (1);
	}
	// printf("time printf1 : %llu\n", ft_get_time(philo->params->start));
	printf("%d %d %s\n", (int)(time / 1000), philo->id, action);
	// printf("time printf2 : %llu\n", ft_get_time(philo->params->start));
	pthread_mutex_unlock(&philo->params->write);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	uint64_t	time;
	int			stop;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = philo->left_fork;
	right = philo->right_fork;
	if (!(philo->id % 2))
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	pthread_mutex_lock(left);
	// printf("time : %llu\n", ft_get_time(philo->params->start));
	if (ft_print_action(philo, ACTION_FORK))
	{
		pthread_mutex_unlock(left);
		return (1);
	}
	// printf("time : %llu\n", ft_get_time(philo->params->start));
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
	philo->die_at = ft_get_time(philo->params->start) + philo->params->fasting_limit * 1000;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->lock);
	stop = ft_usleep(philo->params->meal_duration * 1000, philo->params);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
	philo->nbr_time_eaten ++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	return (stop);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_print_action(philo, ACTION_SLEEP))
		return (1);
	return (ft_usleep(philo->params->sleep_duration * 1000, philo->params));
}

int	ft_routine(t_philo *philo)
{
	if (ft_eat(philo))
		return (1);
	if (philo->nbr_time_eaten == philo->params->nbr_meals)
	{
		// printf("here lllllllllllllllllllllllllllllllllllllllllllllllll_ %d\n", philo->id);
		pthread_mutex_lock(&philo->params->finished_philos_mutex);
		philo->params->finished_philos ++;
		pthread_mutex_unlock(&philo->params->finished_philos_mutex);
		return (1);
	}
	if (ft_sleep(philo))
		return (1);
	if (ft_print_action(philo, ACTION_THINK))
		return (1);
	// if (!(philo->id % 2) && (philo->params->nbr_philos % 2))
	// 	return (ft_usleep(philo->params->meal_duration * 200, philo->params));
	// TODO gerer les prios
	return (0);
}

void	*ft_start_routine(void *philo_ptr)
{
	t_philo	*philo;
	uint64_t	time;
	int		routine;

	philo = (t_philo *)philo_ptr;
	time = ft_get_time(philo->params->start);
	pthread_mutex_lock(&philo->lock);
	philo->die_at = time + philo->params->fasting_limit * 1000;
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->lock);
	// printf("die_at %f, last_meal %f, id %d, over %d, is_eating %d, nbr_time_eaten %d\n", philo->die_at, philo->last_meal, philo->id, philo->over, philo->is_eating, philo->nbr_time_eaten);	
	// if (!(philo->id % 2))
	// 	usleep(philo->params->meal_duration * 900);
	// TODO mettre ca dans une varible
	while (!ft_the_end(philo->params))
	{
		routine = ft_routine(philo);
		if (routine == 1)
		{
			// pthread_mutex_lock(&philo->params->write);
			// printf("philo %d stop\n", philo->id);
			// pthread_mutex_unlock(&philo->params->write);
			return (NULL);
		}
		// TODO message erreur
	}
	// pthread_mutex_lock(&philo->params->write);
	// printf("philo %d stop\n", philo->id);
	// pthread_mutex_unlock(&philo->params->write);
	return (NULL);
}

int	ft_monitor(void *params_ptr)
{
	t_params	*params;
	int			i;
	uint64_t		time;

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
			if ((params->philos[i].die_at == 0) || (params->philos[i].nbr_time_eaten == params->nbr_meals))
			{
				pthread_mutex_unlock(&params->philos[i].lock);
				i ++;
				continue ;
			}
			// printf("die at : %llu\n", params->philos[i].die_at);
			time = ft_get_time(params->start);
			if (((int)(time / 1000)) >= ((int)(params->philos[i].die_at / 1000)))
			{
				ft_print_action(&params->philos[i], ACTION_DIED);
				pthread_mutex_lock(&params->stop_mutex);
				params->stop = 1;
				pthread_mutex_unlock(&params->stop_mutex);
			}
			pthread_mutex_unlock(&params->philos[i].lock);
			i ++;
		}
		usleep(5);
	}
	return (0);
}