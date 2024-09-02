/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:11:00 by octoross          #+#    #+#             */
/*   Updated: 2024/09/02 18:55:30 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_args_help(int n)
{
	if (n == 1)
		printf("%s\e[1m%s\e[m", MESSAGE_1, HELP_1);
	else if (n == 2)
		printf("%s\e[1m%s\e[m", MESSAGE_2, HELP_2);
	else if (n == 3)
		printf("%s\e[1m%s\e[m", MESSAGE_3, HELP_3);
	else if (n == 4)
		printf("%s\e[1m%s\e[m", MESSAGE_4, HELP_4);
	else if (n == 5)
		printf("%s\e[1m%s\e[m", MESSAGE_5, HELP_5);
	else
		printf("%s-%s-%s-%s-%s(-)%s", HELP_ARGS,
			HELP_1, HELP_2, HELP_3, HELP_4, HELP_5);
}

void	ft_help(int argc, char **argv)
{
	if (argc == 1)
		ft_args_help(0);
	else if (!ft_strcmp(argv[1], "1"))
		ft_args_help(1);
	else if (!ft_strcmp(argv[1], "2"))
		ft_args_help(2);
	else if (!ft_strcmp(argv[1], "3"))
		ft_args_help(3);
	else if (!ft_strcmp(argv[1], "4"))
		ft_args_help(4);
	else if (!ft_strcmp(argv[1], "5"))
		ft_args_help(5);
	else
		ft_args_help(0);
}

int	ft_parsing(t_params *params, int argc, char **argv)
{
	int	valid;

	if (argc <= 0)
		return (printf("%s", ERR_NE_ARGS), 1);
	if ((!ft_strcmp(argv[0], "-help") || !ft_strcmp(argv[0], "help") || !ft_strcmp(argv[0], "-h")) && HELP)
		return (ft_help(argc, argv), -1);
	if ((argc < 4))
		return ("%s", printf(ERR_NE_ARGS), 1);
	else if (argc > 5)
		return ("%s", printf(ERR_TM_ARGS), 1);
	valid = 0;
	params->nbr_philos = ft_atopi(argv[0]);
	params->fasting_limit = ft_atosi(argv[1], &valid);
	params->meal_duration = ft_atosi(argv[2], &valid);
	params->sleep_duration = ft_atosi(argv[3], &valid);
	if (argc == 5)
		params->nbr_meals = ft_atopi(argv[4]);
	else
		params->nbr_meals = -1;
	if ((params->nbr_philos <= 0) || (valid != 3)
		|| (params->nbr_meals <= 0 && argc == 5))
		return (printf("%s", ERR_ATOI), 1);
	return (0);
}

int	ft_bybye_philos(t_philo **philos, int nbr_philo, char *err)
{
	int i;

	i = 0;
	while (i < nbr_philo)
		free((*philos)[i ++].thread);
	free(*philos);
	*philos = NULL;
	if (err)
		printf("%s", err);
	return (1);
}
int	ft_init_philo(t_philo *philos, int i, t_params *params)
{
	philos[i].die_at = 0;
	philos[i].last_meal = 0;
	philos[i].id = i + 1;
	philos[i].nbr_time_eaten = 0;
	philos[i].is_eating = 0;
	philos[i].params = params;
	philos[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!philos[i].thread)
		return (1);
	philos[i].left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(philos[i].left_fork))
		return (free(philos[i].thread), 1);
	pthread_mutex_init(philos[i].left_fork, NULL);
	// TODO fail les mutex init
	if (i > 0)
		philos[i - 1].right_fork = philos[i].left_fork;
	// TODO case 1 philo
	if (i == params->nbr_philos - 1)
		philos[i].right_fork = philos[0].left_fork;
	pthread_mutex_init(&philos[i].lock, NULL);
	// TODO fail les mutex init
	return (0);
}

// void	print_all(t_params *params)
// {
// 	int		i;
// 	uint64_t	time;
	
// 	i = 0;
// 	while (i < params->nbr_philos)
// 	{
// 		printf("die_at %f, last_meal %f, id %d, is_eating %d, nbr_time_eaten %d\n", params->philos[i].die_at, params->philos[i].last_meal, params->philos[i].id, params->philos[i].is_eating, params->philos[i].nbr_time_eaten);
// 		i ++;
// 	}
// 	ft_get_time(&time, params->start);
// 	printf("time : %f\n", time);
// }


int	ft_init_threads(t_params *params)
{
	int	i;

	if (gettimeofday(&params->start, NULL) == -1)
		return (printf("%s", ERR_TIME), 1);
	// print_all(params);
	i = 0;
	while (i < params->nbr_philos)
	{
		if (pthread_create(params->philos[i].thread, NULL, &ft_start_routine, &params->philos[i]))
		// TODO destroy thread create avant le fail
			return (printf("%s", ERR_INIT_THREAD), 1);
		i ++;
	}
	ft_monitor(params);
	i = 0;
	while (i < params->nbr_philos)
	{
		if (pthread_join(*params->philos[i].thread, NULL))
		// TODO destroy thread create après le fail
			return (printf("%s", ERR_DESTROY_THREAD), 1);
		i ++;
	}
	return (0);
}



int	ft_init(t_params *params)
{
	int	i;

	params->finished_philos = 0;
	params->stop = 0;
	if (USLEEP_PACE <= 0 || USLEEP_PACE >= 10000 || (USLEEP_PACE % params->meal_duration) || (USLEEP_PACE % params->sleep_duration))
		params->usleep_pace = 50;	
	else
		params->usleep_pace = USLEEP_PACE;
	params->philos = malloc(sizeof(t_params) * params->nbr_philos);
	if (!params->philos)
		return (printf("%s", ERR_MALLOC), 1);
	i = 0;
	while (i < params->nbr_philos)
	{
		if (ft_init_philo(params->philos, i, params))
			return (ft_bybye_philos(&params->philos, i, ERR_MALLOC));
		i ++;
	}
	if (pthread_mutex_init(&params->write, NULL))
		return (ft_bybye_philos(&params->philos, params->nbr_philos, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&params->finished_philos_mutex, NULL))
		return (1); //TODO
	if (pthread_mutex_init(&params->stop_mutex, NULL))
		return (1); //TODO
	ft_init_threads(params);
	return (0);
}
