/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:26:42 by octoross          #+#    #+#             */
/*   Updated: 2024/09/07 22:26:39 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		i ++;
	return (s1[i] - s2[i]);
}

unsigned long	ft_atosi(const char *s, int *valid)
{
	int					i;
	unsigned long long	n;

	i = 0;
	n = 0;
	if (s[0] == '+')
		i ++;
	while (s[i] && ('0' <= s[i]) && (s[i] <= '9'))
	{
		n = n * 10 + (s[i ++] - '0');
		if (n * 1000 > ULONG_MAX)
			return (n);
	}
	if (!s[i])
		(*valid)++;
	return (n);
}

int	ft_atopi(const char *s)
{
	int				i;
	unsigned int	n;

	i = 0;
	n = 0;
	if (s[0] == '+')
		i ++;
	while (s[i] && ('0' <= s[i]) && (s[i] <= '9'))
	{
		n = n * 10 + (s[i ++] - '0');
		if (n > INT_MAX)
			return (-1);
	}
	if (!s[i])
		return (n);
	return (-1);
}

unsigned long	ft_pgcd(unsigned long u, unsigned long v)
{
	unsigned long	n;

	if (u < v)
		return (ft_pgcd(v, u));
	while (v != 0)
	{
		n = (u % v);
		u = v;
		v = n;
	}
	return (n);
}
