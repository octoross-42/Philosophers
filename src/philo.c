/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:31:19 by octoross          #+#    #+#             */
/*   Updated: 2024/01/30 16:34:27 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*ft_nbr_eat(char *text, int nbr_philos)
{
	int	i;
	int	j;
	int	*nbr_eat;
	int	words;
	int	index;

	i = 0;
	while (isspace(text[i])) // TODO flemme
		i ++;
	words = ft_nbr_words(text, ' ');
	if (words == 1 && text[0] == ']')
		return (NULL);
	if (text[1])
		words -= (text[strlen(text) - 2] == ' '); // TODO flemme
	if (words != nbr_philos && words != 1)
		return (NULL);
	nbr_eat = (int *)malloc(sizeof(int) * words);
	if (!nbr_eat)
		return (NULL);
	index = 0;
	i = 0;
	while (isspace(text[i])) // TODO flemme
		i ++;
	while (index < words)
	{
		nbr_eat[index] = 0;
		while (isdigit(text[i]))
			nbr_eat[index] = nbr_eat[index] * 10 + (text[i ++] - '0');
		if (text[i] && text[i] != ']' && !isspace(text[i]))
			return (free(nbr_eat), NULL);
		while (isspace(text[i]))
			i ++;
		index ++;
	}
	if ((text[i] && text[i] != ']') || (text[i] && text[i + 1]))
		return (free(nbr_eat), NULL);
	while (index < nbr_philos)
		nbr_eat[index ++] = nbr_eat[0];
	return (nbr_eat);
}

int	ft_parsing(t_philo *philo, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
		return (printf(ERR_NBR_ARGS), 1);
	philo->nbr_philos = atoi(argv[1]); // TODO flemme
	if (philo->nbr_philos < 1)
		return (printf(ERR_FORMAT_ARGS), 1);
	philo->die = atoi(argv[2]);
	if (philo->die < 1)
		return (printf(ERR_FORMAT_ARGS), 1);
	philo->eat = atoi(argv[3]);
	if (philo->eat < 1)
		return (printf(ERR_FORMAT_ARGS), 1);
	philo->sleep = atoi(argv[4]);
	if (philo->sleep < 1)
		return (printf(ERR_FORMAT_ARGS), 1);
	if (argc > 5)
	{
		if (!(argc == 6 || argc - philo->nbr_philos == 5))
			return (printf(ERR_FORMAT_ARGS), 1);
		philo->nbr_eat = (int *)malloc(sizeof(int) * philo->nbr_philos);
		if (!philo->nbr_eat)
			return (printf(ERR_MALLOC));
		if (argv[5][0] == '[')
			philo->nbr_eat = ft_nbr_eat(&argv[5][1], philo->nbr_philos);
		else
			philo->nbr_eat = ft_nbr_eat(argv[5], philo->nbr_philos);
		if (!philo->nbr_eat)
			return (printf(ERR_FORMAT_ARGS), 1);
		j = 0;
		while (j < philo->nbr_philos)
			printf("eat: %d\n", philo->nbr_eat[j ++]);
	}
	return (0);
}

int	ft_setup_philos(t_philo philo)
{
	int	i;

	i = 0;
	
	while (i < philo.nbr_philos)
	{
		if ()
		i ++;
	}
	int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
}

int	ft_usleep(size_t ms)
{
	// BECAUSE OF INCOMPETENCE
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_parsing(&philo, argc, argv))
		return (1);
	if (ft_setup_philos(philo))
		return (1);
	return (0);
}
