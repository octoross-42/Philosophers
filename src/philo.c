/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:31:19 by octoross          #+#    #+#             */
/*   Updated: 2024/08/19 17:14:22 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_bybye(t_params *params)
{
	int	i;
	int	err;

	err = 0;
	free(params->monitor);
	if (pthread_mutex_destroy(&params->write))
		err = 1;
	i = 0;
	while (i < params->nbr_philos)
	{
		if (pthread_mutex_destroy(params->philos[i].left_fork))
			err = 1;
		free(params->philos[i].left_fork);
		free(params->philos[i ++].thread);
	}
	free(params->philos);
	return (err);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (ft_parsing(&params, argc - 1, &argv[1]))
		return (1);
	if (ft_init(&params))
		return (1);
	if (ft_bybye(&params))
		return (printf("%s", ERR_DESTROY), 1);
	return (0);
}
