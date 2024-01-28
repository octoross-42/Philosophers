/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:59:50 by octoross          #+#    #+#             */
/*   Updated: 2024/01/28 21:01:52 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
        size_t  len;
        size_t  i;
        char    *concatenated;

        if (!s1 || !s2)
                return (0);
        len = ft_strlen(s1) + ft_strlen(s2);
        concatenated = (char *)malloc(sizeof(char) * (len + 1));
        if (!concatenated)
                return (0);
        concatenated[len] = '\0';
        i = 0;
        while (s1[i])
        {
                concatenated[i] = s1[i];
                i ++;
        }
        len = i;
        while (s2[i - len])
        {
                concatenated[i] = s2[i - len];
                i ++;
        }
        return (concatenated);
}

char    **free_until(char **tab, size_t index)
{
        size_t  i;

        i = 0;
        while (i < index)
                free(tab[i++]);
        free(tab);
        return (0);
}

size_t  ft_nbr_words(char const *s, char c)
{
        size_t  nbr_words;
        size_t  i;

        nbr_words = 0;
        i = 0;
        while (s[i] && s[i] == c)
                i ++;
        while (s[i])
        {
                nbr_words ++;
                while (s[i] && s[i] != c)
                        i ++;
                while (s[i] && s[i] == c)
                        i ++;
        }
        return (nbr_words);
}

char    *ft_next_word(const char *s, size_t *i, char c)
{
        char    *word;
        int             len;

        len = 0;
        while (s[*i + len] && s[*i + len] != c)
                len ++;
        word = (char *)malloc(sizeof(char) * (len + 1));
        if (!word)
                return (0);
        word[len] = '\0';
        len = 0;
        while (s[*i] && s[*i] != c)
                word[len++] = s[(*i)++];
        while (s[*i] && s[*i] == c)
                (*i)++;
        return (word);
}

char    **ft_split(char const *s, char c)
{
        size_t  nbr_words;
        size_t  i;
        char    **splited;

        if (!s)
                return (0);
        nbr_words = ft_nbr_words(s, c);
        splited = (char **)malloc(sizeof(char *) * (nbr_words + 1));
        if (!splited)
                return (0);
        splited[nbr_words] = 0;
        nbr_words = 0;
        i = 0;
        while (s[i] && s[i] == c)
                        i ++;
        while (s[i])
        {
                splited[nbr_words] = ft_next_word(s, &i, c);
                if (!splited[nbr_words])
                        return (free_until(splited, nbr_words));
                nbr_words ++;
        }
        return (splited);
}
