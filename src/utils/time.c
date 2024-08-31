/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:56:24 by octoross          #+#    #+#             */
/*   Updated: 2024/08/31 14:16:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_start_time(double *start)
// {
// 	struct timeval	tv;
	
// 	if (gettimeofday(&tv, NULL) == -1)
// 		return (printf("%s", ERR_TIME), 1);
// 	*utime = tv.tv_sec * 1000000L + tv.tv_usec;
// 	return (0);
// }

int	ft_get_time(double *utime, struct timeval ref)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) == -1)
		return (printf("%s", ERR_TIME), 1);
	*utime = (tv.tv_sec - ref.tv_sec) * 1000000L + (tv.tv_usec - ref.tv_usec);
	return (0);
}

int	ft_usleep(double sleep_duration)
{
	struct timeval	start;
	double			timer;

	if (sleep_duration <= 0)
		return (0);
	if (gettimeofday(&start, NULL) == -1)
		return (1);
	if (ft_get_time(&timer, start))
		return (1);
	if (sleep_duration - timer > 1000)
		usleep((sleep_duration - timer) / 2);
	while (timer < sleep_duration)
	{
		if (ft_get_time(&timer, start))
			return (1);
		if (sleep_duration - timer > 1000)
			usleep((sleep_duration - timer) / 2);
	}
	return (0);
}
