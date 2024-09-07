/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:56:24 by octoross          #+#    #+#             */
/*   Updated: 2024/09/07 22:57:23 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(struct timeval ref)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - ref.tv_sec) * 1000000L + (tv.tv_usec - ref.tv_usec));
}

bool	ft_usleep(unsigned long sleep_duration, t_data *data)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (!ft_the_end(data))
	{
		if (ft_get_time(start) >= sleep_duration)
			return (true);
		usleep(data->usleep_pace);
	}
	return (false);
}
