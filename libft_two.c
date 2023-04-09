/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:59:11 by ylamraou          #+#    #+#             */
/*   Updated: 2023/04/09 01:09:19 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

int	ft_strlcat(char *dst, char *src, int size)
{
	int	i;
	int	lendst;
	int	lensrc;

	i = 0;
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size < lendst)
		return (size + lensrc);
	while (*src && (lendst + i + 1) < size)
		dst[lendst + i++] = *src++;
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}

void	*ft_calloc(int count, int size)
{
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (0);
	ft_bzero(s, count * size);
	return (s);
}

void	strjoin_help(char *src, int *i, char *tmp)
{
	int	len;

	len = 0;
	while (src && src[len])
	{
		tmp[*i] = src[len];
		len++;
		(*i)++;
	}
	tmp[*i] = '\0';
}

char	*strjoin(char *dst, char *src)
{
	int		i;
	int		ln;
	char	*tmp;

	i = 0;
	ln = ft_strlen(dst) + ft_strlen(src);
	tmp = malloc(sizeof(char) * (ln + 1));
	if (!tmp)
	{
		printf("Error: malloc failed in strjoin\n");
		return (NULL);
	}
	tmp[ln] = '\0';
	if (dst)
	{
		while (dst[i])
		{
			tmp[i] = dst[i];
			i++;
		}
	}
	if (!src)
		return (tmp);
	strjoin_help(src, &i, tmp);
	return (tmp);
}
