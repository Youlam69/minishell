/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 01:29:51 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/08 08:03:22 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start + 1)
		len = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	return (str[j] = '\0', str);
}

static int	size_str(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c && *s)
		s++;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static int	size_tab(char const *s, char c)
{
	int	size_2d;

	size_2d = 0;
	while (*s)
	{
		if (*s != c)
		{
			size_2d++;
			while (*s != c && *s)
				s++;
		}
		while (*s == c && *s)
			s++;
	}
	return (size_2d);
}

char	*alloc_str(char **tab, char *s, char c, int i)
{
	int		j;
	char	*str;

	j = 0;
	str = malloc(sizeof(char) * size_str(s, c) + 1);
	if (!str)
	{
		while (i >= 0)
			free(tab[i--]);
		free(tab);
		return (NULL);
	}
	while (*s && *s != c)
		str[j++] = *s++;
	str[j] = '\0';
	tab[i] = str;
	i++;
	return (s);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof (char *) * (size_tab(s, c) + 1));
	if (!tab)
		return (NULL);
	if (!*s)
	{
		tab[0] = s;
		return (tab);
	}
	i = 0;
	while (*s)
	{
		if (*s != c)
			s = alloc_str (tab, s, c, i++);
		if (!*s)
			break ;
		s++;
	}
	tab[i] = NULL;
	return (tab);
}
