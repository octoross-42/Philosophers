/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:11:00 by octoross          #+#    #+#             */
/*   Updated: 2024/09/04 18:15:47 by octoross         ###   ########.fr       */
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

void	ft_attribute_parsing(t_data *data, int argc, char **argv, int *valid)
{
	*valid = 0;
	data->nbr_philos = ft_atopi(argv[0]);
	data->fasting_limit = ft_atosi(argv[1], valid);
	data->meal_duration = ft_atosi(argv[2], valid);
	data->sleep_duration = ft_atosi(argv[3], valid);
	if (argc == 5)
		data->nbr_meals = ft_atopi(argv[4]);
	else
		data->nbr_meals = -1;
}

int	ft_parsing(t_data *data, int argc, char **argv)
{
	int	valid;

	if (argc < 4)
		return (printf("%s", ERR_NE_ARGS), 1);
	else if (argc > 5)
		return (printf("%s", ERR_TM_ARGS), 1);
	if ((!ft_strcmp(argv[0], "-help") || !ft_strcmp(argv[0], "help")
			|| !ft_strcmp(argv[0], "-h")) && HELP)
		return (ft_help(argc, argv), -1);
	ft_attribute_parsing(data, argc, argv, &valid);
	if (data->nbr_philos == 1)
		return (ft_case_one(data), 1);
	if (valid == 3 && ((data->fasting_limit < 10) || (data->meal_duration < 10)
			|| (data->sleep_duration < 10)))
		return (printf("%s", ERR_DURATION), 1);
	if ((data->nbr_philos <= 0) || (valid != 3)
		|| (data->nbr_meals <= 0 && argc == 5))
		return (printf("%s", ERR_ATOI), 1);
	return (0);
}
