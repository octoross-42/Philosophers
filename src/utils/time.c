/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:56:24 by octoross          #+#    #+#             */
/*   Updated: 2024/09/02 15:59:42 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_start_time(uint64_t *start)
// {
// 	struct timeval	tv;
	
// 	if (gettimeofday(&tv, NULL) == -1)
// 		return (printf("%s", ERR_TIME), 1);
// 	*utime = tv.tv_sec * 1000000L + tv.tv_usec;
// 	return (0);
// }

uint64_t	ft_get_time(struct timeval ref)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - ref.tv_sec) * 1000000L + (tv.tv_usec - ref.tv_usec));
}

// int	ft_usleep(uint64_t sleep_duration, t_params *params)
// {
// 	struct timeval	start;
// 	uint64_t			timer;

// 	if (sleep_duration <= 0)
// 		return (0);
// 	if (gettimeofday(&start, NULL) == -1)
// 		return (1);
// 	if (ft_get_time(&timer, start))
// 		return (1);
// 	if (sleep_duration - timer > 1000)
// 		usleep((sleep_duration - timer) / 2);
// 	while ((timer < sleep_duration) && !ft_the_end(params))
// 	{
// 		if (ft_get_time(&timer, start))
// 			return (1);
// 		if (sleep_duration - timer > 1000)
// 			usleep((sleep_duration - timer) / 2);
// 	}
// 	return (0);
// }

int		ft_usleep(uint64_t sleep_duration, t_params *params)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (!ft_the_end(params))
	{
		if (ft_get_time(start) >= sleep_duration)
			return (0);
		usleep(params->usleep_pace);
	}
	return (1);
}
