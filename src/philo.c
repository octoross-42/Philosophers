/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:31:19 by octoross          #+#    #+#             */
/*   Updated: 2024/01/28 21:27:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*ft_nbr_eat(char *text, int nbr_philos)
{
	int	i;
	int	*nbr_eat;
	int	words;

	i = 0;
	while (isspace(text[i])) // TODO flemme
		i ++;
	words = ft_nbr_words(text, ' ');
	if (words == 1 && text[0] == ']')
		return (NULL);
	words -= (text[strlen(text) - 2] == ' '); // TODO flemme
	if (words != nbr_philos)
		return (NULL);
	nbr_eat = (int *)malloc(sizeof(int) * nbr_philos);
	if (!nbr_eat)
		return (NULL);
	i = 0;
	while (i < nbr_philos)
	{
		while (isspace(text[i])) // TODO flemme
			i ++;
		while (text[i])
		{
			while (text[i])
			i ++;
		}
		i ++;
	}
}

int	ft_parsing(t_philo *philo, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 6)
		return (printf(ERR_NBR_ARGS), 1);
	philo->nbr_philos = atoi(argv[1]); // TODO flemme
	philo->die = atoi(argv[1]);
	philo->eat = atoi(argv[2]);
	philo->sleep = atoi(argv[3]);
	if (argc > 6)
	{
		if (!((argv[6][0] == '[' && argv[6][strlen(argv[6]) - 1] && argc == 7)
				|| argc - philo->nbr_philos == 5))
			return (printf(ERR_FORMAT_ARGS), 1);
		philo->nbr_eat = (int *)malloc(sizeof(int) * philo->nbr_philos);
		if (!philo->nbr_eat)
			return (printf(ERR_MALLOC));
		if (argv[6][0] == '[')
		{
			philo->nbr_eat = ft_nbr_eat(argv[6][1], philo->nbr_philos);
			if (!philo->nbr_eat)
				return (printf(ERR_FORMAT_ARGS), 1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_parsing(&philo, argc, argv))
		return (1);
	return (0);
}
