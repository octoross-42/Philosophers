/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:30:46 by octoross          #+#    #+#             */
/*   Updated: 2024/09/02 18:55:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# define HELP 1
# define USLEEP_PACE 50

# define ERR_NE_ARGS "Error : Not enough arguments\n"
# define ERR_TM_ARGS "Error : Too many arguments\n"
# define ERR_MALLOC "Error : malloc failed\n"
# define ERR_ATOI "Error : args should be strictly positive ints\n"
# define ERR_INIT_THREAD "Error : thread could not initiate\n"
# define ERR_DESTROY_THREAD "Error : thread could not be destroyed\n"
# define ERR_INIT_MUTEX "Error : mutex could not be initiated\n"
# define ERR_DESTROY_MUTEX "Error : mutex could not be destroyed\n"
# define ERR_TIME "Error : time could not be fetched: gettimeofday failed\n"

# define HELP_ARGS "Arguments should be 4 or 5 (optional) positive numbers\n"
# define HELP_1 "\tnumber of philosophers\n"
# define HELP_2 "\ttime spent fasting before dying\n"
# define HELP_3 "\tmeal duration\n"
# define HELP_4 "\tsleep duration\n"
# define HELP_5 "\tnumbers of times each philosopher should eat before ending\n"

# define MESSAGE_1 "1rst arg should be :\n"
# define MESSAGE_2 "2nde arg be relatable :\n"
# define MESSAGE_3 "3rd be the most important part (of life) :\n"
# define MESSAGE_4 "4rth be never enough :\n"
# define MESSAGE_5 "5th is as necessary as life (optional):\n"

# define ACTION_FORK "has taken a fork"
# define ACTION_EAT "is eating"
# define ACTION_SLEEP "is sleeping"
# define ACTION_THINK "is thinking"
# define ACTION_DIED "died"

# include <limits.h>
# include <stdint.h>

int	ft_strcmp(const char *s1, const char *s2);
uint64_t	ft_atosi(const char *s, int *valid);
int	ft_atopi(const char *s);

#endif
