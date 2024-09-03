/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:31:19 by octoross          #+#    #+#             */
/*   Updated: 2024/09/03 18:37:58 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
