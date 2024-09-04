/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:31:19 by octoross          #+#    #+#             */
/*   Updated: 2024/09/04 18:15:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_case_one(t_data *data)
{
	uint64_t	time;

	data->stop = 0;
	if (USLEEP_PACE <= 0 || USLEEP_PACE >= 10000
		|| (USLEEP_PACE % data->meal_duration)
		|| (USLEEP_PACE % data->sleep_duration))
		data->usleep_pace = 50;
	else
		data->usleep_pace = USLEEP_PACE;
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (printf("%s", ERR_INIT_MUTEX), 1);
	if (gettimeofday(&data->start, NULL) == -1)
		return (printf("%s", ERR_TIME), 1);
	printf("0 1 %s\n", ACTION_FORK);
	ft_usleep(data->fasting_limit * 1000, data);
	time = ft_get_time(data->start);
	printf("%lu 1 %s\n", (time / 1000), ACTION_DIED);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_parsing(&data, argc - 1, &argv[1]))
		return (1);
	if (ft_init(&data))
		return (1);
	ft_clear_data(&data, -1, 0, NULL);
	return (0);
}
