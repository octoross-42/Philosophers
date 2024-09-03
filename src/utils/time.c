/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:56:24 by octoross          #+#    #+#             */
/*   Updated: 2024/09/03 18:45:04 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_get_time(struct timeval ref)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - ref.tv_sec) * 1000000L + (tv.tv_usec - ref.tv_usec));
}

int	ft_usleep(uint64_t sleep_duration, t_data *data)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (!ft_the_end(data))
	{
		if (ft_get_time(start) >= sleep_duration)
			return (0);
		usleep(data->usleep_pace);
	}
	return (1);
}
