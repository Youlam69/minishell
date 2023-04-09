/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:49:54 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 01:00:12 by ylamraou         ###   ########.fr       */
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

void	ft_putstr_3d(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str1)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
	ft_putstr_fd("\n", 2);
}

int	is_dq(char c)
{
	return (c == DQ);
}

int	is_dlr(char c)
{
	return (c == DLR);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int        len;
    int        l;
    int        i;
    char    *str;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    str = (char *)malloc(sizeof(char) * len);
    l = ft_strlen(s1);
    if (!str)
        return (NULL);
    i = -1;
    while (i++ <= l)
        str[i] = s1[i];
    i = 0;
    while (l < len)
        str[l++] = s2[i++];
    str[len] = '\0';
    return (str);
}
