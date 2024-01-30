/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:32:59 by octoross          #+#    #+#             */
/*   Updated: 2024/01/30 14:16:20 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <ctype.h>

# define ERR_FORMAT_ARGS "Error : Wrong format for arguments\n"
# define ERR_NBR_ARGS "Error : Not enough arguments\n"
# define ERR_MALLOC "Error : malloc failed\n"
# define ERR_ATOI "Error : args is not atoiable :("

typedef struct s_philosophe
{
	pthread_t	*thread;
	int			pidLeft;
	int			pidRight;
	pthread_mutex_t    mutex;
}	t_philosophe;

typedef struct s_philo
{
	t_philosophe	*philosophes;
	int				nbr_philos;
	int				die;
	int				eat;
	int				sleep;
	int				*nbr_eat;
}	t_philo;

size_t  ft_nbr_words(char const *s, char c);

#endif